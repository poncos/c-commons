## Description

This is a on-going utility library built upon low level C/C++ apis to make easier to external application make use of those APIs, although is not just a wraper, the idea is offer higher level functionalities, like FIFO message queues using shared memory for example.


## Build

The build scripts are prepared to distribute this library as a shared library named "libc-commons.so", to generate it, the commands shown below must be run within the folder "build"

cmake ..

make

## Test code

Within the test folder several classes implemented to test some of the functionalities offered by the library are located, to compile and generate the binaries to execute this test code, the next commands must be run within the folder "test/build"

cmake ..

make

### Test cases execution

Once the commands detailed above finished, two binaries are created "c-commons-fifo-test", "c-commons-shm-test". 
  
