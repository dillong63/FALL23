	section .data
prompt: db 'Enter a string: '
buffer: resb 100			; reserver 100 bytes
	
	
	section .text ; code
	global _start
_start:
	mov	rax,4		;write
	mov	rbx,1		;stdout
	mov	rcx, prompt	;where char statrs
	mov	rdx, buffer-prompt	;16 chars
	int	0x80
	
	mov	rax,3		;read
	mov	rbx, 0		; from stdin
	mov	rcx, buffer	;start storage
	mov	rdx, 100	; no more than 100 chars
	int 	0x80
	
	mov 	rdx,rax		;#chars read
	mov	rax,4		;write
	mov	rbx, 1		;std out
	mov	rcx, buffer	;starting point
	int	0x80
	
	;return to linux
	mov	rax,1
	mov	rbx, 0
	int 	0x80
