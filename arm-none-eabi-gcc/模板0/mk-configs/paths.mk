#######################################
# 路径
#######################################

# 当前路径
PROJ_PATH      := $(shell pwd)


######################
###### 总体路径 ######
######################

# 重新定义 MK_CONFIG_PATH
MK_CONFIG_PATH  := $(PROJ_PATH)/mk-configs
# 中间文件路径
BUILD_PATH      := $(PROJ_PATH)/build
# 最终文件路径
RESULT_PATH     := $(PROJ_PATH)/result
# 源文件路径
SOURCE_PATH     := $(PROJ_PATH)/src
# 头文件路径
HEAD_PATH       := $(PROJ_PATH)/include
# 链接脚本路径
LD_PATH         := $(PROJ_PATH)/ld_scripts


######################
###### 源码路径 ######
######################
# core_hal .c 源文件路径
CORE_HAL_SRC_PATH     := $(shell find $(SOURCE_PATH)/__CHIP__ $(SOURCE_PATH)/__HALLIB__ -type f -name "*.c")
# core_hal .s 源文件路径
CORE_HAL_ASM_SRC_PATH := $(shell find $(SOURCE_PATH)/__CHIP__ -type f -name "*.s")
# core_hal .h 头文件路径
CORE_HAL_INCLUDE_PATH :=    \
	$(HEAD_PATH)/__CHIP__   \
	$(HEAD_PATH)/__CORTEX__   \
	$(HEAD_PATH)/__HALLIB__ \
	$(HEAD_PATH)/__HALLIB__/Legacy

# AlterLib 源文件
AlterLib_SRC_PATH             := $(shell find $(SOURCE_PATH)/AlterLib -type f -name "*.c")
# AlterLib 头文件
AlterLib_INCLUDE_PATH := $(HEAD_PATH)/AlterLib

# Central Devices On Chip 源文件
CentralDevicesOnChip_SRC_PATH             := $(shell find $(SOURCE_PATH)/CentralDevicesOnChip -type f -name "*.c")
# Central Devices On Chip 头文件
CentralDevicesOnChip_INCLUDE_PATH := $(HEAD_PATH)/CentralDevicesOnChip

# Central Devices On Board 源文件
CentralDevicesOnBoard_SRC_PATH             := $(shell find $(SOURCE_PATH)/CentralDevicesOnBoard -type f -name "*.c")
# Central Devices On Board 头文件
CentralDevicesOnBoard_INCLUDE_PATH := $(HEAD_PATH)/CentralDevicesOnBoard

# Chip Devices 源文件
CHIP_SUPPORT_SRC_PATH     := $(shell find $(SOURCE_PATH)/ChipDevices -type f -name "*.c")
# Chip Devices 头文件
CHIP_SUPPORT_INCLUDE_PATH := $(HEAD_PATH)/ChipDevices

# Board Devices 源文件
BOARD_SUPPORT_SRC_PATH     := $(shell find $(SOURCE_PATH)/BoardDevices -type f -name "*.c")
# Board Devices 头文件
BOARD_SUPPORT_INCLUDE_PATH := $(HEAD_PATH)/BoardDevices

# utils 源文件
UTILS_SRC_PATH     := $(shell find $(SOURCE_PATH)/utils -type f -name "*.c")
# utils 头文件
UTILS_INCLUDE_PATH := $(HEAD_PATH)/utils

# main 源文件
MAIN_SRC_PATH     := $(SOURCE_PATH)/main/main.c
# main 头文件
MAIN_INCLUDE_PATH := $(HEAD_PATH)/main

# ld 脚本
LD_FILE_PATH  := $(LD_PATH)/STM32H750XX_FLASH.ld

######################
###### 目标路径 ######
######################
# core_hal .o 目标文件路径
CORE_HAL_OBJ_PATH = \
	$(addprefix $(BUILD_PATH)/core_hal/,$(notdir $(CORE_HAL_SRC_PATH:.c=.o)))                   \
	$(addprefix $(BUILD_PATH)/core_hal/,$(notdir $(CORE_HAL_ASM_SRC_PATH:.s=.o)))

# AlterLib .o 目标文件路径
AlterLib_OBJ_PATH             = $(addprefix $(BUILD_PATH)/AlterLib/,$(notdir $(AlterLib_SRC_PATH:.c=.o)))

# Central Devices .o 目标文件路径
CentralDevicesOnChip_OBJ_PATH  = $(addprefix $(BUILD_PATH)/CentralDevicesOnChip/,$(notdir $(CentralDevicesOnChip_SRC_PATH:.c=.o)))
CentralDevicesOnBoard_OBJ_PATH = $(addprefix $(BUILD_PATH)/CentralDevicesOnBoard/,$(notdir $(CentralDevicesOnBoard_SRC_PATH:.c=.o)))

# bsp .o 目标文件路径
BOARD_SUPPORT_OBJ_PATH = $(addprefix $(BUILD_PATH)/bsp/,$(notdir $(BOARD_SUPPORT_SRC_PATH:.c=.o)))
# csp .o 目标文件路径
CHIP_SUPPORT_OBJ_PATH  = $(addprefix $(BUILD_PATH)/csp/,$(notdir $(CHIP_SUPPORT_SRC_PATH:.c=.o)))
# utils .o 目标文件路径
UTILS_OBJ_PATH         = \
	$(addprefix $(BUILD_PATH)/utils/,$(notdir $(UTILS_SRC_PATH:.c=.o)))        \
	$(addprefix $(BUILD_PATH)/utils/,$(notdir $(TYPES_SRC_PATH:.c=.o)))

# main
MAIN_OBJ_PATH = $(addprefix $(BUILD_PATH)/main/,$(notdir $(MAIN_SRC_PATH:.c=.o)))

######################
###### 包含命令 ######
######################
CORE_HAL_INCLUDE_FLAG      := $(foreach dir, $(CORE_HAL_INCLUDE_PATH),      -I$(dir))
BOARD_SUPPORT_INCLUDE_FLAG := $(foreach dir, $(BOARD_SUPPORT_INCLUDE_PATH), -I$(dir))
CHIP_SUPPORT_INCLUDE_FLAG  := $(foreach dir, $(CHIP_SUPPORT_INCLUDE_PATH),  -I$(dir))
UTILS_INCLUDE_FLAG         := $(foreach dir, $(UTILS_INCLUDE_PATH),         -I$(dir))
TYPES_INCLUDE_FLAG         := $(foreach dir, $(TYPES_INCLUDE_PATH),         -I$(dir))
MAIN_INCLUDE_FLAG          := $(foreach dir, $(MAIN_INCLUDE_PATH),          -I$(dir))

CORE_HAL_INCLUDE_FLAG                      := $(foreach dir, $(CORE_HAL_INCLUDE_PATH),                      -I$(dir))
AlterLib_INCLUDE_FLAG                      := $(foreach dir, $(AlterLib_INCLUDE_PATH),              -I$(dir))
CentralDevicesOnChip_INCLUDE_FLAG  := $(foreach dir, $(CentralDevicesOnChip_INCLUDE_PATH),  -I$(dir))
CentralDevicesOnBoard_INCLUDE_FLAG := $(foreach dir, $(CentralDevicesOnBoard_INCLUDE_PATH), -I$(dir))
CHIP_SUPPPORT_SUPPORT_INCLUDE_FLAG         := $(foreach dir, $(CHIP_SUPPPORT_SUPPORT_INCLUDE_PATH),           -I$(dir))
BOARD_SUPPORT_INCLUDE_FLAG                 := $(foreach dir, $(BOARD_SUPPORT_INCLUDE_PATH),                 -I$(dir))
UTILS_INCLUDE_FLAG                         := $(foreach dir, $(UTILS_INCLUDE_PATH),                         -I$(dir))
MAIN_INCLUDE_FLAG                          := $(foreach dir, $(MAIN_INCLUDE_PATH),                          -I$(dir))

# 所有 C 源文件（用于 vpath）
C_SOURCES = \
	$(CORE_HAL_SRC_PATH)                 \
	$(AlterLib_SRC_PATH)                 \
	$(CentralDevicesOnChip_SRC_PATH)     \
	$(CentralDevicesOnBoard_SRC_PATH)    \
	$(CHIP_SUPPORT_SRC_PATH)             \
	$(BOARD_SUPPORT_SRC_PATH)            \
	$(UTILS_SRC_PATH)                    \
	$(MAIN_SRC_PATH)

ASM_SOURCES = $(CORE_HAL_ASM_SRC_PATH)

vpath %.c $(sort $(dir $(C_SOURCES)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))