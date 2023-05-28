;********************************************************************
;	Числовое сравнение целых без знака по всем разрядам 2-х(> < =) Операндов
;********************************************************************
;в файле NCMP2.inc
;1	N!bCMPabJm	GA,GB,Pr,—Ѕќ…				переходы для байтовых размеров
;2	Сучетомотношенийbперейти				синтаксическа¤ форма ~ 1
;3	C!MPABop								переходы дл¤ любых размеров =<32 рр
;4	СучетомОтношений_A?B_перейти			синтаксическа форма	3
;5	xA?xBJmp								переходы  для AX  и  BX
;6	eA?eBJmp								переходы  для 32 разр¤дных
;7	N!bCMPabPr	GA,GB,Pr,SBOY				короткая форма = 0 > =1 < =2
;8	СравнитьA_B_b_Дать_признак				синтаксическа¤ форма ~ 7
;9	Сравнил_Байты_Выдал						синтаксическа¤ форма ~ 7
;10 N!CMPaxbxPr								сравнение слов и вылача признака
;11 N!CMPABwPr								функциональная форма Обращение через A =>BX B=> CX
;12 Сравнил_Слова_Выдал						синтаксическа¤ форма ~ 12
;в файле NCMPabPr.inc
;10 N!bCMPabPrJm							признак и переход
;11	СучетомОтношенийb_Датьпризнак_Перейти	синтаксическа¤ форма ~ 9
;12	N!bCMPabPRiJm							признак и переход
;13	СучетомОтношенийb_ДатьПризнаки_Перейти	синтаксическая форма ~ 11
;********************************************************************
;C!MPABop  RGA,RGB,Pr0,Pr1,Pr2,MISTEK		(Определение размерности операндов)
;eA?eBJmp  EGA,EGB,Pr0,Pr1,Pr2		для 32 разрядных
;xA?xBJmp  GA,GB,Pr0,Pr1,Pr2			для 16 разрядных
;N!bCMPabJm	GA,GB,Pr0,Pr1,Pr2,MISTEK		для 8 разрядных
;************************************
;if A=B then Pr0 v if A>B then Pr1  v if A<B then Pr2;  if Pri(i=0,1,2) then go MEXI
;2.C!MPabJm	al,bl,Pr0,Pr1, 	if A<B then MEXI
;3.C!MPabJm	al,bl,Pr0,,Pr2	if A>B then MEXI
;4.C!MPabJm	al,bl,,,Pr2		if A=B then MEXI  v	if A<B 		 then MEXI
;5.C!MPabJm	al,bl,Pr0,,		if A=B then Pr0   v	if A<B v A<B then MEXI     равно не равно 0
;*****************  1 ******* N!CMPabJm****************  для AL  и  BL укороченный
MACRO N!bCMPabJm  GA,GB,T1,T2,T3,SBOY		;=,>, <
{	LOCAL	MEXI,JmJ,JgJ,JeJ
		УпряталиРегистры	EAX,EBX
			mov	BL,GB				;2-й операнд
			mov	AL,GA				;1-й операнд
		and	AL,0FFh
	jne	@F
		and	BL,0FFh
	jne	JmJ							;A=0 B#0 => A<B закончили
	jmp	JeJ							;A=0  B=0   A=B
@@:
		and	BL,0FFh
	je	JgJ
;*********  Основная часть    **************
		mov	BH,AL  					;чтобы A(bh)  B(bl) были в одной строке
		mov	AH,AL
		xor	AH,BL					;в CL маска
	je	JeJ							;оба операнда A=B ==>
		and	BL,AH					;после выделения маски A
	jne	@F							;A маскированное пересекается с B  маскированное
	jmp	JgJ 						;in B=0 A>B [5*] они не зависимы и надо продолжать
@@:
		and	BH,AH					;	A(bh)
	je	JmJ							;in   A(ah)=0	A<B
;**************************			;Остались операнды только с единичками в разных разрядах
		mov	AX,08080h				;рр 16&8	1
		and	AX,BX					;
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		mov	AX,04040h				;15&7		2
		and	AX,BX					;
	jne	@F
		mov	AX,02020h				; 14&6		3
		and	AX,BX					;
	jne	@F
		mov	AX,01010h				; 13&5		4
		and	AX,BX					;
	jne	@F
		mov	AX,0808h				; 12&4		5
		and	AX,BX					;
	jne	@F
		mov	AX,0404h				; 11&3		6
		and	AX,BX					;
	jne	@F
		mov	AX,0202h				; ;10&2		7
		and	AX,BX					;
	jne	@F
	match	P_us=Ar,SBOY
	\{
	if   ~\ar eq
	jmp	-4							;31
	else
	jmp	\ar							;31
	end if
	\}
@@:									;A(ah)  B(al)
		and	AL,0FFh					;A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ							;B=1 A=0  =>A<B
;***********Общий ВЫХОД*************;B=0 A=1  =>A>B
JgJ:
	ВосстановилиРегистры	EAX,EBX
			if   ~T2 eq
	JMP	T2								;A<B
			else
	JMP	MEXI
			end if
JeJ:
	ВосстановилиРегистры	EAX,EBX
			if   ~T1 eq
	JMP	T1								;–авны A=B
			else
	JMP	MEXI
			end if						;[4]
JmJ:
	ВосстановилиРегистры	EAX,EBX
			if   ~T3 eq
	JMP	T3								;A>B
			else
			end if						;JMP	MEXI
MEXI:									;продолжение после блока
}
;*****************************************************************
;************************** 2 ************** СучетомОтношенийПерейти*************
;	СучетомОтношенийbПерейти\
;			 A=?B\
;			=Pr0 >Pr1  < Pr2\
;			$ПриСбое => M!ISTEK
;****************************************Использует
;		N!CMPabJm	al,bl,ah,0		самый короткий вариант
;		N!CMPabJm	cl,dl,[Priznak],SBOY
;+++++++++++++++++++++++++++++++++++++++++++++++
MACRO СучетомОтношенийПерейти arg
{		Print!afall "No ERROR   here   all   Pr0 & Pr1 & Pr2"
common  	match	OP1 =?  OP2   ==Pr0 =>Pr1  =< Pr2 PUS==>Er,arg
		\{\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
		\Print!afall   "No ERROR   here   all   Pr0 & Pr1 & Pr2"
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>Pr1  =<  PUS==>Er,arg		;1 1  0
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>  =<  PUS==>Er,arg		;1 0 0
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>  =<Pr2  PUS==>Er,arg		;1 0 1
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>Pr1  =<Pr2  PUS==>Er,arg		;0 1 1
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>Pr1  =<  PUS==>Er,arg		;0 1 0
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>  =<Pr2  PUS==>Er,arg		;0 0 1
		\{
			\N!bCMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>  =<  ==Er,arg			;0 0 0
		\{
			\Print!afall   "ERROR   here   all   Pr0 & Pr1 & Pr2"
 		\}
 }
 ;******************** 3 **МАКРОС определения размерности операндов al v AX v EAX в пределах 32 рр
MACRO C!MPABop  RGA,RGB,Pr0,Pr1,Pr2,MISTEK	;=, >, <
{
	 if  RGA   in  <al,ah,bl,bh,cl,ch,dl,dh>
		N!bCMPabJm RGA,RGB,Pr0,Pr1,Pr2,MISTEK
	else
		 if  RGB   in  <al,ah,bl,bh,cl,ch,dl,dh>
			N!bCMPabJm RGA,RGB,Pr0,Pr1,Pr2,MISTEK
		else
		end if
	end if
;*******************
 	if  RGA   in  <AX,BX,CX,DX,BP,SI,DI>
		xA?xBJmp  RGA,RGB,Pr0,Pr1,Pr2
	else
		 if  RGB   in  <AX,BX,CX,DX,BP,SI,DI>
			xA?xBJmp RGA,RGB,Pr0,Pr1,Pr2
		else
		end if
	end if
;*******************
	if  RGA   in  <EAX,EBX,ECX,EDX,EBP,ESI,EDI>
		eA?eBJmp  RGA,RGB,Pr0,Pr1,Pr2
	else
		if  RGB   in  <EAX,EBX,ECX,EDX,EBP,ESI,EDI>
			eA?eBJmp RGA,RGB,Pr0,Pr1,Pr2
		else

		end if
	end if
}
;************************* 4 ************************************
;				 СучетомОтношений_A?B_Перейти\
;					[firstByte] ? 00010000b\
;									=	>P6	<P6	\
;											=>			;MEXIT
;
;************************** 4    **************************************СучетомОтношений_A?B_Перейти
;	common  	match	OP1=? OP2   ==Pr0 =>Pr1  =<Pr2 PUS==>Er,arg
MACRO СучетомОтношений_RА?RВ_Перейти	arg
{Print!afall   arg
common  	match	OP1 =? OP2   ==Pr0 =>Pr1  =<Pr2 PUS==>Er,arg
		\{
			Print!afall   "No ERROR   here   all   Pr0 & Pr1 & Pr2"
			\C!MPABop  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1  =?  OP2   ==Pr0 =>Pr1  =< PUS==>Er,arg		;1 1  0
		\{			\C!MPABop  \OP1,\OP2,\Pr0,\Pr1,\Er
 		\}
common  	match	OP1  =?  OP2   ==Pr0 =>  =<  PUS==>Er,arg		;1 0 0
		\{			\C!MPABop  \OP1,\OP2,\Pr0,,,\Er
 		\}
common  	match	OP1  =?  OP2   ==Pr0 =>  =<Pr2,arg		;1 0 1
		\{			\C!MPABop  \OP1,\OP2,\Pr0,,\Pr2
 		\}
common  	match	OP1 =?  OP2   == =>Pr1  =<Pr2,arg		;0 1 1
		\{			\C!MPABop  \OP1,\OP2,,\Pr1,\Pr2
 		\}
common  	match	OP1  =?  OP2   == =>Pr1  =< ,arg		;0 1 0
		\{														;\Pr0 equ \Pr2	equ
			\C!MPABop  \OP1,\OP2,,\Pr1,
 		\}
common  	match	OP1  =?  OP2   == =>  =<Pr2  ==Er,arg		;0 0 1
		\{			\C!MPABop  \OP1,\OP2,,,\Pr2,\Er
 		\}
common  	match	OP1  =?  OP2   == =>  =<  ==Er,arg			;0 0 0
		\{		\Print!afall   "ERROR   here   all   Pr0 & Pr1 & Pr2"
 		\}
		;Print!afall	arg
 }
;***************** 5  xA?xBJmp****************  для AX  и  BX
MACRO xA?xBJmp  GA,GB,Pr0,Pr1,Pr2			;=, >, <
{	LOCAL	MEXI,JmJ,JgJ,JeJ,NBloc0,NBl
	УпряталиРегистры	EAX,EBX
		mov AX,GA						;1-й операнд
		mov BX,GB						;2-й операнд
;**************************
		and	ah,0FFh
	jne	@F
		and	bh,0FFh
	jne	JmJ								;A=0 B#0 => A<B закончили
	jmp	NBl								;Ah=0  Bh=0 На следующий блок из 0,1,2,3 на 2
@@:
		and	bh,0FFh
	je	JgJ								;A#0 B=0 A>B
		shl	EAX,8						;временно
		mov	al,ah
		xor	al,bh						;проверка на равенство старших байт
		shr	EAX,8
	je	@F 								; Если равны то будем сравнивать мл.байты
		ror	AX,8						;по старшим разрядам 9-16 они перейдут в мл.рр
		ror	BX,8						;вернулм младшие на место
	jmp	NBl
;******
@@:
		and	AL,0FFh
	jne	@F
		and	BL,0FFh
	jne	JmJ							;A=0 B#0 => A<B закончили
	jmp	JeJ							;A=0  B=0   A=B
@@:
		and	BL,0FFh
	je	JgJ
NBl:
;*********  Основная часть    **************
		mov	BH,AL  					;чтобы A(bh)  B(bl) были в одной строке
		mov	AH,AL
		xor	AH,BL					;в AH маска
	je	JeJ							;оба операнда A=B ==>
		and	BL,AH					;после выделения маски A
	jne	@F							;A маскированное пересекается с B  маскированное
	jmp	JgJ 						;in B=0 A>B [5*] они не зависимы и надо продолжать
@@:
		and	BH,AH					;	A(bh)
	je	JmJ							;in   A(ah)=0	A<B
;**************************			;Остались операнды только с единичками в разных разрядах
		mov	AX,08080h				;рр 16&8	1
		and	AX,BX					;
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		mov	AX,04040h				;15&7		2
		and	AX,BX					;
	jne	@F
		mov	AX,02020h				; 14&6		3
		and	AX,BX					;
	jne	@F
		mov	AX,01010h				; 13&5		4
		and	AX,BX					;
	jne	@F
		mov	AX,0808h				; 12&4		5
		and	AX,BX					;
	jne	@F
		mov	AX,0404h				; 11&3		6
		and	AX,BX					;
	jne	@F
		mov	AX,0202h				; ;10&2		7
		and	AX,BX					;
	jne	@F
	jmp	$-4							;Такого не должно быть только сбой компьюьера
@@:									;A(ah)  B(al)
		and	AL,0FFh					;A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ							;B=1 A=0  =>A<B
;***********Общий ВЫХОД*************;B=0 A=1  =>A>B
;************************ конец    AX   BX
JgJ:
	ВосстановилиРегистры	EAX,EBX
			if   ~Pr1 eq
	JMP	Pr1								;A<B
			else
	JMP	MEXI
			end if
JeJ:
	ВосстановилиРегистры	EAX,EBX
			if   ~Pr0 eq
	JMP	Pr0								;–авны A=B
			else
	JMP	MEXI
			end if						;[4]
JmJ:
	ВосстановилиРегистры	EAX,EBX
			if   ~Pr2 eq
	JMP	Pr2								;A>B
			else
			end if						;JMP	MEXI
MEXI:									;продолжение после блока
}
;*******************************************************

;*************Cравнение двух 32 разрядных слов с минимальным кол-вом операций ***************
;1.C!MPAB  	RGA,RGB,Pr0,Pr1,Pr2    Сравнения любых данных в пределах 32 рр и Переход
;2.		J!mA?B  RGA,RGB,Pr0,Pr1,Pr2,MISTEK
;**********       6        eA?eBJmp*****xA?xBJmp******N!bCMPabJm***************EDX  EAX***********************************
		macro eA?eBJmp  EGA,EGB,Pr0,Pr1,Pr2	;=, >, <
{
	LOCAL	MEXI,JmJ,JgJ,JeJ
	if  EGA  in  <EAX,EBX>
	else
		УпряталиРегистры	EAX,EBX
			mov	EBX,EGB				;2-й операнд
			mov	EAX,EGA				;1-й операнд
	end if
	ror	EAX,16
	ror	EBX,16
		and	AX,0FFFFh
	jne	@F
		and	BX,0FFFFh
	jne	JmJ					;A=0 B#0 => A<B закончили
	jmp	NBloc2				;A=0  B=0 На следующий блок из 0,1,2,3 на 2
@@:
		and	BX,0FFFFh
	je	JgJ				;A#0 B=0 A>B
		push	ecx
		mov		CX,AX
		xor		CX,BX
		pop		ECX
	jne	@F				NBloc2					;Старшие разряды равны
		ror	EAX,16
		ror	EBX,16
@@:												;CMPab:
  xA?xBJmp  AX,BX,Pr0,Pr1,Pr2			;без упрятывания
;****************************
JgJ:
			if  EGA  in  <EAX,EBX>
			else
	ВосстановилиРегистры	EAX,EBX
			end if
			if   ~Pr1 eq
	JMP	Pr1										;A<B
			else
	JMP	MEXI
			end if
JmJ:
			if  EGA  in  <EAX,EBX>
			else
	ВосстановилиРегистры	EAX,EBX
			end if
			if   ~Pr2 eq
	JMP	Pr2										;A>B
			else
			end if								;JMP	MEXI
MEXI:											;продолжение после блока
}
;+++++++++КОНЕЦ++ eA?eBJmp +++++++++++++++++++++++++++++
;***************************************************************************
;Формы обращения с учетом регистров МАКРОС сравнения двух байт и присвоение 3-признаков
;N!CMPabPr	al,bl,al,		самый короткий вариант
;N!CMPabPr	AL,BL,CL,SBOY(A=AL)?(B=BL); CL:= 0 или > =1 или < =2; при сбое уйти => SBOY
;N!CMPabPr  CL,DL,[Priznak],SBOY длинный вариант вызова  Упрятываем EAX EBX
;N!CMPabPr	AL,DL,[Priznak],   длинный вариант вызова,при сбое цикл Упрятываем EBX
;N!CMPabPr	DL,BL,[Priznak],   длинный вариант вызова,при сбое цикл Упрятываем EAX
;	35 команд но в среднем < 20 команд
;***************** 7 ******** **N!CMPabPr ****************  для AL  и  BL
MACRO N!CMPabPr  GA,GB,Pr,SBOY		;= 0  > =1 < =2
{	LOCAL	MEXI,JmJ,JgJ,JeJ
	push	EBX
if  ~GA  in  <al>
	mov		al,GA						;1-й операнд
				if  ~GB  in  <bl>
				mov	BL,GB				;2-й операнд
				else
				end if
else
				if  ~GB  in  <bl>
					mov		BL,GB			;2-й операнд
				else
				end if
end if
		and	AL,0FFh					;1
	jne	@F							;2
		and	BL,0FFh					;3
	jne	JmJ							;4A=0 B#0 => A<B закончили
	jmp	JeJ							;5A=0  B=0   A=B
@@:
		and	BL,0FFh					;6
	je	JgJ							;7
;*********  Основная часть    **************
		mov	BH,AL  					;8чтобы  BX= A(AL)  B(BL) были в одной строке
		mov	AH,AL					;9  	    AX = AL    AL
		xor	AH,BL					;10 в 		AH = AL xor BL  маска
	je	JeJ							;11 оба операнда A=B ==> нет отличающихся разрядов
		and	BL,AH					;B 12после выделения маской отличающиеся разряды B
	jne	@F							;13 B маскированное пересекаетсZ с B  маскированное
	jmp	JgJ 						;14  in B(bl)=0 A>B [5*]
@@:
		and	BH,AH					;15 A после выделения маской отличающиеся разряды A(bh)
	je	JmJ							;16 in   A(bh)=0	A<B
;**************************			;17 остались операнды только с единичками в разных разр¤дах
			mov	AX,08080h				;рр 16&8	1
		and	AX,BX					;
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		mov	AX,04040h				;15&7		2
		and	AX,BX					;
	jne	@F
		mov	AX,02020h				; 14&6		3
		and	AX,BX					;
	jne	@F
		mov	AX,01010h				; 13&5		4
		and	AX,BX					;
	jne	@F
		mov	AX,0808h				; 12&4		5
		and	AX,BX					;
	jne	@F
		mov	AX,0404h				; 11&3		6
		and	AX,BX					;
	jne	@F
		mov	AX,0202h				; ;10&2		7
		and	AX,BX					;
	jne	@F
	if   ~SBOY eq
	jmp	-4							;31
	else
	jmp	SBOY						;31 невозможная комбинация через P!rAdrStop
	end if
@@:									;A(ah)  B(al)
		and	AL,0FFh					;32 A=1 B=0  => A<B  else A>B   BL=?
	jne	JmJ							;33 B=1 A=0  =>A<B
;***********   Общий блок **********;B=0 A=1  =>A>B
JgJ:								;********************************
				POP		EBX
		mov Pr,2					;34  A>B	Pr может быть регистром
	JMP	MEXI						;35
;+++++++++++++++++++++++
JeJ:								;********************************
				POP		EBX
		mov Pr,0					;34  A=B	if Pr in 	<cl,ch,dl,dh.bl.bh,al>
	JMP	MEXI						;35				shl Pr,2  or Pr,00b else end if
;++++++++++++++
JmJ:								;********************************
				POP		EBX
		mov Pr,1					;34  A>B
MEXI:								;продолжение после блока
}
;**********************   8 СравнитьA_B_Дать_признак ******************
;	  СравнитьA_B_Дать_признак\
;			 [Par1] =? [B]\
;					$признак_в_ячеку_признаков=:PR			;\
;									;$ПриСбое=>M!ISTEK
;+++++++++++++++++++++++++++++++++++++ использует

;+++++++++++++++++++++++++   8    ++++++++++++++++++++++++++++++++
macro СравнитьA_B_Дать_признак	arg
{	common  	match	OP1 =?  OP2  PUST==:Pr PUSTO==>Er,arg
\{
		if   ~\Er eq
		\N!CMPabPr	\OP1,\OP2,\Pr,\Er
		else
		\N!CMPabPr	\OP1,\OP2,\Pr,
			end if
			\}
}
;************************** 9 ***************************************
;				Сравнил_Байты_Выдал\
;					    al? bl\
;							$Признак_0_1_2_в=:dl\
;											$ПриСбое=>Sboy					;Sboy
;++++++++++++++++++++++++++++  9  +++++++++++++++++++++++++++++
macro Сравнил_Байты_Выдал		arg
{common  	match	OP1 =?  OP2  PUST==:Pr PUSTO==>Er,arg
\{
		if   ~\Er eq
		\N!CMPabPr	\OP1,\OP2,\Pr,\Er
		else
		\N!CMPabPr	\OP1,\OP2,\Pr,
			end if
			\}
}
;*****************************************************************
;  			СРАВНЕНИЕ  СЛОВ
;***************** 10   N!CMPaxbxPr ****************  для AL  и  BL
MACRO N!CMPaxbxPr  GA,GB,Pr,SBOY		;= 0  > =1 < =2
{	LOCAL	MEXI,JmJ,JgJ,JeJ
if  ~GA  in  <AX>
		PUSH	EAX
	mov		AX,GA						;1-й операнд
				if  ~GB  in  <BX>
				PUSH	EBX
				mov	BX,GB				;2-й операнд
				else
				end if
else
				if  ~GB  in  <BX>
					PUSH	EBX
					mov		BX,GB			;2-й операнд
				else
				end if
end if
;**************************
		ror	AX,8						;по старшим разрядам 9-16 они перейдут в мл.рр
		ror	BX,8
		and	al,0FFh
	jne	@F
		and	bl,0FFh
	jne	JmJ								;A=0 B#0 => A<B закончили
	jmp	NBloc0							;A=0  B=0 На следующий блок из 0,1,2,3 на 2
@@:
		and	bl,0FFh
	je	JgJ								;A#0 B=0 A>B
		push	CX
		mov	cl,al
		xor	cl,bl						;проверка на равенство старших байт
		pop		cx
	jne	@F								;NBloc0	 Если не равны то будем сравнивать ст.байты
		ror	AX,8						;по старшим разрядам 9-16 они перейдут в мл.рр
		ror	BX,8						;вернулм младшие на место
;******
@@: 									;CMPab:
										;N!bCMPabJm  al,bl,Pr0,Pr1,Pr2,MISTEK	;без упрятывания
;************************ конец    AX   BX
		and	AL,0FFh					;1
	jne	@F							;2
		and	BL,0FFh					;3
	jne	JmJ							;4A=0 B#0 => A<B закончили
	jmp	JeJ							;5A=0  B=0   A=B
@@:
		and	BL,0FFh					;6
	je	JgJ							;7
;*********  Основная часть    **************
		mov	BH,AL  					;8чтобы  BX= A(AL)  B(BL) были в одной строке
		mov	AH,AL					;9  	    AX = AL    AL
		xor	AH,BL					;10 в 		AH = AL xor BL  маска
	je	JeJ							;можно убрать 11 оба операнда A=B ==> нет отличающихся разрядов
		and	BL,AH					;12после выделения маской отличающиеся разряды B
	jne	@F							;13 B маскированное пересекаетсZ с B  маскированное
	jmp	JgJ 						;14  in B(bl)=0 A>B [5*]
@@:
		and	BH,AH					;15 после выделения маской отличающиеся разряды A(bh)
	je	JmJ							;16 in   A(bh)=0	A<B
;**************************			;17 остались операнды только с единичками в разных разр¤дах
			mov	AX,08080h				;рр 16&8	1
		and	AX,BX					;
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		mov	AX,04040h				;15&7		2
		and	AX,BX					;
	jne	@F
		mov	AX,02020h				; 14&6		3
		and	AX,BX					;
	jne	@F
		mov	AX,01010h				; 13&5		4
		and	AX,BX					;
	jne	@F
		mov	AX,0808h				; 12&4		5
		and	AX,BX					;
	jne	@F
		mov	AX,0404h				; 11&3		6
		and	AX,BX					;
	jne	@F
		mov	AX,0202h				; ;10&2		7
		and	AX,BX					;
	jne	@F
	if   ~SBOY eq
	jmp	-4							;31
	else
	jmp	SBOY						;31 невозможная комбинация через P!rAdrStop
	end if
@@:									;A(ah)  B(al)
		and	AL,0FFh					;32 A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ							;33 B=1 A=0  =>A<B
;***********   Общий блок **********;B=0 A=1  =>A>B
JgJ:								;********************************
if	~GA  in  <al>
	POP		EAX
				if  ~GB  in  <bl>
				POP		EBX
				else
				end if
else
			if  ~GB  in  <bl>
				POP		EBX
			else
			end if
	end if
		mov Pr,2					;34  A>B	Pr может быть регистром
	JMP	MEXI						;35
;+++++++++++++++++++++++
JeJ:								;********************************
if	~GA  in  <al>
	POP		EAX
				if  ~GB  in  <bl>
				POP		EBX
				else
				end if
else
			if  ~GB  in  <bl>
				POP		EBX
			else
			end if
	end if
		mov Pr,0					;34  A=B
	JMP	MEXI						;35
;++++++++++++++
JmJ:								;********************************
if	~GA  in  <al>
	POP		EAX
				if  ~GB  in  <bl>
				POP		EBX
				else
				end if
else
			if  ~GB  in  <bl>
				POP		EBX
			else
			end if
	end if
		mov Pr,1					;34  A>B
MEXI:								;продолжение после блока
}

;*******************************************************
;********************************* 11     ****************
MACRO N!CMPABwPr  GBx,GCx,Pr	;= 0  > =1 < =2
{	LOCAL	MEXI,JmJ,JgJ,JeJ
			УпряталиРегистры	EBX,ECX
if  ~GA  in  <BX>
	mov		BX,GBx						;1-й операнд
				if  ~GB  in  <CX>
				mov	CX,GCx				;2-й операнд
				else
				end if
else
				if  ~GCx  in  <CX>
					mov		CX,GCx			;2-й операнд
				else
				end if
end if
		and	EBX,0FFFFh				;1
	jne	@F							;2
		and	CX,0FFFFh				;3
	jne	JmJ							;4 B#0 => A<B закончили
	jmp	JeJ							;5A=0  B=0   A=B
@@:		and	CX,0FFFFh					;6
	je	JgJ							;7
;*********  Основная часть    **************
		shl	ECX,16  				;16 чтобы  ECX= И(ECXст.рр)  B(BL) были в одной строке
		or	EBX,ECX					;   EBX= B  A
		mov	ECX,EBX					;9  	    AX = AL    AL
		ror	ECX,16					;10 ECX= A  B
		xor	ECX,EBX					;маска   M  M
		and	EBX,ECX					;EBX=   B&M  A&M
	je	JeJ							;11 оба операнда A=B ==> нет отличающихся разрядов
		and	BX,-1					; BX=  A&M выделения маской отличающиеся разряды B
	jne	@F							;13 B маскированное пересекаетсZ с B  маскированное
	jmp	JmJ 						;14  in A(bl)=0 A<B [5*]
@@:		ror	EBX,16					;EBX= A&M B&M
		and	BX,-1					;15 B после выделения маской отличающиеся разряды B
	je	JgJ							;16 in   B(bh)=0	A>B
;**************************			;17 остались операнды только с единичками в разных разр¤дах
			mov	ECX,080008000h		;рр 32&16
@@:		test	EBX,ECX					;EBX= A&M B&M
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	ECX,1
	jmp	@B
@@:		and	EBX,ECX
		xor	EBX,ECX					;обр.0 у кого ст.ед
		and	BX,-1					;32 EBX= (A&M cm.рр) B&M&(0FFFF)
	jne	JgJ							;33	B=1 A=0  =>A>B
;***********   Общий блок 				B=1 A=0  => A<B
JmJ:					 ;********************************
		ВосстановилиРегистры	EBX,ECX
	if Pr in 	<al,cl,ch,dl,dh,bl,bh>
		shl Pr,2
		or Pr,001b
	else
		mov Pr,2					;34  A<B
	end if
	JMP	MEXI
JgJ:					;********************************
		ВосстановилиРегистры	EBX,ECX
	if Pr in 	<al,cl,ch,dl,dh,bl,bh>
		shl Pr,2
		or Pr,010b
	else
		mov Pr,2					;34  A>B
	end if
	JMP	MEXI						;35
;+++++++++++++++++++++++
JeJ:					;********************************
		ВосстановилиРегистры	EBX,ECX
	if Pr in 	<al,cl,ch,dl,dh,bl,bh>
		shl Pr,2
		or Pr,00b
	else
		mov Pr,0					;34  A=B
	end if
;++++++++++++++
MEXI:								;продолжение после блока
}
;+++++++++++++++++++++++++++++++++++++
;			Словное сравнение
;+++++++++++++++++++++++++++++  12    ++++++++++++++++++++++++++++
macro Сравнил_Слова_Выдал		arg
{	common  	match	OP1 =?  OP2  PUST==:Pr,arg
\{
		if   ~\Er eq
		\N!CMPABwPr	\OP1,\OP2,\Pr
		else
		\N!CMPABwPr	\OP1,\OP2,\Pr
			end if
			\}
}
;**********************************************************