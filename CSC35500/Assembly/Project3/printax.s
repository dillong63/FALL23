

    section .text
    extern printDigit
    global printax
printax:
    push    rax
    push    rbx
    push    rcx
    push    rdx

    cmp     rax, 0
    jge     printPos

printPos:
    mov     rcx, 0
doDigit:
    mov     rbx, 0xa
    mov     rdx, 0   ;setup dicde and do only ax/bx
    div     rbx      ; quotient in ax, remainder in dx
    push    rdx      ;push next digit onto stack
    inc     rcx     ;inc counter
    cmp     rax,0
    jne     doDigit  

nextDigit:
    pop     rax
    call    printDigit
    dec     rcx
    cmp     rcx, 0
    jne     nextDigit

    pop    rdx
    pop    rcx
    pop    rbx
    pop    rax

    ret
