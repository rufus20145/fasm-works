include '.\MZERO.inc'

format PE console
entry start

section '.data' data readable writable
    array db 5, 10, 3, 8, 2, 15, 1, 9, 4, 6, 12
    array_size equ $ - array

section '.code' code readable executable
start:
    mov ecx, array_size
    lea esi, [array]
    sub ecx, 2   ; Ignore the first and last elements
    add esi, 1   ; Start from the second element

    local_min_loop:
        movzx eax, byte [esi - 1]
        cmp al, byte [esi]
        jle next_iteration

        movzx eax, byte [esi]
        cmp al, byte [esi + 1]
        jle next_iteration

        ; Local minimum found, you can perform any desired operation here
        ; In this example, we simply set the value to zero
        mov byte [esi], 0

    next_iteration:
        add esi, 1
        loop local_min_loop

    ; Exit the program
    xor eax, eax
    ret

section '.idata' import data readable
include '.\BIBLMCN\DLLALL.inc'

