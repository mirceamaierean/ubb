bits 32 ; assembling for the 32 bits architecture
; (a*a+b/c-1)/(b+c)+d-x; a-word; b-byte; c-word; d-doubleword; x-qword
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw -64
    b db 12
    c dw -3
    d dd 275
    x dq 432243
    ; ...

; our code starts here
segment code use32 class=code
    start:
        mov AL, [b] ; AL -> [b]
        cbw ; AX -> [b]
        cwd ; DX:AX -> [b]
        mov BX, [c] ; BX -> [c]
        idiv BX ; AX -> DX:AX / BX
        mov BX, AX ; BX -> AX
        mov AX, [a] ; AX -> [a]
        imul AX ; DX:AX -> AX * AX
        push DX 
        push AX
        pop EDX
        mov AX, BX ; 
        cwde
        add EAX, EDX ; EAX -> EAX + EDX
        sub EAX, 1 ; EAX -> EAX - 1
        push EAX
        mov EAX, 0
        mov AL, [b] ; AL -> [b]
        cbw
        add AX, [c]; AX -> AX + [c]
        mov BX, AX ; BX -> AX
        pop AX 
        pop DX
        idiv BX ; AX -> DX:AX / BX
        cwde ; EAX -> AX
        add EAX, [d] ; EAX -> EAX + [d]
        cdq ; EDX : EAX
        sub EAX, [x] ; EAX -> EAX - [x]
        sbb EDX, [x + 4] ; EDX -> [x - 4]
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
