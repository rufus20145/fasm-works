;********************************************************************
;в файле NCMP2.inc
;1	N!bCMPabJm	GA,GB,Pr,—Ѕќ…				переходы для байтовых размеров
;2	Сучетомќтношенийbѕерейти				синтаксическая форма ~ 1
;3	C!MPABop								переходы для любых размеров =<32 рр
;4	—учетомќтношений_A?B_ѕерейти			синтаксическая форма	3
;5	xA?xBJmp								переходы  для AX  и  BX
;6	eA?eBJmp								переходы  для 32 разрядных
;7	N!bCMPabPr	GA,GB,Pr,SBOY				короткая форма = 0 > =1 < =2
;8	СравнитьA_B_b_Дать_признак				синтаксическая форма ~ 7
;9	Сравнил_Дал								синтаксическая форма ~ 7
;					в файле NCMPabPr.inc
;10 N!bCMPabPrJm							признак и переход
;11	СучетомОтношенийb_Датьпризнак_Перейти	синтаксическая форма ~ 9
;12	N!bCMPabPRiJm							признак и переход
;13	СучетомОтношенийb_ДатьПризнаки_Перейти	синтаксическая форма ~ 11
;********************************************************************


; 0 = | 1 > | 2<
;***************** 10  N!CMPabPrJm  ****************  для AL  и  BL укороченный
	MACRO	N!CMPabPrJm  GA,GB,Pr,T1,T2,T3,SBOY		;=,>, <
{	LOCAL	MEXI,JmJ,JgJ,JeJ
if  GA  in  <al,bl>
				if  GB  in  <al,bl>
				else
				УпряталиРегистры	EAX,EBX
					mov	BL,GB				;2-й операнд
					mov	AL,GA				;1-й операнд
				end if
else
		УпряталиРегистры	EAX,EBX
			mov	BL,GB				;2-й операнд
			mov	AL,GA				;1-й операнд
end if
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
		xor	AH,BL					;в AH маска
	je	JeJ							;оба операнда A=B ==>
		and	BL,AH					;после выделения маски A
	jne	@F							;A маскированное пересекается с B  маскированное
	jmp	JgJ 						;in B=0 A>B [5*] они не зависимы и надо продолжать
@@:
		and	BH,AH					;	A(bh)
	je	JmJ							;in   A(ah)=0	A<B
;**************************			;ќстались операнды только с единичками в разных разрядах
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
	jmp	-4
	else
	jmp	SBOY						;невозможная  через P!rAdrStop
	end if
@@:									;A(ah)  B(al)
		and	AL,0FFh					;A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ							;B=1 A=0  =>A<B
;***********Общий блок *************;B=0 A=1  =>A>B
JgJ:
if  GA  in  <al,bl>
else
	if  GB  in  <al,bl>
	else
	ВосстановилиРегистры	EAX,EBX
	end if
ВосстановилиРегистры	EAX,EBX
end if
		mov Pr,2
			if   ~T2 eq
	JMP	T2								;A<B
			else
	JMP	MEXI
			end if
JeJ:
if  GA  in  <al,bl>
else
	if  GB  in  <al,bl>
	else
	ВосстановилиРегистры	EAX,EBX
	end if
ВосстановилиРегистры	EAX,EBX
end if
		mov Pr,0
			if   ~T1 eq
	JMP	T1								;Цавны A=B
			else
	JMP	MEXI
			end if						;[4]
JmJ:
if  GA  in  <al,bl>
else
	if  GB  in  <al,bl>
	else
	ВосстановилиРегистры	EAX,EBX
	end if
ВосстановилиРегистры	EAX,EBX
end if
		mov Pr,1
			if   ~T3 eq
	JMP	T3								;A>B
			else
			end if						;JMP	MEXI
MEXI:									;продолжение после блока
}
;************* 11 СучетомОтношенийb_ДатьПризнаки_Перейти******
;СучетомОтношенийb_ДатьПризнаки_Перейти\
;			 A=?B\
;			ѕризнак_в=:PRi\
;			==Pr0 =>Pr1  =< Pr2\
;			ѕри—бое=>M!ISTEK
;*****************************
	MACRO	СучетомОтношенийb_ДатьПризнаки_Перейти	arg
{common match PUSTO==:PRi OP1 =? OP2 PRi=:==P0 PRi=:==P1 PRi=:==P2 ==Pr0 =>Pr1 =< Pr2 ==>Er,arg
		\{N!CMPabPRiJm  \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2 Pusto==:PRi  ==Pr0 =>Pr1  =<  ==Er,arg		;1 1  0
		\{
			N!CMPabPRiJm \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2 Pusto==:PRi ==Pr0 =>  =<  ==Er,arg		;1 0 0
		\{
			N!CMPabPRiJm  \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2 Pusto==:PRi  ==Pr0 =>  =<Pr2  ==Er,arg		;1 0 1
		\{
			N!CMPabPRiJm  \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2 Pusto==:PRi  == =>Pr1  =<Pr2  ==Er,arg		;0 1 1
		\{
			N!CMPabPRiJm \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2 Pusto==:PRi  == =>Pr1  =<  ==Er,arg		;0 1 0
		\{
			N!CMPabPRiJm \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2 Pusto==:PRi  == =>  =<Pr2  ==Er,arg		;0 0 1
		\{
			N!CMPabPRiJm  \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2 Pusto==:PRi  == =>  =<  ==Er,arg			;0 0 0
		\{
			\Print!afall   "ERROR   here   all   Pr0 & Pr1 & Pr2"
 		\}
 }
;*******************************************************
;***********  12 N!CMPabPRiJm  ****************  для AL  и  BL укороченный
	MACRO	N!CMPabPRiJm  GA,GB,Pr,T1,T2,T3,P0,P1,P2,SBOY		;=,>, <
{	LOCAL	MEXI,JmJ,JgJ,JeJ
if  GA  in  <al,bl>
				if  GB  in  <al,bl>
				else
				УпряталиРегистры	EAX,EBX
					mov	BL,GB				;2-й операнд
					mov	AL,GA				;1-й операнд
				end if
else
		УпряталиРегистры	EAX,EBX
			mov	BL,GB				;2-й операнд
			mov	AL,GA				;1-й операнд
end if
		and	AL,0FFh
	jne	@F
		and	BL,0FFh
	jne	JmJ							;A=0 B#0 => A<B закончили
	jmp	JeJ							;A=0  B=0   A=B
@@:
		and	BL,0FFh
	je	JgJ
;*********  ќсновная часть    **************
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
;**************************			;ќстались операнды только с единичками в разных разрядах
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
	jmp	SBOY						;невозможная —»“”ј÷»я :ѕ≈„ј“№ через P!rAdrStop—ќќЅў≈Ќ»я
@@:									;A(ah)  B(al)
		and	AL,0FFh					;A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ							;B=1 A=0  =>A<B
;***********   Общий выход  *************;B=0 A=1  =>A>B
JgJ:
if  GA  in  <al,bl>
else
	if  GB  in  <al,bl>
	else
	ВосстановилиРегистры	EAX,EBX
	end if
ВосстановилиРегистры	EAX,EBX
end if
		mov PR2,P2						;2
			if   ~T2 eq
	JMP	T2								;A<B
			else
	JMP	MEXI
			end if
JeJ:
 if  GA  in  <al,bl>
else
	if  GB  in  <al,bl>
	else
	ВосстановилиРегистры	EAX,EBX
	end if
ВосстановилиРегистры	EAX,EBX
end if
		mov PR0,P0
			if   ~T1 eq
	JMP	T1								;Цавны A=B
			else
	JMP	MEXI
			end if						;[4]
JmJ:
 if  GA  in  <al,bl>
else
	if  GB  in  <al,bl>
	else
	ВосстановилиРегистры	EAX,EBX
	end if
ВосстановилиРегистры	EAX,EBX
end if
		mov PR1,P1
			if   ~T3 eq
	JMP	T3								;A>B
			else
			end if						;JMP	MEXI
MEXI:									;продолжение после блока
}
;*******************13 СучетомОтношенийb_ДатьПризнаки_Перейтии ****
;СучетомОтношенийb_ДатьПризнаки_Перейти\
;		A=?B\
;			PRi:=P0	PRi:=P1 PRi:=P2\
;							==Pr0 =>Pr1  =< Pr2\
;												ѕри—бое=>M!ISTEK
;********************************************************
;*****************************
	MACRO	СучетомОтношенийb_ДатьПризнаки_Перейти	arg
{common match PUSTO==:PRi OP1 =? OP2 PRi=:==P0 PRi=:==P1 PRi=:==P2 ==Pr0 =>Pr1 =< Pr2 ==>Er,arg
		\{N!CMPabPRiJm  \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2 PRi=:==P0 PRi=:==P1 PRi=:==P2  ==Pr0 =>Pr1  =<  ==Er,arg		;1 1  0
		\{
			N!CMPabPRiJm \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2 PRi=:==P0 PRi=:==P1 PRi=:==P2  ==Pr0 =>  =<  ==Er,arg		;1 0 0
		\{
			N!CMPabPRiJm  \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2 PRi=:==P0 PRi=:==P1 PRi=:==P2  ==Pr0 =>  =<Pr2  ==Er,arg		;1 0 1
		\{
			N!CMPabPRiJm  \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2 PRi=:==P0 PRi=:==P1 PRi=:==P2  == =>Pr1  =<Pr2  ==Er,arg		;0 1 1
		\{
			N!CMPabPRiJm \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2 PRi=:==P0 PRi=:==P1 PRi=:==P2  == =>Pr1  =<  ==Er,arg		;0 1 0
		\{
			N!CMPabPRiJm \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2 PRi=:==P0 PRi=:==P1 PRi=:==P2  == =>  =<Pr2  ==Er,arg		;0 0 1
		\{
			N!CMPabPRiJm  \OP1,\OP2,\PRi,\P0,\P1,\P2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2 PRi=:==P0 PRi=:==P1 PRi=:==P2  == =>  =<  ==Er,arg			;0 0 0
		\{
			\Print!afall   "ERROR   here   all   Pr0 & Pr1 & Pr2"
 		\}
 }
;*******************************************************

