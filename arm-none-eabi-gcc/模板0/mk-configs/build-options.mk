######################################
# 编译选项
######################################
####################
##### 选项配置 #####
####################
# 调试
DEBUG = 0

# 编译优化选项（默认 O0）
OPT = Og

# 链接优化选项（暂时没用）

# 使用精简 C 库
SPECS = nano

######################
##### 无配置选项 #####
######################
# 警告（全警告）
WARN = -Wall

# 数据与函数分段优化（配合 --gc-sections）
FUNCTION_SECTION := -ffunction-sections
DATA_SECTION     := -fdata-sections
LINK_SECTION     := --gc-sections

# 编译信息生成
## 生成 .d 文件
MAKE_DOT_D    := -MMD
## 生成头文件伪目标规则
HEAD_PH_TGT   := -MP

# 传给底层汇编器
#     -a：生成汇编列表
#     -ad：包含调试指令
#     -alms：列表内容控制（包含机器码、宏展开、符号表）
#WA := -a,-ad,-alms
WA_LIST := -a,-ad

# 需要链接的库
#     libc.a：标准 c 库
#     libm.a：数学库
#     libnosys.a：nosys 库（空系统调用）
LIBS := -lc -lm -lnosys

# 底层连接器选项
WL_CROSS_REF := --cref

########################
##### 选项配置翻译 #####
########################
# debug
ifeq ($(DEBUG), 1)
DEBUG_CFLAGS = -g -gdwarf-2
else
DEBUG_CFLAGS =
endif

# 优化
ifeq ($(OPT), Og)
OPT_CFLAG  = -Og
OPT_ASFLAG = -Og
else ifeq ($(OPT), O1)
OPT_CFLAG  = -O1
OPT_ASFLAG = -O1
else ifeq ($(OPT), O2)
OPT_CFLAG  = -O2
OPT_ASFLAG = -O2
else ifeq ($(OPT), O3)
OPT_CFLAG  = -O3
OPT_ASFLAG = -O3
else ifeq ($(OPT), Os)
OPT_CFLAG  = -Os
OPT_ASFLAG = -Os
else ifeq ($(OPT), Ofast)
OPT_CFLAG  = -Ofast
OPT_ASFLAG = -Ofast
else
OPT_CFLAG  = -O0
OPT_ASFLAG = -O0
endif

# 链接库规格
ifeq ($(SPECS), nano)
SPECS_LKFLAG = -specs=nano.specs
else ifeq ($(SPECS), nosys)
SPECS_LKFLAG = -specs=nosys.specs
else ifeq ($(SPECS), rdimon)
SPECS_LKFLAG = -specs=rdimon.specs
else ifeq ($(SPECS), newlib)
SPECS_LKFLAG = 
else 
SPECS_LKFLAG = 
endif

# 编译选项
CFLAGS_BUILD  := $(DEBUG_CFLAGS) $(OPT_CFLAG)  $(WARN) $(FUNCTION_SECTION) $(DATA_SECTION) $(MAKE_DOT_D) $(HEAD_PH_TGT)
ASFLAGS_BUILD := $(DEBUG_CFLAGS) $(OPT_ASFLAG) $(WARN) $(FUNCTION_SECTION) $(DATA_SECTION) $(MAKE_DOT_D) $(HEAD_PH_TGT)
LKFLAGS_BUILD := $(SPECS_LKFLAG) -Wl,$(WL_CROSS_REF),$(LINK_SECTION) $(LIBS) 

