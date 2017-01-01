/*
 * ClientSocket.cpp
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *  Created on: 23 Jun 2016
 *      Author: poncos
 */

#include "ccommons/io/ClientSocket.hpp"

#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <arpa/inet.h>

using namespace std;

ClientSocket::ClientSocket(int sockfd, sockaddr_in& sockaddr) : sockfd(sockfd), cli_addr(sockaddr)
{

}

ClientSocket::ClientSocket(int dstport, string dstaddress)
{
	this->init(dstport, dstaddress);
}

void ClientSocket::connect()
{
	if (::connect(sockfd , (struct sockaddr *)&cli_addr , sizeof(cli_addr)) < 0)
	{
		cerr << "PROBLEM connect: " << strerror(errno) << endl;
	}
}

void ClientSocket::write(const uchar* info, int length)
{
	//std::cout << "write: " << sockfd << ": " << info << ":" << length << std::endl;
	try
	{
		::write(sockfd, info, length);
	}
	catch (int e)
	{
		std::cerr << "error writing: (" << e << ")" << strerror(errno)<< endl;
	}
	//std::cout << "write done" << std::endl;
}

void ClientSocket::read(uchar* buffer, int length)
{
	::read(sockfd, buffer, length);
}

void ClientSocket::close()
{
	if(::close(sockfd) < 0)
	{
		//TODO error handling
		cerr << "PROBLEM close: " << strerror(errno) << endl;
	}
}

ClientSocket::~ClientSocket()
{
	// TODO Auto-generated destructor stub
}

void ClientSocket::init(int portno, string address)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct hostent *he;

	if (sockfd<0)
	{
		// TODO throw Exception
		cerr << "PROBLEM socket: " << strerror(errno) << endl;
	}

	bzero((char *) &cli_addr, sizeof(cli_addr));
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_port = htons(portno);
	cli_addr.sin_addr.s_addr = inet_addr(address.c_str());
}

