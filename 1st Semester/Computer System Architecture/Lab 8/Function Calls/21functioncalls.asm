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
	c dd 0
	read_format db "%d%d", 0
	print_format db "%X", 10, 0
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
		mov ax, word [a]
		sub ax, word [b]
		
		mov dx, ax
		shl edx, 16
		
		mov dx, word[a]
		add dx, word[b]
		mov dword [c], edx
		
		push dword [c]
		push print_format
		call [printf]
		add esp, 4 * 2
		
		push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
