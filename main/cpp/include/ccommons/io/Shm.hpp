/*
 * Shm.hpp
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *  Created on: 11 Jul 2016
 *      Author: poncos
 */

#ifndef MAIN_CPP_INCLUDE_CCOMMONS_IO_SHM_HPP_
#define MAIN_CPP_INCLUDE_CCOMMONS_IO_SHM_HPP_

#include "ccommons/utils/CustomTypes.h"

#include <exception>
#include <string>

namespace ccommons
{

	enum ShmExceptionType
	{
		C_COMMONS_SHM_CREATION_ERROR = 1,
	};

	struct ShmException : public std::exception
	{
		std::string message;
		ShmExceptionType id;

		ShmException (ShmExceptionType id, std::string message) noexcept : exception()
		{
			this->id = id;
			this->message = message;
		}

		const char* what() const noexcept {return message.c_str();}

	};

	class ReadOnlyShm
	{
	protected:
		int shmfd;
		std::string filename;
	private:
		size_t readoffset;
		bool keep_shm_file;
	public:
		ReadOnlyShm(std::string name, bool keep_shm_file=false);
		void open();
		std::string read(int length);
		size_t read(char* buffer, int length);
		void close(bool remove);

		virtual ~ReadOnlyShm();
	};

	class ReadWriteShm : public ReadOnlyShm
	{
	private:
		size_t writeoffset;
		size_t shmsize;

	public:
		ReadWriteShm(std::string name,size_t shm_size, bool keep_shm_file=false);
		void open();
		long write(std::string message);
		long write(const char* message, long length);
		virtual ~ReadWriteShm();
	};
};

#endif /* MAIN_CPP_INCLUDE_CCOMMONS_IO_SHM_HPP_ */
