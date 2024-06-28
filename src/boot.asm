bits 32							; nasm directive

; multiboot spec
section .multiboot
align 4
	dd 0x1BADB002				; magic
	dd 0x00						; flags
	dd - (0x1BADB002 + 0x00)	; checksum. m+f+c should be zero

section .text
global start
extern kmain					; kmain is defined in the kernel c file

start:
	cli							; block interrupts
	call kmain
	hlt							; halt the CPU
