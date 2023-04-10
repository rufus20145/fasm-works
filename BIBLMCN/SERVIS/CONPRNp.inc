;  Продолжение CONPRN   
;****************************  3    ****************
	macro	P!rTXTNUMBER	TEXT
{	local	Adruk,spsim,Pref,DlPref,FGH,Writed,Hconsl_d
@@:
	УпряталиРегистры	EBP,EAX,ECX,EDX	
;		mov	EBP,@B
	jmp	FGH		;Не сработало по адресу в EBP:   Печать сообщения с расп. адреса Выход 
Pref 	db	" "
	PRZN	equ	0
	common match  ==TXT TXT1 TXT2 TXT3,TEXT
\{
	db	" "\#\`TXT
	db	" "\#\`TXT1
	db	" "\#\`TXT2
	db	" "\#\`TXT3
	\PRZN	equ	1
	\}
	if	\PRZN eq 0
	common match  ==TXT TXT1 TXT2,TEXT
\{
	db	" "\#\`TXT
	db	" "\#\`TXT1
	db	" "\#\`TXT2
	\PRZN	equ	1
	\}
		if	\PRZN eq 0
	common match  ==TXT TXT1,TEXT
	\{
	db	" "\#\`TXT
	db	" "\#\`TXT1
	\PRZN	equ	1
	\}
			if	\PRZN eq 0	
	match  ==TXT,TEXT
	\{
	db	" "\#\`TXT
	\}
			end if	
		end if
	end if
	db	" "
Adruk	db	10	dup	('!')	; под адрес останова 8 16-ных чисел
spsim	db	0
Hconsl_d	dd	0	
DlPref=spsim-Pref
Writed	dd	21 
FGH:
;[Обращение  N16inASCII ECX,SPSTR,NUMBER] из регистра ECX   строка символов SPSTR 16-ого числа
						;aдрес прерванного места в ECX
		N!16inASCII	EBP,Adruk,8
	invoke	GetStdHandle, STD_OUTPUT_HANDLE
		mov	[Hconsl_d],eax
		
		mov	EAX,[Hconsl_d]
		mov	EDX,DlPref		;длина сообщения
	invoke	WriteConsole,eax,Pref,edx,Writed,0
	ВостановилиРегистры   EBP,EAX,ECX,EDX
}
;**********************************  4     *******************
	macro	P!rAdr	Hconsl,BufPrint,TEXT,adr		;TEXT="NE:A"
{			local	FGH,Pref
@@:
	УпряталиРегистры   EBP,EAX,ECX,ESI,EDI 
		if ~adrDll eq
		mov	EBP,@B			;если не указан адрес
		else
		mov	EBP,adr			;любой адрес связанный с меткой
		end if
	jmp	FGH					;Не сработало: Выход за пределы массива или это не 10-ые числа
Pref	db	TEXT
		db	0

FGH:
DlPref=FGH-Pref
	mov	ECX,DlPref			;Кол-во символов
	mov	ESI,Pref			;Адрес префикса
	mov	EDI,BufPrint		;Адрес буфера  перенос префиксного текста
@@:
	LODSB
	STOSB
	loop	@B
;[Обр.N16inASCII ECX,SPSTR,NUMBER] из рег.ECX строка символов SPSTR 16-ого числа, число символов
	N!16inASCII	EBP,BufPrint+DlPref,8
		mov	EDX,DlPref+10		;8 чисел+2(LF,CR)
		mov	eax,[Hconsl]		;handle console
	invoke	WriteConsole, eax,BufPrint, edx, Writed, 0
	ВосстановилиРегистры   EBP,EAX,ECX,ESI,EDI 
}
;**********************************<-<-<-P!rAdrInDll
