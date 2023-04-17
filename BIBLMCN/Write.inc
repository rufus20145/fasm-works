;1  Записал		1+  'C:\FASM\BIBLMCN\Write.inc'
;	T!YPEM		Запись память память
;	T!YPE		Запись	регистр память
;2	Записали	2* 	'C:\FASM\BIBLMCN\Write.inc'
;3	Считал		3*	'C:\FASM\BIBLMCN\Write.inc'
;4	Считали		4*	'C:\FASM\BIBLMCN\Write.inc'
;5	WriteOne	5* 	'C:\FASM\BIBLMCN\Write.inc'
;6	WriteMany	6*	'C:\FASM\BIBLMCN\Write.inc'
;7	ReadOne		7*	'C:\FASM\BIBLMCN\Write.inc'
;++++++++++++++++++++++++++++++
;********************************* 1 *****************************
;Записал в ОП из регистра	Записал[ADRMEM]:=ECX
;1  Записал		[FlDli]=cl         -- пример только байтовые регистры
; 				[FlDli]:+3	это	[FlDli]:=[FlDli]+3	inc [FlDli]  3 раза
;**************************************************************
	MACRO	Записал	arg
{
repeat 1
	common match dest == =$ src,arg			 ;Пустой оператор
	\{
	break
	\}
  repeat 1
	common match dest =: =+ src,arg			;УВЕЛИЧЕНИЕ НА 1
	\{
		R!inc	\dest,\src
										;\Print!afall   \dest
										;display 13,10
	break									;выход за repeat 1 не надо
	\}
 	repeat 1
			common match dest=:== src,arg
	\{		if  \dest \src eqtype [0] [0]		;[FlSizN]:=[FlDli]
				push	\src				;
				pop		\dest	 			;
			else
				if  \dest eqtype [0]
				 mov \dest,\src				;[FlSizN]:= непосредственные данные
				else
									Print!Rfall   "Ошибка, должно быть[ ]:=x"
									display 13,10
				end if
			end if
	break									;выход за repeat 1 не надо  Записал	\T@1
	\}
;******************
		common  match	 dest == src,arg	;для байтных размерностей1
	\{

IF  \dest \src eqtype [0] [0] 				;Только  присвоение байта[adr1]=[adr2]
					common  match	=[ adr =],dest
					\\{
					\\T!YPEM \dest,\src,\\adr
					\\}
ELSE
  if  \dest  eqtype [0]
	if  \src in <EBP,EAX,EBX,ECX,EDX,ESI,EDI>						;2[FlSizN]=[FlDli] v  [FlSizN]=EAX
	mov dword  \dest,\src						;3	это
									;Print!Rfall   "Ошибка1, должно быть[ ]:=x"
									;display 13,10
	else
		IF 	\src  in <BP,AX,BX,CX,DX,SI,DI>
   				mov word  \dest,\src					;4это байты
		ELSE
				if  \src eqtype  AL
						mov byte \dest,\src				;5	это байты
				else									;[adr] = число ЭТО
				common  match	=[ adr =],\dest
					\\{
					If	\\adr in <edi,esi,EBP,EAX,EBX,ECX,EDX>		;????
						mov   \dest,\src
									Print!Rfall   "Ошибка2, должно быть[ ]:=x  "
									Print!afall	\dest
									display 13,10
					else
					\\T!YPE \dest,\src,\\adr
					end if
					\\}
				end if
		END IF
   end if
  else
						Print!Rfall   "В макро-Записал -Ошибка?, должно быть[ ]:=x  "
						Print!afall	\dest
						display 13,10
  end if
END IF
	\}
;**************************************************************
		end repeat
    end repeat
end repeat
}
;******************************************
	MACRO T!YPEM dest,src,adr			;T!YPEM Определение для [0] и [0]
{	If adr#_r=1
				PUSH	EAX
				mov	AL,src
				mov	dest,AL				;для байтного типа когда [adr1],[adr2]
				POP	EAX
		else
					if adr#_r=2
					PUSH	EAX
					mov	AX,src
					mov	dest,AX			;для словного типа когда [adr1],[adr2]
					POP	EAX
									;Print!Rfall   "Бываем 1 в  macro Записал	arg"
									;display 13,10
					else
						if adr#_r=4
						PUSH	src
						POP		dest
						else
									Print!Rfall   "Ошибка: macro Записал	arg"
									display 13,10
						end if
					end if
		end if
}
;************************************  Определение размерности операнда по расширению _r
;									и запись по адресу памяти с регистра
;adr#_r=1	байта
;adr#_r=2	слово
;adr#_r=4	двойное слово
;++++++++++++++++++++++++++
	MACRO T!YPE dest,src,adr
{	If adr#_r=1
				mov  byte dest,src
		else
					if adr#_r=2
										;Print!Rfall   "Бываем1 в  macro Записал	arg"
										;display 13,10
						mov word dest,src
					else
						if adr#_r=4 & src eqtype EAX
						mov dword  dest,src
						else
										Print!Rfall   "Ошибка: macro T!YPE Записал	arg"
										display 13,10
						end if
					end if
		end if
}

;************************************* 2 ***********************************
;Запись информации как результат множества преобразований
;	2  Записали   arg	Записал & Переписал
;	Записали		([FlDli]:=ECX)	([FlDli]:=CX)
;					([FlDli]=$) v	([FlDli]:=$)		пустой оператор
;	Записали	([FlSizN]:=ECX)
;				([MEM1_w]:=[MEM2_w])
;				([MEM_b]=[MEM_b])
;				([MEM1_d]=[MEM2_d])
;+++++++++++++++++++++++++++++++++++++++++++++
MACRO	Записали arg
{
		common match	=(T@1=)  =(T@2=),arg
		\{	\arg1	equ	\`T@1#\`T@2
		   \MRT	equ	1
			match aww=(ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			Записал	\T@1
			Записал	\T@2
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=),arg
		\{	\arg1	equ	\`T@1#\`T@2\`T@3
		   \MRT	equ	1
			match aww=(ww,\arg1		;если естьхотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
		     	Записал	\T@1
				Записал	\T@2
				Записал	\T@3
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=) =(T@4=),arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4
		   \MRT	equ	1
			match aww=(ww,\arg1		;если естьхотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
		    Записал	\T@1
			Записал	\T@2
			Записал	\T@3
			Записал	\T@4
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=) =(T@4=) =(T@5=),arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4\`T@5
		   \MRT	equ	1
			match aww=(ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
		    Записал	\T@1
			Записал	\T@2
			Записал	\T@3
			Записал	\T@4
			Записал	\T@5
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=) =(T@4=) =(T@5=) =(T@6=),arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4\`T@5\`T@6
		   \MRT	equ	1
			match aww=(ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
			Записал	\T@1
			Записал	\T@2
			Записал	\T@3
			Записал	\T@4
			Записал	\T@5
			Записал	\T@6
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=) =(T@4=) =(T@5=) =(T@6=) =(T@7=),arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4\`T@5\`T@6\`T@7
			\MRT	equ	1
			match aww=(ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
			Записал	\T@1
			Записал	\T@2
			Записал	\T@3
			Записал	\T@4
			Записал	\T@5
			Записал	\T@6
			Записал	\T@7
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=) =(T@4=) =(T@5=) =(T@6=) =(T@7=) =(T@8=),arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4\`T@5\`T@6\`T@7	\`T@8
			\MRT	equ	1
			match aww=(ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
			Записал	\T@1
			Записал	\T@2
			Записал	\T@3
			Записал	\T@4
			Записал	\T@5
			Записал	\T@6
			Записал	\T@7
			Записал	\T@8
		else
				Print!afall   "ERROR now only 8 expresion in macro PUTinSTRUCTURS"
		end if
		\}
}
;************************************* 3 ***********************************
;Считал из ОП				Считали	ECX=:[ADRMEM] 	ECX=:[ADRMEM]
;++++++++++++++++++++++++++++++
	MACRO	Считал	arg
{
repeat 1
	common match dest == =$ src,arg			 ;Пустой оператор
	\{
	break
	\}
 	repeat 1
			common match dest== =: src,arg
	\{
	if  \dest \src eqtype  EAX	[0]			;типа AX=:[FlSizN] v  EAX=:[FlSizN]
   				mov \dest,\src				;
					;Print!Rfall   "Бываем1 в  macro Считал	arg"
					;display 13,10
  	else
		if  \dest \src eqtype AX [0]		;[FlSizN]=:[FlDli]
				mov \dest,\src				;
					Print!Rfall   "Бываем1 в  macro Считал	arg"
					display 13,10
		else
			if  \dest \src eqtype AL [0]
				 mov \dest,\src				;EAX =:непосредственные данные
			else
   			Print!Rfall   "Ошибка, должно быть REG=:"
 			display 13,10
			end if
		end if
  	end if
	break									;выход за repeat 1 не надо  Записал	\T@1
	\}
	common  	match	dest == src,arg		;для байтных размерностей1
	\{
 		if  \dest \src eqtype  EAX [0]		;[FlSizN]=[FlDli] v  [FlSizN]=EAX

   				mov \dest,\src				;это байты
  		else
			if  \dest \src eqtype  AX [0]
			mov \dest,\src				;это слова
			else
				if  \dest \src eqtype  AL [0]
				mov \dest,\src
				else
				Print!Rfall   "Ошибка: macro Считал	arg"
				Print!afall	\src
				display 13,10
				end if
			end if
  		end if
		if  \dest \src eqtype  [0] EAX
		Print!Rfall   "Ошибка: Записать в REG, а не [0]=REG"
		display 13,10
		else
			if  \dest \src eqtype  EAX EAX
			Print!afall   "Это переслал	из регистра в регистр!"
			display 13,10
			else
			end if
		end if
	\}
    end repeat
end repeat
}
;************************************************
;************************************* 4 ***********************************
	MACRO	Считали  arg
{		common match	=(T@1=)  =(T@2=),arg
		\{	\arg1	equ	\`T@1#\`T@2
		   \MRT	equ	1
			match aww=(ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			Считал	\T@1
			Считал	\T@2
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=),arg
		\{	\arg1	equ	\`T@1#\`T@2\`T@3
		   \MRT	equ	1
			match aww=(ww,\arg1		;если естьхотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
		     	Считал	\T@1
				Считал	\T@2
				Считал	\T@3
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=) =(T@4=),arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4
		   \MRT	equ	1
			match aww=(ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
		    Считал	\T@1
			Считал	\T@2
			Считал	\T@3
			Считал	\T@4
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=) =(T@4=) =(T@5=),arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4\`T@5
		   \MRT	equ	1
			match aww=(ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
		    Считал	\T@1
			Считал	\T@2
			Считал	\T@3
			Считал	\T@4
			Считал	\T@5
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=) =(T@4=) =(T@5=) =(T@6=),arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4\`T@5\`T@6
		   \MRT	equ	1
			match aww=(ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
		    Считал	\T@1
			Считал	\T@2
			Считал	\T@3
			Считал	\T@4
			Считал	\T@5
			Считал	\T@6
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=) =(T@4=) =(T@5=) =(T@6=) =(T@7=),arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4\`T@5\`T@6\`T@7
		   \MRT	equ	1
			match aww=(ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
		    Считал	\T@1
			Считал	\T@2
			Считал	\T@3
			Считал	\T@4
			Считал	\T@5
			Считал	\T@6
			Считал	\T@7
		end if
		\}
		common match	=(T@1=)  =(T@2=) =(T@3=) =(T@4=) =(T@5=) =(T@6=) =(T@7=) =(T@8=),arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4\`T@5\`T@6\`T@7	\`T@8
		   \MRT	equ	1
			match aww=(ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
		    Считал	\T@1
			Считал	\T@2
			Считал	\T@3
			Считал	\T@4
			Считал	\T@5
			Считал	\T@6
			Считал	\T@7
			Считал	\T@8
		else
				Print!afall   "ERROR now only 8 expresion in macro PUTinSTRUCTURS"
		end if
		\}
}
;************************************* 5 ***********************************
	MACRO	WriteOne	arg
	{ Записал	arg	}
;************************************* 6 ***********************************
	MACRO	WriteMany	arg
	{ Записали	arg	}
;***********************	7  ****************
	MACRO	WriteOne	ar
{	local parsed
  parsed equ 0
	common match =0 =( arg =),parsed	ar
\{
	Записал	\arg
	parsed equ 1
\}
common match =0  arg ,parsed	ar
\{
	Записал	\arg
	parsed equ 1
\}
}
;********************************* 8
	MACRO	ReadOne	ar
{	local parsed
  parsed equ 0
	common match =0 =( arg =),parsed	ar
\{
	Считал	\arg
	parsed equ 1
\}
	common match =0  arg ,parsed	ar
\{
	Считал	\arg
	parsed equ 1
\}
}
