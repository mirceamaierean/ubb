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
	read_format db "%x%x", 0
	print_sum_format db "sum=%X", 10, 0
	print_dif_format db "dif=%X", 10, 0
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
		add ax, word [b]
		
		push eax
		push print_sum_format
		call [printf]
		add esp, 4 * 2
		
		mov eax, [a]
		mov ebx, [b]
		shr eax, 16
		shr ebx, 16
		sub eax, ebx
		
		push eax
		push print_dif_format
		call [printf]
		add esp, 4 * 2
		
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
