/*
 * Shm.cpp
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *  Created on: 17 Sep 2016
 *      Author: poncos
 */
#include "ccommons/io/Shm.hpp"

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include <iostream>

#include "ccommons/utils/CustomTypes.h"

namespace ccommons
{

int perm = 0600;

ReadOnlyShm::ReadOnlyShm(std::string name, bool keep_shm_file):filename(name),keep_shm_file(keep_shm_file)
{
	this->shmfd = 0;
	this->readoffset = 0;
}

void ReadOnlyShm::open()
{
	if ( (shmfd = shm_open(this->filename.c_str(), O_RDONLY , perm) ) < 1)
	{
		throw ShmException(C_COMMONS_SHM_CREATION_ERROR,strerror(errno));
	}

	int flags = fcntl(shmfd, F_GETFL, 0);
	fcntl(shmfd, F_SETFL, flags | O_NONBLOCK);
}

std::string ReadOnlyShm::read(int length)
{
	char buffer[length+1];
	size_t lr = ::read(shmfd, buffer,length);

	buffer[lr] = '\0';
	std::string content(buffer);

	return content;
}

size_t ReadOnlyShm::read(char* buffer, int length)
{
	size_t lr = ::read(shmfd, buffer,length);

	return lr;
}

void ReadOnlyShm::close(bool remove)
{
	if (shmfd > 0)
	{
		close(shmfd);
	}
}

ReadOnlyShm::~ReadOnlyShm()
{
	if ( !this->keep_shm_file )
	{
		shm_unlink(this->filename.c_str());
	}
}

ReadWriteShm::ReadWriteShm(std::string name,size_t shm_size,bool keep_shm_file) :
		ReadOnlyShm(name,keep_shm_file), shmsize(shm_size)
{
	this->writeoffset = 0;
}

void ReadWriteShm::open()
{
	if ( (shmfd = shm_open(this->filename.c_str(), O_RDWR | O_CREAT, perm) )< 1)
	{
		throw ShmException(C_COMMONS_SHM_CREATION_ERROR,strerror(errno));
	}
}

long ReadWriteShm::write(std::string message)
{
	char buffer[message.length()];
	strcpy(buffer, message.c_str());
	long len = strlen(buffer);

	this->write(buffer, len);
	return 0;
}

long ReadWriteShm::write(const char* message, long length)
{
	// this is to ensure the shm section does not grow beyond the size indicated.
	if ((this->writeoffset + length) <= this->shmsize)
	{
		long written_bytes = ::write(shmfd, message,length);

		this->writeoffset += written_bytes;

		return written_bytes;
	}

	return 0;
}

ReadWriteShm::~ReadWriteShm()
{
	// empty
}

} // END NAMESPACES CCOMMONS
