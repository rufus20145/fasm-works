; ПРИМЕР СОЗДАНИЯ DLL с процедурой

format PE GUI 4.0 DLL
entry DllEntryPoint

include '.\INCLUDE\win32a.inc'

section '.data' code readable writeable

  hIn dd 0
  hOut dd 0
  cnt dd 0

  boot db 0

  SaveReg dd 6 dup(0)

  adrRet dd 0

  ind dd 0
  tmp dd 0

  b dd 0

  buf db 0, 0

  pMem dd 0

section '.text' code readable writeable executable

; include 'mylib\strnum.inc'

proc DllEntryPoint hinstDLL, fdwReason, lpvReserved
  mov eax, TRUE
  ret
endp

writeHex:
  push ecx edi
  cmp eax, 16
  ja .e

  cmp eax, 9
  ja @f
    add eax, '0'
    mov [buf], al
  @@:

  cmp eax, 10
  jne @f
    mov [buf], 'A'
  @@:

  cmp eax, 11
  jne @f
    mov [buf], 'B'
  @@:

  cmp eax, 12
  jne @f
    mov [buf], 'C'
  @@:

  cmp eax, 13
  jne @f
    mov [buf], 'D'
  @@:

  cmp eax, 14
  jne @f
    mov [buf], 'E'
  @@:

  cmp eax, 15
  jne @f
    mov [buf], 'F'
  @@:

  invoke WriteConsole, [hOut], buf, 1, cnt, 0
  .e:
  pop edi ecx
ret

bootProc:
  invoke AllocConsole
  invoke GetStdHandle, STD_INPUT_HANDLE
  mov [hIn], eax
  invoke GetStdHandle, STD_OUTPUT_HANDLE
  mov [hOut], eax
  inc [boot]
ret

SaveRegProgPush:
  mov dword[SaveReg], eax
  mov dword[SaveReg+4], ebx
  mov dword[SaveReg+8], ecx
  mov dword[SaveReg+12], edx
  mov dword[SaveReg+16], esi
  mov dword[SaveReg+20], edi
ret

SaveRegProgPop:
  mov eax, dword[SaveReg]
  mov ebx, dword[SaveReg+4]
  mov ecx, dword[SaveReg+8]
  mov edx, dword[SaveReg+12]
  mov esi, dword[SaveReg+16]
  mov edi, dword[SaveReg+20]
ret

printf:
call SaveRegProgPush

pop eax
mov [adrRet], eax

  cmp [boot], 0
  jne @f
    call bootProc
  @@:

  pop eax
.s:
  cmp byte[eax], 0
  je .e
  xor ebx, ebx
  @@:
    cmp byte[eax+ebx], 0
    je @f
    cmp byte[eax+ebx], '%'
    je @f
    inc ebx
  jmp @b
  @@:

  cmp byte[eax], '%'
  je @f
    lea ecx, [eax+ebx]

    push ecx
      invoke WriteConsole, [hOut], eax, ebx, cnt, 0
    pop eax
    jmp .s
  @@:

  cmp word[eax], '%d'
  jne @f
    pop ebx
    inc eax
    mov ecx, eax ; ecx = string
      ; stdcall IntStr, ebx
      mov ebx, eax ; ebx = IntStr
      ; stdcall lenStr, eax ; eax = lenStr
      push ecx ebx
      invoke WriteConsole, [hOut], ebx, eax, cnt, 0
      pop ebx
      invoke LocalHandle, ebx
      invoke LocalFree, eax
      pop eax
      inc eax
      jmp .s
  @@:

  cmp word[eax], '%x'
  jne .x1
    mov edi, eax
    pop eax
    mov ebx, 16
    xor ecx, ecx
    @@:
      xor edx, edx
      div ebx
      push edx
      inc ecx
    cmp eax, 16
    ja @b

    call writeHex

    @@: pop eax
      call writeHex
    loop @b

    mov eax, edi
    add eax, 2
    jmp .s
  .x1:

  cmp word[eax], '%s'
  jne .s1
      pop ebx
      push eax
      ; stdcall lenStr, ebx
      invoke WriteConsole, [hOut], ebx, eax, cnt, 0
      pop eax
      add eax, 2
      jmp .s
  .s1:

  cmp word[eax], '%%'
  jne @f
    push eax
      invoke WriteConsole, [hOut], eax, 1, cnt, 0
    pop eax
    add eax, 2
    jmp .s
  @@:

  cmp word[eax], '%c'
  jne @f
    pop ebx
    push eax
    mov byte[buf], bl
      invoke WriteConsole, [hOut], buf, 1, cnt, 0
    pop eax
    add eax, 2
    jmp .s
  @@:

  cmp word[eax], '%f'
  jne @f
    pop ebx
    push eax
      ; stdcall FloatStr, ebx, 2
      mov ebx, eax
      ; stdcall lenStr, eax
      invoke WriteConsole, [hOut], ebx, eax, cnt, 0
    pop eax
    add eax, 2
    jmp .s
  @@:

  xor ebx, ebx
  @@:
    inc ebx
    cmp byte[eax+ebx], 0
    je @f
    cmp byte[eax+ebx], '%'
    je @f
    cmp byte[eax+ebx], 'f'
    je .f1
    jmp @b
  @@:
  push eax
    invoke WriteConsole, [hOut], eax, 1, cnt, 0
  pop eax
  jmp .f2
  .f1:
    inc eax
    mov edi, eax
      @@:
        cmp byte[eax], '.'
        je @f
        cmp byte[eax], 'f'
        je .f3
        inc eax
      @@:
      inc eax

        ; stdcall StrInt, eax, 0, ind

        pop ecx

        ; stdcall FloatStr, ecx, eax
        push eax
        mov ebx, eax
        ; stdcall lenStr, eax
        push edi
        invoke WriteConsole, [hOut], ebx, eax, cnt, 0
        pop edi
        add edi, [ind]

        @@:
          cmp byte[edi], 0
          je @f
          cmp byte[edi], '%'
          je @f
          cmp byte[edi], 'f'
          je @f
          inc edi
          jmp @b
        @@:

        pop eax
        push edi
          invoke LocalHandle, eax
          invoke LocalFree, eax
        pop edi

      .f3:

     mov eax, edi
  .f2:

  inc eax

jmp .s

.e:
call SaveRegProgPop
jmp [adrRet]

proc scanf, string, num
call SaveRegProgPush

  cmp [boot], 0
  jne @f
    call bootProc
  @@:

  invoke LocalAlloc, LPTR, 512
  mov [pMem], eax
  invoke ReadConsole, [hIn], eax, 512, cnt, 0

  mov eax, [string]
  mov ebx, [num]

  cmp word[eax], '%d'
  jne @f
    ; stdcall StrInt, [pMem], 0, 0
    mov dword[ebx], eax
    jmp .e
  @@:

  cmp word[eax], '%f'
  jne @f
    ; stdcall StrFloat, [pMem], 0, 0, 1
    mov dword[ebx], eax
    jmp .e
  @@:

  cmp word[eax], '%c'
  jne @f
    mov edx, [pMem]
    mov dl, byte[edx]
    mov byte[ebx], dl
    jmp .e
  @@:

  cmp word[eax], '%s'
  jne @f
    ; stdcall CopyStr, [pMem], 0
    mov dword[ebx], eax
    jmp .e
  @@:

  .e:
    invoke LocalHandle, [pMem]
    invoke LocalFree, eax
call SaveRegProgPop
ret
endp

section '.idata' import data readable writeable

  library kernel,'KERNEL32.DLL'

  import kernel,\
         GetStdHandle, 'GetStdHandle',\
         WriteConsole, 'WriteConsoleA',\
         LocalAlloc, 'LocalAlloc',\
         LocalHandle, 'LocalHandle',\
         LocalFree, 'LocalFree',\
         AllocConsole, 'AllocConsole',\
         LocalLock, 'LocalLock',\
         ReadConsole, 'ReadConsoleA'

section '.edata' export data readable

  export 'myMSVlib.DLL',\
         scanf, 'scanf'

section '.reloc' data readable discardable fixups

  if $=$$
    dd 0,8              ; if there are no fixups, generate dummy entry
  end if
