
lgdtq $0
 

movq %rsp, %rax
pushq $1
pushq %rax
pushfq
pushq $1
pushq $1f
iretq

1:
        movw $1, %ax
        movw %ax, %ds
        movw %ax, %es
        movw %ax, %fs
        movw %ax, %gs
