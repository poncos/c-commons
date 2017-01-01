/*
 * ServerSocket.cpp
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *  Created on: 23 Jun 2016
 *      Author: poncos
 */
#include "ccommons/io/ServerSocket.hpp"

#include "ccommons/utils/log_utils.h"

#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cstring>

#include <thread>
#include <new>

std::thread* listen_thread;

bool active = false;

ServerSocket::ServerSocket(int portno, string address) throw (ServerException) :
		portno(portno), address(address), sockfd(0)
{
	this->init();
}

ClientSocket* ServerSocket::accept(int timeout) throw (ServerException)
{
	struct sockaddr_in* cli_addr=new sockaddr_in();
	struct timeval timeoutval;
	fd_set rfds;
	int client_sockfd,retval;
	uint clilen;
	bool runaccept = true;

	if (timeout >0)
	{
		//TODO this code will be move to another function "is_descriptor_ready(timeout)"
		timeoutval.tv_sec = timeout;
		timeoutval.tv_usec=0;

		FD_ZERO(&rfds);
		FD_SET(sockfd, &rfds);
		FD_SET(STDIN_FILENO, &rfds);

		retval = select(sockfd+1, &rfds, NULL, NULL, &timeoutval);

		if (retval < 0)
		{
			log(LogLevel::ERROR, strerror(errno));

			throw ServerException(SS_SERVER_ERROR,strerror(errno));
		}
		else if (!retval)
		{
			//descriptor not available after timeout
			//cerr << "data not available" << endl;
			runaccept = false;
		}

	}

	if (runaccept)
	{
		client_sockfd = ::accept(sockfd, (struct sockaddr *) cli_addr, &clilen);

		ClientSocket* clientSocket = new ClientSocket(client_sockfd, *cli_addr);

		return clientSocket;
	}

	return NULL;
}

void ServerSocket::start(std::function<void(ClientSocket&)> callback_fcn)
	throw (ServerException)
{
	active = true;
	this->listen();
	listen_thread = new std::thread(&ServerSocket::async_accept, this, callback_fcn);
}

void ServerSocket::stop()
{
	active=false;
	listen_thread->join();
	this->close();
}

void ServerSocket::close()
{
	if (::close(sockfd) < 0 )
	{
		//cerr << "PROBLEM close: " << strerror(errno) << endl;
		log(LogLevel::ERROR, strerror(errno));
	}
}

void ServerSocket::init() throw (ServerException)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd<0)
	{
		throw ServerException(SS_SERVER_ERROR,strerror(errno));
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	int optvalue = 1;
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR, &optvalue,sizeof(int)) < 0)
	{
		//cerr << "PROBLEM socket: " << strerror(errno) << endl;
		log(LogLevel::ERROR, strerror(errno));
	}
}

void ServerSocket::listen() throw (ServerException)
{
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		// TODO exception
		//cerr << "PROBLEM bind: " << strerror(errno) << endl;
		throw ServerException(SS_SERVER_ERROR,strerror(errno));
	}

	::listen(sockfd,5);
}

void ServerSocket::async_accept(std::function<void(ClientSocket&)> f_callback)
{
	//std::cout << "async_listen" << std::endl;

	while(active)
	{
		try
		{
			ClientSocket* clientsock = this->accept(5);
			if (clientsock != NULL)
			{
				f_callback(*clientsock);
			}
		}
		catch(int e)
		{
			//nothing here
		}
	}

//	std::cout << "async_thread finishing" << endl;
}






