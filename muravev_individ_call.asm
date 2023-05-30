include '.\MZERO.inc'
include '.\error_codes.inc'

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
    fileName db '.\data\amplitudes\ST3.uni',0
    fileHandle dd ?
    source dd ?
    sourceSize dd ?

    successMsg db 'Process successfully finished',0
    amplOverflowMsg db 'Overflow of amplitudes number',0
    zeroSamplesMsg db 'Sum of samples is zero',0
    unknownErrorMsg db 'Unknown error',0

section '.text' code readable executable

; НАЧАЛО МАКРОСОВ =================================================================================

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

macro printText res, size
{
        invoke GetStdHandle, STD_OUTPUT_HANDLE ; STD_OUTPUT возвращается в eax
        cmp eax, INVALID_HANDLE_VALUE
    je @error
        invoke WriteConsole, eax, res, size, 0, 0
}
; КОНЕЦ МАКРОСОВ ==================================================================================

@start:
        ; Get the address of var
        ; lea eax, [var]

        mov eax, @myProc

        openFileForRead fileName, fileHandle
        allocMemoryForFileData fileHandle, source, sourceSize
        readDataFromFile fileHandle, source, sourceSize

@myProc:
        invoke myProc, [source], [sourceSize]
        cmp eax, SUCCESS
    jne @myErrorHandle
        printText successMsg, 30

        invoke ExitProcess, 0


@error:
        invoke GetLastError
        invoke ExitProcess, eax

@myErrorHandle:
        cmp eax, NUMBER_OF_SAMPLES_OVERFLOW
    jne @f
        printText amplOverflowMsg, 30
    jmp @myErrEnd
@@:
;         cmp eax, ZERO_SAMPLES
;     jne @f
;         printText zeroSamplesMsg, 23
;     jmp @myErrEnd
; @@:
; при появлении новых кодов ошибок добавлять тут сравнение с ними, jne @f, вывод сообщения и прыжок на выход и метку @@: после
        printText unknownErrorMsg, 14
    jmp @myErrEnd

@myErrEnd:
        invoke ExitProcess, eax
