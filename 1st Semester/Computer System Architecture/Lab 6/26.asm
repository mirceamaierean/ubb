bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s DD 12345678h, 1A2B3C4Dh, 98FEDC76h
    len equ ($-s)/4
    ten db 10
    d times len db 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov esi, s
        cld
        mov ecx, len
        mov edi, d
        repeta:
            LODSW
            mov BH, AH
            LODSW
            mov AL, BH
            mov AH, 0
            div byte [ten]
            cmp AH, 0
            jnz nonmultiple
            mov AL, BH
            STOSB
            nonmultiple:
            loop repeta
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
