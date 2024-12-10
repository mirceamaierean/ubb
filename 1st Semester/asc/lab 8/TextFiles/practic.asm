bits 32

global start

extern exit              
import exit msvcrt.dll
extern fopen, fclose, fprintf, scanf, printf, fread
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fread msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mode_access db 'r', 0
    file_name times 30 db 0
    file_descriptor dd -1

    read_format_file db '%s', 0
    text resb 120

    print_format db '%s', 0
	char db 0
	
	cuv resb 100


; our code starts here
segment code use32 class=code
    start:
		push dword file_name
		push dword read_format_file
		call [scanf]
		add esp, 4 * 2
		
        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2

        ; check if the file opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax
		
		mov edi, text
		
		read_loop:
			; fread(char, step = 1, len = 1, file)
			push dword [file_descriptor]
			push dword 1
			push dword 1
			push dword char
			call [fread]
			add esp, 4 * 4

			; if eax = 0, it means no character was read
			cmp eax, 0
			je process_text
			mov al, byte [char]
			stosb
			
			jmp read_loop

		process_text:
		mov ebx, 0
		mov esi, text
		mov edi, cuv
		get_words:
			lodsb
			cmp al, 0
			je afis
			cmp al, ' '
			je change_ebx
			cmp ebx, 0
			je get_words
			stosb
			jmp get_words
			change_ebx
				cmp ebx, 1
				jne xor_ebx
				stosb
				xor_ebx:
				xor ebx, 1
			jmp get_words
			
		afis: 
		push dword cuv
		push dword print_format
		call [printf]
		add esp, 4 * 2
		
        ; close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
