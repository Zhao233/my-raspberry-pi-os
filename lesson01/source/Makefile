# 执行的taget的顺序
# all -> $(BUILD_DIR)/%_c.o -> $(BUILD_DIR)/%_S.o -> kernel8.img


# 交叉编译工具
ARMGNU ?= aarch64-linux-gnu

# 编译选项（c options）
# Wall : 显示所有的warning
# nostdlib : 不使用任何标准库
# nostartfiles : 不使用标准的启动文件。启动文件负责设置初始化初始栈指针，静态数据，以及跳转到main函数
# ffreestanding : 独立环境，不包含标准库文件，起始位置不一定从main开始。此标志告诉编译器，一些符号不要链接到标准库
# Iinclude : 在include这个文件中搜索头文件
# mgeneral-regs-only : 只使用常规的寄存器，不使用SIMD寄存器
COPS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only

# 编译选项（assembly options）
ASMOPS = -Iinclude

# build路径
BUILD_DIR = build

# 源代码目录
SRC_DIR = src

# qemu 运行选项
QEMU = qemu-system-aarch64
IMAGE = kernel8.img
QEMUOPTS = -m 128 -M raspi3 -cpu cortex-a53 -kernel $(IMAGE)  -nographic \
 -serial null -chardev stdio,id=uart1 -serial chardev:uart1 -monitor none


# 默认的target，prerequisites为kernel8.img，先去寻找依赖的target
all:kernel8.img

# 清除build目录，删除编译完的img文件
clean:
	rm -rf $(BUILD_DIR) *.img

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
# mkdir -p 递归的创建目录（目标中的目录）
	mkdir -p $(@D)

# -MMD 生成文件关联信息，将忽略由 #include<file> 造成的依赖关系，并且输出到.d文件中
# -c 只编译不链接
# -o 指定输出文件名
# $< 第一个目标名字（xxx.c）
# $@ 目标文件集（xxx_c.o）
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)

# c文件修改后缀，改为_c.o作为object
#OBJ_FILES = $(patsubst %.c,%_c.o,$(notdir $(C_FILES)))
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)

# 汇编文件修改后缀，改为_s.o作为objectls
#OBJ_FILES += $(patsubst %.c, %_s.o,$(notdir $(ASM_FILES)))
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

# 修改obj文件的后缀，修改为.d作为依赖文件
DEP_FILES = $(OBJ_FILES:%.o=%.d)

# ？
-include $(DEP_FILES)

kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	$(ARMGNU)-ld -T $< -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img

qemu:
	$(QEMU) $(QEMUOPTS)


qemu-gdb:
	$(QEMU) $(QEMUOPTS) -S


gdb:
	gdb-multiarch -n -x .gdbinit
