            section .data
negSignString   db '-'

    section .text
    extern printDigit
    global printax
printax:
    push    rax
    push    rbx
    push    rcx
    push    rdx

    cmp     ax, 0
    jge     printPos

    ;;neg number print - and negate
    push    rax;

    mov     eax, 4
    mov     ebx, 1
    mov     ecx, negSignString
    mov     edx, 1
    int     0x80

    pop     rax 
    neg     ax
printPos:
    mov     rcx, 0
doDigit:
    mov     bx, 0xa
    mov     dx, 0   ;setup dicde and do only ax/bx
    div     bx      ; quotient in ax, remainder in dx
    push    rdx      ;push next digit onto stack
    inc     rcx     ;inc counter
    cmp     ax,0
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
