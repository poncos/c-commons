/*
 * log_utils.h
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *  Created on: 3 Jul 2016
 *      Author: poncos
 */

#ifndef MAIN_SRC_CPP_UTILS_LOG_UTILS_H_
#define MAIN_SRC_CPP_UTILS_LOG_UTILS_H_

namespace LogLevel
{
	enum LOG_LEVEL
	{
		ERROR = 1,
		WARNING,
		INFO,
		DEBUG,
	};
};

void openapplog(const char* appname);
void closeapplog();
void log(LogLevel::LOG_LEVEL level, const char* message);


#endif /* MAIN_SRC_CPP_UTILS_LOG_UTILS_H_ */
