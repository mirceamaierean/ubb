bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start


; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 1, 5, 3, 8, 2, 9
    l1 equ $ - s
    d1 times l1 db 0
    d2 times l1 db 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
        mov esi, 0
        mov edi, 0
        calc_even:
            mov al, [s + esi]
            test al, 1
            jnz odd
            mov [d1 + edi], al
            inc edi
            odd:
            inc esi
            cmp esi, l1 ; l1 is a constant, so we do not use [l1]
            jb calc_even
        mov esi, 0
        mov edi, 0
        calc_odd:
            mov al, [s + esi]
            test al, 1
            jz ev
            mov [d2 + edi], al
            inc edi
            ev:
            inc esi
            cmp esi, l1 ; l1 is a constant, so we do not use [l1]
            jb calc_odd
            
        ; ...

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
