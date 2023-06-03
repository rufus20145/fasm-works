include 'INCLUDE\WIN32A.INC'

include 'error_codes.inc'

format PE DLL
entry dll_start

section '.import' import readable

include 'BIBLMCN\DLLALL.inc'

section '.data' data readable writeable
    arrPtr dd ?
    arrSize dd ?

; НАЧАЛО МАКРОСОВ =================================================================================
MACRO УпрятатьРегистры [string]
{   common
    forward
    PUSH string
}
MACRO ВостановитьРегистры [string]
{   common
    reverse
    POP string
}
; КОНЕЦ МАКРОСОВ ==================================================================================

section '.code' code readable writeable executable

proc dll_start
        mov eax, TRUE
        cmp eax, TRUE
        ret
endp

; процедура удаляет повторения в заданном массиве,
; а также соответствующе уменьшает значения локальных минимумов
; для этого определяется максимальное количество повторов амплитуды ("длина полочки"),
; а затем вычитается найденное значение из всех значений амплитуд локальных минимумов и 
; и переносится количество отсчётов из ячейки "горизонтали" в ячейку "наклонной"
; передаваемые аргументы:
; arrPtr - dword указатель на исходный массив (он будет изменен)
; arrSize - размер передаваемого массива
;
; результат работы или код ошибки будет передан через регистр eax
; 0x0 - успешное завершение
; 0x1 - переполнение количества отсчётов (при сложении двух значений)

proc processArray, arrPtr, arrSize
        УпрятатьРегистры eax, ebx, ecx, edx, esi
        mov esi, 0
        mov edx, [arrPtr]
        mov eax, 0
        mov ecx, 0

@findMinLoopStart:
        ; более правильная проверка за выход за границы массива, чем просто равенство
        add [arrSize], 4
        cmp esi, [arrSize]
    ja @findMinLoopEnd
        sub [arrSize], 4
        mov al, [edx+esi+2]
        cmp al, cl
    jbe @findMinLoopNextIter
        mov cl, al
@findMinLoopNextIter:
        add esi, 8
    jmp @findMinLoopStart

@findMinLoopEnd:
        xor esi, esi

@processLoopStart:

        ; более правильная проверка за выход за границы массива, чем просто равенство
        add [arrSize], 4
        cmp esi, [arrSize]
    ja @processLoopEnd
        sub [arrSize], 4

        sub [edx+esi], cl
        mov eax, 0
        mov ebx, 0
        mov al, [edx+esi+2]
        cmp al, 0
    je @f
        add al, [edx+esi+3]
    jb @amplOverflow ; флаговый регистр CF = 1, т.е. случилось переполнение
        mov byte [edx+esi+2], 0
        mov byte [edx+esi+3], al
@@:
        add esi, 8
    jmp @processLoopStart

@processLoopEnd:

@success:
        ВостановитьРегистры eax, ebx, ecx, edx, esi
        mov eax, SUCCESS
ret

@amplOverflow:
        ВостановитьРегистры eax, ebx, ecx, edx, esi
        mov eax, NUMBER_OF_SAMPLES_OVERFLOW
ret
endp

section '.edata' export data readable

    export 'Muravev_individ.DLL',\
        processArray, 'processArray'

section '.reloc' data readable discardable fixups

    if $=$$
        dd 0,8
    end if
