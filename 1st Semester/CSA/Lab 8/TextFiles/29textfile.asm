; A text file is given.
; The text file contains numbers (in base 10) separated by spaces.
; Read the content of the file, determine the maximum number (from the numbers that have been read) and write the result at the end of file.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fread, fprintf, fclose
import fopen msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db '29.txt', 0
    mod_access db 'a+', 0
    file_descriptor dd -1

    ten dd 10
    maximum dd 0

    buffer dd 0

    print_format db ' %d', 0

; our code starts here
segment code use32 class=code
    start:
        ; open the file
        ; fopen(file_name, mod_access)
        push dword mod_access
        push dword file_name
        call [fopen]
        add esp, 4 * 2

        ; check if the file was created sucessfully
        cmp eax, 0
        je final
        mov [file_descriptor], eax

        ; read character by character until the characther is not a space / digit
        while_read_char:
            ; fread(buffer, size, count, file_name)
            push dword [file_descriptor]
            push dword 1
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4 * 4

            ; check if something was read
            cmp eax, 0
            je end_while_read_char

            ; we store the character
            mov eax, [buffer]

            ; we check if the character is a space - we read another one if so
            cmp eax, ' '
            je while_read_char

            ; we check if the character is a digit
            cmp eax, '0'
            jb end_while_read_char ; if it was not a space and is below the digit '0' - we reached the end of file - we jump outside
            cmp eax, '9'
            ja end_while_read_char ; if it was not a space and is above the digit '9' - we reached the end of file - we jump outside

            ; if we reach this point, it means out character is a digit - we try to build the number now
            sub eax, 48 ; we convert the character into a real digit - now in eax we have the number we want to build

            while_digit:
                ; we read another character - that's why we need to push the register to not alterate them
                pushad
                push dword [file_descriptor]
                push dword 1
                push dword 1
                push dword buffer
                call [fread]
                add esp, 4 * 4

                ; check if something was read
                cmp eax, 0
                jne more_char

                popad
                jmp end_while_digit

                more_char:
                popad

                ; know we check again if out character is a valid digit - if not, we end this while
                mov ebx, [buffer]
                cmp ebx, '0'
                jb end_while_digit
                cmp ebx, '9'
                ja end_while_digit

                ; if we reached here, it means ebx = our character is a digit - we transform it into an actual digit
                sub ebx, 48

                ; we update the number - eax = eax * 10 + ebx (we assume the result will fit into a doubleword)
                mul dword [ten] ; edx:eax = eax * 10 - but the result will still fit into eax, so we don't really care about edx
                add eax, ebx

                ; now we read another one
                jmp while_digit

            end_while_digit:
            ; we have a number - we compare it to the maximum
            cmp eax, [maximum]
            jle while_read_char ; it's not greater than the actual maximum - we don't care about it anymore - we keep reading

            ; if we reached this point - it's greater than the actual maximum - we update it
            mov [maximum], eax
            jmp while_read_char ; and of course, we read another character

        end_while_read_char:
        ; append the maximum
        push dword [maximum]
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
