/**
 * ClientSocket.hpp
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *  Created on: 23 Jun 2016
 *      Author: poncos
 */

#ifndef MAIN_SRC_CPP_UTILS_IO_CLIENTSOCKET_HPP_
#define MAIN_SRC_CPP_UTILS_IO_CLIENTSOCKET_HPP_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <string>

#include "ccommons/utils/CustomTypes.h"

using namespace std;

enum ClientSocketExceptionType
{
	CS_CLIENT_ERROR = 1,
	CS_READ_TIMEOUT,
};

struct ClientSocketException : public exception
{
	string message;
	ClientSocketExceptionType id;

	ClientSocketException (ClientSocketExceptionType id, string message) noexcept : exception()
	{
		this->id = id;
		this->message = message;
	}

};


class ClientSocket
{
private:
	int sockfd;
	struct sockaddr_in cli_addr;

	void init(int portno, string address);

public:
	ClientSocket(int dstport, string dstaddress);
	ClientSocket(int sockfd, sockaddr_in& sockaddr);
	virtual ~ClientSocket();

	void connect();
	void write(const uchar* info, int length);
	void read(uchar* buffer, int length);

	void close();
};

#endif /* MAIN_SRC_CPP_UTILS_IO_CLIENTSOCKET_HPP_ */
