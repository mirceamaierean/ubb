; A text file is given.
; Read the content of the file, count the number of letters 'y' and 'z' and display the values on the screen.
; The file name is defined in the data segment.
; e.g. zavs - z yyyztzyuz

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we wont be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fclose, fread, printf
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
  mod_access db "r", 0
  file_name db "16.txt", 0
  file_descriptor dd -1

  char db 0
  z_freq dd 0
  y_freq dd 0
	format db 'The letter z appears %d times, while the letter y appears %d times', 0

; our code starts here
segment code use32 class=code
	start:
    ; open the file
    ; eax = fopen(file_name, mod_access)
    push dword mod_access
    push dword file_name
    call [fopen]
    add esp, 4 * 2

    ; save the file
    mov [file_descriptor], eax

    ; check for errors
    cmp eax, 0
    je final

    ; read the file byte by byte
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
      je close_file

      mov al, byte [char]
      cmp byte [char], 'z'
      jne not_z
      
      ; if we enter here, it means the character is z
      inc dword [z_freq]
      jmp read_loop ; we read again

      not_z:
      cmp byte [char], 'y'
      jne not_y
      ; if we enter here, it means the character is y
      inc dword [y_freq]
      jmp read_loop ; we read again

      not_y:
      jmp read_loop

    ; close the file
    close_file:
    push dword [file_descriptor]
    call [fclose]
    add esp, 4

    ; print on the console the frequencies
    push dword [y_freq]
    push dword [z_freq]
    push format
    call [printf]
    add esp, 4 * 3

	final:
	  ; exit(0)
    push    dword 0      ; push the parameter for exit onto the stack
    call    [exit]       ; call exit to terminate the program
