;********************************************
;			Оглавление  переключателей
;1 S!WITC						с проверкой на кол-во меток с индексом переключателя
;2 S!WITCH						самый короткий переключатель по индексу
;2R Перейти_по_переключателю 	Эквивалентно 2
;3 S!WITCA 						парсинг
;		Парсинги
; в файле SWITCH\PARS.inc
;4 S!WITCL							Эквивалентно 5	переключение по любому регистру
;5 S!WITCS							переключение по совпадению кода символа в памяти
;6 Если_это_совпадает_с_символом_то_перейти 	-синтаксическая форма~ S!WITCL
;7 Если_это_Символ_то_Перейти		~S!WITCS
;*********************************
;********************************* 4  ***********************************************
;S!WITCL	на регистре байтовом NMR сравнивается со с списком str1 при = переход str2
; Если не сравнилось, то переход FEND;Если не указан,то идем дальше, в том числе сравнение повторяется
;*********************************
	MACRO	S!WITCL	NMR,FEND,[str1,str2]		;переключение по совпадению кода символа
     {      common
	push EAX
		mov	al,NMR
		mov	ah,al				;ЕСЛИ 	 на AH значение для сравнения ТО сработает
	forward						; здесь выборка string по кол-ву параметров
		mov	ah,str1
		xor	ah,al				;совпал символ
	pop	EAX
	je	str2
	common
			if   ~FEND eq		;при плохом исходе-не совпал
	JMP	FEND
			else
			end if
    }
;*********************			;конец макроса
;***************************************************************
;****************************5****************
MACRO	S!WITCS	FEND,[str1,str2]		;переключение по совпадению кода символа в памяти
     {     common
	 local	SSMB,SJMP			;label
		УпряталиРегистры	EBX,ECX
		mov	bl,Rswtch			;		[RSWT]
		cmp	bl,Rsimb			;Проверка на не выход за пределы меток переключения
	JE	@F						;для обработки ошибок надо вст. EXITERROR EXBAD1
		mov	EBP,@F				;Фиксируем адрес останова
	P!rAdrStop	=BalarirevNE	S!WITCHS	NumbSim	NotEqu NumbJmp	;+ASCIIадрес
@@:
		xor	EBX,EBX
		mov	ECX,Rsimb			;количество символов
@@:
		mov	ah,[CS:SSMB+EBX]
		xor	ah,al				совпал символ
	je	@F						;GJMP
		inc	bl
	loop	@B
		ВосстановилиРегистры	EBX,ECX
	jmp	FEND
@@:
		shl	EBX,2				;EBX,2  через 4 байта адрес
		mov	EAX,EBX
		ВосстановилиРегистры	EBX,ECX
	jmp	[CS:SJMP+EAX]			;EBX
;************************
Rswtch = 0						;Счетчик числа переходов
Rsimb = 0
label	SSMB	byte
	forward
Rsimb = Rsimb+1
					if	str1 	eqtype ''
STRC 	equ	""#str1
					else
STRC	equ	str1
					end if
	db	STRC
	common
label	SJMP	dword	;name dword для32 разрядного адреса, для 64 pp адр. pword
	forward				; здесь выборка string по кол-ву параметров
Rswtch = Rswtch+1   	;local label В зависимости от кол-ва переменных накапл.счетчик
	dd	str2			;Формирование адресных констант для32 разрядного адреса
    }

;********************************синтаксическая часть*******************************
;Если_это_Совпадает_с_Символом_то_Перейти
;*********************   П Р И М Е Р
;Если_RGb_Совпадает_(с_Si_то_POINTi)\
;		?:=AL \
;(_S1  =>greater)(_S2 =>separator)(03Bh =>greater)(03Bh =>greater)\
 ( 01Bh  =>CMNINC )( 01Bh  =>CMNINC ) (01Dh  =>separator)\
;	=>ExiPloxo
;*****************************  6 *************	Если_это_Совпадает_с_Символом_то_Перейти
	MACRO	Если_это_Совпадает_с_Символом_то_Перейти	ARG
{
list equ
Pstr2 equ
Pstr1 equ
Pstr0 equ
Pk	equ										;Print!afall	ARG
common	match	=?=:==RG  =( S1 ==>P1 =) =( S2 ==>P2 =)  ==>PF,ARG
\{
	\spisadd	list,\RG					;занесли регистр параметр
	\spisadd	list,\PF					;занесли куда перейти  параметр
	\spisadd	list,\S1					;занесли 1 к=1 какой символ
	\spisadd	list,\P1					;занесли 2 к=1 куда перейти по совпадению
	\spisadd	list,\S2					;занесли 1 к=2 какой символ
											;Print!afall	S2
											;display ' <0>',0Dh,0Ah
											;Print!afall	\PF
											;Print!afall   \P2
											;display ' <1>',0Dh,0Ah
	stradd	Pk,\P2							;Pk	equ	\P2
;*****************************************
			repeat 1
											;\Print!afall  Pk
											;\display ' Pk 2',0Dh,0Ah

	\L!EXM	Pk,Pstr2,Pstr1,Pstr0			;match P$i =) =( S$i == P$k,\Pk	match P!i =) =( S!i == P!k,\\P$k

											;\Print!afall   Pstr2
											;\display ' Pstr2 3.0',0Dh,0Ah
			if	~ Pstr2	eq
			\spisadd	list,Pstr0			;занесли 1 параметр
			\spisadd	list,Pstr1			;занесли 1 параметр
			stradd	Pk,Pstr2
			else
											;\Print!afall   Pk
											;\display '  Pk 4.0 break',0Dh,0Ah
											;\Print!afall   list
											;\display	0Dh,0Ah
											;\display ' 5.0',0Dh,0Ah
		break								;выход за repeat   3 4 парсинга
			end if
	\L!EXM	Pk,Pstr2,Pstr1,Pstr0	;match P$i =) =( S$i == P$k,\Pk	match P!i =) =( S!i == P!k,\\P$k
											;\Print!afall   Pk
											;\display ' Pk 3.1',0Dh,0Ah
			if	~ Pstr2	eq
			\spisadd	list,Pstr0			;занесли 1 параметр
			\spisadd	list,Pstr1			;занесли 1 параметр
			stradd	Pk,Pstr2
											;\Print!afall   list
											;\display	0Dh,0Ah
											;\display ' 4.1',0Dh,0Ah
			else
											;\Print!afall   Pk
											;\display '  Pk 5.1 break',0Dh,0Ah
											;\Print!afall   list
											;\display	0Dh,0Ah
											;\display ' 6.1',0Dh,0Ah
		break								;выход за repeat   5 или 6 парсинга
			end if
;*****************************************************
	\L!EXM	Pk,Pstr2,Pstr1,Pstr0			;match P$i =) =( S$i == P$k,\Pk	match P!i =) =( S!i == P!k,\\P$k
											;\Print!afall   Pk
											;\display ' Pk 3.2',0Dh,0Ah
			if	~ Pstr2	eq
			\spisadd	list,Pstr0			;занесли 1 параметр
			\spisadd	list,Pstr1			;занесли 1 параметр
			stradd	Pk,Pstr2
											;\Print!afall   list
											;\display	0Dh,0Ah
											;\display ' 4.2',0Dh,0Ah
			else
											;\Print!afall   Pk
											;\display '  Pk 5.2 break',0Dh,0Ah
											;\Print!afall   list
											;\display	0Dh,0Ah
											;\display ' 6.2',0Dh,0Ah
		break								;выход за repeat   7 или 8 парсинга
			end if
;********************************************
	\L!EXM	Pk,Pstr2,Pstr1,Pstr0	;match P$i =) =( S$i == P$k,\Pk	match P!i =) =( S!i == P!k,\\P$k
											;\Print!afall   Pk
											;\display ' Pk 3.2',0Dh,0Ah
			if	~ Pstr2	eq
			\spisadd	list,Pstr0			;занесли 1 параметр
			\spisadd	list,Pstr1			;занесли 1 параметр
			stradd	Pk,Pstr2
											;\Print!afall   list
											;\display	0Dh,0Ah
											;\display ' 4.2',0Dh,0Ah
			else
											;\Print!afall   Pk
											;\display '  Pk 5.2 break',0Dh,0Ah
											;\Print!afall   list
											;\display	0Dh,0Ah
											;\display ' 6.2',0Dh,0Ah
		break								;выход за repeat   9 или 10 парсинга
			end if
;*****************************************************
	\L!EXM	Pk,Pstr2,Pstr1,Pstr0			;match P$i =) =( S$i == P$k,\Pk	match P!i =) =( S!i == P!k,\\P$k
											;\Print!afall   Pk
											;\display ' Pk 3.2',0Dh,0Ah
			if	~ Pstr2	eq
			\spisadd	list,Pstr0			;занесли 1 параметр
			\spisadd	list,Pstr1			;занесли 1 параметр
			stradd	Pk,Pstr2
											;\Print!afall   list
											;\display	0Dh,0Ah
											;\display ' 4.2',0Dh,0Ah
			else
											;\Print!afall   Pk
											;\display '  Pk 5.2 break',0Dh,0Ah
											;\Print!afall   list
											;\display	0Dh,0Ah
											;\display ' 6.2',0Dh,0Ah
		break								;выход за repeat   11 или 12 парсинга
			end if
;********************************************
	\L!EXM	Pk,Pstr2,Pstr1,Pstr0	;match P$i =) =( S$i == P$k,\Pk	match P!i =) =( S!i == P!k,\\P$k
											;\Print!afall   Pk
											;\display ' Pk 3.2',0Dh,0Ah
			if	~ Pstr2	eq
			\spisadd	list,Pstr0				;занесли 1 параметр
			\spisadd	list,Pstr1				;занесли 1 параметр
			stradd	Pk,Pstr2
												;\Print!afall   list
												;\display	0Dh,0Ah
												;\display ' 4.2',0Dh,0Ah
			else
												;\Print!afall   Pk
												;\display '  Pk 5.2 break',0Dh,0Ah
												;\Print!afall   list
												;\display	0Dh,0Ah
												;\display ' 6.2',0Dh,0Ah
		break									;выход за repeat   13 или 14 парсинга
			end if
;********************************************
	\L!EXM	Pk,Pstr2,Pstr1,Pstr0	;match P$i =) =( S$i == P$k,\Pk	match P!i =) =( S!i == P!k,\\P$k
												;\Print!afall   Pk
												;\display ' Pk 3.2',0Dh,0Ah
			if	~ Pstr2	eq
			\spisadd	list,Pstr0				;занесли 1 параметр
			\spisadd	list,Pstr1				;занесли 1 параметр
			stradd	Pk,Pstr2
												;\Print!afall   list
												;\display	0Dh,0Ah
												;\display ' 4.2',0Dh,0Ah
			else
												;\Print!afall   Pk
												;\display '  Pk 5.2 break',0Dh,0Ah
												;\Print!afall   list
												;\display	0Dh,0Ah
												;\display ' 6.2',0Dh,0Ah
		break									;выход за repeat   15 или 16 парсинга
			end if
;********************************************
	\L!EXM	Pk,Pstr2,Pstr1,Pstr0	;match P$i =) =( S$i == P$k,\Pk	match P!i =) =( S!i == P!k,\\P$k
											;\Print!afall   Pk
											;\display ' Pk 3.2',0Dh,0Ah
			if	~ Pstr2	eq
			\spisadd	list,Pstr0			;занесли 1 параметр
			\spisadd	list,Pstr1			;занесли 1 параметр
			stradd	Pk,Pstr2
											;\Print!afall   list
											;\display	0Dh,0Ah
											;\display ' 4.2',0Dh,0Ah
			else
					\Print!afall   Pk
					\display '  Pk 5.2 break',0Dh,0Ah

					\Print!afall   list
					\display	0Dh,0Ah
					\display ' 6.2',0Dh,0Ah
		break									;выход за repeat   17 или 18 парсинга
			end if
;********************************************
	\L!EXM	Pk,Pstr2,Pstr1,Pstr0		;match P$i =) =( S$i == P$k,\Pk	match P!i =) =( S!i == P!k,\\P$k
												;\Print!afall   Pk
												;\display ' Pk 3.2',0Dh,0Ah
			if	~ Pstr2	eq
			\spisadd	list,Pstr0				;занесли 1 параметр
			\spisadd	list,Pstr1				;занесли 1 параметр
			stradd	Pk,Pstr2
												;\Print!afall   list
												;\display	0Dh,0Ah
												;\display ' 4.2',0Dh,0Ah
			else
									\Print!afall   Pk
									\display '  Pk 5.2 break',0Dh,0Ah

												;\Print!afall   list
												;\display	0Dh,0Ah
					;\display ' 6.2',0Dh,0Ah
		break									;выход за repeat   19 или 20 парсинга
							\Print!Rfall   "Выход за 19-20 параметров"
							\display	0Dh,0Ah
		end if
;********************************************
		end repeat
		\spisadd	list,Pk						;занесли 1 параметр
												;\Print!afall   list
												;\display ' Pk 7.1',0Dh,0Ah
	match params, list \\{ S!WITCL params \\}	;Обращение к макросу S!WITCS т.к. list единая строка
												;\Print!afall   list
												;\display ' 7.2',0Dh,0Ah
\}
;*************************  7 *****************	Если_это_Символ_то_Перейти
	MACRO	Если_это_Символ_то_Перейти	ARG
{common	match	=?=:==RG  =(S1 ==>P1=) =(S2 ==>P2 =)  =>>PF,ARG
\{
Print!afall	\P2
display	0Dh,0Ah
\NMRuu	equ	1
match aww==ww,\P2
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
											;Print!afall   \NMRuu
		S!WITCS	\RG,\PF,\S1,\P1,\S2,\P2
end if
\}
common	match	=?=:==RG =(S1 ==>P1=) =(S2 ==>P2 =) =(S3 ==>P3=)  =>>PF,ARG
\{
Print!afall	\P3
display	0Dh,0Ah
	S!WITCS	\RG,\PF,\S1,\P1,\S2,\P2,\S3,\P3
\}
;***************************************************************}
