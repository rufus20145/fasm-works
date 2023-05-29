include '.\MZERO.inc'

format PE CONSOLE 
entry @dll_start

section '.import' import readable

include '.\BIBLMCN\DLLALL.inc'


section '.code' code readable writeable executable

@dll_start:
    mov eax, TRUE
    cmp eax, TRUE

    invoke ExitProcess, 0