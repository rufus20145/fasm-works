include '.\MZERO.inc'

format PE CONSOLE
entry start

section '.data' data readable writeable

    source  db  7Dh, 00h, 00h, 01h, 80h, 00h, 00h, 01h, 7Eh, 00h, 00h, 01h, 7Fh, 00h, 02h, 00h, 7Fh, 00h, 00h, 01h, 80h, 00h, 00h, 01h, 7Fh, 00h, 01h, 00h, 7Fh, 00h, 00h, 01h
    result_size equ  08h
    result  db  result_size dup(0)
    Writed  dd  21
    ; path  db  'C:\projects\fasm\st2.uni', 0
; TODO добавить размер входного массива, т.к. в конце идут значения амплитуды, а не количество отсчётов
macro getNumOfAmps sourceArr, resultArr, resultSize
{
    УпрятатьРегистры eax, ebx, ecx, edx, ebp, esi, edi
    add esi, 2 ; пропускаем первые два байта
@@loop:
    cmp edi, resultSize
    je @getNumEnd
    movzx eax, [sourceArr + esi]
    movzx ebx, [sourceArr + esi + 1]
    ; TODO проверка на два нуля
    add eax, ebx
    mov [resultArr + edi], al
    inc edi
    add esi, 4
jmp @@loop

@getNumEnd:
    ВостановитьРегистры eax, ebx, ecx, edx, ebp, esi, edi
}

macro printResult result, resultSize
{
    УпрятатьРегистры eax, edi
@@outLoop:
    cmp edi, resultSize
    je @print
    movzx eax, [result + edi]
    add eax, 30h
    mov [result + edi], al
    inc edi
jmp @@outLoop


@print:
    ВостановитьРегистры eax, edi
    invoke GetStdHandle, STD_OUTPUT_HANDLE
    invoke  WriteConsole,eax,result,8,Writed,0
}

section '.code' code readable writeable executable

start:
    ; Обнуление индесных регистров
    xor esi, esi
    xor edi, edi

    getNumOfAmps source, result, result_size

    printResult result, result_size

    ret

section '.import' import readable
include '.\BIBLMCN\DLLALL.inc'
