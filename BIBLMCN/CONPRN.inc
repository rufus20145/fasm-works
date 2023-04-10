;1	P!rAdrStop		'C:\FASM\BIBLMCN\CONPRN.inc'
;2	N!16inASCII		'C:\FASM\BIBLMCN\CONPRN.inc'
;3	P!rTxtAdr		'C:\FASM\BIBLMCN\CONPRN.inc'
;4	P!rTXTNUMBER	'C:\FASM\BIBLMCN\SERVIS\CONPRNp.inc'
;5	P!rAdr			'C:\FASM\BIBLMCN\SERVIS\CONPRNp.inc'
;**************************  1    ************************************************
;P!rAdrStop	TEXT	;ТЕКСТ из 1- 4 слов и распечатывается адрес выхода из программы
;P!rAdrStop	=BalarirevNE	TEST	C!MPabJm	macros      ;+  ASCIIадрес
;P!rAdrStop	=BalarirevNE									;+ASCIIадрес
;P!rAdrStop	=BalarirevNE	TEST							;+ASCIIадрес
;P!rAdrStop	=BalarirevNE	TEST	C!MPabJm				;+ASCIIадрес
;масro	N!16inASCII	EBP,Adruk,8
;	УпряталиРегистры	EAX,EBX,ECX,EDX,ESI,EDI
;	ВосcтановилиРегистры   EAX,EBX,ECX,EDX,ESI,EDI
;Используемые	процедуры	GetStdHandle, STD_OUTPUT_HANDLE
;		WriteConsole,eax,Pref,edx,Writed,0
;		invoke	ExitProcess, 1
;***************************************************************************
MACRO	P!rAdrStop	 TEX
{	local	Adruk,Pref,Writed,FGH
@@:
	УпряталиРегистры	EBP,EAX,ECX,EDX	;++
	jmp	FGH

Pref	db	" "
	common match AK ==TEXT,TEX
	\{
\PRZN	equ	0
	common match  TXT TXT1 TXT2 TXT3,\TEXT
	\\{
	db	" "\\#\\`TXT
	db	" "\\#\\`TXT1
	db	" "\\#\\`TXT2
	db	" "\\#\\`TXT3
\\PRZN	equ	1
	\\}
		if	\\PRZN eq 0
	common match  TXT TXT1 TXT2,\TEXT
\\{
	db	" "\\#\\`TXT
	db	" "\\#\\`TXT1
	db	" "\\#\\`TXT2
\\PRZN	equ	1
\\}
			if	\\PRZN eq 0
	common match  TXT TXT1,\TEXT
\\{
	db	" "\\#\\`TXT
	db	" "\\#\\`TXT1
\\PRZN	equ	1
\\}
				if	\\PRZN eq 0
	match  TXT,TEXT
\\{
	db	" "\\#\\`TXT
\\}
				end if
			end if
		end if
	
	db	" "
Adruk	db	10	dup	('!')	; под адрес останова 8 16-ных чисел
	db	0
;Hconsl_d	dd	0
DlPref=Adruk+10-Pref
Writed	dd	21
FGH:
 		mov	EBP,@B
;[Обращение  N16inASCII ECX,SPSTR,NUMBER] из регистра ECX   строка символов SPSTR 16-ого числа
						;aдрес прерванного места в ECX
		N!16inASCII	EBP,Adruk,8
	invoke	GetStdHandle, STD_OUTPUT_HANDLE
		mov	[AK],eax
		
		mov	EAX,[AK]
		mov	EDX,DlPref		;длина сообщения
		\}
	invoke	WriteConsole,eax,Pref,edx,Writed,0
ВосстановилиРегистры   EBP,EAX,ECX,EDX  ;3
	invoke	ExitProcess, 1
}
;******************  Старый вариант P!rAdrStop 	реально сейчас 	P!rAdr
;******************************  2  ********************************************
;+++++++++++++++++++++++++++++++++    Получение ASCII кода  символов  16-ых чисел для регистра 32 разрядного
; 		[Обращение  N16inASCII	EAX,buffer,8] из регистра EAX   строка символов buffer 16-ого числа
MACRO	N!16inASCII	P0,P1,P2			;новый макрос перевода
	{		local	spisim
 УпряталиРегистры EAX,EBX,ECX,EDI
		mov	EDI,P1				;SPSTR  куда пишем символы
		mov	ebx,P0				;где находится адрес
		mov	ECX,P2				;08h	8   16-ичных чисел  в EBX
@@:								;PUSH	ESI
		rol	ebx,4
		mov	al,bl
		and	EAX,0Fh
		mov	al,[CS:spisim+EAX]
		stosb					; запись символов в буфер  SPSTR
	loop	@B
		mov	ax,0A0Dh			;+2 символа перевода строки
		stosw
  ВосстановилиРегистры  EAX,EBX,ECX,EDI	;2
	jmp	spisim+16				; передача с обходом   ENDSPIS
spisim:
	db	"0123456789ABCDEF"	;ASCII -символы чисел
	}							;--------Получение ASCII кода числа символов ENDSPIS:
;+***************************************   Конец   N16inASCII
;****************08.09.2019***********  макрос    P!rTxtAdr печати текста и содержимого   EBP******
;Добавили параметр   AKN -адрес ячейки, где фиксируется номер канала. Через запятую идет текст и печатается
;содержимое в регистре EBP
;	P!rTxtAdr		TEXT		;ТЕКСТ из 1- 4 слов и распечатывается адрес выхода из программы
; P!rTxtAdr	AKN,=BalarirevNE	TEST	C!MPabJm  macros     (по умолчанию +  ASCIIадрес  регистра EBP)
;P!rTxtAdr	AKN,=BalarirevNE					+ASCIIадрес
;P!rTxtAdr	AKN,=BalarirevNE	TEST				+ASCIIадрес
;P!rTxtAdr		=BalarirevNE	TEST	C!MPabJm	+ASCIIадрес
;масro	N!16inASCII	EBP,Adruk,8
;	УпряталиРегистры	EAX,EBX,ECX,EDX,ESI,EDI
;	ВостановилиРегистры   EAX,EBX,ECX,EDX,ESI,EDI
;Используем процедуры GetStdHandle, STD_OUTPUT_HANDLE
;		WriteConsole,eax,Pref,edx,Writed,0
;		invoke	ExitProcess, 1
;***************************************************************************
macro	P!rTxtAdr		TEX
{
	local	Adruk,s_psi,P_ref,FGH,Writed
@@:
	УпряталиРегистры	EAX,EBX,ECX,EDX,ESI,EDI
	jmp	FGH		;Не сработала, по адресу в EBP:   Печать сообщения с расп. адреса Выход
P_ref 	db	" "
common match AK ==TEXT,TEX
	\{
\PRZN	equ	0
	common match  TXT TXT1 TXT2 TXT3,\TEXT
	\\{
	db	" "\\#\\`TXT
	db	" "\\#\\`TXT1
	db	" "\\#\\`TXT2
	db	" "\\#\\`TXT3
\\PRZN	equ	1
	\\}
		if	\\PRZN eq 0
	common match  TXT TXT1 TXT2,\TEXT
\\{
	db	" "\\#\\`TXT
	db	" "\\#\\`TXT1
	db	" "\\#\\`TXT2
\\PRZN	equ	1
\\}
			if	\\PRZN eq 0
	common match  TXT TXT1,\TEXT
\\{
	db	" "\\#\\`TXT
	db	" "\\#\\`TXT1
\\PRZN	equ	1
\\}
				if	\\PRZN eq 0
	match  TXT,TEXT
\\{
	db	" "\\#\\`TXT
\\}
				end if
			end if
		end if
	db	" "
Adruk	db	10	dup	('!')	; под адрес останова 8 16-ных чисел
s_psi	db	0
;DlPref=spsi-Pref
Writed	dd	21
;Hconsl	dd	0
FGH:
;[Обращение  N16inASCII ECX,SPSTR,NUMBER] из регистра ECX   строка символов SPSTR 16-ого числа
						;aдрес прерванного места в ECX
		N!16inASCII	EBP,Adruk,8
		mov	EAX,[AK]
		and	EAX,-1
	JNE	@f
				invoke	GetStdHandle, STD_OUTPUT_HANDLE
				mov	[AK],eax
@@:
D_lPref=s_psi-P_ref
		mov	EDX,D_lPref
				;mov	eax,[Hconsl_d]		;handle consoleHconsl_d
	invoke	WriteConsole,eax,P_ref,edx,Writed,0
	\}
@@:
		ВосстановилиРегистры   EAX,EBX,ECX,EDX,ESI,EDI	;N
						;invoke	ExitProcess, 1
}
