; Read a file name and a text from the keyboard.
; Create a file with that name in the current folder and write the text that has been read to file.
; Observations: The file name has maximum 30 characters. The text has maximum 120 characters.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fclose, fprintf, scanf
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mode_access db 'w', 0
    file_name times 30 db 0
    file_descriptor dd -1

    ; read_format db '%[^”,10,”]%s', 0
    read_format db '%s', 0
    text resb 120

    print_format db '%s', 0

; our code starts here
segment code use32 class=code
    start:

		push dword file_name
		push dword read_format
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

        ; read the text
        push dword text
        push dword read_format
        call [scanf]
        add esp, 4 * 2

        ; print the text
        push dword text
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
