/*
 * ShmFifo.cpp
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *
 *  Created on: 2 Oct 2016
 *      Author: poncos
 */

#include "ccommons/io/ShmFifo.hpp"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

namespace ccommons
{

ShmFifo::ShmFifo(std::string a_shm_name, int a_shm_size, bool keep_shm_file)
{
	shm = new ReadWriteShm(a_shm_name, a_shm_size, keep_shm_file);
	shm->open();

	this->written_messages = 0;
}

void ShmFifo::write(const char* message, int length)
{
	shm_fifo_message struct_message;
	std::memcpy(struct_message.content, message, length);
	struct_message.value_length = length;
	struct_message.status = 0;

	//std::lock_guard<std::mutex> lock_guard(write_mutex);
	this->written_messages++;
	struct_message.message_number = this->written_messages;

	this->shm->write(reinterpret_cast<const char*>(&struct_message), SIZE_MESSAGE);
}

shm_fifo_message& ShmFifo::read()
{
	shm_fifo_message* struct_message = new shm_fifo_message();

	//std::lock_guard<std::mutex> lock_guard(read_mutex);
	this->shm->read(reinterpret_cast<char*>(struct_message), SIZE_MESSAGE);

	return *struct_message;
}

void ShmFifo::read(shm_fifo_message& buffer)
{
	//std::lock_guard<std::mutex> lock_guard(read_mutex);
	this->shm->read(reinterpret_cast<char*>(&buffer), SIZE_MESSAGE);
}

long ShmFifo::num_messages()
{
	return this->written_messages;
}

ShmFifo::~ShmFifo()
{
	delete(shm);
}

} /* namespace ccommons */
