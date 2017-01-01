/*
 * shmfifo_test.cpp
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *  Created on: 3 Dec 2016
 *      Author: poncos
 */

#include "ccommons/io/ShmFifo.hpp"

#include <iostream>
#include <sys/time.h>

using namespace std;
using namespace ccommons;

int main(int argc, char** argv)
{
	ccommons::ShmFifo shmFifo("/fifotest_shm",(1048000016), true);

	cout << "Size message: " << SIZE_MESSAGE << endl;

	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms1 = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	for (int i=0;i<1000000;i++)
	{
		shmFifo.write("holaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaadios",133);
	}

	gettimeofday(&tp, NULL);
	long int ms2 = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	cout << "Delay: " << (ms2-ms1) << " - messages written: " << shmFifo.num_messages() << endl;
}
