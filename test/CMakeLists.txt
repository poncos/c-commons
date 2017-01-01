cmake_minimum_required (VERSION 2.6)
project (c-commons-test CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

INCLUDE_DIRECTORIES( "/usr/include/" )
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/../../main/cpp/include")

message(PROJECT_DIRECTORY "${PROJECT_BINARY_DIR}")

add_executable(c-commons-shm-test cpp/shm/shm_test.cpp ${PROJECT_BINARY_DIR}/../../main/cpp/src/ccommons/io/Shm.cpp)

add_executable(c-commons-fifo-test cpp/shmfifo/shmfifo_test.cpp ${PROJECT_BINARY_DIR}/../../main/cpp/src/ccommons/io/Shm.cpp ${PROJECT_BINARY_DIR}/../../main/cpp/src/ccommons/io/ShmFifo.cpp)

TARGET_LINK_LIBRARIES( c-commons-shm-test rt)
TARGET_LINK_LIBRARIES( c-commons-fifo-test rt)