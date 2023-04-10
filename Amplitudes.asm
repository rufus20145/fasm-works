include '.\MZERO.inc'

format PE CONSOLE
entry @start

section '.data' data readable writeable
    fileName db 'C:\\projects\\fasm\\ST1.uni',0
    fileHandle dd ?
    source dd ?
    sourceSize dd ?
    resultPtr dd ?
    resultSize dd ?

macro readFileData source, sourceSize
{

invoke CreateFile, fileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
    cmp eax, INVALID_HANDLE_VALUE
je @error
    mov [fileHandle], eax

    invoke GetFileSize, [fileHandle], 0
    cmp eax, 0xffffffff ; это INVALID_FILE_SIZE, который у нас отсутствует в виде константы
je @error
    mov [sourceSize], eax

    invoke VirtualAlloc, 0, [sourceSize], MEM_COMMIT, PAGE_READWRITE
    cmp eax, 0
je @error
    mov [source], eax

    invoke ReadFile, [fileHandle], [source], [sourceSize], 0, 0
    cmp eax, 0
je @error

}

; список аргументов:
; source - исходный массив
; sourceSize - размер исходного массива
; resultPtr - ячейка, в которую будет помещен указатель на выходной массив
; resultSize - ячейка, в которую будет помещен размер выходного массива
;
; пример обращения:
; !getCountOfAmps исходный_массив размер_исходного будущий_указатель_на_выходной_массив будущий_размер_результата
;
macro !getCountOfAmps arg {
    common match source sourceSize resultPtr resultSize ,arg
    \{
        getCountOfAmps source, sourceSize, resultPtr, resultSize
    \}
}

macro getCountOfAmps srcArr, srcSize, resArr, resSize
{
        xor edi, edi
        xor esi, esi

        ; определяем размер и выделяем память на результирующий массив
        mov eax, [srcSize]
        shr eax, 2 ; эквивалентно делению на 4
        mov [resSize], eax
        invoke VirtualAlloc, 0, [resSize], MEM_COMMIT, PAGE_READWRITE
        cmp eax, 0
    je @error
        mov [resArr], eax
        mov edx, eax
        add esi, 2 ; сразу пропускаем первые два байта, т.к. там значение первой амплитуды
@countLoop:
        cmp edi, [resSize]
    je @countEnd
        mov ecx, [srcArr]
        mov al, [ecx + esi]
        mov bl, [ecx + esi + 1]
        add al, bl
        cmp al, 0
    je @errorZeroes
        cmp al, 0xFF
    jae @errorAbove
        mov byte [edx + edi], al
        inc edi
        add esi, 4
    jmp @countLoop

; TODO возвращать код ошибки и номер элемента, на котором сломались, а не завершать программу
@errorZeroes:
    invoke ExitProcess, 0x17

@errorAbove:
    invoke ExitProcess, 0x18

@countEnd:
}

macro printResult res, size
{
    xor edi, edi
    mov edx, [res]

@prepareDataLoop: ; цикл для преобразования бинарных данных в числовые
        cmp edi, [size]
    je @print
        add byte [edx + edi], 30h
        inc edi
    jmp @prepareDataLoop

@print:
    invoke GetStdHandle, STD_OUTPUT_HANDLE ; STD_OUTPUT возвращается в eax
    cmp eax, INVALID_HANDLE_VALUE
je @error
    invoke WriteConsole, eax, [res], [size], 0, 0
}

section '.code' code readable writeable executable

@start:
    mov ebx, @countLoop

    readFileData source, sourceSize

    !getCountOfAmps source sourceSize resultPtr resultSize
    printResult resultPtr, resultSize

    invoke CloseHandle, [fileHandle]
    invoke ExitProcess, 0

@error:
    invoke GetLastError
    invoke ExitProcess, eax

section '.import' import readable

include '.\BIBLMCN\DLLALL.inc'
