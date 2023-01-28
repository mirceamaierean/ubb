; A file name is given (defined in the data segment).
; Create a file with the given name, then read numbers from the keyboard and write those numbers in the file, until the value '0' is read from the keyboard.

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
    ; ...
    mode_access db 'a', 0
    file_name db '12.txt', 0
    file_descriptor dd -1

	; 10 is \n character, for console print, there is also a 13 that has to be put after 10
    print_format db '%d', 10, 0
    read_format db '%d', 0

    number dd -1

; our code starts here
segment code use32 class=code
    start:
        ; A file name is given (defined in the data segment). Create a file with the given name, then read numbers from the keyboard and write those numbers in the file, until the value '0' is read from the keyboard.

        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2

        ; check if the file was opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax

        ; read number as long as we meet a 0
        while_read_numbers:
            push dword number
            push dword read_format
            call [scanf]
            add esp, 4 * 2

            cmp dword [number], 0
            je end_while_read_numbers

            ; append the number to the file
			; fprintf = (FILE* , format, v1)
            push dword [number]
            push dword print_format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 3

            jmp while_read_numbers

        end_while_read_numbers:
        ; close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
