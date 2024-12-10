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
	a dd 0
	b dd 0
	read_format db "%d%d", 0
	print_format db "%d", 10, 0
	yes db "YES", 0
	no_txt db "NO", 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
		push dword b
		push dword a 
		push dword read_format
		call [scanf]
		add esp, 4 * 3
		
		mov eax, 0
		mov al, byte [a]
		mov ebx, 0
		mov bx, word [b]
		compute:
			cmp ebx, 0
			jz no
			mov edx, ebx
			shr ebx, 1
			xor dl, al
			cmp dl, 0
			jnz compute
			push dword yes
			call [printf]
			add esp, 4
			jmp final
        ; ...
    
		no:
			push dword no_txt
			call [printf]
			add esp, 4
        ; exit(0)
		final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
