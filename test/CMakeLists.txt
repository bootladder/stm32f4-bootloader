cmake_minimum_required(VERSION 3.0)
project(stm32f4-bootloader)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(../src)


add_executable(stm32f4-bootloader-test
        main_unit_test.c
        test_ihexcommandparser.c
        test_bootloader.c
        mockflash.c

        ../src/ihexcommandparser.c
        ../src/bootloader.c
        ../src/hex2int.c
        )

