; A file name and a text (defined in the data segment) are given.
; The text contains lowercase letters, digits and spaces.
; Replace all the digits on odd positions with the character ‘X’.
; Create the file with the given name and write the generated text to file.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we wont be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fprintf, fclose
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
  mode_access db 'w', 0
  file_name db '21.txt', 0
  file_descriptor dd -1

  string db '2002T55his is such a nice text wow 123'
  string_len equ ($ - string)
  updated_string times (string_len + 1) db 0 ; (string_len + 1), because we want to reserve a byte also for the 0 (since we pass this string to a C function)
  print_format db '%s', 0

; our code starts here
segment code use32 class=code
  start:
    ; open the file
    push dword mode_access
    push dword file_name
    call [fopen]
    add esp, 4 * 2

    ; check if the file was opened correctly
    cmp eax, 0
    je final
    mov [file_descriptor], eax

    ; iterate through the string
    mov esi, string
    mov edi, updated_string
    mov ecx, string_len
    mov ebx, 1 ; this is the human counter

    loop_string:
      lodsb ; al = the current character
      test ebx, 1 ; performs (ebx & 1) -> if we get a 1, the position is odd and the ZF = 0
      jz not_good_char

      ; otherwise, if the position is odd, we check if our character is a digit
      cmp al, '0'
      jb not_good_char
      cmp al, '9'
      ja not_good_char

      ; if we reach this point, it means our character is on an odd position and it is a digit -> we update it with 'X'
      mov al, 'X'

      not_good_char:
      stosb ; store the possibly modified character into edi

      inc ebx

      loop loop_string

      ; add the 0 end of string
      mov al, 0
      stosb

      ; print the updated_string
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
