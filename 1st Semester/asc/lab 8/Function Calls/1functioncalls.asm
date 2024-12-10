bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf

; our data is declared here (the variables needed by our program)
segment data use32 class=data
	n dw 0       ; in this variable we'll store the value read from the keyboard
	format  db "%d", 0  ; %d <=> a decimal number (base 10)
	messageprint db "%d", 0
	a dw 0
	result dd 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
		push dword a       ; ! addressa of n, not value
        push dword format
        call [scanf]       ; call function scanf for reading
        add esp, 4 * 2     ; free parameters on the stack
                           ; 4 = size of a dword; 2 = no of perameters
		mov bx, [a]
		
		push dword a
		push dword format 
		call [scanf]
		add esp, 4 * 2
		mov ax, [a]
		
		mul bx
		push dx
		push ax
		pop eax
		mov dword[result], eax
		
        ; ...
		push dword [result]
		push dword messageprint
        ;push dword messageprint ; ! on the stack is placed the address of the string, not its value
        call [printf]      ; call function printf for printing
        add esp, 4*2      ; free parameters on the stack; 4 = size of dword; 1 = number of parameters
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
