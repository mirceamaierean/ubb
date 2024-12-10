bits 32 ; assembling for the 32 bits architecture

; Given 2 dublucuvinte R and T. Compute the doubleword Q as follows:
; the bits 0-6 of Q are the same as the bits 10-16 of T
; the bits 7-24 of Q are the same as the bits 7-24 of (R XOR T).
; the bits 25-31 of Q are the same as the bits 5-11 of R.
; declare the EntryPoint (a label defining the very first instruction of the program)

global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    r dd 0101110111010111010011101b
    t dd 0111010011110111110000010b
    q dd 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
        mov eax, [t]
        mov cl, 10
        shr eax, cl
        mov ecx, 1111111b
        and eax, ecx
        mov ebx, [r]
        mov ecx, [t]
        xor ebx, ecx
        mov edx, 1111111111111111110000000b
        and ebx, edx
        or eax, ebx
        mov ebx, 0
        mov ebx, [r]
        mov edx, 111111100000b
        and ebx, edx
        mov cl, 20
        shl ebx, cl
        or eax, ebx
        mov [q], eax
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
