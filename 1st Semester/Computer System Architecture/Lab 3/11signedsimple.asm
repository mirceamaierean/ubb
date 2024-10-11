bits 32 ; assembling for the 32 bits architecture
; d-(a+b+c)-(a+a)
; a - byte, b - word, c - double word, d - qword - Signed representation

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 8
    b dw -30
    c dd 17
    d dq 10024
    ; ...

; our code starts here
segment code use32 class=code
    start:
        mov EAX, dword [d]
        mov EDX, dword [d + 4]
        sub AL, [a]
        sub AX, [b]
        sub EAX, [c]
        sbb AL, [a]
        sub AL, [a]
        
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
