include '.\MZERO.inc'
include '.\error_codes.inc'

format PE DLL
entry dll_start

section '.import' import readable

include '.\BIBLMCN\DLLALL.inc'

section '.data' data readable writeable
    arrPtr dd ?
    arrSize dd ?

section '.code' code readable writeable executable

proc dll_start
        mov eax, TRUE
        cmp eax, TRUE
        ret
endp

@consolidate:
        add al, bl
    jb @amplOverflow ; флаговый регистр CF = 1, т.е. случилось переполнение
        sub byte [edx+esi], 2
        mov byte [edx+esi+2], 0
        mov byte [edx+esi+3], al
ret

proc myProc, arrPtr, arrSize
        mov esi, 0
        mov edx, [arrPtr]

@consolidateLoopStart:
        cmp esi, [arrSize]
    je @consolidateLoopEnd
        mov eax, 0
        mov ebx, 0
        mov al, [edx+esi+2]
        mov bl, [edx+esi+3]
        cmp al, 0
    je @f
        cmp bl, 0
    je @f
        call @consolidate ; два байта отсчётов != 0, т.е. уменьшаем амплитуду на 2 и кладем отсчёты в одну ячейку
@@:
        ; TODO делать проверку на два нуля?
        add esi, 4
    jmp @consolidateLoopStart

@consolidateLoopEnd:
        mov esi,4

@success:
        mov eax, SUCCESS
ret

@zeroSamples:
        mov eax, ZERO_SAMPLES
ret

@amplOverflow:
        mov eax, NUMBER_OF_SAMPLES_OVERFLOW
ret
endp

section '.edata' export data readable

    export 'Muravev_individ.DLL',\
        myProc, 'myProc'

section '.reloc' data readable discardable fixups

    if $=$$
        dd 0,8
    end if
