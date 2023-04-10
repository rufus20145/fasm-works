include '.\MZERO.inc'

format PE CONSOLE
entry @start

section '.data' data readable writeable

    source db 7Dh, 00h, 00h, 01h, 80h, 00h, 00h, 01h, 7Eh, 00h, 00h, 01h, 7Fh, 00h, 02h, 00h, 7Fh, 00h, 00h, 01h, 80h, 00h, 00h, 01h, 7Fh, 00h, 01h, 00h, 7Fh, 00h, 00h, 01h
    sourceSize dd 32
    resultPtr dd ?
    resultSize dd ?
    ; path  db  'C:\projects\fasm\st2.uni', 0

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
        УпрятатьРегистры eax, ebx, ecx, edx, ebp, esi, edi
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
        ; TODO проверка на два нуля в складываемых байтах, возвращать код ошибки и номер элемента, на котором сломались
        movzx eax, [srcArr + esi]
        movzx ebx, [srcArr + esi + 1]
        add eax, ebx
        mov byte [edx + edi], al
        inc edi
        add esi, 4
    jmp @countLoop

@countEnd:
    ВостановитьРегистры eax, ebx, ecx, edx, ebp, esi, edi
}

macro printResult res, size
{
    УпрятатьРегистры eax, edx, edi
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
    invoke WriteConsole, eax, [res], [size] ; два опицональных аргумента не указаны

    ВостановитьРегистры eax, edx, edi
}

section '.code' code readable writeable executable

@start:
    !getCountOfAmps source sourceSize resultPtr resultSize
    printResult resultPtr, resultSize

    invoke ExitProcess, 0

@error:
    invoke GetLastError
    invoke ExitProcess, eax

section '.import' import readable

include '.\BIBLMCN\DLLALL.inc'
