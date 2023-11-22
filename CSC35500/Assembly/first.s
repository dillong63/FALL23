	section	.text	; following is code
	global	_start	; this code contains the global symbol _start
_start:
	mov	rax, 0x1122334455667788 ; base 16 constant
	mov	ax, 8			; base 10 constant
	mov	ah, 9
	mov	al, 10
	
	mov 	eax, 1	; tells linux which sys call to use (1=exit)
	mov	ebx, 0	; specifies parameter exit needs
	int 	0x80
