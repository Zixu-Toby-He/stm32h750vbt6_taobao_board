######################################
# target
######################################
TARGET = target

# .mk文件路径
MK_CONFIG_PATH := $(shell pwd)/mk-configs

-include $(MK_CONFIG_PATH)/info-print.mk

-include $(MK_CONFIG_PATH)/paths.mk
-include $(MK_CONFIG_PATH)/build-options.mk
-include $(MK_CONFIG_PATH)/core.mk
-include $(MK_CONFIG_PATH)/compiler.mk
-include $(MK_CONFIG_PATH)/macros.mk

# 暂时
INCLUDE_FLAGS = \
	$(CORE_HAL_INCLUDE_FLAG)                 \
	$(AlterLib_INCLUDE_FLAG)                 \
	$(CentralDevicesOnChip_INCLUDE_FLAG)     \
	$(CentralDevicesOnBoard_INCLUDE_FLAG)    \
	$(BOARD_SUPPORT_INCLUDE_FLAG)            \
	$(CHIP_SUPPORT_INCLUDE_FLAG)             \
	$(UTILS_INCLUDE_FLAG)                    \
	$(MAIN_INCLUDE_FLAG)


CFLAGS  = $(CFLAGS_CORE)  $(C_DEFS_FLAGS) $(INCLUDE_FLAGS) $(CFLAGS_BUILD) -Wa,$(WA_LIST)
ASFLAGS = $(ASFLAGS_CORE) $(AS_DEFS_FLAGS) $(ASFLAGS_BUILD)
LDFLAGS = $(LKFLAGS_CORE) $(LKFLAGS_BUILD) -T$(LD_FILE_PATH)

####################
##### 目录创建 #####
####################
$(BUILD_PATH):
	@echo  -e $(CMDCOLOR_GREEN)"创建编译目录"$(CMDCOLOR_NONE)
	@mkdir -p $@
	@mkdir -p $(BUILD_PATH)/core_hal
	@mkdir -p $(BUILD_PATH)/AlterLib
	@mkdir -p $(BUILD_PATH)/CentralDevicesOnChip
	@mkdir -p $(BUILD_PATH)/CentralDevicesOnBoard
	@mkdir -p $(BUILD_PATH)/bsp
	@mkdir -p $(BUILD_PATH)/csp
	@mkdir -p $(BUILD_PATH)/utils
	@mkdir -p $(BUILD_PATH)/main
	@echo  -e $(CMDCOLOR_GREEN)"编译目录已创建"$(CMDCOLOR_NONE)

$(RESULT_PATH):
	@echo  -e $(CMDCOLOR_GREEN)"创建结果目录"$(CMDCOLOR_NONE)
	@mkdir -p $@
	@echo  -e $(CMDCOLOR_GREEN)"结果目录已创建"$(CMDCOLOR_NONE)


CORE_HAL_OBJ              := $(CORE_HAL_OBJ_PATH)
AlterLib_OBJ              := $(AlterLib_OBJ_PATH)
CentralDevicesOnChip_OBJ  := $(CentralDevicesOnChip_OBJ_PATH)
CentralDevicesOnBoard_OBJ := $(CentralDevicesOnBoard_OBJ_PATH)
BOARD_SUPPORT_OBJ         := $(BOARD_SUPPORT_OBJ_PATH)
CHIP_SUPPORT_OBJ          := $(CHIP_SUPPORT_OBJ_PATH)
UTILS_OBJ                 := $(UTILS_OBJ_PATH)
MAIN_OBJ                  := $(MAIN_OBJ_PATH)

#######################################
# 目标文件编译
#######################################

# core_hal 将.c文件编译成.o文件
## 指定依赖文件名
$(BUILD_PATH)/core_hal/%.o: COMPILE_MSG   = -MF"$(@:%.o=%.d)"
## -alms：列表内容指定控制（包含机器码、宏展开、符号表）
$(BUILD_PATH)/core_hal/%.o: WA_ALM_C        = -alms=$(BUILD_PATH)/core_hal/$(notdir $(<:.c=.lst))
$(BUILD_PATH)/core_hal/%.o: WA_ALM_S        = -alms=$(BUILD_PATH)/core_hal/$(notdir $(<:.s=.lst))
## 实际编译
$(BUILD_PATH)/core_hal/%.o: %.c | $(BUILD_PATH)
	@echo -e $(CMDCOLOR_BLUE)"当前编译项"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@$(CC) -c $(CFLAGS) $(COMPILE_MSG) -Wa,$(WA_ALM_C) $< -o $@
	@echo -e $(CMDCOLOR_GREEN)"编译完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@echo

$(BUILD_PATH)/core_hal/%.o: %.s | $(BUILD_PATH)
	@echo -e $(CMDCOLOR_BLUE)"当前编译项"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@$(AS) -c $(ASFLAGS) $(COMPILE_MSG) -Wa,$(WA_ALM_S) $< -o $@
	@echo -e $(CMDCOLOR_GREEN)"编译完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@echo

# AlterLib .o文件
## 指定依赖文件名
$(BUILD_PATH)/AlterLib/%.o: COMPILE_MSG   = -MF"$(@:%.o=%.d)"
## -alms：列表内容指定控制（包含机器码、宏展开、符号表）
$(BUILD_PATH)/AlterLib/%.o: WA_ALM        = -alms=$(BUILD_PATH)/AlterLib/$(notdir $(<:.c=.lst))
$(BUILD_PATH)/AlterLib/%.o: %.c | $(BUILD_PATH)
	@echo -e $(CMDCOLOR_BLUE)"当前编译项"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@$(CC) -c $(CFLAGS) $(COMPILE_MSG) -Wa,$(WA_ALM) $< -o $@
	@echo -e $(CMDCOLOR_GREEN)"编译完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@echo

# CentralDevicesOnChip .o文件
## 指定依赖文件名
$(BUILD_PATH)/CentralDevicesOnChip/%.o: COMPILE_MSG   = -MF"$(@:%.o=%.d)"
## -alms：列表内容指定控制（包含机器码、宏展开、符号表）
$(BUILD_PATH)/CentralDevicesOnChip/%.o: WA_ALM        = -alms=$(BUILD_PATH)/CentralDevicesOnChip/$(notdir $(<:.c=.lst))
$(BUILD_PATH)/CentralDevicesOnChip/%.o: %.c | $(BUILD_PATH)
	@echo -e $(CMDCOLOR_BLUE)"当前编译项"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@$(CC) -c $(CFLAGS) $(COMPILE_MSG) -Wa,$(WA_ALM) $< -o $@
	@echo -e $(CMDCOLOR_GREEN)"编译完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@echo

# CentralDevicesOnBoard .o文件
## 指定依赖文件名
$(BUILD_PATH)/CentralDevicesOnBoard/%.o: COMPILE_MSG   = -MF"$(@:%.o=%.d)"
## -alms：列表内容指定控制（包含机器码、宏展开、符号表）
$(BUILD_PATH)/CentralDevicesOnBoard/%.o: WA_ALM        = -alms=$(BUILD_PATH)/CentralDevicesOnBoard/$(notdir $(<:.c=.lst))
$(BUILD_PATH)/CentralDevicesOnBoard/%.o: %.c | $(BUILD_PATH)
	@echo -e $(CMDCOLOR_BLUE)"当前编译项"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@$(CC) -c $(CFLAGS) $(COMPILE_MSG) -Wa,$(WA_ALM) $< -o $@
	@echo -e $(CMDCOLOR_GREEN)"编译完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@echo

# bsp .o文件
## 指定依赖文件名
$(BUILD_PATH)/bsp/%.o: COMPILE_MSG   = -MF"$(@:%.o=%.d)"
## -alms：列表内容指定控制（包含机器码、宏展开、符号表）
$(BUILD_PATH)/bsp/%.o: WA_ALM        = -alms=$(BUILD_PATH)/bsp/$(notdir $(<:.c=.lst))
$(BUILD_PATH)/bsp/%.o: %.c | $(BUILD_PATH)
	@echo -e $(CMDCOLOR_BLUE)"当前编译项"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@$(CC) -c $(CFLAGS) $(COMPILE_MSG) -Wa,$(WA_ALM) $< -o $@
	@echo -e $(CMDCOLOR_GREEN)"编译完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@echo

# csp .o文件
## 指定依赖文件名
$(BUILD_PATH)/csp/%.o: COMPILE_MSG   = -MF"$(@:%.o=%.d)"
## -alms：列表内容指定控制（包含机器码、宏展开、符号表）
$(BUILD_PATH)/csp/%.o: WA_ALM        = -alms=$(BUILD_PATH)/csp/$(notdir $(<:.c=.lst))
$(BUILD_PATH)/csp/%.o: %.c | $(BUILD_PATH)
	@echo -e $(CMDCOLOR_BLUE)"当前编译项"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@$(CC) -c $(CFLAGS) $(COMPILE_MSG) -Wa,$(WA_ALM) $< -o $@
	@echo -e $(CMDCOLOR_GREEN)"编译完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@echo

# util .o文件
## 指定依赖文件名
$(BUILD_PATH)/utils/%.o: COMPILE_MSG   = -MF"$(@:%.o=%.d)"
## -alms：列表内容指定控制（包含机器码、宏展开、符号表）
$(BUILD_PATH)/utils/%.o: WA_ALM        = -alms=$(BUILD_PATH)/utils/$(notdir $(<:.c=.lst))
$(BUILD_PATH)/utils/%.o: %.c | $(BUILD_PATH)
	@echo -e $(CMDCOLOR_BLUE)"当前编译项"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@$(CC) -c $(CFLAGS) $(COMPILE_MSG) -Wa,$(WA_ALM) $< -o $@
	@echo -e $(CMDCOLOR_GREEN)"编译完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@echo

# main .o文件
## 指定依赖文件名
$(BUILD_PATH)/main/%.o: COMPILE_MSG   = -MF"$(@:%.o=%.d)"
## -alms：列表内容指定控制（包含机器码、宏展开、符号表）
$(BUILD_PATH)/main/%.o: WA_ALM        = -alms=$(BUILD_PATH)/main/$(notdir $(<:.c=.lst))
$(BUILD_PATH)/main/%.o: %.c | $(BUILD_PATH)
	@echo -e $(CMDCOLOR_BLUE)"当前编译项"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@$(CC) -c $(CFLAGS) $(COMPILE_MSG) -Wa,$(WA_ALM) $< -o $@
	@echo -e $(CMDCOLOR_GREEN)"编译完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$<"$(CMDCOLOR_NONE)
	@echo

#######################################
# 静态库编译
#######################################

$(RESULT_PATH)/core_hal.a: $(CORE_HAL_OBJ) | $(RESULT_PATH)
	@echo -e $(CMDCOLOR_BLUE)"生成动态库"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@echo -e $(CMDCOLOR_BLUE)"当前打包项"$(CMDCOLOR_NONE)"："
	@$(foreach path, $(CORE_HAL_OBJ), echo -e "\t"$(CMDCOLOR_LBLUE)"$(path)"$(CMDCOLOR_NONE);)
	@$(AR) rcs $@ $(CORE_HAL_OBJ)
	@echo -e $(CMDCOLOR_GREEN)"动态库生成完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@echo

$(RESULT_PATH)/Board_Support_Package.a: $(BOARD_SUPPORT_OBJ) | $(RESULT_PATH)
	@echo -e $(CMDCOLOR_BLUE)"生成动态库"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@echo -e $(CMDCOLOR_BLUE)"当前打包项"$(CMDCOLOR_NONE)"："
	@$(foreach path, $(BOARD_SUPPORT_OBJ), echo -e "\t"$(CMDCOLOR_LBLUE)"$(path)"$(CMDCOLOR_NONE);)
	@$(AR) rcs $@ $(BOARD_SUPPORT_OBJ)
	@echo -e $(CMDCOLOR_GREEN)"动态库生成完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@echo

$(RESULT_PATH)/Chip_Support_Package.a: $(CHIP_SUPPORT_OBJ) | $(RESULT_PATH)
	@echo -e $(CMDCOLOR_BLUE)"生成动态库"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@echo -e $(CMDCOLOR_BLUE)"当前打包项"$(CMDCOLOR_NONE)"："
	@$(foreach path, $(CHIP_SUPPORT_OBJ), echo -e "\t"$(CMDCOLOR_LBLUE)"$(path)"$(CMDCOLOR_NONE);)
	@$(AR) rcs $@ $(CHIP_SUPPORT_OBJ)
	@echo -e $(CMDCOLOR_GREEN)"动态库生成完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@echo

$(RESULT_PATH)/utils.a: $(UTILS_OBJ) | $(RESULT_PATH)
	@echo -e $(CMDCOLOR_BLUE)"生成动态库"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@echo -e $(CMDCOLOR_BLUE)"当前打包项"$(CMDCOLOR_NONE)"："
	@$(foreach path, $(UTILS_OBJ), echo -e "\t"$(CMDCOLOR_LBLUE)"$(path)"$(CMDCOLOR_NONE);)
	@$(AR) rcs $@ $(UTILS_OBJ)
	@echo -e $(CMDCOLOR_GREEN)"动态库生成完成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@echo

#######################################
# 链接目标
#######################################

# -L：添加库搜索路径
LIB_PATH := $(RESULT_PATH)
# 需要链接的库（顺序敏感！！！）
LIBS     := \
	utils.a \
	Board_Support_Package.a \
	Chip_Support_Package.a \
	core_hal.a

$(RESULT_PATH)/$(TARGET).elf: $(RESULT_PATH)/core_hal.a $(RESULT_PATH)/Board_Support_Package.a $(RESULT_PATH)/Chip_Support_Package.a $(RESULT_PATH)/utils.a $(MAIN_OBJ) $(AlterLib_OBJ) $(CentralDevicesOnChip_OBJ) $(CentralDevicesOnBoard_OBJ)
	@echo -e $(CMDCOLOR_BLUE)"生成执行链接格式目标文件"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@$(CC) $(MAIN_OBJ) $(AlterLib_OBJ) $(CentralDevicesOnChip_OBJ) $(CentralDevicesOnBoard_OBJ) $(LDFLAGS) -Wl,-Map=$(BUILD_PATH)/$(TARGET).map \
		-L$(LIB_PATH) $(foreach lib, $(LIBS), -l:$(lib))               \
		-o $@
	@echo -e $(CMDCOLOR_GREEN)"执行链接格式目标文件已生成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@$(SZ) $@
	@echo

$(RESULT_PATH)/$(TARGET).hex: $(RESULT_PATH)/$(TARGET).elf
	@echo -e $(CMDCOLOR_BLUE)"生成代码镜像目标文件"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@$(HEX) $< $@
	@echo -e $(CMDCOLOR_GREEN)"代码镜像目标文件已生成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@echo

$(RESULT_PATH)/$(TARGET).bin: $(RESULT_PATH)/$(TARGET).elf
	@echo -e $(CMDCOLOR_BLUE)"生成二进制目标文件"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@$(BIN) $< $@
	@echo -e $(CMDCOLOR_GREEN)"二进制目标文件已生成"$(CMDCOLOR_NONE)"："$(CMDCOLOR_LBLUE)"$@"$(CMDCOLOR_NONE)
	@echo


#######################################
# 直接调用目标
#######################################
all: $(RESULT_PATH)/$(TARGET).elf $(RESULT_PATH)/$(TARGET).hex $(RESULT_PATH)/$(TARGET).bin
	@echo "make all 编译完成"

core_hal: $(RESULT_PATH)/core_hal.a
	@echo "make core_hal 编译完成"

bsp: $(RESULT_PATH)/Board_Support_Package.a
	@echo "make bsp 编译完成"

csp: $(RESULT_PATH)/Chip_Support_Package.a
	@echo "make csp 编译完成"

utils: $(RESULT_PATH)/utils.a
	@echo "make utils 编译完成"

main: $(MAIN_OBJ)
	@echo $(MAIN_OBJ)
	@echo "make main 编译完成"

wrap: all
	@echo "make wrap 编译完成"

#######################################
# 清理规则
#######################################

core_hal_clean:
	@echo "Cleaning core_hal"
	@rm -f $(BUILD_PATH)/core_hal/*
	@rm -f $(RESULT_PATH)/core_hal.a

bsp_clean:
	@echo "Cleaning bsp"
	@rm -f $(BUILD_PATH)/bsp/*
	@rm -f $(RESULT_PATH)/Board_Support_Package.a

csp_clean:
	@echo "Cleaning csp"
	@rm -f $(BUILD_PATH)/csp/*
	@rm -f $(RESULT_PATH)/Chip_Support_Package.a

utils_clean:
	@echo "Cleaning utils"
	@rm -f $(BUILD_PATH)/utils/*
	@rm -f $(RESULT_PATH)/utils.a

main_clean:
	@echo "Cleaning main"
	@rm -f $(BUILD_PATH)/main/*

clean: core_hal_clean bsp_clean csp_clean utils_clean
	@echo "Cleaning all"
	@rm -f $(MAIN_OBJ) $(MAIN_OBJECTS:.o=.d) $(MAIN_OBJECTS:.o=.lst)
	@rm -f $(RESULT_PATH)/$(TARGET).*
	@rm -f $(BUILD_PATH)/*.map
	@rm -rf $(BUILD_PATH) $(RESULT_PATH)

#######################################
# 依赖文件包含
#######################################
-include $(wildcard $(BUILD_PATH)/*/*.d)

# 显示信息
info:
	@echo "Project Structure:"
	@echo "  Core HAL sources: $(words $(CORE_HAL_SRC_PATH)) files"
	@echo "  BSP sources:      $(words $(BOARD_SUPPORT_SRC_PATH)) files"
	@echo "  CSP sources:      $(words $(CHIP_SUPPORT_SRC_PATH)) files"
	@echo "  Utils sources:    $(words $(UTILS_SRC_PATH)) files"
	@echo "  Build directory:  $(BUILD_PATH)"
	@echo "  Result directory: $(RESULT_PATH)"


.PHONY: all core_hal bsp csp utils _main wrap clean core_hal_clean bsp_clean csp_clean utils_clean info