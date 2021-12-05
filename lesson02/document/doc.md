# 任务目标
## 1. 增加printf函数
## 2. 根据boot protocal配置相关寄存器
### 进入内核态前的准备工作
1. MMU = off
2. D-cache = off
3. I-cache = on or off
4. x0 = physical address to the FDT blob

### 相关寄存器配置
sctlr_el1
### 
## 3. 配置完毕后跳转到el1

# linux boot protocal
1. 

# 