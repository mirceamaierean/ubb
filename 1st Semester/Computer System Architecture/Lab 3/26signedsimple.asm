bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start
;(c-d-a)+(b+b)-(c+a) = - d - a + b + b - a = -a - a + b + b - d
; a - byte, b - word, c - double word, d-quad word - Signed representation

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 17
    b dw -40
    c dd 1234
    d dq 483574
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov EAX, 0
        sub AL, [a]
        sub AL, [a]
        cbw
        add AX, [b]
        add AX, [b]
        cwde
        cdq
        sub EAX, [d]
        sbb EDX, [d + 4]
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
