/*
 * ShmFifo.h
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *  Created on: 2 Oct 2016
 *      Author: poncos
 */

#ifndef MAIN_CPP_INCLUDE_CCOMMONS_IO_SHMFIFO_HPP_
#define MAIN_CPP_INCLUDE_CCOMMONS_IO_SHMFIFO_HPP_

#include "ccommons/io/Shm.hpp"

#include <string>
#include <mutex>

namespace ccommons
{

#define MESSAGE_CONTENT_SIZE 1024


struct shm_fifo_message
{
	int64_t value_length	= 0;
	int64_t message_number	= 0;
	int8_t  status			= 0;
	char 	content[MESSAGE_CONTENT_SIZE] = {0};
};

#define SIZE_MESSAGE sizeof(shm_fifo_message)

class ShmFifo
{
private:
	std::mutex write_mutex;
	std::mutex read_mutex;
	long written_messages;

public:
	ShmFifo(std::string a_shm_name, int a_shm_size, bool keep_shm_file = false);

	void write(const char* message, int length);
	long num_messages();
	shm_fifo_message& read();
	void read(shm_fifo_message& buffer);

	virtual ~ShmFifo();

protected:
	ReadWriteShm* shm;
};

} /* namespace ccommons */

#endif /* MAIN_CPP_INCLUDE_CCOMMONS_IO_SHMFIFO_HPP_ */
