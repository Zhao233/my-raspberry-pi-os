.globl gen_timer_init          
gen_timer_init:                
    mov x0, #1
    msr CNTP_CTL_EL0, x0       
    ret            

.globl gen_timer_reset         
gen_timer_reset:               
    mov x0, #1                 
    lsl x0, x0, #24            
    msr CNTP_TVAL_EL0, x0      
    ret
