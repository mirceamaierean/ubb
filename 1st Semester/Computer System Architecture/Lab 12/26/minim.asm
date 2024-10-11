bits 32

global _minim

segment data public data use32

segment code public code use32


_minim:
    ; create a stack frame
    push ebp
    mov ebp, esp
    
    ; retreive the function's arguments from the stack
    ; [ebp+4] contains the return value 
    ; [ebp] contains the ebp value for the caller
    mov eax, [ebp + 8]        ; eax <- a
    
    mov ebx, [ebp + 12]        ; ebx <- b
    
	cmp eax, ebx ; set the flags
	
	jl final ; if the smallest number is already in eax, we jump to final
	
    mov eax, ebx            ; move in eax the smallest number

	final:
    mov esp, ebp
    pop ebp

    ret
    ; cdecl call convention - the caller will remove the parameters from the stack