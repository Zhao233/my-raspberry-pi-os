# 任务目标
## 1. 增加printf函数
## 2. 根据boot protocal配置相关寄存器
### 进入内核态前的准备工作
1. 关闭地址翻译和cache
    + MMU = off
    + D-cache = off
    + I-cache = on or off
    + x0 = physical address to the FDT blob
2. 配置EL2，EL3信息

### 相关寄存器配置
SCTLR_EL1
HCR_EL2
SCR_EL3
SPSR_EL3
### 
## 3. 配置完毕后跳转到el1

# linux boot protocal
1. 

# 