            section .data
buffer:   db 0xa 

    section .text
    global printDigit
printDigit:
    push    rax
    push    rbx
    push    rcx
    push    rdx

    add     al, 0x30    ; convert al to charachter
    mov     [buffer], al ;store what want to print into buffer


    mov     rax, 4
    mov     rbx, 1
    mov     rcx, buffer
    mov     rdx, 1
    int     0x80

    pop    rdx
    pop    rcx
    pop    rbx
    pop    rax

    ret
