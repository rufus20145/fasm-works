;1	N!CMPabPr	GA,GB,Pr,—Ѕќ…			в файле NCMPabPr.inc
;2	N!CMPabJm							переход
;3	N!CMPabPrJm							признак и переход
;4	—равнитьA_B_ƒать_признак			~1
;***********************************************************			

;*****************A?BPr ****************  дл¤ AL  и  BL
	MACRO	N!CMPabPr  GA,GB,Pr,SBOY		;=,<  ,  >
{	LOCAL	MEXI,JmJ,JgJ,JeJ
if  GA & GB  in  <al,bl>
else
		УпряталиРегистры	EAX,EBX
			mov	BL,GB				;2-й операнд
			mov	AL,GA				;1-й операнд
end if
		and	al,0FFh
	jne	@F
		and	AL,0FFh
	jne	JmJ							;A=0 B#0 => A<B закончили
	jmp	JeJ							;A=0  B=0   A=B
@@:			
		and	BL,0FFh
	je	JgJ	
;*********  ќсновна¤ часть    **************
		mov	BH,AL  					;чтобы A(bh)  B(bl) были в одной строке
		mov	AH,AL			
		xor	AH,BL					;в CL маска
	je	JeJ							;оба операнда A=B ==>
		and	BL,AH					;после выделени¤ маски A
	jne	@F							;A маскированное пересекаетс¤ с B  маскированное
	jmp	JgJ 						;in B=0 A>B [5*] они не зависимы и надо продолжать
@@:
		and	BH,AH					;	A(bh)
	je	JmJ							;in   A(ah)=0	A<B
;**************************			;ќстались операнды только с единичками в разных разр¤дах
		mov	AX,08080h				;рр 16&8	1
		and	AX,BX					;
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разр¤ды TEMP[0-7] 
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
	jmp	SBOY						;невозможна¤ —»“”ј÷»я :ѕ≈„ј“№ через P!rAdrStop—ќќЅў≈Ќ»я 
@@:									;A(ah)  B(al)
		and	AL,0FFh					;A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ							;B=1 A=0  =>A<B	
;***********ќбщий ¬џ’ќƒ*************;B=0 A=1  =>A>B
JgJ:
if  GA & GB  in  <al,bl>
else
	ВосстановилиРегистры	EAX,EBX
end if
		mov Pr,2					;A>B	Pr может быть регистром		
	JMP	MEXI
JeJ:	
if  GA & GB  in  <al,bl>
else
	ВосстановилиРегистры	EAX,EBX
end if
		mov Pr,0					;A=B		
	JMP	MEXI						;
JmJ:
if  GA & GB  in  <al,bl>
else
	ВосстановилиРегистры	EAX,EBX
end if
		mov Pr,1					;A>B		
MEXI:								;продолжение после блока
}
;*****************************************************************
;*****************N!CMPabJm****************  дл¤ AL  и  BL укороченный
	MACRO	N!CMPabJm  GA,GB,T1,T2,T3,SBOY		;=,>, < 
{	LOCAL	MEXI,JmJ,JgJ,JeJ
if  GA & GB  in  <al,bl>
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
;*********  ќсновна¤ часть    **************
		mov	BH,AL  					;чтобы A(bh)  B(bl) были в одной строке
		mov	AH,AL			
		xor	AH,BL					;в CL маска
	je	JeJ							;оба операнда A=B ==>
		and	BL,AH					;после выделени¤ маски A
	jne	@F							;A маскированное пересекаетс¤ с B  маскированное
	jmp	JgJ 						;in B=0 A>B [5*] они не зависимы и надо продолжать
@@:
		and	BH,AH					;	A(bh)
	je	JmJ							;in   A(ah)=0	A<B
;**************************			;ќстались операнды только с единичками в разных разр¤дах
		mov	AX,08080h				;рр 16&8	1
		and	AX,BX					;
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разр¤ды TEMP[0-7] 
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
	jmp	SBOY						;невозможна¤ —»“”ј÷»я :ѕ≈„ј“№ через P!rAdrStop—ќќЅў≈Ќ»я 
@@:									;A(ah)  B(al)
		and	AL,0FFh					;A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ							;B=1 A=0  =>A<B	
;***********ќбщий ¬џ’ќƒ*************;B=0 A=1  =>A>B
JgJ:
if  GA & GB  in  <al,bl>
else
ВосстановилиРегистры	EAX,EBX		;[7] [40]
end if
			if   ~T2 eq
	JMP	T2								;A<B
			else
	JMP	MEXI
			end if
JeJ:	
if  GA & GB  in  <al,bl>
else
ВосстановилиРегистры	EAX,EBX		;[7] [40]
end if
			if   ~T1 eq
	JMP	T1								;Цавны A=B
			else
	JMP	MEXI
			end if						;[4]
JmJ:
if  GA & GB  in  <al,bl>
else
ВосстановилиРегистры	EAX,EBX		;[7] [40]
end if
			if   ~T3 eq
	JMP	T3								;A>B
			else
			end if						;JMP	MEXI
MEXI:									;продолжение после блока
}
;*****************************************************************
;*****************  N!CMPabPrJm  ****************  дл¤ AL  и  BL укороченный
	MACRO	N!CMPabPrJm  GA,GB,Pr,T1,T2,T3,SBOY		;=,>, < 
{	LOCAL	MEXI,JmJ,JgJ,JeJ
if  GA & GB  in  <al,bl>
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
;*********  ќсновна¤ часть    **************
		mov	BH,AL  					;чтобы A(bh)  B(bl) были в одной строке
		mov	AH,AL			
		xor	AH,BL					;в CL маска
	je	JeJ							;оба операнда A=B ==>
		and	BL,AH					;после выделени¤ маски A
	jne	@F							;A маскированное пересекаетс¤ с B  маскированное
	jmp	JgJ 						;in B=0 A>B [5*] они не зависимы и надо продолжать
@@:
		and	BH,AH					;	A(bh)
	je	JmJ							;in   A(ah)=0	A<B
;**************************			;ќстались операнды только с единичками в разных разр¤дах
		mov	AX,08080h				;рр 16&8	1
		and	AX,BX					;
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разр¤ды TEMP[0-7] 
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
	jmp	SBOY						;невозможна¤ —»“”ј÷»я :ѕ≈„ј“№ через P!rAdrStop—ќќЅў≈Ќ»я 
@@:									;A(ah)  B(al)
		and	AL,0FFh					;A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ							;B=1 A=0  =>A<B	
;***********ќбщий ¬џ’ќƒ*************;B=0 A=1  =>A>B
JgJ:
 if  GA & GB  in  <al,bl>
else
ВосстановилиРегистры	EAX,EBX		;[7] [40]
end if
		mov Pr,2
			if   ~T2 eq
	JMP	T2								;A<B
			else
	JMP	MEXI
			end if
JeJ:	
if  GA & GB  in  <al,bl>
else
ВосстановилиРегистры	EAX,EBX		;[7] [40]
end if
		mov Pr,0
			if   ~T1 eq
	JMP	T1								;Цавны A=B
			else
	JMP	MEXI
			end if						;[4]
JmJ:
 if  GA & GB  in  <al,bl>
else
ВосстановилиРегистры	EAX,EBX		;[7] [40]
end if
		mov Pr,1
			if   ~T3 eq
	JMP	T3								;A>B
			else
			end if						;JMP	MEXI
MEXI:									;продолжение после блока
}
;*****************************************************************
;	  —равнитьA_B_ƒать_признак\
;			 A=?B\
;			ѕризнак_в=:PRi\
;			ѕри—бое=>M!ISTEK
;**************************************** »спользует
;	~	N!CMPabPr	al,bl,T1,T2,T3,SBOY		самый короткий вариант
;	~	N!CMPabPr	cl,dl,T1,T2,T3,SBOY

;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MACRO	СравнитьA_B_b_Дать_признак	arg
{common  	match	OP1 =?  OP2  PUST==:Pr PUSTO==>Er,arg
\{
		if   ~\Er eq
		\N!CMPabPr	\OP1,\OP2,\Pr,\Er
		else
		\N!CMPabPr	\OP1,\OP2,\Pr,
			end if
			\}
}
;******************************************************************
;	СучетомОтношений_A?B_Перейти\
;			 A=?B\
;			==Pr0 =>Pr1  =< Pr2\
;			ѕри—бое=>M!ISTEK
;****************************************»спользует
;		N!CMPabJm	al,bl,ah,0		самый короткий вариант
;		N!CMPabJm	cl,dl,[Priznak],SBOY
;+++++++++++++++++++++++++++++++++++++++++++++++
	MACRO	СучетомОтношений_A?B_Перейти	arg
{common  	match	OP1 =?  OP2   ==Pr0 =>Pr1  =< Pr2 ==>Er,arg
		\{\N!CMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>Pr1  =<  ==Er,arg		;1 1  0
		\{
			\N!CMPabJm  \OP1,\OP2,\Pr0,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>  =<  ==Er,arg		;1 0 0
		\{
			\N!CMPabJm  \OP1,\OP2,\Pr0,\Pr1,,\Er
 		\}
common  	match	OP1 =?  OP2   ==Pr0 =>  =<Pr2  ==Er,arg		;1 0 1
		\{
			\N!CMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>Pr1  =<Pr2  ==Er,arg		;0 1 1
		\{
			\N!CMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>Pr1  =<  ==Er,arg		;0 1 0
		\{
			\N!CMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>  =<Pr2  ==Er,arg		;0 0 1
		\{
			\N!CMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er
 		\}
common  	match	OP1 =?  OP2   == =>  =<  ==Er,arg			;0 0 0
		\{
			\Print!afall   "ERROR   here   all   Pr0 & Pr1 & Pr2"
 		\}
 }
;*******************************************************
;—учетомќтношений_ƒатьѕризнак_ѕерейти\
;			 A=?B\
;			ѕризнак_в=:PRi\
;			==Pr0 =>Pr1  =< Pr2\
;			ѕри—бое=>M!ISTEK

;*****************  N!CMPabPrJm  ****************  дл¤ AL  и  BL укороченный
	MACRO	N!CMPabPRiJm  GA,GB,Pr,T1,T2,T3,P0,P1,P2,SBOY		;=,>, < 
{	LOCAL	MEXI,JmJ,JgJ,JeJ
if  GA & GB  in  <al,bl>
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
;*********  ќсновна¤ часть    **************
		mov	BH,AL  					;чтобы A(bh)  B(bl) были в одной строке
		mov	AH,AL			
		xor	AH,BL					;в CL маска
	je	JeJ							;оба операнда A=B ==>
		and	BL,AH					;после выделени¤ маски A
	jne	@F							;A маскированное пересекаетс¤ с B  маскированное
	jmp	JgJ 						;in B=0 A>B [5*] они не зависимы и надо продолжать
@@:
		and	BH,AH					;	A(bh)
	je	JmJ							;in   A(ah)=0	A<B
;**************************			;ќстались операнды только с единичками в разных разр¤дах
		mov	AX,08080h				;рр 16&8	1
		and	AX,BX					;
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разр¤ды TEMP[0-7] 
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
	jmp	SBOY						;невозможна¤ —»“”ј÷»я :ѕ≈„ј“№ через P!rAdrStop—ќќЅў≈Ќ»я 
@@:									;A(ah)  B(al)
		and	AL,0FFh					;A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ							;B=1 A=0  =>A<B	
;***********ќбщий ¬џ’ќƒ*************;B=0 A=1  =>A>B
JgJ:
if  GA & GB  in  <al,bl>
else
ВосстановилиРегистры	EAX,EBX		;[7] [40]
end if
 
		mov PR2,P2						;2
			if   ~T2 eq
	JMP	T2								;A<B
			else
	JMP	MEXI
			end if
JeJ:	
 if  GA & GB  in  <al,bl>
else
ВосстановилиРегистры	EAX,EBX		;[7] [40]
end if
		mov PR0,P0
			if   ~T1 eq
	JMP	T1								;Цавны A=B
			else
	JMP	MEXI
			end if						;[4]
JmJ:
 if  GA & GB  in  <al,bl>
else
ВосстановилиРегистры	EAX,EBX		;[7] [40]
end if
		mov PR1,P1
			if   ~T3 eq
	JMP	T3								;A>B
			else
			end if						;JMP	MEXI
MEXI:									;продолжение после блока
}
;*****************************************************************

;СучетомОтношенийb_ДатьПризнак_Перейти\
;		A=?B\
;			PRi:=P0	PRi:=P1 PRi:=P2\
;							==Pr0 =>Pr1  =< Pr2\
;												ѕри—бое=>M!ISTEK
;********************************************************
;*****************************
	MACRO	СучетомОтношенийb_ДатьПризнак_Перейти	arg
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

;M!ISTEK:
;	P!rAdrStop	=BalarirevNE	MACRO	C!abcPr	ERROR
if   ~\Pr0 eq
		if   ~\Pr1 eq
				if   ~\Pr2 eq	
				\N!CMPabJm  \OP1,\OP2,\Pr0,\Pr1,\Pr2,\Er	
				else
				\N!CMPabJm  \OP1,\OP2,\Pr0,\Pr1,,\Er
				end if
		else
				if   ~\Pr2 eq
				\N!CMPabJm  \OP1,\OP2,\Pr0,,\Pr2,\Er
				else
				\N!CMPabJm  \OP1,\OP2,\Pr0,,,\Er
				end if				
		end if
	else
		if   ~\Pr1 eq
				if   ~\Pr2 eq
				\N!CMPabJm  \OP1,\OP2,,\Pr1,\Pr2,\Er	
				else
				\N!CMPabJm  \OP1,\OP2,,\Pr1,,\Er
				end if
		else
				if   ~\Pr2 eq
				\N!CMPabJm  \OP1,\OP2,,,\Pr2,\Er	
				else
				\N!CMPabJm  \OP1,\OP2,,,,\Er			;ќш-ка «ачем провер¤ли
				end if
		end if
	end if