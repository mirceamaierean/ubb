bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fread, printf, fopen ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fread msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
	sir db "#$%^&*", 0
	len equ $-sir
	file_name db "5.txt", 0       ; filename to be read
	access_mode dd "r", 0
	file_descriptor dd -1
	format db "%d", 0
	char db 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
		push dword access_mode
		push dword file_name
		call [fopen]
		add esp, 4 * 2
		
		mov ebx, 0
		
		mov dword [file_descriptor], eax
		cmp eax, 0
		je final

		read_chars:
			push dword [file_descriptor]
			push dword 1
			push dword 1
			push dword char
			call [fread]
			cmp eax, 0
			je print_result
			
			add esp, 4 * 4
			mov esi, sir
			mov ecx, len
			cld
			repeta:
				LODSB
				cmp AL, byte [char]
				jnz step_up
				add ebx, 1
				step_up:
				loop repeta
			jmp read_chars
		
		print_result:
			push ebx
			push dword format
			call [printf]
			add esp, 4 * 2
			
		final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
