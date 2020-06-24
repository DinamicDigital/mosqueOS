section .stivalehdr

stivalehdr:
	dq stack.top
	dw 0
	dw 0
	dw 0
	dw 0
	dq 0

section .text

global _start

extern kernel_main

_start:
	call kernel_main

section .bss

stack:
	resb 4096
	.top:
