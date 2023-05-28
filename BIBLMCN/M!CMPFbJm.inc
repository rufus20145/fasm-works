;			M!CMPFbJm	-полная(F) максимальная проверка отношений двух байт
;	ВсяИнфаОтношенийБайтМножествПереходы
;Проверка работы макроса     C:\FASM\BIBLMCN\TEST\M!CMPFbJm.asm
;**************************************************
   MACRO M!CMPFbJm  GA,GB, Kd,PS,ka,kb,m1,m2,m3,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14
{
   LOCAL	MEXI,M!ISTEK,DBAab,DBAba,P6BAab,POBA,P6BA,PBAab,OBA,Dab,P6ABab,Rba,OAB,\
	Pr8,Pr7,Pr6,Pr5,Pr4,Pr3,Pr2,Pr1,Pr0,O8BAab,P8BAab,R8BAba,R8BA,P8BA,D7ab,P7ABab,D7ba,P7AB,CKL
	УпряталиРегистры	EAX,EBX,ECX,EDX,EBP
			mov	BL,GB		;2-й операнд
			mov	AL,GA		;1-й операнд
		ЧислоЕдиницБайте  AL	 =ka			;Для количественной оценки
							;ka = кол-во ед. в А
		ЧислоЕдиницБайте  BL	 =kb			;Для количественной оценки
							;kb = кол-во ед. в B
		and	al,0FFh			;A&E
	jne	@F
		and	bl,0FFh			;B&E
	jne	Pr1					;JmJ	A=0 B#0 => A<B закончили
	jmp	Pr0					;JeJ  	A=0  B=0   A=B
@@:
		and	bl,0FFh
	je	Pr2					;JgJ	A#0 B=0 => A>B закончили
;*********
		mov	BH,al  			;чтобы A(bh)  B(bl) были в одной строке
		mov	CL,AL
		xor	CL,BL			;в CL маска
							;AxorB=>N1-получим несовпадающие б. в A,B
	je	Pr3					;JeJ  	оба операнда A=B ==>
;**************Далее нетривиальные ситуации**********
		ЧислоЕдиницБайте  CL	 =m1

		mov	CH,AL			;в СН совпадающие биты
		and	CH,BL			; A & B  => N2  - получение совпадающих бит в  A и  B

		ЧислоЕдиницБайте  CH	 =m2
	mov	AH,AL				;  AH  все биты и вA  и в B
	or	AH,BL				;A  v B  => N3 - получение бит присутствующих в A и  B
		ЧислоЕдиницБайте  AH	 =m3

		and	BL,CL			;после выделения маски A
	jne	@F					;A маскир. пересекается с маскированное
							;А либо  погружено и нет  1, либо они не зависимы
	jmp	Pr4					;JgJ;in B=0 A>B  B?A  B в A зависимы
@@:
		and	BH,CL			;	A(bh)
	je	Pr5					; II направление: JmJ	 A?B  	A<B
;*****************************************

;*************************Есть пересекающиеся и не пересекающиеся разряды ***
		and	CH,0FFh			;Есть ли пересекающиеся разряды
	jz	Pr6					; III направление: нет пересекающихся разрядов
;******************************IV направление*************************
;Если есть совпадающие и не совпадающие, то имеет смысл рассмотреть только общую совпадающую часть,
; т.е. та, которая включается в другую, а это N2  = A&B
;***Есть совпадающие ************** Pr7	  +  	Pr8   И то и другое
	mov	BP,08080h			;Остались операнды с единичками в разных разр-ах
	mov	ECX,8	      		;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0   на выx. смотреть флаг PF  XNOR рр TEMP[0-7]
		shr	BP,1			;	if PF=0  		JNP  METKA
	loop	@B				;
	JMP	M!ISTEK
@@:							;A(ah)  B(al)
		and	AL,0FFh			;A=0 B#0  => A<B  else A>B   BL=?
	jne	P8BA				;B=1 A=0  =>A<B верхняя B больше A
							;B=0 A=1  =>A>B
;*************  Pr7
		push	ECX			; vA=?(A) - номер ст. единички в [A >B
;************************** верхняя грань А  больше верхней грани  B
		and	BP,0FFh			;убираем старшие разряды чтобы щупать B
	jmp	P7AB
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0   на выx. смотреть флаг PF
P7AB:
		shr	BP,1			;		if PF=0
	loop	@B				;
	JMP	M!ISTEK
@@:
			push	ECX		; vB=?(B) - номер ст. единички в (B => [A(B
;***********************  Проверяем нижнюю грань
 	mov	BP,0101h			;Остались операнды с единичками в разных разр-ах
	mov	ECX,8	      		;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
		shl	BP,1			;
	loop	@B
	JMP	M!ISTEK
@@:
		and	AL,0FFh			;A=0 B#0  => A<B  else A>B   BL=?
	jne	P7ABab
;******************* 			 [A    (B        b)	a]
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; na=?(A) - номер младшей единички a]
			and	BP,0FFh		;убираем старшие разряды чтобы щупать B
	jmp	D7ba
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
D7ba:
		shl	BP,1			;	if PF=0
	loop	@B
	JMP	M!ISTEK
;***********************  Проверяем нижнюю грань
@@:
		mov	EAX,9
		sub	EAX,ECX
			push	EAX		; nb=?(B) - номер младшей единички b)
		xor	EAX,EAX
			pop	EDX			; nb
			pop	ECX			; na
			pop	EBX			; vB
			pop	EAX			; vA
		shl	EAX,24
		shl	EBX,16			; vA vB
		or	EAX,EBX			; vA vB
		shl	EDX,8			; vA vB nb
		or	EAX,EDX
		or	EAX,ECX			; vA vB nb na
			mov	PS, V11		;PrABba	EQU  V11
			mov	Kd,EAX		;[A(B b)a]
;Если есть совпадающие и не совпадающие, то имеет смысл рассмотреть только общую совпадающую часть,
; т.е. та, которая включается в другую, а это N2  = A&B  и это свойство можно рассмотреть отдельно N2 ? 0FFh,
; обращаясь к той же операции сравнения множеств после завершения данных направлений  p11 p12 p13 p14
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	jmp	P11					; P81 A>B Пересекающиеся проверять отдельно A&B
;***  Координаты границ в Kd=Koordint =>  [A     (B	 a]	 b)
;*** Закончили с комб.  пересечение до [A , после до (B, после до b) и до a]
;*******************
;***************************************************************************
P7ABab:
;******************* 			 [A    (B        b)	a]
		mov	EAX,9
		sub	EAX,ECX		;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; nb=?(B) - номер младшей единички b)
		and	BP,0FF00h		;убираем младшие разряды чтобы щупать A
	inc	ECX
	jmp	D7ab
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
D7ab:
		shl	BP,1			;if PF=0
	loop	@B				;
	JMP	M!ISTEK
;***********************  Проверяем нижнюю грань
@@:
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; na=?(A) - номер младшей единички a]
		xor	EAX,EAX
			pop	EDX			; na
			pop	ECX			; nb
			pop	EBX			; vB
			pop	EAX			; vA
		shl	EAX,24			; vA
		shl	EBX,16			; vB
		or	EAX,EBX			; vA vB
		shl	EDX,8			; nb
		or	EAX,EDX			; vA vB na
		or	EAX,ECX			; vA vB na nb

			mov	PS, V12		;PrABab  V12
			mov	Kd,EAX		;[A(B a]b)
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	jmp	P12					;P82 A>B Пересекающиеся проверять отдельно A&B
;******************** Закончили с комб. Pr7AB ********
;*************  Pr8
;***************** комб.  P8BA   -  верхняя грань B  больше верхней грани  A**********
P8BA:
		push	ECX		 	; vB=?(B) - номер ст. единички  в (B
		and	BP,0FF00h		;убираем младшие разряды чтобы щупать A
	jmp	R8BA
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0   на выx. смотреть флаг PF
R8BA:
		shr	BP,1			;if PF=0
	loop	@B
	JMP	M!ISTEK
@@:
		push	ECX			; vA=?(A) номер старшей единички в [A => (B [A
;***********************  Проверяем нижнюю грань
 	mov	BP,0101h			;Остались операнды с единичками в разных разр-ах
	mov	ECX,8	      		;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
		shl	BP,1			;
	loop	@B
	JMP	M!ISTEK
@@:
		and	AL,0FFh			;A=0 B#0  => A<B  else A>B   BL=?
	jne	P8BAab
;P8BAba ******************************   (B[A    b)  a]   - далее
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; na=?(A) - номер младшей единички a]
		and	BP,0FFh			;убираем старшие разряды чтобы щупать B
	jmp	R8BAba
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
R8BAba:
		shl	BP,1			;if PF=0
	loop	@B
	JMP	M!ISTEK
;***********************  Проверяем нижнюю грань
@@:
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; nb=?(B) - номер младшей единички b)
		xor	EAX,EAX
			pop	EDX			; nb
			pop	ECX			; na
			pop	EBX			; vA
			pop	EAX			; vB
		shl	EBX,24			;  vB
		shl	EAX,16			; vB   vA
		or	EAX,EBX			; vB   vA
		shl	EDX,8
		or	EAX,EDX			;vB   vA   nb
		or	EAX,ECX			;vB   vA   nb   na
			mov	Kd,EAX		;(B[A    b)  a]
			mov	PS, V13
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
							;[PrSovm],PrBAba	EQU  V13
	jmp	P13					;P83      A<B Пересекающиеся проверять отдельно A&B
;************************************
P8BAab:						; (B[A a] b)
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; nb=?(B) - номер младшей единички b)
		and	BP,0FF00h		;убираем младшие разряды чтобы щупать A
	jmp	O8BAab
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
O8BAab:
		shl	BP,1			;	if PF=0
	loop	@B				;
	JMP	M!ISTEK
;***********************  Проверяем нижнюю грань
@@:
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; na=?(A) - номер младшей единички a]
		xor	EAX,EAX
			pop	EDX			; na
			pop	ECX			; nb
			pop	EBX			; vB
			pop	EAX			; vA
		shl	EBX,24			; vB
		shl	EAX,16			; vA
		or	EAX,EBX			; vB vA
		shl	EDX,8			; na
		or	EAX,EDX			; vB vA na
		or	EAX,ECX			; vB vA na nb
			mov	Kd,EAX		; [Koordint],EAX  =(B[A a] b)
			mov	PS, V14 	;[PrSovm],PrBAab	EQU  V14
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	jmp	P14					;P84	 A<B Пересекающиеся проверять отдельно A&B
;*****************************************************
;******************************************************
Pr0:						;A=0  B=0   A=B
			mov	m1,0
			mov	m2,0
			mov	m3,0
			mov	Kd,0
			mov	PS, V1 		;[PrSovm],V1 - признак
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	JMP	P1					;A=B
;*****************************
Pr1:						;A=0 B#0 => A<B
			mov	cl,kb
 			mov	m1,cl
							;mov	m2,0  Замещаем KOL  кол-во единиц в B
							;mov	m3,0  Замещаем KACH  степень изменений B
		K!LKACHinB	BL,m2,m3
		and	bx,0FFh			;выделяем только B
		BSF	cx,bx			; номер младшей единички в B
		mov	al,cl			; номер не больше 7
		BSR	cx,bx			; номер старшей единички в  B
		mov	ah,cl
		and	EAX,0FFFFh
			mov	Kd,EAX
			mov	PS, V2 		;[V2   A<B закончили		признак
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	JMP	P2					; A<B
;******************
Pr2:						;A#0 B=0 => A>B
			mov	cl,ka
 			mov	m1,cl
							;mov	m2,0
							;mov	m3,0 Замещаем KACH  степень изменений A
		K!LKACHinB	AL,m2,m3		;Замещаем m2=KOL  кол-во единиц в A
		and	ax,0FFh			;выделяем только A
		BSF	cx,bx			; номер младшей единички в A
		mov	al,cl			; номер не больше 7
		BSR	cx,bx			; номер старшей единички в  A
		mov	ah,cl
		and	EAX,0FFFFh
			mov	Kd,EAX
			mov	PS, V3 		;V3 - признак
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	JMP	P3				;A>B
;**************************
Pr3:						;оба операнда A=B ==>
		mov	m1,0
		K!LKACHinB	AL,m2,m3		;Замещаем m2=KOL  кол-во единиц в A
		and	ax,0FFh			;выделяем только A
		BSF	cx,bx			; номер младшей единички в A
		mov	al,cl			; номер не больше 7
		BSR	cx,bx			; номер старшей единички в  A
		mov	ah,cl
		and	EAX,0FFFFh
			mov	Kd,EAX		;число всех и в А  и в B
			mov	PS, V4
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	JMP	P4				;A=B
;************************   Поглощение *******  A  включает в себя   B     P5 *******
Pr4:
		K!ACHinB		bh,m3		;в А   m3 =KACH (в A);
							; ka-kb=непересек=m1;  m2 = kb  m3=ka   =KACH в A
		ror	bx,8			;сохраняем младшие разряды
		BSF	cx,bx			; номер младшей единички в A
		mov	al,cl			; номер не больше 7
		BSR	cx,bx			; номер старшей единички в  А
		mov	ah,cl
		rol	bx,8			;B
		BSR	cx,bx			; номер старшей единички B
		shl	EAX,16			;<=
		mov	ah,cl			; номер не больше 7  старшей единички B
		BSF	cx,bx			; номер младшей единички B
		mov	al,cl			; номер не больше 7
			mov	Kd,EAX		;диапазон включения A  в  B
			mov	PS, V5 		;[PrSovm],V5      - признак
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	JMP	P5					;	in B=0 A>B

;************************ Поглощение *B  включает в себя   A *********  P6 *********************
Pr5:						; B  включает в себя   A
		K!ACHinB		bl,m3		;в B     m3 =KACH в B
							; kb-ka=непересек=m1;  m2 = ka  m3=kb
		ror	bx,8
		BSF	cx,bx			; номер младшей единички A
		mov	al,cl
		BSR	cx,bx			; номер старшей единички  A
		mov	ah,cl			; AX  номер старшей единички  A младшей единички
		rol	bx,8			; возврат  B
		BSR	cx,bx			; номер старшей единички B
		shl	CX,8			;CX <=
		mov	BP,CX
		BSF	cx,bx			; номер младшей единички B
		or	CX,BP
		shl	ECX,16
		or	EAX,ECX
			mov	Kd,EAX		;диапазон включения B  в  А
			mov	Kd,0
			mov	PS, V6		; [PrSovm],V6  - признак
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	JMP	P6					;in A=0 A<B
;************************************ P6 ********************************
;*********** нет пересекающихся разрядов ***P7-P10 *Множества не пересекаются *************************
Pr6:
;***************************[ (     ) ]  v [ (    ]  )& { [ ] ( ) } v (  [   ] ) v (  [  ) ] & { () [ ]}
;
	mov	BP,08080h			;Остались операнды с единичками в разных разр-ах
	mov	ECX,8	      		;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		and	AX,BX			;BH = A  BL=B  одновременно провер.ст.ед
	jne	@F					; ZF=1 if 0
		shr	BP,1
	loop	@B				;
	JMP	M!ISTEK
;************
@@:							;A(ah)  B(al)
		and	AL,0FFh			;A=0 B#0  => A<B  else A>B   BL=?
	jne	P6BA				;JmJ	;B=1 A=0  =>A<B верхняя B больше A
		push	ECX			; vA=?(A) - номер ст. единички в [A
;************************** верхняя грань А  больше верхней грани  B
		and	BP,0FFh	;убираем старшие разряды чтобы щупать B 	A>B
	jmp	OAB
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0   на выx. смотреть флаг PF
OAB:
		shr	BP,1			;		if PF=0
	loop	@B				;
	JMP	M!ISTEK
@@:
		push	ECX			; vB=?(B) - номер ст. единички в (B => [A(B
;***********************  Проверяем нижнюю грань
 	mov	BP,0101h			;Остались операнды с единичками в разных разр-ах
	mov	ECX,8	      		;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
		shl	BP,1			;
	loop	@B				;]
	JMP	M!ISTEK
@@:
		and	AL,0FFh
	jne	P6ABab
;******************* 			 [A    (B        b)	a]
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; na=?(A) - номер младшей единички a]
		and	BP,0FFh			;убираем старшие разряды чтобы щупать B
	jmp	Rba
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
Rba:
		shl	BP,1			;if PF=0
	loop	@B
	JMP	M!ISTEK
;***********************  Проверяем нижнюю грань
@@:
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; nb=?(B) - номер младшей единички b)
		xor	EAX,EAX
			pop	EDX			; nb
			pop	ECX			; na
			pop	EBX			; vB
			pop	EAX			; vA
		shl	EAX,24
		shl	EBX,16			; vA vB
		or	EAX,EBX			; vA vB
		shl	EDX,8			; vA vB nb
		or	EAX,EDX
		or	EAX,ECX			; vA vB nb na

			mov	Kd,EAX		; [Koordint],EAX  = [A(B b)a]

			mov	PS, V7 		;[PrSovm],PrABba	;V7
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	jmp	P7					;  	A>B
;***  Координаты границ в Koordint
;*** Закончили с комб. P6ABba и пересечение до [A , после до (B, после до b) и до a]
;*******************  			[A     (B	 a]	 b)
P6ABab:
;******************* 			 [A    (B        b)	a]
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; nb=?(B) - номер младшей единички b)
		and	BP,0FF00h		;убираем младшие разряды чтобы щупать A
	jmp	Dab
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
Dab:
		shl	BP,1			;	if PF=0
	loop	@B
	JMP	M!ISTEK
;***********************  Проверяем нижнюю грань
@@:
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; na=?(A) - номер младшей единички a]
		xor	EAX,EAX
			pop	EDX			; na
			pop	ECX			; nb
			pop	EBX			; vB
			pop	EAX			; vA
		shl	EAX,24			; vA
		shl	EBX,16			; vB
		or	EAX,EBX			; vA vB
		shl	EDX,8			; nb
		or	EAX,EDX			; vA vB na
		or	EAX,ECX			; vA vB na nb
			mov	PS, V8 			;[PrSovm],PrABab
			mov	Kd,EAX			;[Koordint],EAX  = [A(B a]b)
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	jmp	P8				;P72		A>B
;******************** Закончили с комб. P6AB ********
;***************** комб.  PrBA **********
P6BA:
		push	ECX		 	; vB=?(B) - номер ст. единички  в (B
;************************** верхняя грань B  больше верхней грани  A     A<B
		and	BP,0FF00h		;убираем младшие разряды чтобы щупать A
	jmp	OBA
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0   на выx. смотреть флаг PF
OBA:
		shr	BP,1			;if PF=0
	loop	@B
	JMP	M!ISTEK
@@:
		push	ECX			; vA=?(A) номер старшей единички в [A => (B [A
;***********************  Проверяем нижнюю грань
 	mov	BP,0101h			;Остались операнды с единичками в разных разр-ах
	mov	ECX,8	      		;рр 9&1;10&2;11&3; 12&4; 13&5; 14&6; 15&7р ;16&8-исключ.
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
		shl	BP,1			;
	loop	@B
	JMP	M!ISTEK
@@:
		and	AL,0FFh			;A=0 B#0  => A<B  else A>B   BL=?
	jne	PBAab
;PBAba ******************************   (B[A    b)  a]
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; na=?(A) - номер младшей единички a]
		and	BP,0FFh			;убираем старшие разряды чтобы щупать B
	jmp	DBAba
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
DBAba:
		shl	BP,1			;if PF=0
	loop	@B
	JMP	M!ISTEK
;***********************  Проверяем нижнюю грань
@@:
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; na=?(A) - номер младшей единички a]
		xor	EAX,EAX
			pop	EDX			; nb
			pop	ECX			; na
			pop	EBX			; vA
			pop	EAX			; vB
		shl	EBX,24			;  vB
		shl	EAX,16			; vB   vA
		or	EAX,EBX			; vB   vA
		shl	EDX,8
		or	EAX,EDX			;vB   vA   nb
		or	EAX,ECX			;vB   vA   nb   na
 		mov	PS, V9 			;[PrSovm],PrBAba
		mov	Kd,EAX			; [Koordint],EAX = (B[A   b)   a]
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	jmp	P9					;P73		A<B
;************************************
PBAab:						; (B[A a] b)
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; nb=?(B) - номер младшей единички b)
		and	BP,0FF00h		;убираем младшие разряды чтобы щупать A
	jmp	DBAab
@@:
		mov	AX,BP
		and	AX,BX
	jne	@F					; ZF=1 if 0
DBAab:
		shl	BP,1			;if PF=0
	loop	@B
	JMP	M!ISTEK
;***********************  Проверяем нижнюю грань
@@:
		mov	EAX,9
		sub	EAX,ECX			;7 - 0  6  - 1  5 - 2  4- 3  3 - 4  2 - 5   1 -6  0 -  7
			push	EAX		; na=?(A) - номер младшей единички a]
		xor	EAX,EAX
			pop	EDX			; na
			pop	ECX			; nb
			pop	EBX			; vB
			pop	EAX			; vA
		shl	EBX,24			; vB
		shl	EAX,16			; vA
		or	EAX,EBX			; vB vA
		shl	EDX,8			; na
		or	EAX,EDX			; vB vA na
		or	EAX,ECX			; vB vA na nb
		mov	PS, V11 		;[PrSovm],PrBAab	; V10
		mov	Kd,EAX 			;[Koordint],EAX	= (B[A a] b)
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	jmp	P10					;P74	A<B
;********************* Закончили с комб.  Pr6BA **************
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через
M! :
M!ISTEK:
	P!rAdrStop   =BalakirevNE ERROR  in_macro C!MPMbJm
MEXI:		 				;продолжение после блока
}
;********************************************************************************
MACRO ВсяИнфаОтношенийБайтМножествПереходы arg
{
	common match  GA==? GB == Kd ==PS ==ka ==kb ==m1 ==m2 ==m3\
==>P1 ==>P2 ==>P3 ==>P4 ==>P5 ==>P6 ==>P7 ==>P8 ==>P9 ==>P10 ==>P11==>P12 ==>P13 ==>P14,arg
\{
M!CMPFbJm  \GA,\GB,\Kd,\PS,\ka,\kb,\m1,\m2,\m3,\P1,\P2,\P3,\P4,\P5,\P6,\P7,\P8,\P9,\P10,\P11,\P12,\P13,\P14
\}
}
;************************************************