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
    fileName db '.\data\amplitudes\ST2.uni',0
    fileHandle dd ?
    source dd ?
    sourceSize dd ?

section '.text' code readable executable

; НАЧАЛО МАКРОСОВ

macro openFileForRead srcFileName, out_fileHandle
{
        invoke CreateFile, srcFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
        cmp eax, INVALID_HANDLE_VALUE
    je @error
        mov [out_fileHandle], eax
}

macro allocMemoryForFileData fileHandle, out_arrPtr, out_arrSize
{
        invoke GetFileSize, [fileHandle], 0
        cmp eax, 0xffffffff ; это INVALID_FILE_SIZE, который у нас отсутствует в виде константы
    je @error
        mov [out_arrSize], eax

        invoke VirtualAlloc, 0, eax, MEM_COMMIT, PAGE_READWRITE
        cmp eax, 0
    je @error
        mov [out_arrPtr], eax
    }

macro readDataFromFile fileHandle, sourcePtr, sourceSize
{
        invoke ReadFile, [fileHandle], [sourcePtr], [sourceSize], 0, 0
        cmp eax, 0
    je @error
}
; КОНЕЦ МАКРОСОВ

@start:
    ; Get the address of my_variable
    ; lea eax, [my_variable]

    mov eax, @myProc

    openFileForRead fileName, fileHandle
    allocMemoryForFileData fileHandle, source, sourceSize
    readDataFromFile fileHandle, source, sourceSize

@myProc:
    invoke myProc, [source], [sourceSize]

    invoke ExitProcess, 0


@error:
    invoke GetLastError
    invoke ExitProcess, eax