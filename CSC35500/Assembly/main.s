	section .text ; code
    extern printax
    extern printNL
	global _start
_start:
    mov     ax,0
myLabel:
    call    printax
    call    printNL

    inc     ax
    cmp     ax, 0xa 
    jl      myLabel 

    ; clean up and go back to Linux
    mov     eax, 1
    mov     ebx, 0
    int     0x80