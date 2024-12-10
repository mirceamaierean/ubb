; A text file is given.
; Read the content of the file, determine the uppercase letter with the highest frequency and display the letter along with its frequency on the screen.
; The name of text file is defined in the data segment.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fclose, fread, printf
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    ; A - ascii code 65
    ; Z - ascii code 90
    a_char db 0
    letters_freq times 26 dw 0 ; we keep a word for the frequency of a certain letter

    mode_access db 'r', 0
    file_name db '8.txt', 0
    file_descriptor dd -1

    maximum dd 0
    answer_letter dd -1

    print_format db '%d %c', 0

; our code starts here
segment code use32 class=code
    start:

        ; open the file
        push dword mode_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2

        ; check if the file opened correctly
        cmp eax, 0
        je final
        mov [file_descriptor], eax

        ; read from the file character by character
        read_chars:
            push dword [file_descriptor]
            push dword 1
            push dword 1
            push dword a_char
            call [fread]
            add esp, 4 * 4

            ; check if something was read
            cmp eax, 0
            je end_read_chars

            ; move the character inside al - to access it faster
            mov al, byte [a_char]

            ; check if the character is an uppercase letter
            cmp al, 'A'
            jb not_uppercase
            cmp al, 'Z'
            ja not_uppercase

            ; if we reach this point, it means that the letter is uppercase
            ; we have the ascii code of the letter inside al
            sub al, 'A' ; now we have 0 - A, 1 - B, 2 - C ...
            ; we want to make sure everything else in eax (beside al) is 0
            mov ah, 0
            cwde

            ; and now to increase the frequency we access word [letters_freq + 2 * eax]
            ; we first need to multiply eax with 2
            ; we make a copy to use it later
            mov ebx, eax

            mov ecx, 2
            mul ecx ; edx:eax = eax * 2 - we assume the result still fits inside eax

            inc word [letters_freq + eax]

            ; and we can also compare it with the maximum
            mov ecx, 0
            mov cx, word [letters_freq + eax]

            cmp ecx, [maximum]
            jb not_better

            ; if we reach this point, it means that the maximum it's better - we update it
            mov [maximum], ecx

            ; we add again to ebx 65 to get the real ascii code
            add ebx, 'A'
            mov [answer_letter], ebx

            not_better:
            not_uppercase:
            ; we read another one
            jmp read_chars

        end_read_chars:
        ; we print the result
        push dword [answer_letter]
        push dword [maximum]
        push dword print_format
        call [printf]
        add esp, 4 * 3

        ; close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
