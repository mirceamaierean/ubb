bits 32 ; assembling for the 32 bits architecture
segment code use32 public code
; declare the EntryPoint (a label defining the very first instruction of the program)
global module_11        

module_11:
	mov ESI, [ESP + 4]
	cld
	mov EDX, 0
	mov EAX, 0
	compute_nr:
		LODSB
		cmp AL, 0
		jz final
		sub AL, '0'
		shl EDX, 1
		add EDX, EAX
		jmp compute_nr		
	final:
	ret