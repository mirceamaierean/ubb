bits 32

global start

extern exit, scanf, printf

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
	a dd 0
	b dd 0
	res dd 0
	format db "%d%d", 0
	messageprint db "%d/%d=%d", 0

segment code use32 class=code
	start:
		push dword b
		push dword a
		push dword format
		call [scanf]
		add esp, 4 * 3
		
		push dword [a]
		pop ax
		pop dx
		
		mov bx, [b]
		
		div bx

		mov word [res], ax
		push dword [res]
		push dword [b]
		push dword [a]
		push dword messageprint
		call [printf]
		add esp, 4 * 4
		
		push dword 0
		call [exit]