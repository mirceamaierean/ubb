bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
; (a+b)/(2-b*b+b/c)-x; a-doubleword; b,c-byte; x-qword

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 4231
    b db -8
    c db -7
    x dq 213321
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov AL, [b] ; AL -> b
        cbw ; AX -> AL
        cwde ; EAX -> AX
        add EAX, [a]
        push EAX
        mov EAX, 0
        mov AL, [b]
        cbw 
        idiv byte [c]
        cbw
        mov BX, AX
        mov AL, [b]
        imul AL
        sub BX, AX
        mov AX, BX
        add AX, 2
        mov BX, AX
        pop AX
        pop DX
        idiv BX
        cwde
        cdq
        sub EAX, [x]
        sbb EDX, [x + 4]
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
