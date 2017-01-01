cmake_minimum_required (VERSION 2.6)
project (c-commons CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

INCLUDE_DIRECTORIES( "/usr/include/" )
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/../main/cpp/include")

message(PROJECT_DIRECTORY "${PROJECT_BINARY_DIR}")

add_library(c-commons SHARED
	${PROJECT_BINARY_DIR}/../main/cpp/src/ccommons/utils/log_utils.cpp
	${PROJECT_BINARY_DIR}/../main/cpp/src/ccommons/io/Shm.cpp 
	${PROJECT_BINARY_DIR}/../main/cpp/src/ccommons/io/ShmFifo.cpp 
	${PROJECT_BINARY_DIR}/../main/cpp/src/ccommons/io/ClientSocket.cpp 
	${PROJECT_BINARY_DIR}/../main/cpp/src/ccommons/io/ServerSocket.cpp
	)