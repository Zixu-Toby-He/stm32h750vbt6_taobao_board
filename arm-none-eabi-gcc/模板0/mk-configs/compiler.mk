#######################################
# 编译器选项
#######################################
GCC_PATH := /usr/bin
PREFIX = arm-none-eabi-

# gcc 编译器 bin 目录既可以通过 make GCC_PATH=xxx 环境变量指定
# 也可以通过环境变量指定
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
AR = $(GCC_PATH)/$(PREFIX)ar   # 添加 ar 命令，用于创建静态库
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
AR = $(PREFIX)ar   # 添加 ar 命令，用于创建静态库
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

