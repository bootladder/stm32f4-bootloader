cmake_minimum_required(VERSION 3.0)
project(stm32f4-bootloader)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(./src/hal)

add_executable(stm32f4-bootloader
        src/main.c
        src/commandlineprotocol.c
        src/printing_help.c

        src/target/led.c
        src/target/usart.c

        src/hal/stm32f4xx_gpio.c
        src/hal/stm32f4xx_rcc.c
        src/hal/stm32f4xx_usart.c
        src/hal/stm32f4xx_flash.c
        src/hal/startup_stm32f4xx.s.o
        src/hal/system_stm32f4xx.c
        )


#######################################
# FLAGS
#######################################
set(COMMON_FLAGS " ")
string(APPEND COMMON_FLAGS "  -g  -O0                 ")
#string(APPEND COMMON_FLAGS " -Wall   -Wextra  -Wconversion                 ")

set(CMAKE_C_FLAGS "  -std=c99                      ")
set(CMAKE_CXX_FLAGS "  -std=c++14                      ")
string(APPEND CMAKE_C_FLAGS ${COMMON_FLAGS})
string(APPEND CMAKE_CXX_FLAGS ${COMMON_FLAGS})

set(TARGET_LINK_FLAGS "")
string(APPEND TARGET_LINK_FLAGS " -Wl,-Map=output.map  ")

set(TARGET_SPECIFIC_FLAGS " ")
string(APPEND TARGET_SPECIFIC_FLAGS "  -mcpu=cortex-m4 -mthumb  -DARM_MATH_CM4 ")
string(APPEND TARGET_SPECIFIC_FLAGS " -D'__FPU_PRESENT=1' -mfloat-abi=hard -mfpu=fpv4-sp-d16 ")
#string(APPEND TARGET_SPECIFIC_FLAGS " --no-exceptions -nostartfiles")
string(APPEND TARGET_SPECIFIC_FLAGS " --no-exceptions ")

string(APPEND CMAKE_C_FLAGS ${TARGET_SPECIFIC_FLAGS})
string(APPEND CMAKE_CXX_FLAGS ${TARGET_SPECIFIC_FLAGS})

# Avoid known bug in linux giving:
#    arm-none-eabi-gcc: error: unrecognized command line option '-rdynamic'
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

SET(PATH_TO_LINKERSCRIPT "../src/hal/stm32f407.ld")
string(APPEND TARGET_LINK_FLAGS " -specs=nosys.specs -specs=nano.specs ")
string(APPEND TARGET_LINK_FLAGS " -T${PATH_TO_LINKERSCRIPT}  ")


set_target_properties(stm32f4-bootloader PROPERTIES LINK_FLAGS ${TARGET_LINK_FLAGS} )

##################################
# TOOLCHAIN
#################################

set(TOOLCHAIN_PATH "/usr/bin")

set(CMAKE_C_COMPILER   "${TOOLCHAIN_PATH}/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/arm-none-eabi-g++")
set(OBJCOPY            "${TOOLCHAIN_PATH}/arm-none-eabi-objcopy")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}/arm-none-eabi-as")
set(CMAKE_AR           "${TOOLCHAIN_PATH}/arm-none-eabi-ar")
