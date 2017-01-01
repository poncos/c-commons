/*
 * ServerSocket.hpp
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *  Created on: 23 Jun 2016
 *      Author: poncos
 */
#ifndef MAIN_SRC_CPP_UTILS_IO_SERVERSOCKET_HPP_
#define MAIN_SRC_CPP_UTILS_IO_SERVERSOCKET_HPP_

#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <strings.h>
#include <string>
#include <functional>
#include <exception>

#include "ccommons/utils/CustomTypes.h"
#include "ccommons/io/ClientSocket.hpp"

using namespace std;

enum ServerExceptionType
{
	SS_SERVER_ERROR = 1,
	SS_READ_TIMEOUT,
};

struct ServerException : public exception
{
	string message;
	ServerExceptionType id;

	ServerException (ServerExceptionType id, string message) noexcept : exception()
	{
		this->id = id;
		this->message = message;
	}

};

class ServerSocket
{
	private:
		int sockfd, portno;
		string address;
		struct sockaddr_in serv_addr;

		void init() throw (ServerException);
		void listen() throw (ServerException);
		void async_accept(std::function<void(ClientSocket&)> f_callback);

	public:
		ServerSocket(int portno, string address) throw (ServerException);

		ClientSocket* accept(int timeout) throw (ServerException) ;
		void start(std::function<void(ClientSocket&)> callback_fcn)
			throw (ServerException);
		void stop();
		void close();
};

#endif /* MAIN_SRC_CPP_UTILS_IO_SERVERSOCKET_HPP_ */
