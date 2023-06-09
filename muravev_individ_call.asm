include '.\MZERO.inc'
include '.\error_codes.inc'

format PE CONSOLE
entry @start

section '.import' import readable
    library kernel, 'KERNEL32.DLL',\
        my_dll, 'Muravev_individ.dll'

    import my_dll, \
        processArray, 'processArray'
    import	kernel,\
        ExitProcess,	'ExitProcess',\
        GetStdHandle,	'GetStdHandle',\
        GetLastError,	'GetLastError',\
        WriteConsole,	'WriteConsoleA',\
        CloseHandle,	'CloseHandle',\
        CreateFile,		'CreateFileA',\
        ReadFile,		'ReadFile',\
        WriteFile,		'WriteFile',\
        VirtualAlloc,	'VirtualAlloc',\
        GetFileSize,	'GetFileSize'

section '.data' data readable writeable
    inputFileName db '.\data\amplitudes\ST1.uni',0
    resultFilename db '.\data\amplitudes\res.uni',0
    fileHandle dd ?
    resultFileHandle dd ?
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

macro writeDataToFile resultFilename, resultFileHandle, resArrPtr, resSize {
        invoke CreateFile, resultFilename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
        cmp eax, INVALID_HANDLE_VALUE
    je @error
        mov [resultFileHandle], eax
        invoke WriteFile, [resultFileHandle], [resArrPtr], [resSize] , 0, 0
        cmp eax, 0
    je @error
        invoke CloseHandle, [resultFileHandle]
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
        openFileForRead inputFileName, fileHandle
        allocMemoryForFileData fileHandle, source, sourceSize
        readDataFromFile fileHandle, source, sourceSize
        ; invoke CloseHandle, fileHandle ; выбрасывает непоятное исклюние, TODO потом разобраться

        invoke processArray, [source], [sourceSize]
        cmp eax, SUCCESS
    jne @myErrorHandle
        printText successMsg, 30

        writeDataToFile resultFilename, resultFileHandle, source, sourceSize

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
