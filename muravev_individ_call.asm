include '.\MZERO.inc'

format PE CONSOLE
entry @start

section '.import' import readable
include '.\BIBLMCN\DLLALL.inc'


section '.data' data readable writeable
    my_variable dd 42 ; Example variable

section '.text' code readable executable
    @start:
        ; Get the address of my_variable
        lea eax, [my_variable]

        invoke ExitProcess, 0