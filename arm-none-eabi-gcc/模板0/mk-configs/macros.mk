#######################################
# 宏定义
#######################################

# 编译宏
C_DEFS := USE_HAL_DRIVER STM32H750xx

AS_DEFS := 


C_DEFS_FLAGS  := $(foreach def, $(C_DEFS),  -D$(def))
AS_DEFS_FLAGS := $(foreach def, $(AS_DEFS), -D$(def))