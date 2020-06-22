lgdt 0
mov rax, rsp
push 0
push rax
pushf
push 0
push 1
iret

.l1:
mov ax, 0
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
