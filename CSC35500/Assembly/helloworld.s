	section	.data
hello:	db "Hello, World!", 0xA
	section	.text	; following is code
	global	_start	; this code contains the global symbol _start
_start:
	mov	edx, 14		;length of string
	mov	ecx, hello	;this syscall requires ecx to hold address edx is length
	mov	eax, 4		;eax=4 print string
	mov	ebx,1		;parameter for printing string
	int	0x80
	
	mov 	eax, 1	; tells linux which sys call to use (1=exit)
	mov	ebx, 0	; specifies parameter exit needs
	int 	0x80
