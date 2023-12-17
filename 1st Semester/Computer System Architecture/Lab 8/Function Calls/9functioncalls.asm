bits 32

global start

extern exit, scanf, printf

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
	a dd 0
	res dd 0
	format db "%d", 0
	messageprint db "%d", 0

segment code use32 class=code
	start:
		; read a
		push dword a
		push dword format
		call [scanf]
		add esp, 4 * 2
		
		; move the value of a in ebx, OTHER REGISTERS ARE AFFECTED BY THE SCANF FUNCTION
		mov ebx, [a]
		
		; read b
		push dword a
		push dword format
		call [scanf]
		add esp, 4 * 2
		
		; Move EBX to EAX, and add the new read number
		mov eax, ebx
		add eax, [a]
		; Convert the number to Quadword
		cdq
		; Subtract a from ebx
		sub ebx, [a]
		; Compute EDX:EAX / EBX <=> (a + b) / (a - b)
		div ebx

		push eax
		push dword messageprint
		call [printf]
		add esp, 4 * 2
		
		push dword 0
		call [exit]