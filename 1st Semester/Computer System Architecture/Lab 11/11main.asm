bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern module_11
						  
; our data is declared here (the variables needed by our program)
segment data use32 class=data
	nr resb 32
	len equ 3
	conv resd 1
	stringformat db "%s", 0
	intformat db "%x", 10, 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
		compute_nr:
			push dword nr
			push dword stringformat
			call [scanf]       ; call function scanf for reading
			add esp, 4 * 2
			
			push dword nr
			call module_11
			add esp, 4 * 2
			
			push EDX
			push dword intformat
			call [printf]      ; call function printf for printing
			add esp, 4 * 2      ; free parameters on the stack; 4 = size of dword; 1 = number of parameters
			jmp compute_nr
	
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
