; A file name and a text (defined in data segment) are given.
; The text contains lowercase letters, uppercase letters, digits and special characters.
; Replace all digits from the text with character 'C'.
; Create a file with the given name and write the generated text to file.


bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fprintf, fclose
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mode_access db 'w', 0
    file_name db '24.txt', 0
    file_descriptor dd -1

    string db 'dssascs2fsa4sdsaGJGKDC222@q!-DS210!'
    string_len equ ($ - string)
    updated_string times (string_len + 1) db -1
    print_format db '%s', 0

; our code starts here
segment code use32 class=code
    start:
        ; open the file
		; fopen(FILE*, format"
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2

        ; check if the file opened correctly
        cmp eax, 0
        je final
		
        mov [file_descriptor], eax

        ; iterate through the string
        mov esi, string
        mov edi, updated_string
        mov ecx, string_len
		cld
        loop_string:
            lodsb ; move into al the character from esi

            ; check if the character is a digit
            cmp al, '0'
            jb not_a_digit
            cmp al, '9'
            ja not_a_digit

            ; if we reach this point, the character is a digit - we replace it with C
            mov al, 'C'

            not_a_digit:
            stosb ; store it into edi
        loop loop_string

        ; for C printing we need to append 0 to the end of the updated_string
        mov al, 0
        stosb

        ; print the string
        push dword updated_string
        push dword print_format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4 * 3

        ; close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

		