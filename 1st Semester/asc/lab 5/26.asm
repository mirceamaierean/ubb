bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 1, 4, 2, 3, 8, 4, 9, 5
    l1 equ $ - s
    max db 0
    min db 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
        mov al, [s]
        mov [max], al
        mov al, [s + 1]
        mov [min], al
        mov esi, 0
        calc:
            test esi, 1
            mov al, [s + esi]
            jz even
            jnz odd
            even:
                cmp al, [max]
                jb incr
                mov [max], al
                jmp incr
            odd:
                cmp al, [min]
                ja incr
                mov [min], al
                jmp incr
            incr:
                inc esi
                cmp esi, l1
                jb calc
                
            
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
