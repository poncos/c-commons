/*
 * log_utils.c
 *
 * License: MIT
 *
 * (c) Copyright 2016 Esteban Collado Cespon.
 *
 *  Created on: 3 Jul 2016
 *      Author: poncos
 */
#include "ccommons/utils/log_utils.h"

#include <syslog.h>

void openapplog(const char* appname)
{
	openlog(appname, LOG_PID|LOG_CONS, LOG_USER);
}

void closeapplog()
{
	closelog();
}

void log(LogLevel::LOG_LEVEL level, const char* message)
{
	switch(level)
	{
	case LogLevel::ERROR:
		syslog(LOG_ERR | LOG_LOCAL0, "%s", message);
		break;
	case LogLevel::WARNING:
		syslog(LOG_WARNING | LOG_LOCAL1, "%s", message);
		break;
	case LogLevel::INFO:
		syslog(LOG_INFO | LOG_LOCAL2, "%s", message);
		break;
	case LogLevel::DEBUG:
		syslog(LOG_DEBUG | LOG_LOCAL3, "%s", message);
		break;
	default:
		syslog(LOG_INFO | LOG_LOCAL2, "%s", message);
		break;
	}
}




