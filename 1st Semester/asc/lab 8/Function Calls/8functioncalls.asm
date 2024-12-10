bits 32

global start

extern exit, scanf, printf

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
	a dd 100
	b dd 0
	res dd 0
	format db "%d", 0
	messageprint db "%d + %d/%d=%d", 0

segment code use32 class=code
	start:
		push dword b
		push dword format
		call [scanf]
		add esp, 4 * 2
		
		push dword [a]
		pop ax
		pop dx
		
		mov bx, [b]
		div bx

		mov word[res], ax
		mov eax, [a]
		add eax, [res]
		
		push eax
		push dword [b]
		push dword [a]
		push dword [a]
		push dword messageprint
		call [printf]
		add esp, 4 * 5
		
		push dword 0
		call [exit]