bits 32

global _base10
; linkeditorul poate folosi segmentul public de date si pentru date din afara
segment data public data use32
    
segment code public code use32

_base10:
    ; creare cadru de stiva pentru programul apelat
    push ebp
    mov ebp, esp
    mov esi, [ebp + 8]
	cld
	mov edx, 0
	mov eax, 0
	compute_nr:
		LODSB
		cmp al, 0
		jz final
		sub al, '0'
		shl edx, 1
		add edx, eax
		jmp compute_nr		
	final:
	mov eax, edx
	mov esp, ebp
    pop ebp
    ret
    