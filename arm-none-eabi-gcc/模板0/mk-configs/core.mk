#######################################
# 核心支持
#######################################
CPU       = cortex-m7          # cpu
FPU       = fpv5-d16           # fpu
FLOAT_ABI = hard               # float-abi
TOOLCHAIN = thumb              # 指令集

# 编译选项
CFLAGS_CORE  = -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FLOAT_ABI) -m$(TOOLCHAIN)
ASFLAGS_CORE = -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FLOAT_ABI) -m$(TOOLCHAIN)
LKFLAGS_CORE = -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FLOAT_ABI) -m$(TOOLCHAIN)
