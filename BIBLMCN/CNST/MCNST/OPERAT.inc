;1. CrPUSH	[string]
;1.1	УпрятатьРегистры 	[string]
;1.2 CrPUSHs	[string]	Упрятывание с контролем стека
;1.3 CrPUSHе	t_t1,[RE]	;упрятывание регистра и формирование константы под именем REt_t1
;2. CrPOP		[string]  v  CrPOP	[string]
;2.1	ВосстановитьРегистры	[string]
;2.2    CrPOP	[string]	Восстановление с контролем стека

;3. ВозвратИзDLL	REAX,[arg]
;3.1 ExDllC

;4. EntryDLL
;4.1 ВходВDLL	[arg]
;5.0 ОбнулилиРегистры	[Reg]
;5.1 ОбнулитьРегистры	[Reg]
;5.2 ObnulR		[RR]

;6.1 Инкримент Reg,Number
;6.2 Rinc		Reg,Number
;6.3 Инкримент (Reg1+Number1),(Reg2+Number2),.....
;
;7.1 Декримент	Reg,Number
;7.2 Rdec		Reg,Number
;7.3 Декрименты	(Reg1+Number1),(Reg2+Number2),.....
;
;8.1 Load!WriteMany	EBX =al |  EDX=al  |  ECX=al |  EAX=al
;      Загрузили!Присвоили	EBX =al |  EDX=al  |  ECX=al |  EAX=al
;*
;8.2 Load!Write	(EBX =al),(EDX=al),(EAX=al)		[arg]
;*
;8.3 Load!WriteOne 	EAX=al
;      Загрузил!Присвоил	EBX =EAX	  двойное слово
;      Загрузил!Присвоил	EBX =AX  слово
;      Загрузил!Присвоил	EBX =al	байт

;9.1 Полученное!Выгрузить
;9.2 Realize!Stowe
;*
; 10.1 Продвинул!поЦепочке  EBX<=ECX
; 10.2 Продвинули!поЦепочке	EAX<=EBX<=ECX<=EDX
; 10.3 MovingChain	EAX<=EBX<=ECX<=EDX
;*
;9. WrSwitchA?B	Rez1,Rez2,PRb,PRba,PRbe
;10. C1stosd	ParTb,ParSd,ParRd,ParLd
;11. C2stosd	ParDr,ParDl,N
;12. Cloads	ParMOM,REG
;13.WriteMany 	[parav1]			;([FlSizN]=ECX),([pMm]=ESI),([pMmz]=EDI),([NOTCH]=0)
;14 WriteOne 	parav1			;([FlSizN]=ECX)
;15 Tokenu 	[sequence]			;ПЕЧАТЬ констант и текстовых строк в процессе трансляции




;Отладочные инструменты
;20. Cdisplay		name		;- во время трансляции
	macro .. [.] {match .,. }

	macro COMMENT [.] {match .,. }

;macro ..[.]{.}  ----???????????????
;**********************1.2*****Упрятывание с контролем во время трансляции**********
MACRO	CrPUSHs	[string]			;A C D B   нумерация регистров
     {
     common
	forward
Rpushpop = Rpushpop+1  			;local label
	PUSH	string
    common					; label db string,0
}
;***********
macro PutSpisok  Spisok,registr
     {
       match any,Spisok \{ Spisok equ Spisok,registr \}
       match ,Spisok \{ Spisok equ registr \}			;срабатывает на первом этапе
     }
;*********************1.3 ***PUSHе ******
;				Маркировочное упрятывание. ПРИМЕР:  PUSHе  EBP,1
;					           Появляется константа EBP1
;				Можно PUSHе  EBP,one  ==> константа EBPone
;SpisokSteka	equ
 	MACRO	CrPUSHе	prefix,[RE]	;упрятывание регистра и формирование константы под именем REt_t1
{
common
 	PutSpisok	SpisokSteka,prefix#RE	;Запись упрятывающая уникальное имя регистра
forward
Rpushpop = Rpushpop+1  		;local label
	push	RE
}
;********************* 17 _____
;*******************1******
;**********************18**POPe	 RE,t_t1
;				Маркировочное восстановление из стека
 	MACRO	CrPOPe	t_t1, [RE]			;упрятали указатель на стек под именем t_t1
{

	if  ~ defined	SpisokSteka#t_t1		;если упрятывание с такой маркировкой не проходило
		display	"NE:  REG " # `RE
		display	`t_t1 # " not push"		;регистр не упрятывался через группу
	Restore	RE#t_t1
	display 13,10
	end if
	pop	RE
  }
;*********************1_____


;*******************5.1***********
	MACRO	ОбнулитьРегистры	[Reg]		;XOR	Reg,Reg
{
forward
		XOR	Reg,Reg
}
;*************

	MACRO	ОбнулилиРегистры	[Reg]		;XOR	Reg,Reg
{
forward
		XOR	Reg,Reg
}
;*********************5.2*****	Макро для обнуления списка регистров
	MACRO	ObnulR	[Reg]			;XOR	Reg,Reg
	{
forward
		XOR	Reg,Reg
	}
;*******************___________________

;*******************6.3
	MACRO	Инкрименты [arg]			;  !	EAX++2	ECX++4
{	match	(Reg =++ Number),arg
	\{ Rinc	\Reg,\Number\}
}

;******************7.3   *
;		ECX--4
	MACRO	Декрименты	[arg]		;DECRIMENT
{	match	(Reg=--Number),arg
	\{ Rdec	\Reg,\Number\}
}
;*****************7______________________
;********** 8 ********************
;********************************************
;Load!WriteMany	EBX =al &  EDX=al  &  ECX=al &  EAX=al
;Загрузили!Присвоили	EBX =al &  EDX=al  &  ECX=al &  EAX=al
;*
;Load!Write	(EBX =al),(EDX=al),(EAX=al)		[arg]
;*
;Load!WriteOne 	EAX=al
;Загрузил!Присвоил	EBX =EAX	  двойное слово
;Загрузил!Присвоил	EBX =AX  слово
;Загрузил!Присвоил	EBX =al	байт
;***************8.1**
MACRO	Загрузили!Присвоили arg		;Load!WriteMany	arg
{	Load!WriteMany	arg }
;****************
MACRO	Load!WriteMany	arg
{
	common  	match	P1 =& P2 ,arg
 	\{\arg1	equ	\`P1#\`P2
	   \NMRuu	equ	1
	match w1 =& w2,\P2
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
					;Print!afall   \NMRuu
	 	Load!WriteOne  \P1
		Load!WriteOne  \P2
end if
	\}
;***********
	common  	match	P1 =& P2 =& P3 ,arg		;
 	\{\arg1	equ	\`P1#\`P2
	   \NMRuu	equ	1
	match w1 =& w2,\P3
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
					;Print!afall   \NMRuu
	 	Load!WriteOne  \P1
		Load!WriteOne \P2
		Load!WriteOne  \P3
end if
	\}
;***********
	common  	match	P1 =& P2 =& P3 =& P4 ,arg		;
 	\{\arg1	equ	\`P1#\`P2
	   \NMRuu	equ	1
	match w1 =& w2,\P4
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
					;Print!afall   \NMRuu
	 	Load!WriteOne  \P1
		Load!WriteOne  \P2
		Load!WriteOne  \P3
		Load!WriteOne  \P4
end if
	\}
;***********
	common  	match	P1 =& P2 =& P3 =& P4 =& P5 ,arg		;
 	\{\arg1	equ	\`P1#\`P2
	   \NMRuu	equ	1
	match w1 =& w2,\P5
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
					;Print!afall   \NMRuu
	 	Load!WriteOne  \P1
		Load!WriteOne  \P2
		Load!WriteOne  \P3
		Load!WriteOne  \P4
		Load!WriteOne  \P5
end if
	\}
;***********
	common  	match	P1 =& P2 =& P3 =& P4 =& P5 =& P6,arg		;
 	\{\arg1	equ	\`P1#\`P2
	   \NMRuu	equ	1
	match w1 =& w2,\P6
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
					;Print!afall   \NMRuu
	 	Load!WriteOne  \P1
		Load!WriteOne  \P2
		Load!WriteOne  \P3
		Load!WriteOne  \P4
		Load!WriteOne  \P5
		Load!WriteOne  \P6
end if
	\}
;***********
	common  	match	P1 =& P2 =& P3 =& P4 =& P5 =& P6 =& P7,arg
 	\{\arg1	equ	\`P1#\`P2
	   \NMRuu	equ	1
	match w1 =& w2,\P7
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
					;Print!afall   \NMRuu
	 	Load!WriteOne  \P1
		Load!WriteOne  \P2
		Load!WriteOne  \P3
		Load!WriteOne  \P4
		Load!WriteOne  \P5
		Load!WriteOne  \P6
		Load!WriteOne  \P7
end if
	\}
}
;*********************8.2*****
	MACRO	Load!Write	[arg]		;Load!Write
{forward		Load!WriteOne  arg }
;**************       8.3
	MACRO	Загрузил!Присвоил	arg		;Load!WriteOne
{common	Load!WriteOne	arg}
;*****************
	MACRO	Load!WriteOne	arg
{

	common  	match	OPER == REAX,arg		;
 	\{
	xor	EAX,EAX
	           if   \REAX in   <\al>
	lodsb
			if   ~\OPER in   <al>
				if   \OPER in   <al,ah,bl,bh,cl,ch,dl,dh>
				mov	\OPER,al
				else
				mov	\OPER,EAX
				end if
			end if
	          else
		    if   \REAX in   <AX>
	lodsw
			if   ~\OPER in   <AX>
				if   \OPER  in   <AX,BX,CX,DX,BP,SI,DI>
				mov	\OPER,AX
				else
				mov	\OPER,EAX
				end if

			end if
		    else
		       if   \REAX in   <EAX>		;32 v 24 разряда
	lodsd
			     if   ~\OPER in   <EAX>
				mov	\OPER,EAX
				end if
		        else
		     mov	\OPER,EAX
		      end if
		   end if
	        end if				;пока нет lodsq 64
	\}
}
;************************** 8.4
;**********************конец 8__________________
;********************************
;9.1 Полученное!Выгрузить
;9.2 Realize!Stowe
;*************************** 9 ________________
;***************************10.1 ****************
	MACRO	Продвинул!поЦепочке	arg		;mov	P1,P2
{
	common  	match	P1 =<- P2 ,arg		;!!!!
 	\{	\arg1	equ	\`P1#\`P2
	   \NMRuu	equ	1
	match w1 =<= w2,\P2
			\\{\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
		mov	P1,P2
else
	display	"NE: ERROR(MovingChain) - many operand or not correct"
end if
	\}
}
;**********************10.2
	;MACRO	MovingChain  arg
;{ Продвинули!поЦепочке  arg }
;*******
	MACRO	Продвинули!поЦепочке  arg		;D <= C <= B<=A
{						;WHERE
		Print!afall  arg
		display 13,10
NMRuu	equ	0
	common  	match	P1 =<= P2 ,arg		;
 	\{	\arg1	equ	\`P1#\`P2
	   \NMRuu	equ	1
	match w1 =<= w2,\P2
			\\{\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
		mov	\P1,\P2
end if
	\}
	common  	match	P1 =<= P2 =<= P3,arg		;
	\{	\arg1	equ	\`P1#\`P3
	   \NMRuu	equ	1
			match w1 =<= w2,\P3
			\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
		mov	\P1,\P2
		mov	\P2,\P3
end if
	\}
	common  	match	P1 =<== P2 =<== P3 =<== P4,arg		;
 	\{
	\arg1	equ	\`P2#\`P4
	   \NMRuu	equ	1
			match w1 =<== w2,\arg1
			\\{\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
		Print!afall  \arg1
		display 13,10
		mov	\P1,\P2
		mov	\P2,\P3
		mov	\P3,\P4
else
		Print!afall  \arg1
		display 13,10
end if
	\}
	common  	match	P1 =<= P2 =<= P3=<= P4=<= P5,arg		;
 	\{	\arg1	equ	\`P2#\`P4
	   \NMRuu	equ	1
		match w1 =<= w2,\P4
			\\{\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
		mov	P1,P2
		mov	P2,P3
		mov	P3,P4
		mov	P4,P5
else
end if

	\}
if	NMRuu	eq	0
	display	"NE: ERROR(MovingChain) - many operand or not correct",13,10
	else
	end if
}
;***********************
;			Присвоили!Значения		EAX=[ARG] & [MEM]=EDX
	MACRO	Присвоили!Значения   arg			;ArBvAp
{
		common match a,arg
\{		\arg1	equ	\`a
\NMRuu	equ	1
match aw=&ww,\arg1
\\{	\\MRuu	equ	0\\}
if	\MRuu	eq	1
		ArBvAp	a
				;Print!afall   \NMRuu
end if
\}
;************************
common match a=+b,arg
  \{			\arg1	equ	\`a#\`b		;#\`c#\`d#`b
\NMRuu	equ	1
match aww=& ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
		ArBvAp	a
		ArBvAp	b
     \}
;**************************
common match a=+b=+c,arg
  \{			\arg1	equ	\`a#\`b#\`c
\NMRuu	equ	1
match aww=&ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
		ArBvAp	a
		ArBvAp	b
		ArBvAp	c
end if
     \}
;*************************************
comman	match a=+b=+c=+d,arg
  \{			\arg1	equ	\`a#\`b#\`c#\`d
\NMRuu	equ	1
match aww =& ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
		ArBvAp	a
		ArBvAp	b
		ArBvAp	c
		ArBvAp	d
end if
     \}
;**************************
match a=+b=+c=+d=+ e,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e
\NMRuu	equ	1
match aww =& ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
		ArBvAp	a
		ArBvAp	b
		ArBvAp	c
		ArBvAp	d
		ArBvAp	e
end if
     \}
;**************************
match a=+b=+c=+d=+ e=+f,arg
  \{					\arg1	equ	a#\`b#\`c#\`d#\`e#\`f
\NMRuu	equ	1
match aww =& ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
		ArBvAp	a
		ArBvAp	b
		ArBvAp	c
		ArBvAp	d
		ArBvAp	e
		ArBvAp	f
end if
     \}
;**************************
match a=+b=+c=+d=+ e=+f=+g,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g
\NMRuu	equ	1
match aww =&  ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
		ArBvAp	a
		ArBvAp	b
		ArBvAp	c
		ArBvAp	d
		ArBvAp	e
		ArBvAp	f
		ArBvAp	g
end if
     \}
}
;***********************
;	 ArBvAp	AX=[RAB]    |    ESI++4        | 	ESI++
;********************
	MACRO	ArBvAp	arg
{
	common match pr1===pr2,arg
\{	B!A	\pr1,\pr2  \}
;*
		common match pr1=++,arg
\{
	if	~\pr2inc eq
	Rinc	\pr1,\pr2
	else
	inc	\pr1  \}
}
;***********************
	MACRO	Присвоил!Значение	arg			;B!A	\pr1,\pr2
{
	common match pr1===pr2,arg
\{	B!A	\pr1,\pr2 \}

}
;***********************************************
;*********************
COMMENT 			{
list equ		;пусто
    macro append list,item
     {
       match any, list \{ list equ list,item \}
       match , list \{ list equ item \}			;срабатывает на первом этапе
  END	COMMENT		   }
;*******************************
;	макровызов list			;НЕ ПРОХОДИТ, т.к. не развернуться параметры
;match params, list { макровызов params }		;выход использование match
	MACRO  Процедуры макровызов,[list]	;Процедуры ВызовС++ [list]
{match params, list { макровызов params }

;*****************************************
	MACRO	Инкриментнул!вСтруктуру	Имяструктуры,arg
{
	inc	arg
}

;************************11**************([Str@.Dr_d@]=Zn|EAX-EBX|EBX-EAX)
;					A?expresion  (pr20=pr21)  pr21=EAX-EBX
MACRO	A?expresion	arg
{
	display "EXPRES?"
	 display 13,10
	;Print!afall  arg
	; display 13,10
	repeat 1
	common match (pr1==pr2),arg
	\{
		common match pr21 =+ pr22,pr2 \\{display "EXPRES1" \\}
		common match pr21 =- pr22,pr2
	   \\{
	      if  pr1   in  <al,bl,cl,dl,ah,bh,ch,dh,AX,BX,CX,DX,EAX,EBX,ECX,EDX,EBP>
		if  pr21  in  <al,bl,cl,dl,ah,bh,ch,dh,AX,BX,CX,DX,EAX,EBX,ECX,EDX,EBP>
		     if  pr22  in  <al,bl,cl,dl,ah,bh,ch,dh,AX,BX,CX,DX,EAX,EBX,ECX,EDX,EBP>
		     sub	pr21,pr22						;все три параметра регистры
		     mov	pr1,pr21
			display "EXPRES00"
		     break
		    else
		    sub	pr21,pr22		;[pr22]
		    mov	pr1,pr21
		     break
		   end if
		else
		end if
	else							;mem reg reg
		if  pr21  in  <al,bl,cl,dl,ah,bh,ch,dh,AX,BX,CX,DX,EAX,EBX,ECX,EDX,EBP>
		     if  pr22  in  <al,bl,cl,dl,ah,bh,ch,dh,AX,BX,CX,DX,EAX,EBX,ECX,EDX,EBP>
		     sub	pr21,pr22						;все три параметра регистры
		     mov	pr1,pr21		;[pr1]
			display "EXPRES01"
			display 13,10
		     break
		    else
		    sub	pr21,pr22		;[pr22]
		    mov	pr1,pr21		;[pr1]
		     break
		   end if
		else
		end if
	end if
	\\}
	exp	equ	(pr1=pr2)	;pr1=const
	display "EXPRES="
	 display 13,10
	WriteOne  	exp		;A?expresion  (pr20=pr21)
	Print!afall  exp
 	display 13,10
	break
\}
	break
     end   repeat
}
;*******************************************
;******************************10***************

;********************************************


;***********************10
;***********************11***
;		******** макро по записи полей структуры часть 2: C2stosd	ParDr,ParDl,N
MACRO	C2stosd	ParDr,ParDl,N
{					;s
			LOCAL	SHA1,SHA2,SHA3,SHA4,FINICH

		mov	[Str@fp.N],AX	; 1пар. номер отсчета средней точки может быть 1 2 слова
		mov	[Str@fp.Dr],cl	; 2 пар отсчеты справа
 		mov	[Str@fp.Dl],bl	; 3 пар отсчеты слева

		mov	EAX,[SECNf]	;SECNf
		stosd
FINICH:
	CrPOP   EAX,EBX ,ECX,EBP
}
;***********************11
;***********************12************* Обращение Cloads	[ParMOM],EBX  v Cloads   al,EBX  v  Cloads 2,EBX




;***********************1****  WriteC
	MACRO	WriteMany 	[parav1]		;([FlSizN]=ECX),([pMm]=ESI),([pMmz]=EDI),([NOTCH]=0)
{
forward
	WriteOne 	parav1
}
;**********************1****   END
;**********************14*** WriteOne **** WriteOne
;1.					(EDX=EBP)|
;2.						(ECX=[FlSizN])|
;3.			(ECX=FlSizN) -Error  надо (ESI=FlSizN) |
;4.							         ([FlSizN]=ECX)|
;5.						4.=5.		(FlSizN=ECX) ~~[FlSizN]=ECX|
;6.								([FlSizN]=const)|
;7.			~(mem=[MEM}|	-запрещена  Error
;8									[MEM]=25
;9									      DLINA=SHIRINA
;10			 ([FlSizN=ECX)    нет закрывающей  Error
	MACRO	WriteOne 	parav1
{
      common     match ( parav ) ,parav1
      \{
	common  match  prut  == para,parav
	\\{
	if  prut     in  <al,bl,cl,dl,ah,bh,ch,dh,AX,BX,CX,DX,bp,si,di,EAX,EBX,ECX,EDX,ESI,EDI,EBP,ESP>	;1.
		if  para     in  <al,bl,cl,dl,ah,bh,ch,dh,AX,BX,CX,DX,bp,si,di,EAX,EBX,ECX,EDX,ESI,EDI,EBP,ESP>  ;1.1
			mov	prut,para				;1. REG,REG   <8>
		else
		prob='['
		       repeat 1					;A
			common  irps token,para			;
 				\\\{
 				if  \\\`token=prob			;'[' -первый раз
					if  \\\`token='['
 					  prob=']'			;должна быть закрывающаяся
					else			;имеется закрывающаяся
					   mov	prut,para		;2.REG,[MEM]   <7>
		    break			;выход за repeat 1    		;А
					end if
	 			end if
				\\\}
			if  prob=']'		;если были в пред. if, то не нашли  "]"
			display '<<Error =1 in WriteOne =>'
			display \\`prut
			display ' nessary ] for [.Illegal contructions.>> ',0Dh,0Ah
			end if
			if  prut     in  <ESI,EDI>		;Если не попали на [ и ] , то без скобок
			  mov	prut,para			;3.REG,MEM   <6>
		    break
			else

				if  para eqtype dword		;eqtype число	=> пусто
				mov	prut,para
				display '***************>> ',0Dh,0Ah
		    break
				else
			  display '<<Error =2 in WriteOne=>'
			  display \\`para
			  display ' - illegal contructions.Must be ESI,EDI.>> ',0Dh,0Ah
		    break
				end if
			end if
			break
		   end repeat
		end if
	else				;1-ый  if(1.1)     1.2
	prob='['					;prut(левая часть)   не регистр, а скорей всего адрес
		if  para     in  <al,bl,cl,dl,ah,bh,ch,dh,AX,BX,CX,DX,bp,si,di,EAX,EBX,ECX,EDX,ESI,EDI,EBP,ESP> ;1.2.1
			repeat 1
			  common  irps token,prut			;
 				\\\{
 				if  \\\`token=prob			;1.2.1 '[' -первый раз
					if  \\\`token='['
 					  prob=']'			;должна быть закрывающаяся
					else			;имеется закрывающаяся
					   mov	prut,para		;4.[MEM],REG <5>
					   break			;выход за repeat 1    ;А
					end if
	 			end if
				\\\}
				    if  prob=']'		;если были в пред. if то не нашли  "]"
					display '<Error =3 in WriteOne '
					display \\`para
					display ' nessary ] for [.Illegal contructions.>> ',0Dh,0Ah
				    end if				; <4>
								;Если не попали на [ и ], то без скобок
					mov	[prut],para	;5.MEM,REG искусственно добавим[]
				      break
			end repeat
		else				;MEM,MEM перем. со скобками "[ ]" или без них 1.2.2
			repeat 1
			common  irps token,para			;
 			\\\{
 			if  \\\`token=prob			;1.2.2  '[' -первый раз
				if  \\\`token='['
 				prob=']'			;должна быть закрывающаяся
				else			;имеется закрывающаяся
				     if \\\`token=']'
				     else
					display '<<Error =4 in WriteOne '
					display \\\`para
					display ' nessary ] for [.Illegal contructions.>> ',0Dh,0Ah
				     end if
				end if
			end if
			\\\}
			end repeat
		prob1='['
			if  prob=']'					;если были в пред. if то нашли  "]"?
				repeat 1
				 common  irps tokn,prut		;4
 				  \\\{
 				  if  \\\`tokn=prob1			;'['
					if  \\\`tokn='['
 					prob1=']'			;должна быть закрывающаяся
					else			;имеется закрывающаяся
					      if \\\`tokn=']'
				     	     else
					      display '<<Error =5 in WriteOne'
					      display \\\`para
					      display ' nessary ] for [.Illegal contructions.>> ',0Dh,0Ah
				    	      end if
					end  if
					push	EAX		;<3>
				  mov	EAX,para
				  mov	prut,EAX
				  pop	EAX				;6.[MEM],[MEM]
				  break
	 			else					;7.mem,[MEM]
				  display '<<Error =6 in WriteOne: definition of '
				  display \\\`prut				;err
				  display '  contains illegal contructions.>>',0Dh,0Ah
				  break
	 			end if
				 \\\}
				end repeat
			else					;[ ] скобок не было  в para  ? = MEM
					;display \\`para		;1.2.2
				repeat 1
				 common  irps tokn,prut		;4
 				  \\\{
 					if  \\\`tokn=prob1		;'['
						if  \\\`tokn='['
 					  	prob1=']'		;должна быть закрывающаяся
						else		;имеется закрывающаяся
						      if \\\`tokn=']'
				     		     else
						      display '<<Error =7 in WriteOne '
						      display \\\`para
						      display ' nessary ] for [.Illegal contructions.>> ',0Dh,0Ah
				     		    end if
						end  if
						;display \\\`para		;1.2.2
 						mov	prut,para	;8.[MEM],const <2>
						break
	 				else		;
						prut=para		;9.NCONST,ARG = const <1>
						break
	 				end if
				   \\\}
				end repeat
	 		end if
	         	end if				;1.2  конец if
	end if					;1-ый if
  	\\}
         \}
}
 ;*********************14***




;************************19 ****
;Макрос	для выхода из  плохой ситуации для УСЛОВЛЕННОГО ПЕРЕХОДА и ВЫХОДА СРАЗУ со зачением номера
;Nploxo = 11 любое число
;*********************
;Обращение  1)PLOXO JMPERROR,Nploxo??  2)PLOXO EXITERROR	3)PLOXO ,11
;************************************
; МАКРОС   прежде всего для DLL,так как они должны дать ответ, вызвавшей программе
	macro	PLOXO Uslov,Nploxo
{
if ~ Uslov eq
	if  defined Uslov
		jmp	Uslov		;JMPERROR - общая метка для перехода по ошибке EXBAD1
	else
		display	"No such MET "#`Uslov
		display 13,10
	end if
end if

	 if ~ Nploxo eq
	invoke	ExitProcess, Nploxo		;ОКОНЧАНИЕ,если нет метки куда перейти при ошибке
	 end if
 }
;**********************EXITERROR***********??????********* Выход по ошибке
	MACRO	EXITERROR	JADR
	{
@@:
		mov	EBP,@b		;Фиксируем адрес останова
if ~ JADR eq
	jmp	JADR
end if
		;++++++++++++++++ERROR+++++++++++++++++++++
	}
;*********************19_____
;				Служебные инструменты
;	!	EAX <= [Number]		;[Number] <= [Number], al<=bl
;	! 	Сравнил!Перейти	   al ? bl =>\
;	!			= INCBL	>	<	;<проба>
;	!
;
;***********************
MACRO !  [arg]		;!
{
;	1. для пересылки значений ~ mov, но можно [B],[A]
common  	match	 	P1  =<=== P2 ,arg
\{
  	B!A	\P1,\P2
\}
;	2. Для выполнения любого макроса без запятых (",")
common  	match	 	P1 P2 ,arg
\{
  	\P1 	\P2
\}
}
;***********************************
	MACRO	A_   arg			;*
{
	db	" "#`arg
}
;***************************
	MACRO	@   arg			;*
{
	db	"@"
	common  match  aru  ara,arg
   \{
	A_	\aru
	\common  \irps \tokn,\ara
        	\\{
	Print!afall   \\tokn
	display "0",13,10
	A_	\\tokn

  	\\}
		;A_	\aru
		;A_	\ara
	;macro _   AR \\{	db	0 \\}

\}
	db	"@"
}

;**********************************
;	!	!!	AX<=BX      EXC<=EDX     EDX<=[arg]    [arg] <= [arg1]
MACRO !!  [arg]
{
;	1. для пересылки значений ~ mov, но можно [B],[A]
common  	match	 	P1  =<=== P2 P3  =<=== P4,arg
\{
  	B!A	\P1,\P2
	B!A	\P3,\P4
\}
common  	match	 	P1  =<=== P2 P3  =<=== P4 P5  =<=== P6,arg
\{
  	B!A	\P1,\P2
	B!A	\P3,\P4
	B!A	\P5,\P6
\}
common  	match	 	P1  =<=== P2 P3  =<=== P4 P5  =<=== P6 P7  =<=== P8,arg
\{
  	B!A	\P1,\P2
	B!A	\P3,\P4
	B!A	\P5,\P6
	B!A	\P7,\P8
\}
common  	match	 	P1  =<=== P2 P3  =<=== P4 P5  =<=== P6 P7  =<=== P8 P9  =<=== P10,arg
\{
  	B!A	\P1,\P2
	B!A	\P3,\P4
	B!A	\P5,\P6
	B!A	\P7,\P8
	B!A	\P7,\P8
\}
}
;**********************************
; ПересылкаИзAвВ	[B],[A]
;	!	EAX <= [Number]
	MACRO  B!A	dest,src		;B!A	любая пересылка
{
  if dest src eqtype [0] [0]
    push    src
    pop dest
  else
    mov dest,src
  end if
}

;**********
;*********************15***** макровызова для случая использования специальных знаков: запятой и кавычек "
macro Tokenu [sequence]
{
 common  irps token, sequence
 \{
 if '' eqtype token
 display "'",token,"'",32
	 else
 display \`token,32
	 end if
 \}
display 13,10
}
;***********************15-----
MACRO	Cdisplay	name
     {
	display "NE: Current  "
common	display `name # " is "
	d = '0' + name
    	display d
	display 13,10
}
;*******************

;			Подвал
;Записали!вСтруктуру	Имяструктуры+ESI  [[ИмяПоля+ESI]=Значение] [[ИмяПоля+ESI]++
;Записал!вСтруктуру	Имяструктуры:   [[ИмяПоля]++    [[ИмяПоля]=Значение] [ИмяПоля]++
.. {	MACRO	Записали!вСтруктуру
{	common match pr1++pr2,arg
\{		common match pr21++pr22,pr2
	\\{		common match pr221++pr222,pr22
		\\\{		common	match	pr2221++pr2222,pr222
					\\\\{inc	pr2221
					common	match	pr2221==pr2222,pr2222
					\\\\}
				inc	pr221
		\\\]
		       inc	pr21
	\\}
		inc  pr1			;Инкриментнул!вСтруктуру	Имяструктуры,arg
}

