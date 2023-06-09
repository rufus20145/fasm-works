;			МАКРОСы сравнения 3-х множеств
;	UC!ABCJmp					1+						; Все значения не нулевые для УНИПРИМ
;	УчитываяОтношенияWПерейти	2*						;Синтаксический Оператор
;	УчитываяАрифметическиеОтношенияWПерейти	3*			;синоним УчитываяОтношенияWПерейти
;******************************* 1   Все значения не нулевые для УНИПРИМ
; МОЯ РАБОТА
macro UC!ABCJmp  Ga,Gb,Gc,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,Sboy
{	local  HGK,CSZ,JmJ,JeJ,JgJ,JmJ1,JeJ1,JgJ1,MEXI,MEXI1,JmJ2,JeJ2,JgJ2,JmJ3,JeJ3,JgJ3,\
			SJMP,NBl,NBl1
;*** 1
	УпряталиРегистры	EAX,EBX,ECX			;Gc,Gb,Ga	параметры
	if  ~Ga  in  <AX>
	mov	AX,Ga
else
end	if
	if  ~Gb  in  <BX>
		mov	BX,Gb
	else
	end	if
		if  ~Gc  in  <CX>
			mov	CX,Gc
		else
		end	if
	УпряталиРегистры	ECX,EBX,EAX			;Ga,Gc,Gb,Ga	параметры
	POP EBX			; A		Ga
	POP	ECX			; B		Gb
;****2
		;Сравнил_Слова_Выдал\
		;	BX ? CX\
		;			$Признак_при_ сравнении_А_В_0_1_2_в=:al
;**************************
		PUSH ECX
;*********  Основная часть    **************
		shl	ECX,16  				;16 чтобы  ECX= И(ECXст.рр)  B(BL) были в одной строке
		or	EBX,ECX					;   EBX= B  A
		mov	ECX,EBX					;9  	    AX = AL    AL
		ror	ECX,16					;10 ECX= A  B
		xor	ECX,EBX					;маска   M  M
		and	EBX,ECX					;EBX=   B&M  A&M
	je	JeJ							;11 оба операнда A=B ==> нет отличающихся разрядов
		and	BX,-1					; BX=  A&M выделения маской отличающиеся разряды B
	jne	@F							;13 B маскированное пересекается с B  маскированное
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
JmJ:								;POP	EBX
		POP	ECX
		mov al,1					;34  A<B
	JMP	MEXI
JgJ:								;POP	EBX
		POP	ECX
		mov al,2					;34  A>B
	JMP	MEXI						;35
;+++++++++++++++++++++++
JeJ:								;POP	EBX
		POP	ECX
		mov al,00b
;++++++++++++++
MEXI:
;**************************
;*** 3
					movzx	EBX,CX	;B
					POP	ECX			; 35  восстановили С
									;Сравнил_Слова_Выдал\
									;BX ? CX\
									;$Признак_AL<-2_or_признак_0_1_2_в=:al
;*** 4
;*********  Основная часть    **************
		shl	ECX,16  				;16 чтобы  ECX= И(ECXст.рр)  B(BL) были в одной строке
		or	EBX,ECX					;   EBX= B  A
		mov	ECX,EBX					;9  	    AX = AL    AL
		ror	ECX,16					;10 ECX= A  B
		xor	ECX,EBX					;маска   M  M
		and	EBX,ECX					;EBX=   B&M  A&M
	je	JeJ1							;11 оба операнда A=B ==> нет отличающихся разрядов
		and	BX,-1					; BX=  A&M выделения маской отличающиеся разряды B
	jne	@F							;13 B маскированное пересекаетсZ с B  маскированное
	jmp	JmJ1 						;14  in A(bl)=0 A<B [5*]
@@:		ror	EBX,16					;EBX= A&M B&M
		and	BX,-1					;15 B после выделения маской отличающиеся разряды B
	je	JgJ1						;16 in   B(bh)=0	A>B
;**************************			;17 остались операнды только с единичками в разных разр¤дах
			mov	ECX,080008000h		;рр 32&16
@@:		test	EBX,ECX				;EBX= A&M B&M
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	ECX,1
	jmp	@B
@@:		and	EBX,ECX
		xor	EBX,ECX					;обр.0 у кого ст.ед
		and	BX,-1					;32 EBX= (A&M cm.рр) B&M&(0FFFF)
	jne	JgJ1						;33	B=1 A=0  =>A>B
;***********   Общий блок 				B=1 A=0  => A<B
JmJ1:								;POP	EBX
		shl	al,2
		or al,1						;34  A<B
	JMP	MEXI1						;  60
JgJ1:								;POP	EBX
		shl	al,2
		or al,2						;34  A>B
	JMP	MEXI1						;35
;+++++++++++++++++++++++
JeJ1:								;POP	EBX
		shl	al,2
		or al,00b
;++++++++++++++
MEXI1:
;**************************
;*** 5
		and	EAX,0FFh
		cmp AL,10					;Число переключателей
	JG	Sboy
		shl	EAX,3					;через 8 байт команды
		add	EAX,SJMP
	jmp	EAX
label	SJMP	dword
	POP		ECX						;восстановили С
	POP		EBX						;A 0
	POP		EAX						;B
	jmp	near	P3					;243C	0
	POP		ECX						;восстановили С
	POP		EBX						;A 1
	POP		EAX						;B
	jmp	near	P5					;24B8		1
	POP		ECX						;восстановили С
	POP		EBX			;A 2
	POP		EAX			;B
	jmp	near	P6		;24F6		2
	POP		ECX			;восстановили С
	POP		EBX			;A 3
	POP		EAX			;B
	jmp	near	Sboy	;26D1		3
	POP		ECX			;восстановили С
	POP		EBX			;A
	POP		EAX			;B 4
	jmp	near	P4		;247A		4
	POP		ECX			;восстановили С
	POP		EBX			;A 5
	POP		EAX			;B
	jmp	near	P2		;23FE		5
	POP		ECX			;восстановили С
	POP		EBX			;A 6
	POP		EAX			;B
	jmp	near	HGK		;;224C		6
	POP		ECX			;восстановили С
	POP		EBX			;A 7
	POP		EAX			;B
	jmp	near	Sboy	;2685
	POP		ECX			;восстановили С
	POP		EBX			;A 8
	POP		EAX			;B
	jmp	near	P7		;;23C6
	POP		ECX			;восстановили С
	POP		EBX			;A 9
	POP		EAX			;B
	jmp	near	CSZ		;2196
	POP		ECX			;восстановили С
	POP		EBX			;A 10
	POP		EAX			;B
	jmp	near	P1		;2254
						;S!WITC	EAX,P3,P5,P6,Sboy,P4,P2,HGK,Sboy,P7,CSZ,P1,Sboy
;*** 6					;72+ 4*13  =72+52 =124     Для перхода в среднем 72+4 v  +60
CSZ:					;СучетомОтношений_A?B_Перейти\
						;		AX ? CX\
						;			=P11 >P12  < P13
;*******************
	УпряталиРегистры	EAX,EBX
										;mov AX,GA						;1-й операнд
		mov BX,CX						;2-й операнд
;**************************
		and	ah,0FFh
	jne	@F
		and	bh,0FFh
	jne	JmJ2							;A=0 B#0 => A<B закончили
	jmp	NBl								;Ah=0  Bh=0 На следующий блок из 0,1,2,3 на 2
@@:		and	bh,0FFh
	je	JgJ2							;A#0 B=0 A>B
		shl	EAX,8						;
		mov	al,ah
		xor	al,bh						;проверка на равенство старших байт
		shr	EAX,8
	je	@F 								; Если равны то будем сравнивать мл.байты
		ror	AX,8						;по старшим разрядам 9-16 они перейдут в мл.рр
		ror	BX,8						;вернулм младшие на место
	jmp	NBl
;******
@@:		and	AL,0FFh
	jne	@F
		and	BL,0FFh
	jne	JmJ2							;A=0 B#0 => A<B закончили
	jmp	JeJ2							;A=0  B=0   A=B
@@:		and	BL,0FFh
	je	JgJ2
NBl:
;*********  Основная часть    **************
		mov	BH,AL  					;чтобы A(bh)  B(bl) были в одной строке
		mov	AH,AL
		xor	AH,BL					;в AH маска
	je	JeJ2						;оба операнда A=B ==>
		and	BL,AH					;после выделения маски A
	jne	@F							;A маскированное пересекается с B  маскированное
	jmp	JgJ2 						;in B=0 A>B [5*] они не зависимы и надо продолжать
@@:		and	BH,AH					;	A(bh)
	je	JmJ2							;in   A(ah)=0	A<B
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
	jmp	-4							;Такого не должно быть только сбой компьютера
@@:		and	AL,0FFh					;A(ah)  B(al)  A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ2						;B=1 A=0  =>A<B
;***********Общий ВЫХОД*************;B=0 A=1  =>A>B
JgJ2:
	ВосстановилиРегистры	EAX,EBX
	JMP	P12								;A>B
JeJ2:
	ВосстановилиРегистры	EAX,EBX
	JMP	P11								;Pr0		;равны A=B
JmJ2:
	ВосстановилиРегистры	EAX,EBX
	JMP	P13								;A<B
;*** 7
HGK:								;СучетомОтношений_A?B_Перейти\
									;		AX ? CX\
									;				=P8 	>P9  	< P10
;************************
	УпряталиРегистры	EAX,EBX
										;mov AX,GA						;1-й операнд
		mov BX,CX						;2-й операнд
;**************************
		and	ah,0FFh
	jne	@F
		and	bh,0FFh
	jne	JmJ3							;A=0 B#0 => A<B закончили
	jmp	NBl1							;Ah=0  Bh=0 На следующий блок из 0,1,2,3 на 2
@@:		and	bh,0FFh
	je	JgJ3							;A#0 B=0 A>B
		shl	EAX,8						;временно
		mov	al,ah
		xor	al,bh						;проверка на равенство старших байт
		shr	EAX,8
	je	@F 								; Если равны то будем сравнивать мл.байты
		ror	AX,8						;по старшим разрядам 9-16 они перейдут в мл.рр
		ror	BX,8						;вернули младшие на место
	jmp	NBl1
;******
@@:		and	AL,0FFh
	jne	@F
		and	BL,0FFh
	jne	JmJ3							;A=0 B#0 => A<B закончили
	jmp	JeJ3							;A=0  B=0   A=B
@@:		and	BL,0FFh
	je	JgJ3
NBl1:
;*********  Основная часть    **************
		mov	BH,AL  						;чтобы A(bh)  B(bl) были в одной строке
		mov	AH,AL
		xor	AH,BL						;в AH маска
	je	JeJ3							;оба операнда A=B ==>
		and	BL,AH						;после выделения маски A
	jne	@F								;A маскированное пересекается с B  маскированное
	jmp	JgJ3 							;in B=0 A>B [5*] они не зависимы и надо продолжать
@@:		and	BH,AH						;	A(bh)
	je	JmJ3							;in   A(ah)=0	A<B
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
	jmp	-4							;Такого не должно быть только сбой компьютера
@@:		and	AL,0FFh					;A(ah)  B(al)  A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ3						;B=1 A=0  =>A<B
;***********Общий ВЫХОД*************;B=0 A=1  =>A>B
JgJ3:
	ВосстановилиРегистры	EAX,EBX
	JMP	P9								;A>B
JeJ3:
	ВосстановилиРегистры	EAX,EBX
	JMP	P8								;Pr0		;равны A=B
JmJ3:
	ВосстановилиРегистры	EAX,EBX
	JMP	P10								;A<B
;************************  Занимает 026Еh =622 байта
}
;*******************************
;************************ конец   UC!ABCJmp AX ?  BX ? CX
;***********************************************
;		УчитываяОтношенияWПерейти\
;			AX ? BX ? CX \
;							$Отн<\>=>P1\
;							   $Отн(/\)=>P2\
;								 $Отн(_/)=>P3\
;  =>P4 =>P5=>P6=>P7 =>P9 =>P10 =>P11  =>P_12  =>P_13 =>P_14 =>Sboy
;
;+++++++++++++++++++++++++++++++++++++++++++++++
;*************** УчитываяОтношенияWПерейти  синонимы  УчитываяАрифметическиеОтношенияWПерейти
macro УчитываяАрифметическиеОтношенияWПерейти	arg
{
		УчитываяОтношенияWПерейти	arg
}
;****************
MACRO УчитываяОтношенияWПерейти	arg
{
		;Print!afall   arg
		;display	'10'
  common match A =? B =? C =? F_1 ==> P1  F_2==> P2  F_3==> P3  F_4==> P4 F_5==>P5 F_6==>P6\
   F_7==>P7  F_8==>P8  F_9==>P9  F_10==>P10 F_11==>P11  F_12==>P12  F_13==>P13 F_14==>Sboy,arg
		\{
			;\display 0Dh,0ah
			;\Print!Rfall   F_1
			;\display 0Dh,0ah
			;\Print!afall   F_2
			;\display 0Dh,0ah
			;\Print!afall   F_13
			;\display 0Dh,0ah
			;\Print!afall   F_9
 \UC!ABCJmp  \A,\B,\C,\P1,\P2,\P3,\P4,\P5,\P6,\P7,\P8,\P9,\P10,\P11,\P12,\P13,\Sboy
			;display	"10",0Dh,0ah
			;Print!afall   \P11
		\}
		common match A =? B =? C =?  ==> P1  ==> P2  ==> P3  ==> P4 ==>P5 ==>P6\
   ==>P7  ==>P8  ==>P9  ==>P10 ==>P11  ==>P12  ==>P13 ==>Sboy,arg
   \{
 \UC!ABCJmp  \A,\B,\C,\P1,\P2,\P3,\P4,\P5,\P6,\P7,\P8,\P9,\P10,\P11,\P12,\P13,Sboy
			;display	"10",0Dh,0ah
			;Print!afall   \P11
		\}
}
;**********************************************
;	ДвигаемсяВнизУвеличивая [Rc_d]=+1 =ПокаНе 	$<\__>=>H_8_17 или	$<\/>=>H_1_7
;	ПродвигаемсяВверх	ПокаНе	$</``>=>P1	или 	$</\>=>P2
;	ПродвигаемсяПрямо	ПокаНе	$<__/>=>P1	или		$<\/>=>P2
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
R_r=2
;*********************
MACRO ВЫГРУЗКА_АМПЛИТУДЫ_В	 CX
{
				if R_r=1
		Bыгрузить_и_ЗаписатьРег_Если_0_Перейти	=>_FINI\
						=>cl
						and	cl,0FFh
			else
					if R_r=2
		Bыгрузить_и_ЗаписатьРег_Если_0_Перейти	=>_FINI\
						=> CX
					else
					Print!Rfall  "Обрабатываем пока байтные и словные данные"
					display 13,10
					end if
			end if
}
;************************************************************
;		ДвигаемсяВнизУвеличивая\
;				 Rc_d=+1	Rotch_b=+1	Npoint_w=+1\
;			ПокаНе $<\__>=>P7 или	$<\/>=>P12
;++++++++++++++++++++++++++++++++++++++++++++
MACRO ДвигаемсяВнизУвеличивая 			arg
{	LOCAL	H_h
common match P0===+PUS P01===+PUS P02===+PUS =ПокаНе =$<\__>==>P1  =или  =$<\/>==>P2,arg
	\{
\H_h:
				inc		\[P0]					;[Rc_d]
			Продвинули   BX <= CX
		ВЫГРУЗКА_АМПЛИТУДЫ_В	 CX
				inc	\[P01]				;[Rotch_b];количество отсчетов от Начала до к-ца УНИПРИМа
				inc	\[P02]				;[Npoint_w]		;Координата точки
\UC!ABCJmp  \AX,\BX,\CX,\H_h,\Ex2,\Ex3,\_Ex4,\_Ex5,\_Ex6,\P1,\_Ex9,\_Ex10,\_Ex11,\P2,\P2,\P2,\ExiPloxo
			\Print!Rfall	"Вниз"
			\Print!afall   \P1
			display		0Dh,0ah
	\}
}
;*******************************************************
;	ДвигаемсяяВверхУвеличивая\
;				 Rc_d=+1	Rotch_b=+1	Npoint_w=+1\
;			ПокаНе $</``>=>P4 или	$</\>=>P9
;+++++++++++++++++++++++++++++++++++++++++++++++
MACRO ДвигаемсяяВверхУвеличивая	arg
{
common match P0===+PUS P01===+PUS P02===+PUS =ПокаНе =$</``>==>P1  =или  =$</\>==>P2,arg
	\{
	LOCAL	\H_h
\H_h:
				inc		\[P0]					;[Rc_d]
			Продвинули   BX <= CX
		ВЫГРУЗКА_АМПЛИТУДЫ_В	 CX
				inc	\[P01]				;[Rotch_b];количество отсчетов от Начала до к-ца УНИПРИМа
				inc	\[P02]				;[Npoint_w]		;Координата точки
\UC!ABCJmp  \AX,\BX,\CX,\H_h,\Ex2,\Ex3,\P1,\_Ex5,\_Ex6,\_Ex7,\P2,\P2,\P2,\_Ex12,\_Ex13,\_Ex14,\ExiPloxo
			\Print!Rfall	"Вверх"
			\Print!afall   \P1
			display		0Dh,0ah
	\}
}
;*******************************************************
;	ДвигаемсяПрямоУвеличивая\
;				 Rc_d=+1	Rotch_b=+1	Npoint_w=+1\
;	ПокаНе	$<__/>=>P5	или		$<``\>=>P6
;+++++++++++++++++++++++++++++++++++++++++++++
MACRO ДвигаемсяПрямоУвеличивая	arg
{	LOCAL	H_h
common match P0===+PUS P01===+PUS P02===+PUS =ПокаНе =$<__/>==>P1  =или  =$<``\>==>P2,arg
	\{
	LOCAL	\H_h
\H_h:
				inc		\[P0]					;[Rc_d]
			Продвинули   BX <= CX
		ВЫГРУЗКА_АМПЛИТУДЫ_В	 CX
				inc	\[P01]				;[Rotch_b];количество отсчетов от Начала до к-ца УНИПРИМа
				inc	\[P02]				;[Npoint_w]		;Координата точки
\UC!ABCJmp  \AX,\BX,\CX,\H_h,\Ex2,\Ex3,\_Ex4,\P1,\P2,\_Ex7,\_Ex9,\_Ex10,\_Ex11,\_Ex12,\_Ex13,\_Ex14,\ExiPloxo
			\Print!Rfall	"Прямо"
			\Print!afall   \P1
			display 0Dh,0ah
	\}
}