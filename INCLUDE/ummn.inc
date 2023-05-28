;МАКРОСЫ для UMMN.asm  => ummn.inc
;********************
;1 ВыделиАмплитуды	arg
;2 Собери_WAV		arg
;3 РазделСтроки		arg
;4 ДайКлючНаПечать
;5 ДайКлючНаПрием
;6 ЗапросПутиК_каталогу	arg
;7 ДописалСлеш arg
;	ДописалСимвол arg
;8 Запрос_КомандыЕсли1Слово
;9 ПоТекущему_Установить
;10ДополниПутьИменемФла
;11Дублировать					Дублировать без фиксации кол-ва отдублтрованного
;********************	1
;12ДайВиртПамять
;13D_ДайДлинуФайла
;14Скоректируй_Тип_ФайлаСмениУказатель
;15Дай_файла_Ключ\
;16УстановиУказФайла
;17ВыдайСообщение   $С_устройства$=Hconsl
;18ПрочтиИнформацию $С_устройствоhandle$=Hin
;19Перенести		$Из_буфераПриематекста$=BUFpos
;20ЧтениeФайла
;21ЗаписьФайла
;+++++++++++++++++++++++++  ПРИМЕР
;	Выдели_из_WAV_Амплитуды
;		$OutАдр_фла_записи$=pMemz\
;		$InАдр_фла_чтения$=pMem\
;		$InДли_фла_чтения=FlSizeL\
;		$OutДли_инф_с_аплитудамиEAX$=NSIGN\
;		$OutНачало_аплитуд$=pMemS\
;		$OutДлина_файла_записи$=ECX
;+++++++++++++++++++++++++
MACRO ВыделиАмплитуды	arg
{common match A1==P1 B_1==P2 C1==P3 D1==P4 E1==P5 F1==P6 G1===> ADR1 G2===>,arg
	\{
		Print!Rfall   'ВыделиАмплитуды вошли'
		display 0Dh,0ah
		mov	EDI,[\P1]						;[pMemz]			Адрес начала файла записи
		mov	ESI,[\P2]						;[pMem]				;Адрес начала файла чтения
if  \P3  eqtype  EAX
					mov	ecx,\P3				; Длина информации всего файла
else
					mov	ecx,[\P3]			; общая длина полученного файла
end if										;Длина файла чтения
			invoke	SLWAV,edi,esi,ecx		;[pMemz],[pMem],[FlSizeL]
if  \P4  eqtype  EAX
					POP	\P4					;ECX   Длина информации всего файла
else
					pop	[\P4]				;EAX - общая длина полученного файла
end if

if  \P5  eqtype  EAX
					POP	\P5					;ECX		; Длина информации всего файла
else
					pop	[\P5]				;EAX - общая длина полученного файла
end if

if  \P6  eqtype  EAX
					POP	\P6					; Длина информации всего файла
else
					pop	[\P6]				;EAX - общая длина полученного файла
end if
		cmp	ECX,0FFFFFFFFh
	jne	\ADR1
	\}
common match A1==P1 B_1==P2 C1==P3 D1==P4 E1==P5 F1==P6 G1===> ADR1 G2===>ADR2,arg
	\{
		;Print!afall   \P1
		;display 0Dh,0ah
		mov	EDI,[\P1]						;[pMemz]				;Адрес начала файла записи
		mov	ESI,[\P2]						;[pMem]				;Адрес начала файла чтения
if  \P3  eqtype  EAX
					mov	ecx,\P3				; Длина информации всего файла
else
					mov	ecx,[\P3]			;EAX - общая длина полученного файла
end if										;Длина файла чтения
			invoke	SLWAV,edi,esi,ecx		;[pMemz],[pMem],[FlSizeL]
if  \P4  eqtype  EAX
					POP	\P4					;ECX		; Длина информации всего файла
else
					pop	[\P4]				;EAX - общая длина полученного файла
end if

if  \P5  eqtype  EAX
					POP	\P5					;ECX		; Длина информации всего файла
else
					pop	[\P5]				;EAX - общая длина полученного файла
end if

if  \P6  eqtype  EAX
					POP	\P6					; Длина информации всего файла
else
					pop	[\P6]				;EAX - общая длина полученного файла
end if
		cmp	ECX,0FFFFFFFFh
	jne	\ADR1
		if	~\ADR2	eq						;Плохой ответ
@@:
				MOV		ebp,@B
	jmp	\ADR2
		else
		end if
	\}
}
;-------------------------------------
;********************	2
;*************************************************************
;			Собери_WAV
;		InАдр_ф_ла_зп=pMem InАдр_фла_чт=pMemz InДли_фла_чт=ECX\
;		OutНачало_выходного=pMem OutНачало_входного=pMemz OutДлина_файла_записиREG=ECX\
;			КО_ХорошоECX=>WRITZm1		КО_ПлохоECX_0FFFFFFFF=>
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MACRO Собери_WAV	arg
{common match A1==P1 B_1==P2 C1==P3 D1==P4 E1==P5 F1==P6 G1===> ADR1 G2===>,arg
	\{
		Print!Rfall		"Собери_WAV вошли "
		;Print!afall   \P6
		display 0Dh,0ah
		mov	EDI,[\P1]					;[pMemz]				;Адрес начала файла записи
		mov	ESI,[\P2]					;[pMem]				;Адрес начала файла чтения
if  \P3  eqtype  EAX
			MOV ECX,\P3				; Длина информации всего файла
else
			MOV ECX,[\P3]			;EAX - общая длина полученного файла
end if										;Длина файла чтения
	invoke	LPWAV,edi,esi,ecx		;[pMemz],[pMem],[FlSizeL]
if  \P4  eqtype  EAX
					POP	\P4				;ECX		; Длина информации всего файла
else
					pop	[\P4]			;EAX - общая длина полученного файла
end if

if  \P5  eqtype  EAX
					POP	\P5				;ECX		; Длина информации всего файла
else
					pop	[\P5]			;EAX - общая длина полученного файла
end if

if  \P6  eqtype  EAX
					POP	\P6				; Длина информации всего файла
else
					pop	[\P6]			;EAX - общая длина полученного файла
end if
		cmp	ECX,0FFFFFFFFh
	jne	\ADR1
	\}

common match A1==P1 B_1==P2 C1==P3 D1==P4 E1==P5 F1==P6 G1== => ADR1 G2== =>ADR2,arg
	\{
		;Print!afall   \P1
		display 0Dh,0ah
		mov	EDI,[\P1]							;[pMemz]	Адрес начала файла записи
		mov	ESI,[\P2]							;[pMem]		Адрес начала файла чтения
if  \P3  eqtype  EAX
					MOV ECX,\P3				; Длина информации всего файла
else
					MOV ECX,[\P3]			;EAX - общая длина полученного файла
end if										;Длина файла чтения
			invoke	LPWAV,edi,esi,ecx		;[pMemz],[pMem],[FlSizeL]
if  \P4  eqtype  EAX
						POP	\P4					; Длина информации всего файла
else
						pop	[\P4]				;EAX - общая длина полученного файла
end if
if  \P5  eqtype  EAX
						POP	\P5					; Длина информации всего файла
else
						pop	[\P5]				;EAX - общая длина полученного файла
end if
if  \P6  eqtype  EAX
						POP	\P6					; Длина информации всего файла
else
						pop	[\P6]				;EAX - общая длина полученного файла
end if
@@:
				MOV		ebp,@B
		and		ECX,0FFFFFFFFh
	je	\ADR2
		cmp	ECX,0FFFFFFFFh
	jne	\ADR1
		if	~\ADR2	eq
@@:
				MOV		ebp,@B
	jmp	\ADR2
		else
		end if
	\}
}
;------------------------------------------------
;********************	3
;АдрСод_строки сОДЕРЖИМОЕ строки раскладывается на слова по АдресСпискаСлов
;с учетом символов двух разделителей (обычно пробел и Sim_TAB)\
;с подсчетом числа в СчетчикКолваСлов, а длина слова в байтах \
;кратна 2 0-1б 1-2б 2-4б 3-8б 4-16б 5-32б
;РазделСтроки	АдрСод_строки=EAX	СчетчикКолваСлов=S_JMP	АдресСпискаСлов=P_word\
;				Делитель1=Sim_TAB Делитель2=020h Количество2n=5
;++++++++++++++++++++++++++++++++++++
MACRO РазделСтроки	arg
{	local	C_word,PRbuff,rtOut
	УпряталиРегистры  	EAX,ECX,EDX,ESI,EDI
	common match A1==P1 B_1==P_2 C1==P3 D1==P4 E1==P5 F1==P6,arg
	\{
	;Print!afall   \P1
		;display 0Dh,0ah
		;Print!afall   [\P_2]
		;display 0Dh,0ah
		;Print!afall   \P3
		;display 0Dh,0ah
		;Print!afall   \P4
		;display 0Dh,0ah
	;display	"*****************"
	;display 0Dh,0ah
		mov	esi,\P1					;eax        			; address command line
;Повторяющаяся
C_word:								;цикл по словам
		xor	ecx,ecx         		; zero ecx & use as counter
		mov	edi,\P3					;P_word	 в начале номер слова нулевой
PRbuff:
		lodsb						; считываем байт из address command line
      	cmp	al, 0					;признак конца строки символов
	je 	rtOut						;всё исчерпали строку ==  Выход
		cmp al,\P4					;Sim_TAB 				; tab  меняем
	jne @F							; не tab
      	mov al,\P5					;020h	 				;заменяем пробелом
@@:
		cmp	al,\P5					;020h		 Это пробел
	je	@F							;nprob						; Это не пробел
		inc ecx						;Это не пробел
      	stosb						; запись символов в буфера buffer а затем Nfile
	jmp	PRbuff						;следующий символ дл пробелов
;**********
@@:
		mov	al,0
		stosb						; запись символа 0 в слово
		inc	[\P_2]					;[S_JMP]	увеличиваем для следующего слова
		movzx	EDX,[\P_2]
		shl	EDX,\P6
		mov	edi,\P3
		add	edi,edx
		dec	edi
		mov	[EDI],ECX				;счетчик символов по словам Далее должна идти 2 слово и т.д.

;++++++++++++++++++		Крутимся на пробелах и не суммируем их в общем числе
@@:
		lodsb						;Чтение следующего символа  ОБРАБОТКА ПРОБЕЛОВ
		cmp al,\P4					;Sim_TAB 				; tab  меняем
	je @B							; не tab
		cmp	al,\P5					;020h;inc	ecx		; increment counter счетчик символов
	je	@B							;пропускаем пробелы, если их несколько
		cmp	al,0Dh					;0Dh
	je	@B							;пропускаем служебный
		cmp	al,0Ah					;0Ah
	je	@B							;пропускаем служебный
		cmp	al,0					;признак конца строки символов
	je	rtOut						;нет пробела сразу 0
		xor	ecx,ecx
		movzx	EDX,[\P_2]			;[S_JMP]	Номер слова c 0
		shl	EDX,\P6					;по для 32 байта это 5 для 16=4 8=3 4=2 2=1 (сдвиг)
		mov	edi,\P3					;P_word	куда перзаписываем 1-ую часть команд строки
		add	edi,edx					;Сдвигаемся по словам
		inc ecx						;Это не пробел
      	stosb						;запись символа уже в новый буфер
	jmp	PRbuff						;следующее слово в строке
;*********************            Слово и пробелы до следующего слова прочитаны
rtOut:			        			; increment counter счетчик символов								;mov	al,0h			; это конец имени файла
      	stosb       				; write last byte  0
;************************
		inc	[\P_2]					;[S_JMP]	увеличиваем для следующего слова
		movzx	EDX,[\P_2]
		shl	EDX,\P6
		mov	edi,\P3
		add	edi,edx
		dec	edi
		mov	[EDI],ECX				;счетчик симв. по словам Далее должна идти 2 слово и т.д.
		\}
	ВосстановилиРегистры	EAX,ECX,EDX,ESI,EDI
}
;********************	4
;****************************************************************************
;	1.Запрашиваем короткий ключ ( HANDLE)  консоли для использования в распечатках
;		ДайКлючНаПечать	Hconsl
;	STD_OUTPUT_HANDLE   ==>	[GetStdHandle]  ==>Hconsl
;+++++++++++++++++++++++++++++++++++++++
MACRO ДайКлючНаПечать	P1
{
	invoke	GetStdHandle, STD_OUTPUT_HANDLE
		mov	[P1],eax				;handle консоли
}
;********************	5
;***************************************
;	ДайКлючНаПрием	Hin
;+++++++++++++++++++++++++++++++++++++++
MACRO ДайКлючНаПрием	P1
{
	invoke 	GetStdHandle, STD_INPUT_HANDLE
		mov [P1], eax					;handle  приема с консоли
}
;********************	6
;***************************************
;	EDX=Bufcat & 256 ==> [GetCurrentDirectory]  ==> [Bufcat] = c:\XXX\YYY & EAX(кол-во символов)
;					выбор имени файла из командной строки
;	ЗапросПутиК_каталогу	Bufcat,Bufcat_r\
;		ЗапросПутиК_каталогу\
;					Запиши_послеУстан_в_EDI=Bufcat\
;					ЕгоДлина=Bufcat_r\
;							Ответ_В_EAX=RNsim\
;			ПереходХорошо=>ADR1		УходПлохо=>ADR2
;+++++++++++++++++++++++++++++++++++++++
MACRO ЗапросПутиК_каталогу	arg
{
	common match A1==P1 B_1==P_2 C1==P3 D1== =>ADR1 E1== =>ADR2,arg
	\{
	Print!Rfall  "ЗапросПути ="
	Print!afall	\P3
					display 13,10
			mov	EDI,\P1 							;Bufcat адрес буфера с путем к ТЕКУЩЕМУ каталогу файлов
	invoke	GetCurrentDirectory,\P_2,EDI			;Bufcat_r запрос пути к файлам
			mov	[\P3],EAX							;Длина строки символов пути к ФАЙЛАМ
			cmp	EAX,-1								;EAX
		if	~\ADR2	eq	0
	jne	\ADR2
		else
	JMP	@F											;no mist
		end	if
			mov	EBP,@F
			JMP	\ADR1								;EXITER		Пока не обрабатываем
@@:
	\}
}
;********************	7
;***************************************
;ДописалСлешВ_путьФиксВнегоУказ  [RNsim]
;ДописалСлеш	$InПо_АдресуИмениПути$=Bufcat
; 				$InПо_Указателю_на_конец_строки$=RNsim
;				$OutФиксируем_Новый_Указатель_в$=RNsim
;+++++++++++++++++++++++++++++++++++++++
MACRO ДописалСлеш	arg
{common match A1==P1 B_1==P2 C1==P3,arg
	\{
	push	EDI
	mov	EDI,\P1 							;Bufcat адрес буфера с путем к ТЕКУЩЕМУ каталогу файлов
	add	EDI,[\P2]							;EAX

	mov	al,"\"
	stosb									;записываем \
	mov	EDI,[\P2]
	inc	EDI
	mov	[\P3],EDI						;mov [RNsim],EDI	Кол-во сивмолов в строке, где записан путь
	POP		EDI
	\}
}
;***************************************
;ДописалСимвол	$InПо_АдресуИмениПути$=Bufcat
; 				$InПо_Указателю_на_конец_строки$=RNsim
;				$InСимвол$=Type_T
;				$OutФиксируем_Новый_Указатель_в$=RNsim
;+++++++++++++++++++++++++++++++++++++++
MACRO ДописалСимвол	arg
{common match A1==P1 B_1==P2  C1==P3 D1==P4,arg
	\{
	push	EDI
	mov	EDI,\P1 							;Bufcat адрес буфера с путем к ТЕКУЩЕМУ каталогу файлов
	add	EDI,[\P2]							;EAX
	mov	al,	\P3								;указанный символ через SIMBOL equ " "  например "\"
	stosb									;записываем
	mov	EDI,[\P2]
	inc	EDI
	mov	[\P4],EDI						;mov [RNsim],EDI	Кол-во сивмолов в строке, где записан путь
	POP		EDI
	\}
}
;********************	8
;***************************************
;		==>    [ GetCommandLine  ]  ==> EAX=ADR_CommandLine
;			     	Запрос_КомандыЕсли1Слово\
;						Уходим =>NOcline
;+++++++++++++++++++++++++++++++++++++++
   MACRO  	Запрос_КомандыЕсли1Слово  arg
{    		common match D1 == =>ADR1,arg
	\{
		invoke GetCommandLine		;Запрос командной  строки при запуске программы MMN T0001.txt
		mov	ECX,10  				;Если нет 2 части стандартное кол-во символов =10
		mov	ESI,Nfile				;Если нет 2 части
		cmp	eax,1					;если нет 2 командной строки
	je	\ADR1						;NOcline Открываем стандартное имя файла N00001.txt
	\}
}
;************************ПОКА НЕ ИСПОЛЬЗОВАЛОСЬ***************
;		==>    [ GetCommandLine  ]  ==> EAX=ADR_CommandLine
;			     	Запрос_Командной_строки \
;						$ИмяФайла_В_ESI_$=Nfil\
;						$ДлинаИмениФайла_В_ECX$=10\
;						$Если_Одно_СловоУходим$ =>NOcline\
;						$ЕслиДваСлова_Уходим$	=>(пусто дальше) МЕТКА
;+++++++++++++++++++++++++++++++++++++++
MACRO 	Запрос_Командной_строки  arg
{    		common match D1 == =>ADR1	D2 == =>ADR2,arg
	\{
	invoke GetCommandLine			;Запрос командной  строки при запуске программы MMN T1.txt
		mov	ECX,10  				;Если нет 2 части стандартное кол-во символов =10
		mov	ESI,Nfile				;Если нет 2 части
		cmp	eax,1					;если нет 2 командной строки
	je	\ADR1						;NOcline Открываем стандартное имя файла N00001.txt
;ВСТАВИТЬ ОПРЕДЕЛЕНИЕ Nfile:=ИМЕНИ ФАЙЛА И TCX=ДЛИНЫ СТРОКИ
			if	~\ADR2	eq			;Если нет метки двигаемся дальше
@@:
	jmp	\ADR2						;Иначе переход
		else
		end if
	\}
}
;********************	9
;***************************************
;		ПоТекущему_Установить\
;								InСчетчикуСлов=T_Word\
; 								InИ_адресуСписка=P_word\
;								InСдвигСучетомБуф=5\
;								OutАдрес_начала_строки=AdrN\
;						 		OutКол_воCимволов_в_ней=AdrN_L\
;							ЕслиКолвоНоль => EXITER
MACRO ПоТекущему_Установить	arg
{
		common match A1==P1 B_1==P2 C1==P3 E1==P4 S1==P5 D1== =>ADR ,arg
	\{	УпряталиРегистры	EAX,EDX,ESI
		movzx	EAX,[\P1]			;[T_Word]Номер слова c 0 это имя запущенной программы
		mov		EDX,EAX				;ECX,EAX Запоминаем Номер слова
		inc	EAX						;Берем следующее относительно его -1 число байт тек.
		shl	EAX,\P3					;через 32 байта  1-2 2-4 3-8 4-16 5-32
		mov	ESI,\P2					;mov  ESI,P_word Список начинается в P_word	куда перзаписываем 1-ую часть команд строки
		add	eax,ESI					;esi Начало текста из команд строки
		dec	eax						;-1 относительно последующего Указатель на число байт в EDX
		shl	EDX,\P3					;shl ECX,	через 32 байта  1-2 2-4 3-8 4-16 5-32
		add	ESI,EDX					;add ESI,ECX Формируем Указатель на текст
;Результат установления Адреса и Длины Команды в байтах
		mov		[\P4],ESI
		movzx	EDX,byte [EAX]		;movzx	ECX,byte [EDX]	Число байт в тексте
		mov		[\P5],EDX
		cmp 	dl,0				;Если количество =0,то ошибка
		ВосстановилиРегистры	EAX,EDX,ESI
	jne	@F
						mov	EBP,@F
					JMP	\ADR			;EXITER
@@:
	\}
}
;********************	10
;***************************************
;	ДополниПутьИменемФла	$ИмяФайла$=V_File\
;							$Адрес_ИмениПути_к_файлам$=Bufcat\
;							$ФиксируемУказательЗаКонцом_в$=RNsim\
;							$InДлинаИмениФайла$=NBUF\
;							$ИтоговаяДлинаПути$=Cdlina
;++++++++++++++++++++++
MACRO ДополниПутьИменемФла	arg
{					УпряталиРегистры 		ECX,ESI,EDI
			common match A0==P1 A1==P2 B_1==P3 C1==P4 D1==P5,arg
	\{
				Print!Rfall  "Параметр из ДополниПутьИменемФла  ="
				Print!afall	\P5
					display 13,10
		mov	ESI,\P1				;Исходная информация
							;dec	ESI					;добавляем T к имени АДРЕС НА 1 МЕНЬШЕ
		mov	EDI,P2				;В  Bufcat будем дописывать имя файла
		mov	ECX,[\P3]			;номер символа после /
		add	EDI,ECX				;Будет Указатель на последнею
		add	ECX,[\P4]			;номер символа после /+ колво символов в имени файла
		mov	[\P5],ECX			;[Cdlina]кол-во символов в пути+имени файла
		mov	ECX,[\P4]
							;inc	ecx					;Т.К. добавляем T к имени
		rep	movsb				;Заполнение Bufcat именем файла
					ВосстановилиРегистры 	ECX,ESI,EDI
	\}
}
;-----------------------------------
;********************	11
;***************************************
;*****************************	19	********************
;	Дублировать\
;					$InИз_буфераПриема$=BUFpos\
;					$InВ_буфер_Имени$=V_File\
;					$InКоличество_байт_из_в_ячейке$=NBUF\
;					$OutФиксируемДлинуИмениФайла$=RNsim
;**************************************Добавляется в структуру(V_Name -(V_File) -	U_Name_r)
;---
MACRO Дублировать	arg
{
NMRuu	equ	1
	common match A1==P1	A2==P2	 A3== =[ P3 =] A4==P4,arg
	\{\NMRuu	equ	0

						УпряталиРегистры 		ECX,ESI,EDI

						mov	ECX,[\P3]
												Print!Rfall  "Дублировать с квадратными скобками ="
												Print!afall	\P3
												display 13,10
			mov	ESI,\P1
			mov	EDI,\P2
		rep movsb
			mov	ECX,[\P3]
			mov	[\P4],ECX						;RNsim
						ВосстановилиРегистры 	ECX,ESI,EDI
	\}
;Дублировать с учетом сдвига  в P3  и в P4=P4+P3
	if NMRuu eq 0

	else
common match A1==P1	A2==P2	 A3==P3 A4==P4,arg
	\{\NMRuu	equ	0

						УпряталиРегистры 		ECX,ESI,EDI
						mov	ECX,\P3
												Print!Rfall  "Дублировать ="
												Print!afall	\P3
												display 13,10
			mov	ESI,\P1
												;
			mov	EDI,\P2
			add	EDI,[\P4]
		rep movsb
			mov	ECX,\P3
			add	[\P4],ECX						;RNsim
						ВосстановилиРегистры 	ECX,ESI,EDI
	\}
end if
;*****************************
	if NMRuu eq 0

	else
	common match A1==P1	A2==P2	 A3==P3,arg
	\{\NMRuu	equ	0
												Print!Rfall  "ДублироватьБезФиксации ="
												Print!afall	\P3
												display 13,10
						УпряталиРегистры 		ECX,ESI,EDI
			mov	ECX,[\P3]
			mov	ESI,\P1
			mov	EDI,\P2
		rep movsb
						ВосстановилиРегистры 	ECX,ESI,EDI
	\}
	end if
;********************

}
;-----------------------------------
;**************************
;********************	12
;***************************************
;+++++++++++++++++++++++++   	Выделение виртуальной памяти
;		ДайВиртПамять	InАдресРазмера=FlSizeL	InДобавьИзАдеса=FlSizeL\
;		OutФиксАдресВиртПамяти=pMem Плохо=>EXITER
;L=65536 & MEM_COMMIT &PAGE_EXECUTE_READWRITE ==>    [VirtualAlloc]
;  ==>[pMem] =EAX (начало выделенной памяти)
;++++++++++++++++++++++++++++++++++++++
MACRO ДайВиртПамять	arg
{			common match A1==P1 B_1==P2 C1==P3 D_1==P4 Ad===>EXITERR,arg
	\{
		mov	eax,[\P1]						;[FlSizeL]
		add		EAX,[\P2]					;512	пока 2 Brakit a 16*2=32
		add		EAX,01FFFh					;ВРЕМЕННО
		mov		[\P4],EAX
	invoke	VirtualAlloc,0,eax,MEM_COMMIT,PAGE_EXECUTE_READWRITE
		mov	[\P3],eax						;[pMem] начало выделенной памяти pMem =10 00 00
      		test	eax,eax
         JNE @F
						mov	EBP,@F
				JMP	\EXITERR
@@:
 	\}
}
;-----------------------------------
;********************	13
;***************************************
;+++++++++++++++++++++++++
;	D_ДайДлинуФайла	InПоКлючу=haRead_T\
;						OutМладшиеВ=FlSizeL\
;						OutСтаршиеРазрядыВ=FlSizeH\
;						ПриFlSizeH_не_0 => EXITER
MACRO D_ДайДлинуФайла	arg
{			common match A1==P1 B_1==P2 C1==P3 Ad===>EXITERR,arg
	\{
     invoke	GetFileSize,[\P1],[\P2]
		mov	[\P2],eax					;22DF		Длина файла младшие 32 разряда
		xor	eax,0FFFFFFFFh
	jne @F								;Длина не определена
							mov	ebp,@F	;Есть старших разрядов размера файла
						JMP	\EXITERR		;Пока не обрабатываем
@@:
		mov	eax,[\P3]
 		test	eax,eax
		and		eax,0FFFFFFFFh
	je	@F								;Нет старших разрядов размера файла
							mov	ebp,@F	;Есть старших разрядов размера файла
						JMP	\EXITERR		;Пока не обрабатываем
@@:
 	\}
}
;-----------------------------------
;********************	14
;	Коректируй_Тип_Смени_на_След\
;	InТекТип_По_адресу=ASWORK 	InСледующий_через=7		ОжидаемыйТип=Type_T\
;	InНомер_Коррект_Символа_По_адресу=RNsim		InАдресуПути=Bufcat\
;	ЕслиТип_0 => EXITER
;
;+++++++++++++++++++++++++++++++++
		MACRO КоректируйТипСмениСлед	arg
{			common match A1==P1 B_1==P2 C1==P3 D_1==P4 E_2==P5 Ad===>EXITERR Ad1==>Norm,arg
	\{
		mov	ESI,[\P1]				;[ASWORK]
		lodsb						;БЕРЕМ 1 ИЗ списка через 8 на чтение T\N\S\U\K\Q\
		and	al,0FFh					;проверка на ноль
	je	\EXITERR
		ADD		ESI,\P2				;7 СЛЕДУЮЩЕЕ ИМЯ В ГРУППЕ ЧЕРЕЗ 8 БАЙТ 7 т.к. загрузили байт N
		mov	[\P1],ESI				;пЕРВЫЙ РАЗ УСТАНАВЛИВАЕМ [ASWORK] Адрес_начала_строки=ESI
		cmp	al,\P3					; восстановить  было "N"
	je	@F
					mov	EBP,@F
				JMP	\Norm			;Идем на проверку симметричной буквы
@@:
		mov	ESI,[\P4]				;[RNsim]	номер символа с началом имени файла
		mov	[\P5+ESI],al			;[Bufcat+ESI],al Вписываем первый символ (T)
	\}
}
;-----------------------------------
;********************	15
;	Дай_файла_Ключ\
;	In1АдресПути=Bufcat
;	$In2ИспользованиеКак$=GENERIC_READ\
;	$In3$=0\
;	$In4$=0\
;	$In5Статус$=OPEN_EXISTING\
;	In6=0\
;	$In7$=0\
;	$OutКлюч$=haRead_T
;	$Если_не_прошло$=NoHANDLE
;+++++++++++++++				Открытие (Образование) файла чтения
;ESI=Bufcat &GENERIC_READ& OPEN_EXISTING ==> [ CreateFile]  ==> [haRead_T]=EAX (handle файла чтения)
macro Дай_файла_Ключ	arg
{
common match A1==P1 A2==P2 A3==P3 A4==P4 A5==P5 A6==P6 A7==P7 A8==P8 A9==P9,arg
	\{
								;\Print!Rfall  "ПараметрКлюч ="
								;\Print!afall	\P1
								;				display 13,10
		mov	EDX,\P1							;Bufcat
	invoke  CreateFile,EDX,\P2,\P3,\P4,\P5,\P6,\P7
			mov     [\P8],eax				;[haRead_T] 22DB   HANDLE 1 файла чтения
		xor	eax,0FFFFFFFFh
	jne @F									;Ключ не получили
							mov	ebp,@F		;
						JMP	\P9				;EXITER			;Пока не обрабатываем
@@:
	\}
}
;-----------------------------------
								;macro VUV
								;{	and ECX,0FFFFh	}
;************************** 16
;					УстановиУказФайла\
;КлючФайла=haRead_T	ВеличинаСдвига=0	СдвигВверх=0 МетодСдвига=0
;+++++++++++++++
macro УстановиУказФайла	arg
{			common match A1==P1 A2==P2 A3==P3 A4==P4,arg
	\{
										;КлючФайла=haRead_T
										;xor	ESI,ESI			;mov	ESI,[DistanceToMove]
										;xor	EDI,EDI			;mov	EDI,[DistanceToMoveH]
										;mov	eax,[haRead_T]
	invoke	SetFilePointer,[\P1],\P2,\P3,\P4
										;_In_HANDLE hFile,
										;_In_LONG   DistanceToMove,
										;_Inout_opt_ PLONG  MoveHigh,
										;_In_  DWORD  dw MoveMethod
	\}
}
;-----------------------------------
;************************** 17	******************
;	ВыдайСообщение  $С_устройства$=Hconsl\
;					$АдресБуфераПриема$=UKPOS\
;					$РазмерБуфера$=UKPOS_r\
;					$РеальнаяДлина$=Writed		;Writed	dd	21
;++++++
macro ВыдайСообщение arg
{
												;Print!afall	arg
												;display 13,10
common match A1==P1	A2==P2	 A3==P3 A4==P4,arg
	\{
												;Print!Rfall  "Параметр ="
												;Print!afall	\P3
												;				display 13,10
												;push	EDI
												;mov		EDI,\P3
	invoke WriteConsole,\[P1],\P2,\P3,\P4,0
												;pop		EDI
	\}
}
;***********************************
;Используется свойство определения констант, которым присваивается ПОСТФиКС _t 1' это тип целая константа
macro ВыдайСообщениеА arg
{
common match A1==P1	A2==P2	 A3==P3 A4==P4,arg
	\{
								;Print!Rfall  "Параметр ="
								;Print!afall	\P3
								;	display 13,10
	push	EDI
	\arg1	equ \P3\#_t
								;\NMRuu	equ	1
								;Print!afall	\arg1								;NMRuu
								;display 13,10
								;match =1,\`arg1 	\\{ \\NMRuu equ 0
								;Print!afall \\NMRuu
								;display 13,10\\}
	if defined \arg1
				mov		EDI,[\P3]
									;Print!Rfall   "Это не константа[ ]"
									;display 13,10
	else
				mov		EDI,\P3
									;Print!Rfall   "Это константа"
									;display 13,10
	end if
	invoke WriteConsole,\[P1],\P2,EDI,\P4,0
	pop		EDI
	\}
}
;-----------------------------------
;******************************		18	*******************
;	ПрочтиИнформацию $С_устройствоhandle$=Hin\
;					$АдресБуфераПриема$=BUFpos\
;					$РазмерБуфера$=BUFpos_r\
;					$РеальнаяДлинаПринятогоПоАдресу$=NBUF
;	invoke ReadConsole,[Hin],BUFpos,BUFpos.Dlina,NBUF,0
macro ПрочтиИнформацию arg
{
												;Print!afall	arg
												;display 13,10
common match A1==P1	A2==P2	 A3==P3 A4==P4,arg
	\{
								;Print!Rfall  "Параметр ="
								;Print!afall	\P4
								;display 13,10
	invoke ReadConsole,\[P1],\P2,\P3,\P4,0
	\}
}
;*****************************	19	********************
;	Перенести\
;					$InИз_буфераПриема$=BUFpos\
;					$InВ_буфер_Имени$=V_File\
;					$InКоличество_байт_из_буфера_приема$=NBUF\
;					$InИли_количество_байт_в_стандартное$=6\
;					$OutФиксируемДлинуИмениФайла$=RNsim
								;Добавляется в структуру(V_Name -(V_File) -	U_Name_r)
;---
macro Перенести	arg
{
	local	NMMU									;Print!afall	arg
												;display 13,10
common match A1==P1	A2==P2	 A3==P3	A4==P4 А5==P5,arg
	\{
								;Print!Rfall  "Перенести Параметр ="
								;Print!afall	\P3
								;display 13,10
						УпряталиРегистры 		ECX,ESI,EDI
			mov EDI,\P4			;количество символов для стандартного имени файла
			mov	ECX,[\P3]		;Колво для принятого файлв
			cmp ECX,2			;Если RNTER, то символы  0Dh 0Ah  ЕСХ=2
		jne	@F
			mov	ECX,EDI
		jmp	NMMU
@@:
			dec	ECX				;Не допишем 01Аh
			dec	ECX				;Не допишем 01Dh
			mov	ESI,\P1
			mov	EDI,\P2
			rep movsb
			mov	ECX,[\P3]
			dec	ECX				;Не допишем 01Аh
			dec	ECX				;Не допишем 01Dh
NMMU:
			mov	[\P5],ECX		;RNsim
						ВосстановилиРегистры 	ECX,ESI,EDI
	\}
}
;**************************
;	ЧтениеФайла\
;		$Inhandle_файла$=haRead_T\
;		$InАдрес_памяти$=pMem\
;		$InДлина_файлаЧт$=DlFileN\
;		$OutРеальная_длинаЧт$=NmBytR
;+++++++++++++++++++++++++++++++++++++
MACRO ЧтениеФайла arg				;ЧтениеФайла
{
;Print!Rfall  "ВЫХОДЧт ="
;	display 13,10
	common match A1==P1	A2==P2 A3==P3 A4==P4,arg
	\{
						;\Print!Rfall  "ФайлаЧит ="
						;\Print!afall	\P1
						;display 13,10
		invoke  ReadFile,[\P1],[\P2],[\P3],\P4,0
	\}
}
;***************************
;	ЗаписьФайла\
;		$Inhandle_файла$=haRead_T\
;		$InАдрес_памяти$=pMem\
;		$InДлина_файлаЧт$=DlFileN\
;		$OutРеальная_длинаЧт$=NmBytR
;+++++++++++++++++++++++++++++++++++++
macro ЗаписьФайла 	arg			;ЗаписьФайла
{
common match A1==P1	A2==P2 A3==P3 A4==P4,arg
	\{
										;\Print!Rfall  "ФайлаЧит ="
										;\Print!afall	\P1
										;display 13,10
		invoke  WriteFile,[\P1],[\P2],[\P3],\P4,0
	\}
}