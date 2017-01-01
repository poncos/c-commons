/*
 * shm_test.cpp
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *  Created on: 29 Sep 2016
 *      Author: poncos
 */


#include "ccommons/io/Shm.hpp"

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct shm_fifo_message
{
	int64_t value_length	= 0;
	int64_t message_number	= 0;
	int64_t offset 			= 0;
	int8_t  status			= 0;
	char content[1024] 		= {0};
};

void stringRWTest();
void binaryRWTest();

int main(int argc, char** argv)
{
	binaryRWTest();

	stringRWTest();

	return 1;
}

void stringRWTest()
{
	ccommons::ReadWriteShm rwShm("/stringRWTest_shm",1024,true);

	rwShm.open();
	rwShm.write("hola esto es un mensaje de mierda");
	rwShm.write("adios esto es otro mensaje de mierda");

	ccommons::ReadWriteShm roShm("/stringRWTest_shm",1024,true);

	roShm.open();
	cout << "Reading..." << endl;
	string readInfo = roShm.read(10);

	cout << "Read info: [" << readInfo << "]" << endl;

	string readInfo2 = roShm.read(1024);

	cout << "Read info: [" << readInfo2 << "]"<< endl;
}

void binaryRWTest()
{
	shm_fifo_message message_struct;
	shm_fifo_message message_struct_to_red;
	ccommons::ReadWriteShm rwShm("/binaryRWTest_shm",(1024*1024),true);

	string message = "This is a message again";

	strcpy(message_struct.content,message.c_str());
	message_struct.message_number = 10;
	message_struct.value_length = message.length();

	size_t message_struct_size = sizeof(shm_fifo_message);
	cout << "Writing message with binary length: " << message_struct_size << endl;

	rwShm.open();
	rwShm.write(reinterpret_cast<const char*>(&message_struct), message_struct_size);

	ccommons::ReadWriteShm roShm("/binaryRWTest_shm",(1024*1024),true);

	roShm.open();


	roShm.read(reinterpret_cast<char*>(&message_struct_to_red), sizeof(shm_fifo_message));

	cout << "Read value: " << message_struct_to_red.message_number << " value length: " <<
			message_struct_to_red.value_length << " value: " << message_struct_to_red.content << endl;


}
