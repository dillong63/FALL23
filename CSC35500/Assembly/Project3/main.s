        section .data
    prompta: db 'Enter the the first positive integer: '
    buffera:  resb 64
    promptb: db 'Enter the the Second positive integer: '
    bufferb:  resb 64
    section .text 
    extern   printax
    global  _start
_start:
    ; prompt use for frist number
    mov     rax, 4
    mov     rbx, 1
    mov     rcx, prompta
    mov     rdx, buffera-prompta
    int     0x80

    ; read number
    mov     rax, 3
    mov     rbx, 0
    mov     rcx, buffera
    mov     rdx, 20
    int     0x80
    
    mov     rax, 0
    mov     rdx, 10
    mov     rcx, 0
    mov     rbx, 0
convertNr:
    mov     bl, byte[buffera+rcx]
    cmp     bl, 10
    je      label1
    mov     rdx, 10
    mul     rdx
    sub     rbx,0x30
    add     rax, rbx
    inc     rcx
    jmp     convertNr

label1:
    mov     [buffera], rax 
    ;prompt user for second number

    mov     rax, 4
    mov     rbx, 1
    mov     rcx, promptb
    mov     rdx, bufferb-promptb
    int     0x80

    ; read number
    mov     rax, 3
    mov     rbx, 0
    mov     rcx, bufferb
    mov     rdx, 20
    int     0x80


    mov     rax, 0
    mov     rdx, 10
    mov     rcx, 0
    mov     rbx, 0
convertNr1:
    mov     bl, byte[bufferb+rcx]
    cmp     bl, 10
    je      label2
    mov     rdx, 10
    mul     rdx
    sub     rbx,0x30
    add     rax, rbx
    inc     rcx
    jmp     convertNr1
label2:
    ;; gcd code
    mov     [bufferb], rax 
    mov     rax, 0
    mov     rbx, 0
    mov     rax, [buffera]
    mov     rbx, [bufferb]
topLoop:
    ; recursion base case
    cmp     rbx, 0
    je      printanswer

    ; if a is less than b
    cmp     rax,rbx
    jle     switcher

    ;if b less equal to a
    cmp     rax,rbx
    jge     modulus

modulus:
    mov     rdx, 0 ;intialize edx

    div     rbx
    mov     rax, rbx
    mov     rbx, rdx ; mov the remainder into ebx
    jmp     topLoop ; return
    
; below swaps elements
switcher:
    mov     rcx, rax
    mov     rax, rbx
    mov     rbx, rcx
    jmp     topLoop ;return
    
printanswer:
    call    printax

    ; code to give linux control to exit
    mov     rax, 1
    mov     rbx, 0
    int     0x80
