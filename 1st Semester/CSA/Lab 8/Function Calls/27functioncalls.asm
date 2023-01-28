bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db "mihai", 0
	len equ $-s
	c dd 0
	format db "%c", 0
	print_format db "%c %d", 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword c
		push dword format
		call [scanf]
		add esp, 4 * 2
		
		mov ebx, 0
		mov esi, s
        cld
        mov ecx, len
		repeta:
			LODSB
			cmp al, byte[c]
			jnz dif
			add ebx, 1
			dif:
			loop repeta
			
		push ebx
		push dword [c]
		push dword print_format
		call [printf]
		add esp, 4 * 3
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
