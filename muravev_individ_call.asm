include '.\MZERO.inc'

format PE CONSOLE
entry @start

section '.import' import readable
library kernel, 'KERNEL32.DLL',\
        Muravev_individ, 'Muravev_individ.dll'

    import Muravev_individ, \
        myProc, 'myProc'
    import	kernel,\
        ExitProcess,	'ExitProcess',\
        GetStdHandle,	'GetStdHandle',\
        GetLastError,	'GetLastError',\
        WriteConsole,	'WriteConsoleA',\
        ReadConsole,	'ReadConsoleA',\
        GetCurrentDirectory,	'GetCurrentDirectoryA',\
        CloseHandle,	'CloseHandle',\
        CreateFile,		'CreateFileA',\
        CreateDirectory,'CreateDirectoryA',\
        ReadFile,		'ReadFile',\
        WriteFile,		'WriteFile',\
        GetCommandLine,	'GetCommandLineA',\
        VirtualFree,	'VirtualFree',\
        VirtualAlloc,	'VirtualAlloc',\
        SetFilePointer,	'SetFilePointer',\
        SetCurrentDirectory,'SetCurrentDirectoryA',\
        GetFileSize,	'GetFileSize',\
        GlobalAlloc,    'GlobalAlloc'

section '.data' data readable writeable
    my_variable dd 42 ; Example variable

section '.text' code readable executable
    @start:
        ; Get the address of my_variable
        lea eax, [my_variable]

        invoke myProc

        invoke ExitProcess, 0