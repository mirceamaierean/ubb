bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
	a dd 0
	b dd 0
	result dq 0
	format db "%d%d", 0
	print_format db "%lld", 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
		push dword b
		push dword a
		push dword format
		call [scanf]
		add esp, 4 * 3
		mov eax, [a]
		mov ebx, [a]
		add eax, [b]
		sub ebx, [b]
		imul ebx
		mov [result + 4], edx
		mov [result], eax
		
		push dword [result + 4]
		push dword [result]
		push dword print_format
		call [printf]
		add esp, 4 * 3
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
