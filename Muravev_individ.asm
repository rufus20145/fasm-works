include '.\MZERO.inc'

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
endp

proc myProc, arrPtr, arrSize
    mov eax, [arrPtr]
    mov ebx, [arrSize]

    ret
endp

section '.edata' export data readable

    export 'Muravev_individ.DLL',\
        myProc, 'myProc'

section '.reloc' data readable discardable fixups

  if $=$$
    dd 0,8              ; if there are no fixups, generate dummy entry
  end if
