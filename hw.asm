; ПРИМЕР ИМПОРТА DLL ВРУЧНУЮ
format PE DLL

entry DllEntryPoint

include '.\INCLUDE\win32a.inc'

section '.data' data readable writable
    hello db 'Hello, World!',0

section '.text' code readable executable
DllEntryPoint:
    push ebp
    mov ebp, esp

    push hello
    call [MessageBoxA]

    xor eax, eax
    mov esp, ebp
    pop ebp
    ret

section '.idata' import data readable writeable

    library kernel32, 'kernel32.dll'
    import kernel32, \
        MessageBoxA, 'MessageBoxA'
