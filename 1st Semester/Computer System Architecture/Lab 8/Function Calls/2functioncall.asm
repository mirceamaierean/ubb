bits 32

global start

extern exit, printf, scanf
import exit msvcrt.dll    
import printf msvcrt.dll  
import scanf msvcrt.dll   


segment data use32 class=data
	a dd 0
	res dd 0
	format db "%d", 0

segment code use32 class=data
	start:
		push dword a
		push dword format
		call [scanf]
		add esp, 4 * 2
		
		mov ebx, [a]
		
		push dword a
		push dword format
		call [scanf]
		add esp, 4 * 2
		
		push ebx
		pop ax
		pop dx
		
		mov bx, [a]
		
		div bx
		mov word [res], ax
		
		push dword [res]
		push dword format
		call [printf]
		add esp, 4 * 2
		
		push dword 0
		call [exit]