;0	C!abcJmp

;6 C!abcKoJmp  RGa,RGb,RGc,Ko,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13  	;42
;7 C!abcPr  RGa,RGb,RGc,Ko													;390
;8 СучетомОтношений!Получить!Перейти arg									;731
;9 Relation!Write!Go	arg													;736
;10 C!abcRoJmp  RGa,RGb,RGc,Ko,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,PR1,PR2,PR3,PR4,PR5,PR6,PR7,PR8,PR9,PR10,PR11,PR12,PR13
;11 C!MPabcKo  RGa,RGb,RGc,Ko
;12 J!mA?B  RGA,RGB,Pr0,Pr1,Pr2
;*МАКРОС Команды C!abcJmp RGa,RGb,RGc,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13
MACRO C!abcJmp  P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,Sboy
{
;*** 1
 УпряталиРегистры	EBX,ECX,EDX
;*** 2
;ПеренеслиB	(al=:Ga) (bl=:Gb) (cl=:Gc)			;входные параметры
					mov	al,Ga
					mov	cl,Gcmov	bl,Gb
;*** 3
;Продублировал		dh=bl
					mov	dh,bl
;*** 4
		Сравнил_A_B_Дал\
			  al=bl\
				$Признак_0_1_2_в=:dl\
						$ПриСбое=>Sboy						;Sboy
;*** 5										;Восстановил по дубликату al=dl
					mov al,dl
					mov	bl,cl
;*** 6
		Сравнил_A_B_Дал\
			al=bl\
				$Признак_0_1_2_в=:EAX\
						$ПриСбое=>Sboy						;M!ISTEK
;*** 7Получение значения переключателя через Объединение признаков сравнения A&B B&C
						shl al,2
						or	al,dl				;Объединить  признаки al=(al<-2) ^bl
;*** 8
						ВосстановилиРегистры EBX,ECX,EDX
;*** 9			Перешли_по_переключателю
;								$Регистра=EAX\
;=>P1 =>P2 =>P3 =>P4 =>P5 =>P6 =>P7 =>P8 =>P9 =>P10 =>P11 =>P12 =>P13 =>P14 =>P15 =>P16
;***
			S!WITCH	EAX,Ga,Gb,Gc,P3,P6,P5,Sboy,P7,P1,Pmin,Sboy,P4,Pmax,P2,Sboy
;*** 10
Pmin:
			СучетомОтношенийbПерейти\
					al=?cl\
						=P11 >P12  < P13\
								$ПриСбое=>M!ISTEK
;*** 11
Pmax:
			СучетомОтношенийbПерейти\
					al=?cl\
							=P8 >P9  < P10\
									$ПриСбое=>M!ISTEK
;*** Всего 11 шагов
}
;*****************************************************
;	СучетомОтношений!Получить!Перейти		AX ? BX ? CX =>\
;			Сравнили!Присвоили!Перешли AX?BX?CX? =>\
;	rg=PRA  rg=PRE rg=PRO rg=PRX  rg=PRY rg=PRI rg=PRJ  rg=PRH rg=PRG rg=PRK rg=PRC rg=PRS rg=PRZ
;	   rg=PRA=>P1 	rg=PRE=>P2     =>P3        =>P4       =>P5     =>P6     =>P7      =>P8       =>P9     =>P10     =>P11    =>P12    =>P13
;******************************************************
;Получить!Отношения  EAX ? EBX ? ECX \
;   dl =PRA dl =PRE dl =PRO dl = PRX dl = PRY dl = PRI dl = PRJ dl = PRH dl =PRG dl = PRK dl = PRC dl = PRS dl = PRZ
;******************МАКРОС Команды C!abcJmp  RGa,RGb,RGc,Ko,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13
;			ИСПОЛЬЗУЕМЫЕ МАКРОСЫ
;    в данном  МАКРОСЕ				в Тесте
;include 'C:\FASM\BIBLMC\Rpushpop.inc'
					;include 'C:\FASM\BIBLMC\C!MPabJm.inc'
					;include 'C:\FASM\BIBLMC\N16inASCII.inc'
;include 'C:\FASM\BIBLMC\P!rAdrStop.inc'
					;include 'C:\FASM\BIBLMC\ZeroReg.inc'
					;include 'C:\FASM\BIBLMC\C!abcPr.inc'
					;include 'C:\FASM\BIBLMC\P!rTxtAdr.inc'
;Получить!Отношения  EAX ? EBX ? ECX \
;   dl =PRA dl =PRE dl =PRO dl = PRX dl = PRY dl = PRI dl = PRJ dl = PRH dl =PRG dl = PRK dl = PRC dl = PRS dl = PRZ
;*************Cравнение трех байт с минимальным кол-вом операций -  **********************
;	C!abcPr  RGa,RGb,RGc,Ko,		сравнение 3 переменных A,B,C и код ответа в Ko(регистр байтовый)
;C!MPabcJm 	(PRa=1),(PRe=2),(Pro=3),(PRx=4),(PRy=5),(PRi=6),(Prj=7),(PRh=9),(Prg=10),\
;		(PRk=11),(PRc=12),(PRs=13),(PRz=14)
;ИСПОЛЬЗУЕМ:  	УпряталиРегистры		EAX,EBX,ECX.....
;		ВостановилиРегистры	EAX,EBX,ECX.....
;		C!abcJm  RGa,RGb,RGc,Ko
;***************Установление отношения (A?B?C) с кодом ответа Ko  и переход по 13 направлениям******************
MACRO C!abcKoJmp  RGa,RGb,RGc,Ko,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13
{
	ОпределитьКонстанты   PR@,(a=1),(e=2),(o=3),(x=4),(y=5),(i=6),(j=7),(h=9),(g=10),(k=11),(c=12),(s=13),(z=14)
LOCAL	MISTEK,CeBe010,CeBe101,AeBe011, AeBe100,maxCeAe001,minCeAe110,PRyi,PRxj,PRch,RE@F,CMNE
	УпряталиРегистры	ECX,EDX,ESI,EDI,EBP
						;ОбнулитьРегистры  EAX,EBX,ECX,EDX
		mov	al,RGa
						;можно and al,-1     je PrBC
		mov	bl,RGb
						;можно and bl,-1     je PrAC
		mov	cl,RGc			;cl=C
						;можно and cl,-1     je PrAB
						;mov	dl,al
		mov	dl,cl
		xor	dh,dh			;dh=0
		shl	EDX,16			;подвинули  	0  С  0  0
		mov	dl,bl			;	 -  	0  C  0  B
		mov	dh,al			;     	EDX =>	0  С A  B   >16 C  dh=A dl =B
		mov	ESI,EDX			;	ESI =>	0  С A  B   >16 C  dh=A dl =B

		mov	ah,al
		xor	ah,-1			; не A

		mov	bh,bl
		xor	bh,-1			; не B
		or	dl,al			; A v B (dl=B)
		or	ah,bh			;(не A) v (не B)

		mov	bh,bl
		xor	bh,al			;	BH=>  Mab=(AB)xor
	JNE	RE@F
		mov	ch,cl
		xor	ch,-1			; не C
		or	dl,cl			;DL =>   все значащие разряды DL=ABCor
		or	ah,ch			;AH =>(не A) v (не B) v (не С)

		and	dl,ah			; все общие единички без той которая встреч. 3 раза
	JNE	@F				;все не равны  ____
		mov	EBX,P3			;адрес переключателя
		mov	ah,PR@o			;  примитив	O
	jmp	CMNE				; ++++>1 выход  PRo
@@:
	jmp	PRyi				;__/   	```\  al=A=B=bl  ESI =0  С A  B  cl=C
;*********************************************ПОВТОР от JNE	RE@F до*@@:*******
RE@F:
		mov	ch,cl
		xor	ch,-1			; не C
		or	dl,cl			;DL =>   все значащие разряды DL=ABCor
		or	ah,ch			;AH =>(не A) v (не B) v (не С)

		and	dl,ah			; все общие единички без той которая встреч. 3 раза
;*****************************************************
@@:
		mov	dh,dl
		shl	EDX,8
		mov	dl,dh
		and	EDX,0FFFFFFh		;Маска общих значащих разрядов для 3-х переменных
						;1.   	EDX=ABCor,ABCor,ABCor  кроме 3-х встреч.
		mov	ch,cl
		xor	ch,bl			;	CH=Mbc=(BC)xor
		mov	BL,BH			;	EBX= [X]  [X]  [Mab] [Mab]
	JNE	@F
	jmp	PRxj				;/```   \__  B=C   A?B   BX= [Mab] [Mab]  SI= [A] [B]
@@:
		mov	ah,ch			;AH=(BC)xor
		shl	ECX,8			;ECX=[0] [(BC)xor]  [X]  [X]
		mov	cl,ah			;ECX =[0] [(BC)xor]  [X] [(BC)xor]
		xor	ch,ch			;	ECX= [0]  [Mbc] [0] [Mbc]

		xor	ah,bh			;[Mbc] xor [Mab]  => [Mac]
		mov	al,ah			;AX=[Mac] [Mac]
	JNE	@F
	jmp	PRch				; \/ v  /\  A=C    A?B   BX= [Mab] [Mab]  DX = [A  B]
   @@:
		xchg	EDX,ESI			;ESI =>	0  С A  B  	EDX=[Mabc]
		and	EDX,ESI			; выделили не повторяющиеся 3 раза разряды
		mov	EBP,EDX			;?Далее только не равные значения
						;	EDX = [0  С A  B]  & [Mabc]
		mov	DI,AX			;	AX= [0]   [Mca]   [Mca]
						;	BX= [X]    [X]      [Mab] [Mab]
		mov	ESI,ECX			;	ECX= [0]  [Mcb]      [0]    [Mcb]
					;Встречаются только парные  единички для маски ABC
;******************************  предварительная проверка на 0 значения A B      B  C  AC=????
	mov	EAX,0808080h		;Остались операнды только с единичками в разных разрядах
	mov	EBP,EAX
	mov	ECX,7			;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		and	EAX,EDX		;
	jne	@F			; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	EBP,1		;		if PF=0  		JNP  METKA
		mov	EAX,EBP
	loop	@B			;     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;*************************************************** A=0 B=0 C=0 не должно быть
@@:					;смотрим по выделенным разрядам
		test	EAX,0FF0000h	;C=?    здесь общие единички могут быть только попарно
	jne	@F			;Ce =1	Ae=?	Be=?
			test	AX,0FF00h	; Ce=0     Ae=?  Be=?
		je	maxCeAe001		; Ce=0     Ae=0     Be =1=> max  /\
			and	al,0FFh		;Be=?
		jne	AeBe011			; Ce=0     Ae=1	Be=1		C<A  C<B
		jmp	CeBe010			; +Ce=0     Ae=1	Be=0	 A> B  A>C
@@:	and	al,0FFh			; Ce =1	Ae=	Be=?
	JNE 	CeBe101			;+ Ce =1   Ae=	Be=1=>  Ae=0   A<B   A<C только 2 единички A С
		test	AX,0FF00h	; Ce =1   Ae=?	Be=0 =>
	JE 	AeBe100		    	; Ce =1    Ae=0	Be=0		C>A   C>B
	jmp 	minCeAe110		; Ce =1    Ae=1	Be=0   =>	A>B  B<C      \/
;*******************************+*
CeBe010:					;	Ce=0     Ae=1	Be=0	 A> B  A>C
		and	EDX,ESI		;Mcb	Ce=?		Be=?
@@:
		shr	EBP,1		;следующую единичку т.к. C=0 и B=0 были одновременно
		mov	EAX,EBP
		and	EAX,EDX		;С  В    теперь повторяющихся единичек нет
	jne	@F			; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;**********************************+**
@@:
		mov	ah,PR@a
		mov	EBX,P1
		and	al,0FFh		; Ce =     Ae=1	Be=?	A>B  A>C
	jne	CMNE			;++++>  5  Ce=0  Ae=1 B=1  B>C  => A>B> C    вниз
		mov	ah,PR@s
		mov	EBX,P12
	jmp	CMNE			;++++>  6   B=0    A>B<C  C=1    => A>B<C   A >C   `\/
;*******************************************+*
CeBe101:					; Ce =1   Ae=0	Be=1=>Ae=0 A<B   A<C
		and	EDX,ESI		;Mcb
@@:
		shr	EBP,1		;следующую единичку т.к. B=1 и C=1 были одновременно
		mov	EAX,EBP
		AND	EAX,EDX		;С  В    теперь повторяющихся единичек нет
	jne	@F			; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;***********************************************+*
@@:						; Ce =   Ae=0	Be=?	A<B  A<C
		mov	ah,PR@k
		mov	EBX,P10
		and	al,0FFh
	jne	CMNE				;+> Ce =0 Ae=0   B=1 B>C  => A<B> C  A<C    ./\
		mov	EBX,P2
		mov	ah,PR@e
	jmp	CMNE				;+> Ce =1 Ae=0   B=0    B<C      => A<B<C   /
;*******************************************+*
AeBe011:						; Ce=0     Ae=1	Be=1		C<A  C<B
		and	DX,BX			;Mab  значащие и один раз встречаются единички
@@:
		shr	BP,1
		mov	AX,BP
		AND	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;******************************************+**
@@:
		mov	AH,PR@g
		mov	EBX,P9
		and	al,0FFh			;Be=?	C<A	C<B
	jne	CMNE				;+>  7 C=0 B =1 B>A  => A<B> C    C<A	 /\.
		mov	EBX,P1
		mov	AH,PR@a
	jmp	CMNE				;++++>  8	C=0   B=0  => A>B>C    \
;*****************************+*
 AeBe100:						; Ce =1    Ae=0	Be=0  =>    C>B   C>A
		and	DX,BX			;Mab  значащие и один раз встречаются единички
@@:
		shr	BP,1
		mov	AX,BP
		and	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;*****************************************+**
@@:
		mov	ah,PR@e
		mov	EBX,P2
		and	al,0FFh			;Ce =1 B=? => A=    C>B  C>A
	jne	CMNE				;+>  9   A<B  B=1    B>A  => C>B>A  A<B<C   /
		mov	EBX,P13
		mov	ah,PR@z			;C=1 A=1  B=0   \/
	jmp	CMNE			;+>  10  C>B  C=1   B=0  =>C>B<A    A>B<C   \/`
;*********************************************+*
maxCeAe001:					; Ce=0     Ae=0   B =1=> max 	 /\
		shr	EDX,8			; 0  C  A   равенство учли при формировании маски
		and	DX,DI			;EDI=Mac
@@:
		shr	BP,1
		mov	AX,BP
		and	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;**********************************************+**
@@:						; Ce=0     Ae=0   B =1=> max 	 /\
		mov	ah,PR@g
		mov	EBX,P9
		and	al,0FFh			;A=?
	jne	CMNE				;+>  11 A=1 C<A  => A<B> C  A>C  /\.
		mov	EBX,P10
		mov	ah,PR@k
	jmp	CMNE				;+>  12  A=0   C>A  => A<B>C    A<C	./\
;***********************************************+*
minCeAe110:					; Ce =1    Ae=1	Be=0   =>	A>B  B<C   \/
		shr	EDX,8			; 0  C  A   равенство учли при формировании маски
		and	DX,DI			;EDI=Ma
@@:
		shr	BP,1
		mov	AX,BP
		and	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;***********************************+**
@@:
		mov	ah,PR@s
		mov	EBX,P12
		and	al,0FFh			;A=?
	jne	CMNE				;+>  13  A=1 Be=0  C<A  => A>B< C  A>C   `\/
		mov	EBX,P13
		mov	ah,PR@z
	jmp	CMNE				;+>  14  A=0  Be=0 C>A  => A>B<C    A<C    \/`
	;}
;*************************************************al=A=B=bl  ESI =0  С A  B  cl=C
PRyi:					;__/   	```\   надо проверять B C
		mov	DH,AL
		mov	DL,CL		; CX =[A] [C]     C ? A   ~  C? B   одинаково  т.к. A=B
		xor	al,cl		;Mca
		mov	ah,al		;AX=Mac Mac
		and	DX,AX  		;and	CX,AX	      [C  A]  & [Mac Mac]
		and	DH,0FFh			;A=? после выделения маски С & (BC)
	jne	@F				;они не зависимы и надо продолжать
		mov	ah,PR@y			;A=0  Y	(A=B) & (A=B<C)   __/
		mov	EBX,P5
	jmp	CMNE				; 2 выход  PRy
@@:
		and	DL,0FFh			;C=?
	jne	@F				;C=1	надо продолжать
		mov	EBX,P6
		mov	ah,PR@i			;C=0 	(A=B) & (A=B>C)  ```\
	jmp	CMNE				;  3 выход  PRi
@@:
	mov	BP,08080h				;Остались операнды только с единичками в разных разрядах
	mov	ECX,7				;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		and	AX,DX			;
	jne	@F			; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	BP,1		;		if PF=0  		JNP  METKA
	loop	@B			;
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;************************************************************************************
@@:
		mov	ah,PR@y		;A=0 Y	(A=B) & (B<C)   __/ т.к. bl=B=0
		mov	EBX,P5
		and	al,0FFh		;
	jne	CMNE			;A=1  A>C   по флагу  if FP=1, который вырабат. если bl=0, т.е. B<C
		mov	EBX,P6
		mov	ah,PR@i		;C=0 	(A=B) & (B=A>C)  ```\
	jmp	CMNE
;***********************************
;*************************************************	;B=C   A?B   BX= [Mab] [Mab]  SI= [A] [B]
PRxj:						;/```   \__    C=B  пр-ка  A ? B
		and	BX,SI
		and	BH,0FFh			;A=?   после выделения маски  (A B)
	jne	@F				;A=1    A>B
		mov	EBX,P4
		mov	ah,PR@x			;A=0 	(A<B) & (B=C)  /```
	jmp	CMNE				;  2 выход  PRy
@@:
		and	BL,0FFh			;B=?
	jne	@F				;	надо продолжать
		mov	EBX,P7
		mov	ah,PR@j			;C=B 	(A>B) & (A>B=C)  ```\
	jmp	CMNE				;  3 выход  PRi
@@:
	mov	BP,08080h				;Остались операнды только с единичками в разных разрядах
	mov	ECX,7				;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		and	AX,BX			;
	jne	@F			; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	BP,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;************************************************************************************************************
@@:						; B>C
		mov	ah,PR@x			;A=0 	(A<B) & (B=C)  /``` т.к. bl=B=0
		mov	EBX,P4
		and	AL,0FFh			;BL=?
	jne	CMNE				;BL=1 A=0  =>A<B
		mov	EBX,P7
		mov	ah,PR@j			;A=1   	(A>B) & (B=C)  ```\
	jmp	CMNE
;***********************************; \/ v  /\  A=C    A?B   BX= [Mab] [Mab]  SI = [A  B]
PRch:						; A=C	\/	/\
		and	BX,SI
		and	BL,0FFh			;B=?   после выделения маски  (A B)
	jne	@F				;	B=1 переход
		mov	EBX,P11
		mov	ah,PR@c			;B=0 	(A>B) & (A=C) \/    т.к. bl=B=0
	jmp	CMNE				;
@@:
		and	BH,0FFh			;A=?
	jne	@F				;	надо продолжать
		mov	EBX,P8
		mov	ah,PR@h			;A=0 	(A<B) & (A=C) /\
	jmp	CMNE				;  3 выход  PRi
@@:
	mov	BP,08080h				;Остались операнды только с единичками в разных разрядах
	mov	ECX,7				;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		AND	AX,BX			;
	jne	@F				;
		shr	BP,1			;
	loop	@B				;
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
@@:
		mov	ah,PR@h			;B=0 	(B<A) & (A=C) \/    т.к. bl=B=0
		mov	EBX,P8
		and	AL,0FFh			;BL=B
	jne	CMNE				;BL=1 A=0  =>A<B  /\   PR@h
		mov	EBX,P11
		mov	ah,PR@c			;A=0 ```\	(A>B) & (A=C)
	jmp	CMNE			;
;***********************************

;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
MISTEK:
	P!rAdrStop	=BalarirevNE	macro C!MPabcJm	ERROR
;******************		Общий ВЫХОД
;************************************************************************************************************
;***********************************************
;
CMNE:
	mov	[Ko],AX		;результат сравнения
	ВостановилиРегистры	ECX,EDX,ESI,EDI,EBP
	jmp	EBX		;		FINISH
;*********************************
}
;			ИСПОЛЬЗУЕМЫЕ МАКРОСЫ
;    в данном  МАКРОСЕ				в Тесте
;include 'C:\FASM\BIBLMC\Rpushpop.inc'
					;include 'C:\FASM\BIBLMC\C!MPabJm.inc'
					;include 'C:\FASM\BIBLMC\N16inASCII.inc'
;include 'C:\FASM\BIBLMC\P!rAdrStop.inc'
					;include 'C:\FASM\BIBLMC\ZeroReg.inc'
					;include 'C:\FASM\BIBLMC\C!abcPr.inc'
					;include 'C:\FASM\BIBLMC\P!rTxtAdr.inc'
;*********************************************************************
MACRO C!abcPr  RGa,RGb,RGc,Ko		;Pr0,Pr1,Pr2	;=, >, <
{
	ОпределитьКонстанты   PR@,(a=1),(e=2),(o=3),(x=4),(y=5),(i=6),(j=7),(h=9),(g=10),(k=11),(c=12),(s=13),(z=14)
LOCAL	MISTEK,CMNEXI,CeBe010,CeBe101,AeBe011, AeBe100,maxCeAe001,minCeAe110,PRyi,PRxj,PRch,RE@F
	УпряталиРегистры	EBX,ECX,EDX,ESI,EDI,EBP
						;ОбнулитьРегистры  EAX,EBX,ECX,EDX
		mov	al,RGa
						;можно and al,-1     je PrBC
		mov	bl,RGb
						;можно and bl,-1     je PrAC
		mov	cl,RGc			;cl=C
						;можно and cl,-1     je PrAB
						;mov	dl,al
		mov	dl,cl
		xor	dh,dh			;dh=0
		shl	EDX,16			;подвинули  	0  С  0  0
		mov	dl,bl			;	 -  	0  C  0  B
		mov	dh,al			;     	EDX =>	0  С A  B   >16 C  dh=A dl =B
		mov	ESI,EDX			;	ESI =>	0  С A  B   >16 C  dh=A dl =B

		mov	ah,al
		xor	ah,-1			; не A

		mov	bh,bl
		xor	bh,-1			; не B
		or	dl,al			; A v B (dl=B)
		or	ah,bh			;(не A) v (не B)

		mov	bh,bl
		xor	bh,al			;	BH=>  Mab=(AB)xor
	JNE	RE@F
		mov	ch,cl
		xor	ch,-1			; не C
		or	dl,cl			;DL =>   все значащие разряды DL=ABCor
		or	ah,ch			;AH =>(не A) v (не B) v (не С)

		and	dl,ah			; все общие единички без той которая встреч. 3 раза
	JNE	@F				;все не равны  ____
		mov	ah,PR@o			;  примитив	O
	jmp	CMNEXI				; ++++>1 выход  PRo
@@:
	jmp	PRyi				;__/   	```\  al=A=B=bl  ESI =0  С A  B  cl=C
;*********************************************ПОВТОР от JNE	RE@F до*@@:*******
RE@F:
		mov	ch,cl
		xor	ch,-1			; не C
		or	dl,cl			;DL =>   все значащие разряды DL=ABCor
		or	ah,ch			;AH =>(не A) v (не B) v (не С)

		and	dl,ah			; все общие единички без той которая встреч. 3 раза
;*****************************************************
@@:
		mov	dh,dl
		shl	EDX,8
		mov	dl,dh
		and	EDX,0FFFFFFh		;Маска общих значащих разрядов для 3-х переменных
						;1.   	EDX=ABCor,ABCor,ABCor  кроме 3-х встреч.
		mov	ch,cl
		xor	ch,bl			;	CH=Mbc=(BC)xor
		mov	BL,BH			;	EBX= [X]  [X]  [Mab] [Mab]
	JNE	@F
	jmp	PRxj				;/```   \__  B=C   A?B   BX= [Mab] [Mab]  SI= [A] [B]
@@:
		mov	ah,ch			;AH=(BC)xor
		shl	ECX,8			;ECX=[0] [(BC)xor]  [X]  [X]
		mov	cl,ah			;ECX =[0] [(BC)xor]  [X] [(BC)xor]
		xor	ch,ch			;	ECX= [0]  [Mbc] [0] [Mbc]

		xor	ah,bh			;[Mbc] xor [Mab]  => [Mac]
		mov	al,ah			;AX=[Mac] [Mac]
	JNE	@F
	jmp	PRch				; \/ v  /\  A=C    A?B   BX= [Mab] [Mab]  DX = [A  B]
   @@:
		xchg	EDX,ESI			;ESI =>	0  С A  B  	EDX=[Mabc]
		and	EDX,ESI			; выделили не повторяющиеся 3 раза разряды
		mov	EBP,EDX			;?Далее только не равные значения
						;	EDX = [0  С A  B]  & [Mabc]
		mov	DI,AX			;	AX= [0]   [Mca]   [Mca]
						;	BX= [X]    [X]      [Mab] [Mab]
		mov	ESI,ECX			;	ECX= [0]  [Mcb]      [0]    [Mcb]
					;Встречаются только парные  единички для маски ABC
;******************************  предварительная проверка на 0 значения A B      B  C  AC=????
	mov	EAX,0808080h		;Остались операнды только с единичками в разных разрядах
	mov	EBP,EAX
	mov	ECX,7			;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		and	EAX,EDX		;
	jne	@F			; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	EBP,1		;		if PF=0  		JNP  METKA
		mov	EAX,EBP
	loop	@B			;     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;*************************************************** A=0 B=0 C=0 не должно быть
@@:					;смотрим по выделенным разрядам
		test	EAX,0FF0000h	;C=?    здесь общие единички могут быть только попарно
	jne	@F			;Ce =1	Ae=?	Be=?
			test	AX,0FF00h	; Ce=0     Ae=?  Be=?
		je	maxCeAe001		; Ce=0     Ae=0     Be =1=> max  /\
			and	al,0FFh		;Be=?
		jne	AeBe011			; Ce=0     Ae=1	Be=1		C<A  C<B
		jmp	CeBe010			; +Ce=0     Ae=1	Be=0	 A> B  A>C
@@:	and	al,0FFh			; Ce =1	Ae=	Be=?
	JNE 	CeBe101			;+ Ce =1   Ae=	Be=1=>  Ae=0   A<B   A<C только 2 единички A С
		test	AX,0FF00h	; Ce =1   Ae=?	Be=0 =>
	JE 	AeBe100		    	; Ce =1    Ae=0	Be=0		C>A   C>B
	jmp 	minCeAe110		; Ce =1    Ae=1	Be=0   =>	A>B  B<C      \/
;*******************************+*
CeBe010:					;	Ce=0     Ae=1	Be=0	 A> B  A>C
		and	EDX,ESI		;Mcb	Ce=?		Be=?
@@:
		shr	EBP,1		;следующую единичку т.к. C=0 и B=0 были одновременно
		mov	EAX,EBP
		and	EAX,EDX		;С  В    теперь повторяющихся единичек нет
	jne	@F			; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;**********************************+**
@@:
		mov	ah,PR@a
		and	al,0FFh		; Ce =     Ae=1	Be=?	A>B  A>C
	jne	CMNEXI			;++++>  5  Ce=0  Ae=1 B=1  B>C  => A>B> C    \
		mov	ah,PR@s
	jmp	CMNEXI			;++++>  6   B=0    A>B<C  C=1    => A>B<C   A >C   `\/
;*******************************************+*
CeBe101:					; Ce =1   Ae=0	Be=1=>Ae=0 A<B   A<C
		and	EDX,ESI		;Mcb
@@:
		shr	EBP,1		;следующую единичку т.к. B=1 и C=1 были одновременно
		mov	EAX,EBP
		AND	EAX,EDX		;С  В    теперь повторяющихся единичек нет
	jne	@F			; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;***********************************************+*
@@:						; Ce =   Ae=0	Be=?	A<B  A<C
		mov	ah,PR@k
		and	al,0FFh
	jne	CMNEXI				;+> Ce =0 Ae=0   B=1 B>C  => A<B> C  A<C    ./\
		mov	ah,PR@e
	jmp	CMNEXI				;+> Ce =1 Ae=0   B=0    B<C      => A<B<C   /
;*******************************************+*
AeBe011:						; Ce=0     Ae=1	Be=1		C<A  C<B
		and	DX,BX			;Mab  значащие и один раз встречаются единички
@@:
		shr	BP,1
		mov	AX,BP
		AND	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;******************************************+**
@@:
		mov	AH,PR@g
		and	al,0FFh			;Be=?	C<A	C<B
	jne	CMNEXI				;+>  7 C=0 B =1 B>A  => A<B> C    C<A	 /\.
		mov	AH,PR@a
	jmp	CMNEXI				;++++>  8	C=0   B=0  => A>B>C    \
;*****************************+*
 AeBe100:						; Ce =1    Ae=0	Be=0  =>    C>B   C>A
		and	DX,BX			;Mab  значащие и один раз встречаются единички
@@:
		shr	BP,1
		mov	AX,BP
		and	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;*****************************************+**
@@:
		mov	ah,PR@e
		and	al,0FFh			;Ce =1 B=? => A=    C>B  C>A
	jne	CMNEXI				;+>  9   A<B  B=1    B>A  => C>B>A  A<B<C   /
		mov	ah,PR@z			;C=1 A=1  B=0   \/
	jmp	CMNEXI			;+>  10  C>B  C=1   B=0  =>C>B<A    A>B<C   \/`
;*********************************************+*
maxCeAe001:					; Ce=0     Ae=0   B =1=> max 	 /\
		shr	EDX,8			; 0  C  A   равенство учли при формировании маски
		and	DX,DI			;EDI=Mac
@@:
		shr	BP,1
		mov	AX,BP
		and	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;**********************************************+**
@@:						; Ce=0     Ae=0   B =1=> max 	 /\
		mov	ah,PR@g
		and	al,0FFh			;A=?
	jne	CMNEXI				;+>  11 A=1 C<A  => A<B> C  A>C  /\.
		mov	ah,PR@k
	jmp	CMNEXI				;+>  12  A=0   C>A  => A<B>C    A<C	./\
;***********************************************+*
minCeAe110:					; Ce =1    Ae=1	Be=0   =>	A>B  B<C   \/
		shr	EDX,8			; 0  C  A   равенство учли при формировании маски
		and	DX,DI			;EDI=Ma
@@:
		shr	BP,1
		mov	AX,BP
		and	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;***********************************+**
@@:
		mov	ah,PR@s
		and	al,0FFh			;A=?
	jne	CMNEXI				;+>  13  A=1 Be=0  C<A  => A>B< C  A>C   `\/
		mov	ah,PR@z
	jmp	CMNEXI				;+>  14  A=0  Be=0 C>A  => A>B<C    A<C    \/`
	;}
;*************************************************al=A=B=bl  ESI =0  С A  B  cl=C
PRyi:					;__/   	```\   надо проверять B C
		mov	DH,AL
		mov	DL,CL		; CX =[A] [C]     C ? A   ~  C? B   одинаково  т.к. A=B
		xor	al,cl		;Mca
		mov	ah,al		;AX=Mac Mac
		and	DX,AX  		;and	CX,AX	      [C  A]  & [Mac Mac]
		and	DH,0FFh			;A=? после выделения маски С & (BC)
	jne	@F				;они не зависимы и надо продолжать
		mov	ah,PR@y			;A=0  Y	(A=B) & (A=B<C)   __/
	jmp	CMNEXI				; 2 выход  PRy
@@:
		and	DL,0FFh			;C=?
	jne	@F				;C=1	надо продолжать
		mov	ah,PR@i			;C=0 	(A=B) & (A=B>C)  ```\
	jmp	CMNEXI				;  3 выход  PRi
@@:
	mov	BP,08080h				;Остались операнды только с единичками в разных разрядах
	mov	ECX,7				;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		and	AX,DX			;
	jne	@F			; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	BP,1		;		if PF=0  		JNP  METKA
	loop	@B			;
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;************************************************************************************
@@:
		mov	ah,PR@y		;A=0 Y	(A=B) & (B<C)   __/ т.к. bl=B=0
		and	al,0FFh		;
	jne	CMNEXI			;A=1  A>C   по флагу  if FP=1, который вырабат. если bl=0, т.е. B<C
		mov	ah,PR@i		;C=0 	(A=B) & (B=A>C)  ```\
	jmp	CMNEXI
;***********************************
;*************************************************	;B=C   A?B   BX= [Mab] [Mab]  SI= [A] [B]
PRxj:						;/```   \__    C=B  пр-ка  A ? B
		and	BX,SI
		and	BH,0FFh			;A=?   после выделения маски  (A B)
	jne	@F				;A=1    A>B
		mov	ah,PR@x			;A=0 	(A<B) & (B=C)  /```
	jmp	CMNEXI				;  2 выход  PRy
@@:
		and	BL,0FFh			;B=?
	jne	@F				;	надо продолжать
		mov	ah,PR@j			;C=B 	(A>B) & (A>B=C)  ```\
	jmp	CMNEXI				;  3 выход  PRi
@@:
	mov	BP,08080h				;Остались операнды только с единичками в разных разрядах
	mov	ECX,7				;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		and	AX,BX			;
	jne	@F			; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	BP,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;************************************************************************************************************
@@:						; B>C
		mov	ah,PR@x			;A=0 	(A<B) & (B=C)  /``` т.к. bl=B=0
		and	AL,0FFh			;BL=?
	jne	CMNEXI				;BL=1 A=0  =>A<B
		mov	ah,PR@j			;A=1   	(A>B) & (B=C)  ```\
	jmp	CMNEXI
;***********************************; \/ v  /\  A=C    A?B   BX= [Mab] [Mab]  SI = [A  B]
PRch:						; A=C	\/	/\
		and	BX,SI
		and	BL,0FFh			;B=?   после выделения маски  (A B)
	jne	@F				;	B=1 переход
		mov	ah,PR@c			;B=0 	(A>B) & (A=C) \/    т.к. bl=B=0
	jmp	CMNEXI				;
@@:
		and	BH,0FFh			;A=?
	jne	@F				;	надо продолжать
		mov	ah,PR@h			;A=0 	(A<B) & (A=C) /\
	jmp	CMNEXI				;  3 выход  PRi
@@:
	mov	BP,08080h				;Остались операнды только с единичками в разных разрядах
	mov	ECX,7				;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		AND	AX,BX			;
	jne	@F				;
		shr	BP,1			;
	loop	@B				;
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
@@:
		mov	ah,PR@h			;B=0 	(B<A) & (A=C) \/    т.к. bl=B=0
		and	AL,0FFh			;BL=B
	jne	CMNEXI				;BL=1 A=0  =>A<B  /\   PR@h
		mov	ah,PR@c			;A=0 ```\	(A>B) & (A=C)
	jmp	CMNEXI			;
;***********************************

;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
MISTEK:
	P!rAdrStop	=BalarirevNE	macro C!abcPr	ERROR
;******************		Общий ВЫХОД
;************************************************************************************************************
;***********************************************
;						FINISH
CMNEXI:				;нормальное завершение
	mov	[Ko],AX		;результат сравнения
	ВостановилиРегистры	EBX,ECX,EDX,ESI,EDI,EBP
;*********************************
}
;********************1 *********СучетомОтношений!Получить!Перейти*****вариант 2***********
;	СучетомОтношений!Получить!Перейти		AX ? BX ? CX =>\
;			Сравнили!Присвоили!Перешли AX?BX?CX? =>\
;(rg=PRA=>P1) (rg=PRE=>P2)  (rg=PRO =>P3)   (rg=PRX =>P4)  (rg=PRY=>P5) (rg=PRI =>P6) (rg=PRJ=>P7) (rg=PRH=>P8)\
; (rg=PRG=>P9) (rg=PRK=>P10)   (rg=PRC=>P11)  (rg=PRS=>P12)   (rg=PRZ=>P13)
;*************************СучетомОтношений!Получить!Перейти ************************************************
MACRO СучетомОтношений!Получить!Перейти arg
{
		Relation!Write!Go	arg
}
;*******************Relation!Write!Go********************************************************************
 	MACRO  Relation!Write!Go	arg		;СучетомОтношений!Получить!Перейти
{		Print!afall   arg
		;display10
  common match A_=? B_ =? C_==> (r_1 ==_A==> P1)   (r_2==_E==> P2)  (r_3==_O==>P3)   (r_4==_X==>P4)   (r_5==_Y==>P5) (r_6==_I==>P6)  (r_7==_J==>P7)  (r_8 ==_H==>P8)  (r_9==_G==>P9)  (r_10==_K==>P10) (r_11==_C==>P11)  (r_12==_S==>P12)   (r_13 ==_Z==>P13),arg
		\{
		\Print!afall   _C
		;\display10

 \C!abcRoJmp  \A_,\B_,\C_,\r_1,\P1,\P2,\P3,\P4,\P5,\P6,\P7,\P8,\P9,\P10,\P11,\P12,\P13,\_A,\_E,\_O,\_X,\_Y,\_I,\_J,\_H,\_G,\_K,\_C,\_S,\_Z
		 \}
;display10
;Print!afall   P11
}
;*********C!abcRoJmp ****Cравнение трех байт с минимальным кол-вом операций -  **********************
;***************Установление отношения (A?B?C) с кодом ответа Ko  и переход по 13 направлениям******************
macro C!abcRoJmp  RGa,RGb,RGc,Ko,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,PR1,PR2,PR3,PR4,PR5,PR6,PR7,PR8,PR9,PR10,PR11,PR12,	PR13
{
	;Print!afall   RGc
	ОпределитьКонстанты   PR@,(a=1),(e=2),(o=3),(x=4),(y=5),(i=6),(j=7),(h=9),(g=10),(k=11),(c=12),(s=13),(z=14)
LOCAL	MISTEK,CeBe010,CeBe101,AeBe011, AeBe100,maxCeAe001,minCeAe110,PRyi,PRxj,PRch,RE@F,CMNE
	УпряталиРегистры	ECX,EDX,ESI,EDI,EBP
						;ОбнулитьРегистры  EAX,EBX,ECX,EDX
		mov	al,RGa
						;можно and al,-1     je PrBC
		mov	bl,RGb
						;можно and bl,-1     je PrAC
		mov	cl,RGc			;cl=C
						;можно and cl,-1     je PrAB
						;mov	dl,al
		mov	dl,cl
		xor	dh,dh			;dh=0
		shl	EDX,16			;подвинули  	0  С  0  0
		mov	dl,bl			;	 -  	0  C  0  B
		mov	dh,al			;     	EDX =>	0  С A  B   >16 C  dh=A dl =B
		mov	ESI,EDX			;	ESI =>	0  С A  B   >16 C  dh=A dl =B

		mov	ah,al
		xor	ah,-1			; не A

		mov	bh,bl
		xor	bh,-1			; не B
		or	dl,al			; A v B (dl=B)
		or	ah,bh			;(не A) v (не B)

		mov	bh,bl
		xor	bh,al			;	BH=>  Mab=(AB)xor
	JNE	RE@F	  			; нет равных значений  по паре A  B
		mov	ch,cl
		xor	ch,-1			; не C
		or	dl,cl			;DL =>   все значащие разряды DL=ABCor
		or	ah,ch			;AH =>(не A) v (не B) v (не С)

		and	dl,ah			; все общие единички без той которая встреч. 3 раза
	JNE	@F				;не общих единичек нет => все не равны  ____
		mov	EBX,P3			;адрес переключателя на точку выхода
		mov	Ko,PR3			;параметр например для  примитива O   PR3=3
	jmp	CMNE				; ++++>1 выход  PRo
@@:
	jmp	PRyi				;__/   	```\  al=A=B=bl  ESI =0  С A  B  cl=C
;*********************************************ПОВТОР от JNE	RE@F до*@@:*******
RE@F:
		mov	ch,cl
		xor	ch,-1			; не C
		or	dl,cl			;DL =>   все значащие разряды DL=ABCor
		or	ah,ch			;AH =>(не A) v (не B) v (не С)

		and	dl,ah			; все общие единички без той которая встреч. 3 раза
;*****************************************************
@@:
		mov	dh,dl
		shl	EDX,8
		mov	dl,dh
		and	EDX,0FFFFFFh		;Маска общих значащих разрядов для 3-х переменных
						;1.   	EDX=ABCor,ABCor,ABCor  кроме 3-х встреч.
		mov	ch,cl
		xor	ch,bl			;	CH=Mbc=(BC)xor
		mov	BL,BH			;	EBX= [X]  [X]  [Mab] [Mab]
	JNE	@F				; нет равных значений  по паре   B  C
	jmp	PRxj				;/```   \__  B=C   A?B   BX= [Mab] [Mab]  SI= [A] [B]
@@:
		mov	ah,ch			;AH=(BC)xor
		shl	ECX,8			;ECX=[0] [(BC)xor]  [X]  [X]
		mov	cl,ah			;ECX =[0] [(BC)xor]  [X] [(BC)xor]
		xor	ch,ch			;	ECX= [0]  [Mbc] [0] [Mbc]

		xor	ah,bh			;[Mbc] xor [Mab]  => [Mac]
		mov	al,ah			;AX=[Mac] [Mac]
	JNE	@F
	jmp	PRch				; \/ v  /\  A=C    A?B   BX= [Mab] [Mab]  DX = [A  B]
   @@:
		xchg	EDX,ESI			;ESI =>	0  С A  B  	EDX=[Mabc]
		and	EDX,ESI			; выделили не повторяющиеся 3 раза разряды
		mov	EBP,EDX			;?Далее только не равные значения
						;	EDX = [0  С A  B]  & [Mabc]
		mov	DI,AX			;	AX= [0]   [Mca]   [Mca]
						;	BX= [X]    [X]      [Mab] [Mab]
		mov	ESI,ECX			;	ECX= [0]  [Mcb]      [0]    [Mcb]
					;Встречаются только парные  единички для маски ABC
;******************************  предварительная проверка на 0 значения A B      B  C  AC=????
	mov	EAX,0808080h		;Остались операнды только с единичками в разных разрядах
	mov	EBP,EAX			;EDX = [0  С A  B]  & [Mabc]
	mov	ECX,7			;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		and	EAX,EDX		;
	jne	@F			; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	EBP,1		;		if PF=0  		JNP  METKA
		mov	EAX,EBP
	loop	@B			;     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;*************************************************** A=0 B=0 C=0 не должно быть
@@:					;смотрим по выделенным разрядам
		test	EAX,0FF0000h	;C=?    здесь общие единички могут быть только попарно
	jne	@F			;Ce =1	Ae=?	Be=?
			test	AX,0FF00h	; Ce=0     Ae=?  Be=?
		je	maxCeAe001		; Ce=0     Ae=0     Be =1=> max  /\
			and	al,0FFh		;Be=?
		jne	AeBe011			; Ce=0     Ae=1	Be=1		C<A  C<B
		jmp	CeBe010			; +Ce=0     Ae=1	Be=0	 A> B  A>C
@@:	and	al,0FFh			; Ce =1	Ae=	Be=?
	JNE 	CeBe101			;+ Ce =1   Ae=	Be=1=>  Ae=0   A<B   A<C только 2 единички A С
		test	AX,0FF00h	; Ce =1   Ae=?	Be=0 =>
	JE 	AeBe100		    	; Ce =1    Ae=0	Be=0		C>A   C>B
	jmp 	minCeAe110		; Ce =1    Ae=1	Be=0   =>	A>B  B<C      \/
;*******************************+*
CeBe010:					;	Ce=0     Ae=1	Be=0	 A> B  A>C
		and	EDX,ESI		;Mcb	Ce=?		Be=?
@@:
		shr	EBP,1		;следующую единичку т.к. C=0 и B=0 были одновременно
		mov	EAX,EBP
		and	EAX,EDX		;С  В    теперь повторяющихся единичек нет
	jne	@F			; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;**********************************+**
@@:
		mov	Ko,PR1			;параметр например для  примитива O   PR3=3
		mov	EBX,P1
		and	al,0FFh		; Ce =     Ae=1	Be=?	A>B  A>C
	jne	CMNE			;++++>  5  Ce=0  Ae=1 B=1  B>C  => A>B> C    вниз
		mov	Ko,PR12			;параметр например для  примитива O   PR3=3
		mov	EBX,P12
	jmp	CMNE			;++++>  6   B=0    A>B<C  C=1    => A>B<C   A >C   `\/
;*******************************************+*
CeBe101:					; Ce =1   Ae=0	Be=1=>Ae=0 A<B   A<C
		and	EDX,ESI		;Mcb
@@:
		shr	EBP,1		;следующую единичку т.к. B=1 и C=1 были одновременно
		mov	EAX,EBP
		AND	EAX,EDX		;С  В    теперь повторяющихся единичек нет
	jne	@F			; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;***********************************************+*
@@:						; Ce =   Ae=0	Be=?	A<B  A<C
		mov	Ko,PR10			;параметр например для  примитива O   PR3=3
		mov	EBX,P10
		and	al,0FFh
	jne	CMNE				;+> Ce =0 Ae=0   B=1 B>C  => A<B> C  A<C    ./\
		mov	EBX,P2
		mov	Ko,PR2			;параметр например для  примитива O   PR3=3
	jmp	CMNE				;+> Ce =1 Ae=0   B=0    B<C      => A<B<C   /
;*******************************************+*
AeBe011:						; Ce=0     Ae=1	Be=1		C<A  C<B
		and	DX,BX			;Mab  значащие и один раз встречаются единички
@@:
		shr	BP,1
		mov	AX,BP
		AND	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;******************************************+**
@@:
		mov	Ko,PR9			;параметр например для  примитива O   PR3=3
		mov	EBX,P9
		and	al,0FFh			;Be=?	C<A	C<B
	jne	CMNE				;+>  7 C=0 B =1 B>A  => A<B> C    C<A	 /\.
		mov	EBX,P1
		mov	Ko,PR1			;параметр например для  примитива O   PR3=3
	jmp	CMNE				;++++>  8	C=0   B=0  => A>B>C    \
;*****************************+*
 AeBe100:						; Ce =1    Ae=0	Be=0  =>    C>B   C>A
		and	DX,BX			;Mab  значащие и один раз встречаются единички
@@:
		shr	BP,1
		mov	AX,BP
		and	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;*****************************************+**
@@:
		mov	Ko,PR2			;параметр например для  примитива O   PR3=3
		mov	EBX,P2
		and	al,0FFh			;Ce =1 B=? => A=    C>B  C>A
	jne	CMNE				;+>  9   A<B  B=1    B>A  => C>B>A  A<B<C   /
		mov	EBX,P13
		mov	Ko,PR13			;параметр PR3=13		;C=1 A=1  B=0   \/
	jmp	CMNE			;+>  10  C>B  C=1   B=0  =>C>B<A    A>B<C   \/`
;*********************************************+*
maxCeAe001:					; Ce=0     Ae=0   B =1=> max 	 /\
		shr	EDX,8			; 0  C  A   равенство учли при формировании маски
		and	DX,DI			;EDI=Mac
@@:
		shr	BP,1
		mov	AX,BP
		and	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;**********************************************+**
@@:						; Ce=0     Ae=0   B =1=> max 	 /\
		mov	Ko,PR9			;параметр например для  примитива O   PR3=3
		mov	EBX,P9
		and	al,0FFh			;A=?
	jne	CMNE				;+>  11 A=1 C<A  => A<B> C  A>C  /\.
		mov	EBX,P10
		mov	Ko,PR10			;параметр например для  примитива O   PR3=3
	jmp	CMNE				;+>  12  A=0   C>A  => A<B>C    A<C	./\
;***********************************************+*
minCeAe110:					; Ce =1    Ae=1	Be=0   =>	A>B  B<C   \/
		shr	EDX,8			; 0  C  A   равенство учли при формировании маски
		and	DX,DI			;EDI=Ma
@@:
		shr	BP,1
		mov	AX,BP
		and	AX,DX
	jne	@F				; ZF=1 if 0
	loop	@B
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;***********************************+**
@@:
		mov	Ko,PR12			;параметр например для  примитива O   PR3=3
		mov	EBX,P12
		and	al,0FFh			;A=?
	jne	CMNE				;+>  13  A=1 Be=0  C<A  => A>B< C  A>C   `\/
		mov	EBX,P13
		mov	Ko,PR13			;параметр например для  примитива O   PR3=3
	jmp	CMNE				;+>  14  A=0  Be=0 C>A  => A>B<C    A<C    \/`
	;}
;*************************************************al=A=B=bl  ESI =0  С A  B  cl=C
PRyi:					;__/   	```\   надо проверять B C
		mov	DH,AL
		mov	DL,CL		; CX =[A] [C]     C ? A   ~  C? B   одинаково  т.к. A=B
		xor	al,cl		;Mca
		mov	ah,al		;AX=Mac Mac
		and	DX,AX  		;and	CX,AX	      [C  A]  & [Mac Mac]
		and	DH,0FFh			;A=? после выделения маски С & (BC)
	jne	@F				;они не зависимы и надо продолжать
		mov	Ko,PR5		;параметр   PR3=5	;A=0  Y	(A=B) & (A=B<C)   __/
		mov	EBX,P5
	jmp	CMNE				; 2 выход  PRy
@@:
		and	DL,0FFh			;C=?
	jne	@F				;C=1	надо продолжать
		mov	EBX,P6
		mov	Ko,PR6			;параметр   PR3=6;C=0 	(A=B) & (A=B>C)  ```\
	jmp	CMNE				;  3 выход  PRi
@@:
	mov	BP,08080h				;Остались операнды только с единичками в разных разрядах
	mov	ECX,7				;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		and	AX,DX			;
	jne	@F			; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	BP,1		;		if PF=0  		JNP  METKA
	loop	@B			;
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;************************************************************************************
@@:
		mov	Ko,PR5		;параметр    PR5=5;A=0 Y	(A=B) & (B<C)   __/ т.к. bl=B=0
		mov	EBX,P5
		and	al,0FFh		;
	jne	CMNE			;A=1  A>C   по флагу  if FP=1, который вырабат. если bl=0, т.е. B<C
		mov	EBX,P6
		mov	Ko,PR6		;параметр   PR3=6		;C=0 	(A=B) & (B=A>C)  ```\
	jmp	CMNE
;***********************************
;*************************************************	;B=C   A?B   BX= [Mab] [Mab]  SI= [A] [B]
PRxj:						;/```   \__    C=B  пр-ка  A ? B
		and	BX,SI
		and	BH,0FFh			;A=?   после выделения маски  (A B)
	jne	@F				;A=1    A>B
		mov	EBX,P4
		mov	Ko,PR4			;параметр    PR3=4	A=0 	(A<B) & (B=C)  /```
	jmp	CMNE				;  2 выход  PRy
@@:
		and	BL,0FFh			;B=?
	jne	@F				;	надо продолжать
		mov	EBX,P7
		mov	Ko,PR7			;параметр PR3=3	C=B 	(A>B) & (A>B=C)  ```\
	jmp	CMNE				;  3 выход  PRi
@@:
	mov	BP,08080h				;Остались операнды только с единичками в разных разрядах
	mov	ECX,7				;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		and	AX,BX			;
	jne	@F			; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	BP,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;************************************************************************************************************
@@:						; B>C
		mov	Ko,PR4			;параметр    PR4=4	A=0 	(A<B) & (B=C)  /``` т.к. bl=B=0
		mov	EBX,P4
		and	AL,0FFh			;BL=?
	jne	CMNE				;BL=1 A=0  =>A<B
		mov	EBX,P7
		mov	Ko,PR7			;параметр   PR7=7	A=1   	(A>B) & (B=C)  ```\
	jmp	CMNE
;***********************************; \/ v  /\  A=C    A?B   BX= [Mab] [Mab]  SI = [A  B]
PRch:						; A=C	\/	/\
		and	BX,SI
		and	BL,0FFh			;B=?   после выделения маски  (A B)
	jne	@F				;	B=1 переход
		mov	EBX,P11
		mov	Ko,PR11			;параметр    PR11=11   B=0 	(A>B) & (A=C) \/    т.к. bl=B=0
	jmp	CMNE				;
@@:
		and	BH,0FFh			;A=?
	jne	@F				;	надо продолжать
		mov	EBX,P8
		mov	Ko,PR8			;параметр    PR3=3	A=0 	(A<B) & (A=C) /\
	jmp	CMNE				;  3 выход  PRi
@@:
	mov	BP,08080h				;Остались операнды только с единичками в разных разрядах
	mov	ECX,7				;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		mov	AX,BP
		AND	AX,BX			;
	jne	@F				;
		shr	BP,1			;
	loop	@B				;
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
@@:
		mov	Ko,PR8			;параметр    PR3=3	B=0 	(B<A) & (A=C) \/    т.к. bl=B=0
		mov	EBX,P8
		and	AL,0FFh			;BL=B
	jne	CMNE				;BL=1 A=0  =>A<B  /\   PR@h
		mov	EBX,P11
		mov	Ko,PR11			;параметр    PR3=3		A=0 ```\	(A>B) & (A=C)
	jmp	CMNE			;
;***********************************
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
MISTEK:
	P!rAdrStop	=BalarirevNE	macro C!MPabcJm	ERROR
;******************		Общий ВЫХОД
;************************************************************************************************************
;***********************************************
;
CMNE:				;результат сравнения
	ВостановилиРегистры	ECX,EDX,ESI,EDI,EBP
	jmp	EBX		;		FINISH
;*********************************
}
;************************************************* C!MPabcKo********************
MACRO C!MPabcKo  RGa,RGb,RGc,Ko		;Pr0,Pr1,Pr2	;=, >, <
{
	ОпределитьКонстанты   PR,(a=1),(e=2),(o=3),(x=4),(y=5),(i=6),(j=7),(h=9),(g=10),(k=11),(c=12),(s=13),(z=14) ;подправить на маленькие
	LOCAL	JmJ,JgJ,JeJ,OUTLOP
;УпряталиРегистры	EAX,EBX,ECX,EDX,EBP
	ОбнулитьРегистры  EAX,EBX,ECX
		mov	al,RGa
		mov	bl,RGb
		mov	cl,RGc
		mov	dl,cl			;cl=C
		shl	EDX,16			;подвинули  	С 0  0
		mov	dh,bl			;	 -  	0  B  0
		mov	dl,al			;     	EDX =>	С B  A   >16 C  dh=B dl =A
		shl	EAX,16			;подвинули  	A 0  0
		mov	ah,cl			;	 -  	0  C  0  ah=C
		mov	al,bl			;	EAX =>	A  C  B  >16 A  ah=C  al=B

		mov	BX,DX			;		0 B  A
		shl	EBX,8			;		B A  0
		mov	bl,cl			;	EBX =>      B A C   bh=A    bl=C
						;      A       C      B  <= EAX
						; xor
						;      С       B      A  <= EDX
						;    (AC) (CB) (BA)
		xor	EAX,EDX			;	EAX =>	>16 (CA)  ah=(BC)  al=(AB)

		mov	EBP,EAX			;EBP =>	A  C  B  >16 A  ah=C  al=B

						;    (AC)   (CB)  (BA)
						; xor
						;       B        A         C
						;   (ACB)  (CBA)  (BAC)
		xor	EBP,EBX			;			маска (ABC)

	JNE	@F				;все равны  ____
		mov	al,PRo			;  примитив	O
	jmp	CMNEXI				;  1 выход  PRo
@@:
			mov	EBP,EAX		;   EBP =>      B A C         BP=>AC
						;EAX =>	>16 (CA)  ah=(BC)  al=(AB)
		test	EAX,0FFh			; маска  al = (AB)      маска ah = (BC)
	JE	@F				;A=B
	JMP	PRODL				; A не = B
@@:						;EBX =>      B A C   bh=A    bl=C
						;EDX =>	С B  A   >16 C  dh=B dl =A
		mov	bh,bl			;bh=C   тюк. A=B   и   C не = B   B?C  if  dh=B bl =C
		mov	bl,dh			;bl=B =>	C ? B  in BX
						;mov	DL,BL
						;xor	DL,BL	;[DL маска  (BC)
						;je	MISTEK	;ЭТО  ОШ-КА     оба операнда B=C ==>
		and	BL,AH			;после выделения маски С & (BC)
	jne	@F				;они не зависимы и надо продолжать
JmJ:		mov	al,PRy			;Y	(A=B) & (B<C)   __/ т.к. bl=B=0
	jmp	CMNEXI				;  2 выход  PRy
@@:
		and	BH,AH			;bh=C

	jne	@F				;	надо продолжать
JgJ:		mov	al,PRi			;I 	(A=B) & (B>C)  ```\
	jmp	CMNEXI				;  3 выход  PRi
@@:
	mov	AX,08080h				;Остались операнды только с единичками в разных разрядах
	mov	ECX,7				;рр 16&8 ;15&7; 14&6; 13&5; 12&4;11&3;10&2; 9&1-исключ.
@@:
		test	BX,AX			;
	jne	@F			; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	AX,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;************************************************************************************************************
@@:					; OUTLOP либо bl  будет 0, то FP=1 и тогда можно   JNP  METKA  !!!!!
	jnp	JgJ			;FP=0  B>C   по флагу  if FP=1, который вырабат. если bl=0, т.е. B<C
	jmp	JmJ			;FP=1  B<C
;***********************************
PRODL:						;A не = B
						;ah=(BC)
	test	EAX,0FF00h			;       маска ah = (BC)
	JE	@F				;B=C
	JMP	PRODL1				; B не = C
@@:						;EBX =>      B A C   bh=A    bl=C
						;EDX =>	С B  A   >16 C  dh=B dl =A
						;EAX =>	>16 (CA)  ah=(BC)  al=(AB)
		mov	bh,dh			;bh=B  B=C   и   A не = B     A?B  if  dh=B dl =A
		mov	bl,dl			;bl=A =>	B ? A  in BX
						;mov	DL,BL
						;xor	DL,BH	;в DL маска
						;je	MISTEK	;оба операнда B=C ==>
		and	BL,AL			;bl=A после выделения маски
	jne	@F				;они не зависимы и надо продолжать
JmJ1:		mov	al,PRx			;X	(A<B) & (B=C)   /```
	jmp	CMNEXI				;  4 выход  PRx  они не зависимы и надо продолжать
@@:
		and	BH,AL			;	bh=B
	jne	@F			;	[9*]	;A>B
JgJ1:		mov	al,PRj			;J 	(A>B) & (B=C)      \__
	jmp	CMNEXI
@@:
	mov	AX,08080h			;Остались операнды только с единичками в разных разрядах
	mov	ECX,7			; рр 16 - 8  ;15 - 7; 14 - 6; 13 - 5; 12 -4; 11-3; 10-2; 9 - 1 -исключается
@@:
		test	BX,AX		;
	jne	@F			; ZF=1 if 0   13*на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	AX,1		;		if PF=0  		JNP  METKA
	loop	@B			;     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;************************************************************************************************************
@@:					; OUTLOP либо bl  будет 0, то FP=1 и тогда можно   JNP  METKA  !!!!!
	jnp	JgJ1			;FP=0  A>B  по флагу  if FP=1, который вырабат. если bl=0, т.е. A<B
	jmp	JmJ1			;FP=1  A<B
;************************************************
; не A  не =  B       B не =  C   		 (AB)не 0    (BC) не 0
PRODL1:						;EBX =>      B A C   bh=A    bl=C
						;EDX =>	С B  A   >16 C  dh=B dl =A
						;EAX =>	>16 (CA)  ah=(BC)  al=(AB)
		mov	bh,dh			;bh=B
		mov	bl,dl			;bl=A =>	B ? A  in BX

		and	BL,AL			;bl= A    после выделения маски
	jne	@F				;[7]
JmJ2:		mov	dl,4h			;признак 	(A>B) 1000 0000     A<B  0100 0000
	jmp	PROVDAL			;  надо продолжать
@@:
		and	BH,AL			;[8 ]	bl
	jne	@F				;
JgJ2:		mov	dl,8h			; 	(A>B)
	jmp	PROVDAL
@@:
	mov	AX,08080h			;[10]  Остались операнды только с единичками в разных разрядах
	mov	ECX,7			;[11] рр 16 - 8  ;15 - 7; 14 - 6; 13 - 5; 12 -4; 11-3; 10-2; 9 - 1 -исключается
@@:
		test	BX,AX		;12
	jne	@F			; ZF=1 if 0   13*на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	AX,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;************************************************************************************************************
@@:					; OUTLOP либо bl  будет 0, то FP=1 и тогда можно   JNP  METKA  !!!!!
	jnp	JgJ2			;FP=0  A>B   [42] по флагу  if FP=1, который вырабат. если bl=0, т.е. A<B
	jmp	JmJ2			;FP=1  A<B
;***********************************************************
PROVDAL:	mov	EAX,EBP			;EBX =>      B A C   bh=A    bl=C
						;EDX =>	С B  A   >16 C  dh=B dl =xxxx
						;EAX =>	>16 (CA)  ah=(BC)  al=(AB)
 		mov	bh,bl			;bh=C
		mov	bl,dh			;bl=B =>	C ? B  in BX

		and	BL,AH			;после выделения маски
	jne	@F				;A маскированное пересекается с B  маскированное
JmJ3:		or	dl,1h			;	 (B<C)
	jmp	PROVDAL1			; они не зависимы и надо продолжать
@@:
		and	BH,AH			;bh=?
	jne	@F				;	;B>C
JgJ3:		or	dl,2h			; 	(B>C)
	jmp	PROVDAL1
@@:
	mov	AX,08080h			;[10]  Остались операнды только с единичками в разных разрядах
	mov	ECX,7			;[11] рр 16 - 8  ;15 - 7; 14 - 6; 13 - 5; 12 -4; 11-3; 10-2; 9 - 1 -исключается
@@:
		test	BX,AX		;12
	jne	@F			; ZF=1 if 0   13*на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	AX,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;************************************************************************************************************
@@:					; OUTLOP либо bl  будет 0, то FP=1 и тогда можно   JNP  METKA  !!!!!
	jnp	JgJ3			;FP=0  B>C   [42] по флагу  if FP=1, который вырабат. если bl=0, т.е. A<B
	jmp	JmJ3			;FP=1  B<C
;***********************************
;   ПРОВЕРКА если нужно А   и   С
; Комбинации в  DL
;10 A>B  10 B>C  => 1 01 0  		A>B>C     A = PRA=1	  	1  	ST2
;10 A>B  01 B<C =>  1 00 1 		A>B<C	\/    C S Z	 \/	0 	ST1
;01 A<B  10 B>C =>  0 11 0 		A<B>C	/\  H G K		3	ST4
;01 A<B  01 B<C =>  0 10 1 		A<B<C	B=PRB=2		2	ST3
PROVDAL1:
		and 	dx,0110h		;000 h out of range ????
		shr	dl,1
	S!WITCH EAX,JgJ4 ;Переключатель по 4 вышеуказанным комбинациям
STTT2:
		mov	al,PRa
	jmp	CMNEXI
;**********************************
;10 A>B  01 B<C =>  1 00 1 		A>B<C	\/    C S Z	 \/	0 	ST1
;**********************************
STTT1:		;mov	EAX,EBP			;EBX =>      B A C   bh=A    bl=C
						;EDX =>	С B  A   >16 C  dh=B dl =xxx
						;EAX =>	>16 (CA)  ah=(BC)  al=(AB)
		shr	EAX,16			;(AxorC)  \/
		and	al,0FFh
	jne	@F
		mov	al,PRC			;A=C  т.к. маска (AC)=0  => PRC
	jmp	CMNEXI
@@:
		and	BL,AL			;bl=Cпосле выделения маски
	jne	@F				;A маскированное пересекается с B  маскированное
JmJ4:		mov	al,PRS			;A>C	 (C<A)
	jmp	CMNEXI				;
@@:
		and	BH,AL			;bh=A
	jne	@F				;
JgJ4:
		mov	al,PRZ			; A<C	(C>A)
	jmp	CMNEXI
@@:
	mov	AX,08080h			;[10]  Остались операнды только с единичками в разных разрядах
	mov	ECX,7			;[11] рр 16 - 8  ;15 - 7; 14 - 6; 13 - 5; 12 -4; 11-3; 10-2; 9 - 1 -исключается
@@:
		test	BX,AX		;12
	jne	@F			; ZF=1 if 0   13*на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	AX,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;***********************************************************************************
@@:					; OUTLOP либо bl  будет 0, то FP=1 и тогда можно   JNP  METKA  !!!!!
	jnp	JgJ4			;FP=0  A>C    флаг не сработал NFP => FP=0
	jmp	JmJ4			;по флагу  if FP=1, который вырабат. если bl=0, т.е. A<C
;*******************************************************************************
;01 A<B  10 B>C =>  0 11 0 		A<B>C	/\  H G K		3	ST4
;	A<B>C	/\  H G K
;********************************************************************************
STTT4:					;EBX =>      B A C   bh=A    bl=C
					;EDX =>	С B  A   >16 C  dh=B dl =xxx
					;EAX =>	>16 (CA)  ah=(BC)  al=(AB)
		shr	EAX,16		;(AC)
		and	al,0FFh
	jne	@F			;A>C   v  A<C
		mov	al,PRH		;A=C  т.к. маска (AC)=0  /\
	jmp	CMNEXI
@@:

		and	BL,AL			;после выделения маски    для C
	jne	@F				; маскированное пересекается с А  маскированное
JgJ5:		mov	al,PRG			 ;	 (A>C)    /\.
	jmp	CMNEXI			; [8*] они не зависимы и надо продолжать
@@:
		and	BH,AL		;[8 ]	bh=A
	jne	@F			;	[9*]	;A<C
JmJ5:
		mov	al,PRK		; 	(A<C)
	jmp	CMNEXI
@@:
	mov	AX,08080h			;[10]  Остались операнды только с единичками в разных разрядах
	mov	ECX,7			;[11] рр 16 - 8  ;15 - 7; 14 - 6; 13 - 5; 12 -4; 11-3; 10-2; 9 - 1 -исключается
@@:
		test	BX,AX		;12
	jne	@F			; ZF=1 if 0   13*на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	AX,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;***** ПЛОХАЯ СИТУАЦИЯ : ПЕЧАТЬ через P!rAdrStop   СООБЩЕНИЯ:  =BalarirevNE inusemacro C!MPabJm	macros
	JMP	MISTEK
;************************************************************************************************************
@@:					; OUTLOP либо bl  будет 0, то FP=1 и тогда можно   JNP  METKA  !!!!!
	jnp	JmJ5			;FP=0  A<C
	jmp	JgJ5			;  по флагу  if FP=1, который вырабат. если bl=0, т.е. A>C
;*************************************************************
;01 A<B  01 B<C =>  0 10 1 		A<B<C	B=PRB=2		2	ST3
;*****************************************************************************
STTT3:
	mov	al,PRE
	jmp	CMNEXI
;***********************
MISTEK:
	P!rAdrStop	=BalarirevNE	macro C!MPabcJm	ERROR
;******************		Общий ВЫХОД
CMNEXI:				;нормальное завершение

	ВостановилиРегистры	EAX,EBX,ECX,EDX,EBP	;[6] [43]  A<B
}
;*****************************************************************************************
;      J!mA?B  RGA,RGB,Pr0,Pr1,Pr2		;=, >, <
;				          EAX => A   EBX => B точки перехода  Pr0,Pr1,Pr2 замыкание макро MEXI
;if A=B then Pr0 v if A>B then Pr1  v if A<B then Pr2;  if Pri(i=0,1,2) then go MEXI
;2. J!mA?B	RGA,RGB,Pr0,Pr1, 	if A<B then MEXI
;3. J!mA?B	RGA,RGB,Pr0,,Pr2	if A>B then MEXI
;4. J!mA?B	RGA,RGB,,,Pr2		if A=B then MEXI  v	if A<B then MEXI
;5.  J!mA?B	RGA,RGB,Pr0,,		if A=B then Pr0  v	if A<B v A<B then MEXI     равно не равно 0
;A)  C!MPABJm  	EAX,EBX,Pr0,Pr1,Pr2	    -Сравнения любых данных в пределах 32 рр и Переход
;B)  C!mpABJm	AX,BX,Pr0,Pr1,Pr2
;Использует:	УпряталиРегистры		EAX,EBX,ECX
;		ВосстановилиРегистры	EAX,EBX,ECX
;*************Cравнение двух байт с минимальным кол-вом операций    *******
; 1.J!mA?B  	RGA,RGB,Pr0,Pr1,Pr2		-Сравнения любых данных в пределах 32 рр и Переход
;*************************************************************
		macro J!mA?B  RGA,RGB,Pr0,Pr1,Pr2		;=, >, <
{
	LOCAL	JmJ,JgJ,JeJ,OUTLOP4,OUTLOP3,OUTLOP2,OUTLOP1,NBloc2,NBloc1,NBloc0,MEXI
		УпряталиРегистры	EAX,EBX,ECX
			push	RGB		;2-й операнд      упрятывание только для AX  и  EAX
			push	RGA		;1-й операнд  и  восставление dw  dd
		pop	EAX
		pop	EBX
		push	EBX			;?
		push	EAX			;? [SP]
;Блок 3
	shr	EAX,24				;старший байт в регистре 1 опеанда
	shr	EBX,24				;старший байт в регистре 2 опеанда
		and	al,0FFh
	jne	@F				; ст.байт не 0
		and	bl,0FFh
	jne	JmJ				;A=0 B#0 => A<B закончили
	jmp	NBloc2				;A=0  B=0 На следующий блок из 0,1,2,3 на 2
@@:
		and	bl,0FFh
	je	JgJ				;A#0 B=0 A>B
;****************************************
		mov	BH,BL  			;2 чтобы B  A были в одной строке
		mov	BL,AL			;1
		mov	CL,BL			;3
		xor	CL,BH			;[4]в CL маска
	je	NBloc2				;	[5*]оба операнда A=B ==>
		and	BL,CL			;[6]после выделения маски
	jne	@F				;[7]A маскированное пересекается с B  маскированное
						;А либо  погружено и нет своих 1, либо они не зависимы
	jmp	JmJ 				; 	[8*] они не зависимы и надо продолжать
@@:
		and	BH,CL		;[8 ]	bl
	je	JgJ			;	[9*]	;A>B
	mov	AX,08080h			;[7]  Остались операнды только с единичками в разных разрядах
	mov	ECX,7			;[8]  16 - 8	;15 - 7; 14 - 6; 13 - 5; 12 -4; 11-3; 10-2; 9 - 1 -исключается
@@:
			test	BX,AX		;12
	jne	OUTLOP1			; ZF=1 if 0   13*на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	AX,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;****************************************************************************************
	P!rAdrStop	=BalarirevNE	inusemacro J!mA?B	error 	;==>
;****************************************************************************************
OUTLOP1:
	JNP	JgJ			;FP=0  A>B   [44]  по флагу  FP=1, который вырабат. если bl=0, т.е. A<B
	jmp	JmJ
;**************************
NBloc2:
		pop	EAX
		pop	EBX
		push	EBX			;
		push	EAX			;
	shr	EAX,16
	shr	EBX,16
		and	al,0FFh
	jne	@F
		and	bl,0FFh
	jne	JmJ				;A=0 B#0 => A<B закончили
	jmp	NBloc1				;A=0  B=0 На следующий блок из 0,1,2,3 на 2
@@:
		and	bl,0FFh
	je	JgJ				;A#0 B=0 A>B
;*******
		mov	BH,BL  			;2 чтобы B  A были в одной строке
		mov	BL,AL			;1
		mov	CL,BL			;3
		xor	CL,BH			;[4]в CL маска
	je	NBloc1				;	[5*]оба операнда A=B ==>
		and	BL,CL			;[6]после выделения маски
	jne	@F				;[7]A маскированное пересекается с B  маскированное
						;А либо  погружено и нет своих 1, либо они не зависимы
	jmp	JmJ 				; 	[8*] они не зависимы и надо продолжать
@@:
		and	BH,CL		;[8 ]	bl
	je	JgJ			;	[9*]	;A>B
	mov	AX,08080h			;[7]  Остались операнды только с единичками в разных разрядах
	mov	ECX,7			;[8]  16 - 8	;15 - 7; 14 - 6; 13 - 5; 12 -4; 11-3; 10-2; 9 - 1 -исключается
@@:
		test	BX,AX		;12
	jne	OUTLOP2			; ZF=1 if 0   13*на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	AX,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;****************************************************************************************
	P!rAdrStop	=BalarirevNE	inusemacro J!mA?B	error 	;==>
;****************************************************************************************
OUTLOP2:
	JNP	JgJ			;FP=0  A>B   [44]  по флагу  FP=1, который вырабат. если bl=0, т.е. A<B
	jmp	JmJ
;**************************
NBloc1:
		pop	EAX
		pop	EBX
		push	EBX			;?
		push	EAX			;? [SP]
	shr	EAX,8
	shr	EBX,8
		and	al,0FFh
	jne	@F
		and	bl,0FFh
	jne	JmJ				;A=0 B#0 => A<B закончили
	jmp	NBloc0				;A=0  B=0 На следующий блок из 0,1,2,3 на 2
@@:
		and	bl,0FFh
	je	JgJ				;A#0 B=0 A>B
;*******************************
		mov	BH,BL  			;2 чтобы B  A были в одной строке
		mov	BL,AL			;1
		mov	CL,BL			;3
		xor	CL,BH			;[4]в CL маска
	je	NBloc0				;	[5*]оба операнда A=B ==>
		and	BL,CL			;[6]после выделения маски
	jne	@F				;[7]A маскированное пересекается с B  маскированное
						;А либо  погружено и нет своих 1, либо они не зависимы
	jmp	JmJ 				; 	[8*] они не зависимы и надо продолжать
@@:
		and	BH,CL		;[8 ]	bl
	je	JgJ			;	[9*]	;A>B
	mov	AX,08080h			;[7]  Остались операнды только с единичками в разных разрядах
	mov	ECX,7			;[8]  16 - 8	;15 - 7; 14 - 6; 13 - 5; 12 -4; 11-3; 10-2; 9 - 1 -исключается
@@:
		test	BX,AX		;12
	jne	OUTLOP3			; ZF=1 if 0   13*на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	AX,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;****************************************************************************************
	P!rAdrStop	=BalarirevNE	inusemacro J!mA?B	error 	;==>
;****************************************************************************************
OUTLOP3:
	JNP	JgJ			;FP=0  A>B   [44]  по флагу  FP=1, который вырабат. если bl=0, т.е. A<B
	jmp	JmJ			;[38]
;************************** Блок последний
NBloc0:
		pop	EAX
		pop	EBX

		and	al,0FFh
	jne	@F
		and	bl,0FFh
	jne	JmJ				;A=0 B#0 => A<B закончили
	jmp	JeJ				;A=0  B=0 На следующий блок из 0,1,2,3 на 2
@@:
		and	bl,0FFh
	je	JgJ
;*********
		mov	BH,BL  			;2 чтобы B  A были в одной строке
		mov	BL,AL			;1
		mov	CL,BL			;3
		xor	CL,BH			;[4]в CL маска
	je	JeJ				;	[5*]оба операнда A=B ==>
		and	BL,CL			;[6]после выделения маски
	jne	@F				;[7]A маскированное пересекается с B  маскированное
						;А либо  погружено и нет своих 1, либо они не зависимы
	jmp	JmJ 				; 	[8*] они не зависимы и надо продолжать
@@:
		and	BH,CL		;[8 ]	bl
	je	JgJ			;	[9*]	;A>B
	mov	AX,[E16E8]		;[7]  Остались операнды только с единичками в разных разрядах
	mov	ECX,7			;[8]  16 - 8	;15 - 7; 14 - 6; 13 - 5; 12 -4; 11-3; 10-2; 9 - 1 -исключается
@@:
			test	BX,AX		;12
	jne	OUTLOP4			; ZF=1 if 0   13*на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	AX,1		;14		if PF=0  		JNP  METKA
	loop	@B			;15     [max 4*7=28-2     15+26=41]
;****************************************************************************************
	P!rAdrStop	=BalarirevNE	inusemacro J!mA?B	error 	;==>
;****************************************************************************************
OUTLOP4:
				;and	BL,AL		;[43] либо bl  либо bh будет 0    JNP  METKA  ????
	JNP	JgJ			;FP=0  A>B   [44]  по флагу  FP=1, который вырабат. если bl=0, т.е. A<B
;************************  ВЫХОДЫ
JmJ:
		ВосстановилиРегистры	EAX,EBX,ECX	;[6] [40]
			if   ~Pr2 eq
	JMP	Pr2			;A>B
			else
		JMP	MEXI
			end if
JgJ:
		ВосстановилиРегистры	EAX,EBX,ECX	;[7] [42]	A>B
			if   ~Pr1 eq
	JMP	Pr1			;A<B
			else
	JMP	MEXI
			end if
JeJ:
		ВосстановилиРегистры	EAX,EBX,ECX	;[3]
	if   ~Pr0 eq
	JMP	Pr0			;Равны A=B
			else
	JMP	MEXI
			end if
MEXI:						;Общий ВЫХОД
}
;;************************************************************************************
;*****************			5. Операция: Число_единиц_в	BYTE
;  На вход любой регистр на выход нельзя EAX,ECX

;*********************************************************************************
; Гипотеза!!! При таком подходе получения качества можно путем фиксации временного промежутка добится устойчивого проявления классов
;
;Операция "Номер класса (качество)" для Число_промежутков _единиц может начинаться из 0 и далее ищем первую встречу 1
;  или с 1 и далее ищем первый 0. Но это симметричные операции имеющие противоположные значения относительно максимума возможного
;П Р И М Е Р Ы
;111 000	11	-битовая последовательность
;=>
;+1 +1   +1    =3  Значение качества
;00 111 0  11
;   +1  +1 +1  =3
;10101010    	?=8  максимум качества   начиная с 1  =7
;01010101 	?=7
;ОпределитьКачествоБайта\
; ?al\		;?[byt]
;**************************** Форма обращения к ОПЕРАТОРУ
;	УстановитьОтношенияБайтовыхМножеcтвиПерейти \
;	A ? B\
;=>P1  =>P2  =>P3 =>P4  =>P5  =>P6  =>P7  =>P8  =>P9 =>P10  =>P11  =>P12 =>P13  =>P14
;Перед входом определить _V1,_V2,.......,_V11,_V12,V13,V14 - код ответа
;либо 	C!MPMalblJm  A,B,Kd,PS,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,K1,K2,K3,K4,K5,K6,K7,K8,K93,K11,K12,K13,K14
;Базовый макрос для верхнего обращения после реструктуризации
;	C!MPMalblJm  A,B,Kd,PS,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14
;********************************************************************************
; Исходные множества  A  B входная информация
;ВЫХОДНАЯ
;Кd  	00 00 ЧислоЕдиницA ЧислоЕдиницB
;Kd+4	m1 m2     m3		 0
;Kd+8	[A (B	  b) 		a]
;Ps	_Vi c учетом адреса перехода
MACRO C!MPMalblJm  GA,GB, Kd,PS,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14
{
   LOCAL	P6BA,Pr8,Pr7,Pr6,Pr5,Pr4,Pr3,Pr2,Pr1,Pr0,P8BA
	УпряталиРегистры	EAX,EBX,ECX,EDX,EBP
			movzx	EBX,GB		;2-й операнд
			movzx	EAX,GA		;1-й операнд
	;Операция: Число_единиц_в (EAX,ECX)	AL\ 		?(A)
		NEDinB	al,DH		;=> DH	=kA
	; Операция:  Число_единиц_в	BL\		?(B)
		NEDinB	BL,DL		;=> DL	kB
		mov	[Kd],EDX		;DX=kA,kB
		and	al,0FFh			;A&E
	jne	@F
		and	bl,0FFh			;B&E
	jne	Pr1				;JmJ	A=0 B#0 => A<B закончили
	jmp	Pr0				;JeJ  	A=0  B=0   A=B
@@:
		and	bl,0FFh
	je	Pr2				;JgJ	A#0 B=0 => A>B закончили
;*********
						;mov	BH,AL  	чтобы A(bh)  B(bl) были в одной строке
		mov	CL,AL
		xor	CL,BL		;в CL маска
					;AxorB=>N1-получим несовпадающие б. в A,B
	je	Pr3				;JeJ  	оба операнда A=B ==>
;**************Далее нетривиальные ситуации**********
					;NEDinB	BYTE,KO
					; Операция:Число_единиц_в	СL\
		NEDinB	CL,DH		;=> DH	m1  число в DH
	mov	CH,AL			;в СН совпадающие биты
	and	CH,BL			; A & B  => N2  - получение совпадающих бит в  A и  B
					; Операция:Число_единиц_в	СH\
		NEDinB	CH,DL			;p=> DL	m2  в DH
	mov	DL,AL			;  AH  все биты и вA  и в B
	or	DL,BL			;A  v B  => N3 - получение бит присутствующих в A и  B
					; Операция:Число_единиц_в	AH\
		mov	BP,DX
		shl	EBP,16
		NEDinB	DL,DH		;=> DH
		mov	BP,Dx		;m3
		and	BP,0FF00h
		mov	[Kd+4],EBP		;EDX= m1, m2, m3, 0
		and	BL,CL		;после выделения маски A
	jne	@F			;A маскир. пересекается с маскированное
					;А либо  погружено и нет  1, либо они не зависимы
	jmp	Pr4			;II направл. JgJ;in B=0 A>B  B?A  B в A зависимы
@@:
		and	AL,CL		;[5 ]	A(bh)
	je	Pr5			; II направление: JmJ		 A?B  	A<B
;*************************Есть пересекающиеся и не пересекающиеся разряды ***
		and	CH,0FFh		; A & B  => N2  - получение совпадающих бит в  A и  B
	jz	Pr6				; III направление: нет пересекающихся разрядов
;******************************IV направление*************************
;***Есть совпадающие ************** Pr7	  +  	Pr8   И то и другое
		bsf	BP,AX		;A
		shl	BP,8
		bsf	CX,BX		;B
		or	BP,CX		;A  B

		bsr	CX,AX		;A	старшие разряды
		shl	CX,8
 		bsr	DX,BX		; старшие	А  В
		or	CX,DX
		mov	DX,CX		;DX  старшие	А  В
		shl	ECX,16
		mov	CX,BP
		mov	[Kd+8],ECX		;==  границы [A(B b)a]
		cmp	dl,dh		;B  A номера старших единичек
	JG	P8BA			;B=1 A=0  =>A<B верхняя B больше A  (B [A
					;B=0 A=1  =>A>B
;*************  Pr7
		cmp	cl,ch		;номера младших единичек [A (B
	jL	@F			; [A (B ] b)
		mov	PS,_V11		;[A (B b) a]
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
	jmp	P11			;[A (B b) a]	A>B
;***  Координаты границ в Koordint
;*** Закончили с комб. Pr6ABba и пересечение до [A , после до (B, после до b) и до a]
;*******************  			[A     (B	 a]	 b)
@@:
					;[A(B b)a]
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,_V12		;PrABab  V12
	jmp	P12			;[A (B ] b)	A>B
;******************** Закончили с комб. Pr7AB ********
;*************  Pr8
;***************** комб.  P8BA **********
P8BA:
						;границы (B [A
		cmp	cl,ch			;номера младших единичек
	jl	@F				;(B [A a] b)
						;(B [A b)a]
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,_V13			;
	jmp	P13				;(B [A b)a]	A>B
;***  Координаты границ в Koordint
;*** Закончили с комб. Pr6ABba и пересечение до [A , после до (B, после до b) и до a]
;*******************  			[A     (B	 a]	 b)
@@:						;
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,_V14 		;(B [A a] b)
	jmp	P14				;      A<B
;************************************
;******************************************************
Pr0:				;JeJ  	;A=0  B=0   A=B
		mov	[Kd+4],0		;EDX= m1, m2, m3, 0
		mov	[Kd+8],0		;[A(B b)a]
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,V1 		;[PrSovm],V1 - признак
	JMP	P1			;A=B
;*****************************
Pr1:				;JmJ	;A=0 B#0 => A<B
		mov	[Kd+4],EDX		;EDX= m1, m2, m3, 0
		mov	[Kd+8],ECX		;+  [A(B b)a]
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS, V2 		;[PrSovm],V2   A<B закончили		признак
	JMP	P2			; A<B
;******************
Pr2:				;JgJ	;A#0 B=0 => A>B
		mov	[Kd+3],EDX		;EDX= m1, m2, m3, 0
		mov	[Kd+8],ECX		;:=   [A(B b)a]
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,_V3 		;[PrSovm],V3 - признак
	JMP	P3			;A>B
;**************************
Pr3:				;JeJ  	;оба операнда A=B ==>
		bsr	CX,AX			;A
		shl	CX,8
		bsf	DX,BX			;B
		or	CX,DX
		mov	[Kd+4],EDX		;EDX= m1, m2, m3, 0
		mov	[Kd+8],ECX		;$$$[A(B b)a]
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,_V4		; [PrSovm],V4 -признак
	JMP	P4			;A=B
;************************************ P5 ********************************
Pr4:
;? =  m2/m3  степень совпадения ?   (т.к.  m2 =?( N2 ) =3)
;? =  m1/m3   степень несовпадения ? ( т.к.  m1 = ?( N1 ) =1)
		bsr	CX,AX			;A
		shl	CX,8
		bsr	DX,BX			;B
		or	CX,DX
		shl	ECX,16
		bsf	CX,AX			;A
		shl	CX,8
		bsf	DX,BX			;B
		or	CX,DX
		mov	[Kd+8],ECX		;///[A(B b)a]
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,_V5 		;[PrSovm],V5	признак
	JMP	P5			;in B=0 A>B
;**********************************************  P6 *********************
Pr5:
;? =  m2/m3  степень совпадения ?   (т.к.  m2 =?( N2 ) =3)
;? =  m1/m3   степень несовпадения ? ( т.к.  m1 = ?( N1 ) =1)
		bsr	CX,AX			;A
		shl	CX,8
		bsr	DX,BX			;B
		or	CX,DX
		shl	ECX,16
		bsf	CX,AX			;A
		shl	CX,8
		bsf	DX,BX			;B
		or	CX,DX
		mov	[Kd+8],ECX		;+=  [A(B b)a]
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,_V6		; [PrSovm],V6		;признак
	JMP	P6			;in A=0 A<B
;************************************ P6 ********************************
;*********** нет пересекающихся разрядов ***P7 ********************************
Pr6:
		bsf	BP,AX		;A
		shl	BP,8
		bsf	CX,BX		;B
		or	BP,CX		;A  B

		bsr	CX,AX		;A	старшие разряды
		shl	CX,8
 		bsr	DX,BX		; старшие	А  В
		or	CX,DX
		mov	DX,CX		;DX  старшие	А  В
		shl	ECX,16
		mov	CX,BP
		mov	[Kd+8],ECX	;]]границы [A(B b)a]
		cmp	dl,dh		;dl=>B  dh=>A номера старших единичек
	JG	P6BA			;B=1 A=0  =>A<B верхняя B больше A (B [A
					;B=0 A=1  =>A>B
		cmp	cl,ch		;номера младших единичек  [A (B
	jL	@F			;номера младших единичек [(   a] b)
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,_V7 		;
	jmp	P7			;  	[(  b) a]
@@:
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,_V8 		;[A (B a]  b)
	jmp	P8			;P72		A>B
;******************** Закончили с комб. P6AB ********
;***************** комб.  PrBA **********
P6BA:
		cmp	cl,ch		;номера младших единичек (B [A
	jL	@F			;(B [A a] b)
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,_V9 		;(B [A b) a]
	jmp	P9			;	A<B
;************************************
@@:
	ВосстановилиРегистры	EAX,EBX,ECX,EDX,EBP
		mov	PS,_V10 		;(B [A a] b)
	jmp	P10			;A<B
;********************* Закончили**************
}
******************
