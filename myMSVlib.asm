; ПРИМЕР СОЗДАНИЯ DLL с процедурой

format PE GUI 4.0 DLL
entry DllEntryPoint

include '.\INCLUDE\win32a.inc'

; section '.data' code readable writeable


section '.code' code readable writeable executable

proc DllEntryPoint
  mov eax, TRUE
  ret
endp

proc scanf
  cmp eax, 1
ret
endp

section '.edata' export data readable

    export 'myMSVlib.DLL',\
        scanf, 'scanf'

section '.reloc' data readable discardable fixups

  if $=$$
    dd 0,8              ; if there are no fixups, generate dummy entry
  end if
