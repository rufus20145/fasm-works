
;***************************************************************************
;	1+	L!oad_and_WriteRG_If_0_Go			'C:\FASM\BIBLMCN\L!oadStowd.inc'
;	2*	Bыгрузить_и_ЗаписатьРег_Если_0_Перейти 'C:\FASM\BIBLMCN\L!oadStowd.inc'    ;Использует 1
;	3*	Загрузка_по_размерности	Ad			'C:\FASM\BIBLMCN\L!oadStowd.inc'
;	4*	ЗагрузилиДанныеИзЯчеек				'C:\FASM\BIBLMCN\L!oadStowd.inc'		;Использует 3

;	5-	R!eadRG_and_Stowd_0					'C:\FASM\BIBLMCN\LoaStoad\L!oaStoad.inc'
;	6*	ПрочитатьРег_и_Загрузить_0			'C:\FASM\BIBLMCN\LoaStoad\L!oaStoad.inc'
;	7*	ЗагрузитьБайтыИзЯчеек				'C:\FASM\BIBLMCN\LoaStoad\L!oaStoad.inc'
;	8*	S!tosByte_From	ARG					'C:\FASM\BIBLMCN\LoaStoad\L!oaStoad.inc'
;	9*	ЗагрузитьСловаИзЯчеек				'C:\FASM\BIBLMCN\LoaStoad\L!oaStoad.inc'
;****************************************   5   ******
MACRO R!eadRG_and_Stowd_0	[Rg1]
{			push	EAX
forward
    if  Rg1   in <al,bl,cl,dl,ah,bh,ch.dh>
			if  Rg1   in <al>
			Print!afall   "ERROR AL not use in macro L!oad_and_WriteRG_If_0_Go"
			else
			end if
		mov al,Rg1
		stosb							; число в AL
common
		xor	al,al			; Нулевое значение массив кончился
		stosb
			pop	EAX
    else
		if  Rg1	 in <AX,BX,CX,DX,SI,DI,BP>
				if  Rg1   in <ax>
				Print!afall   "ERROR AX not use in macro L!oad_and_WriteRG_If_0_Go"
				else
				end if
				mov AX,Rg1
		stosw							; число в AL
common
		xor	ax,ax			; Нулевое значение массив кончился
		stosw
			pop	EAX
		else
		if  Rg1	 in <EAX,EBX,ECX,EDX,EEDI,EBP>
			if  Rg1   in <EAX>
			Print!afall   "ERROR EAX not use in macro L!oad_and_WriteRG_If_0_Go"
			else
			end if
		mov EAX,Rg1
		stosd							; число в AL
common
		xor	al,al			; Нулевое значение массив кончился
		stosd
			pop	EAX
		else
		Print!afall   "ERROR Write not RG in macro L!oad_and_WriteRG_If_0_Go"
		end if
	 end if
    end if
}
;*********************************************  6   ************
MACRO ПрочитатьРег_и_Загрузить_0
{common match	==>Ad  ==>As,arg
		\{
		   \MRT	equ	1
			match aww==ww,\As			;если  MRT= 1, то это наша структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			\R!eadRG_and_Stowd_0	\Ad,\As
		end if
		\}
		common match	==>Ad  ==>As  ==> Bs,arg
		\{ \MRT	equ	1
			match aww==ww,\Bs			;если  MRT= 1, то это наша структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			\R!eadRG_and_Stowd_0	\Ad,\As,\Bs
		end if
		\}
		common match	==>Ad ==>As ==> Bs ==> Ct,arg			;3 аргумента
		\{
		   \MRT	equ	1
			match aww==ww,\Ct			;если есть хотя бы 1 =, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
		\R!eadRG_and_Stowd_0		\Ad,\As,\Bs,\Ct
		end if
		\}
		common match  ==>Ad  ==>As  ==> Bs ==> Cs ==> Ks,arg	;4 аргумента
		\{	\MRT	equ	1
			match aww==ww,\Ks			;если естьхотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
		\R!eadRG_and_Stowd_0	\Ad,\As,\Bs,\Cs,\Ks
		end if
		\}
		common match	==>Ad  ==> As  ==> Bs ==>Cs ==>Ks ==>Hs,arg	; 5 аргументов чтения
		\{\arg1	equ	\`As#\`Bs\`Cs\`Ks\`Hs
		   \MRT	equ	1
			match aww==ww,\Hs			;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
		 \R!eadRG_and_Stowd_0	\Ad,\As,\Bs,\Cs,\Ks,\Hs
		else
		Print!afall   "ERROR only 5 argument Write in macro L!oad_and_WriteRG_If_0_Go"		 		end if
		\}
}
;*******************************   конец 6



;ЗагрузитьБайтыИзЯчеек
;S!tosByte_From
;*************************************************  7  ****
MACRO ЗагрузитьБайтыИзЯчеек		arg
{	push	EAX
	common match	=^=-Ad  =^=-As,arg
	\{					\arg1	equ	\`Ad#\`As
		   \MRT	equ	1
			match aww=^=-ww,\As		;если есть хотя бы 1 =, то это не та структура
			\\{	\\MRT	equ	0 \\}

		if	\MRT	eq	1
			mov	al,\Ad
			stosb
			mov	al,\As
			stosb
		else
		end if
\}
;****************************  ТРИ ОПЕРАНДА
		common match	=^=-Ad =^=-As  =^=-Bs,arg
		\{					;\arg1	equ	\`As#\`Bs
							;\Print!afall   \Bs
		   \MRT	equ	1
			match aww=^=-ww,\Bs		;если есть хотя бы 1 =, то это не та структура
			\\{	\\MRT	equ	0 \\}
			Print!afall   "MRT2="				;
			\Print!afall   \MRT
			display 10
		if	\MRT	eq	1
			mov	al,\Ad
			stosb
			mov	al,\As
			stosb
			mov	al,\Bs
			stosb
		end if
		\}
;****************************  Четыре ОПЕРАНДА
		common match	=^=-Ad =^=-As  =^=-Bs=^=-Cs, arg
		\{				;\arg1	equ	\`As#\`Bs\`Cs
			\Print!afall   \arg
			;display 10
		   \MRT	equ	1
			match aww=^=-ww,\Cs		;если есть хотя бы 1 =, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			mov	al,\Ad
			stosb
			mov	al,\As
			stosb
			mov	al,\Bs
			stosb
			mov	al,\Cs
			stosb
		end if
		\}
;****************************  ПЯТЬ ОПЕРАНДОВ
		common match  =^=-Ad  =^=-As  =^=- Bs =^=-Cs =^=-Ks,arg	;4 аргумента
		\{					;\arg1	equ	\`As#\`Bs\`Cs\`Ds
							; \Print!afall   \Ks
		\MRT	equ	1
			match aww=^=-ww,\Ks		;если естьхотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
			mov	al,\Ad
			stosb
			mov	al,\As
			stosb
			mov	al,\Bs
			stosb
			mov	al,\Cs
			stosb
			mov	al,\Ks
			stosb
		end if
		\}
;****************************  ШЕСТЬ ОПЕРАНДОВ
		common match	=^=-Ad =^=-As=^=- Bs =^=-Cs =^=-Ks=^=-Hs,arg	; 6 аргументов чтения
		\{\arg1	equ	\`As#\`Bs\`Cs\`Ks\`Hs
		   \MRT	equ	1
			match aww=^=-ww,\Hs		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			mov	al,\Ad
			stosb
			mov	al,\As
			stosb
			mov	al,\Bs
			stosb
			mov	al,\Cs
			stosb
			mov	al,\Ks
			stosb
			mov	al,\Hs
			stosb
		else
		end if
		\}
;****************************  СЕМЬ ОПЕРАНДОВ
		common match	=^=-Ad =^=-As =^=- Bs =^=-Cs=^=-Ks=^=-Hs =^=-Ls,arg	; 7 аргум чтения
		\{\arg1	equ	\`As#\`Bs\`Cs\`Ks\`Hs\`Ls
		   \MRT	equ	1
			match aww=^=-ww,\Ls		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			mov	al,\Ad
			stosb
			mov	al,\As
			stosb
			mov	al,\Bs
			stosb
			mov	al,\Cs
			stosb
			mov	al,\Ks
			stosb
			mov	al,\Hs
			stosb
			mov	al,\Ls
			stosb
		else
	 		end if
		\}
;****************************  восемЬ ОПЕРАНДОВ
	common match	=^=-Ad =^=-As =^=- Bs=^=-Cs =^=-Ks=^=-Hs =^=-Ls =^=-Ms,arg	; 8 аргум чтения
		\{\arg1	equ	\`As#\`Bs\`Cs\`Ks\`Hs\`Ls\`Ms
		   \MRT	equ	1
			match aww=^=-ww,\Ms		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			mov	al,\Ad
			stosb
			mov	al,\As
			stosb
			mov	al,\Bs
			stosb
			mov	al,\Cs
			stosb
			mov	al,\Ks
			stosb
			mov	al,\Hs
			stosb
			mov	al,\Ls
			stosb
			mov	al,\Ms
			stosb
		else
		end if
		\}
;****************************  девять ОПЕРАНДОВ
common match	=^=-Ad =^=-As =^=- Bs =^=-Cs =^=-Ks =^=-Hs  =^=-Ls =^=-Ms =^=-Ns,arg	; 9 аргум чтения
		\{\arg1	equ	\`As#\`Bs\`Cs\`Ks\`Hs\`Ls\`Ms\`Ns
		   \MRT	equ	1
			match aww=^=-ww,\Ns		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			mov	al,\Ad
			stosb
			mov	al,\As
			stosb
			mov	al,\Bs
			stosb
			mov	al,\Cs
			stosb
			mov	al,\Ks
			stosb
			mov	al,\Hs
			stosb
			mov	al,\Ls
			stosb
			mov	al,\Ms
			stosb
			mov	al,\Ns
			stosb
		else
		Print!afall   "ERROR now only 9 argument Write in macro S!tosByte_From"		 			end if
		\}
	POP	EAX
}
;************************************** конец		7
;**************************************             8
MACRO S!tosByte_From	ARG
{
ЗагрузитьБайтыИзЯчеек ARG
}
;************************************************    8
;************************************************    9
MACRO ЗагрузитьСловаИзЯчеек		arg
{	push	EAX
	common match	=^=-Ad  =^=-As,arg
	\{					\arg1	equ	\`Ad#\`As
							\Print!afall   \arg1
							display 10
		   \MRT	equ	1
			match aww=^=-ww,\As		;если есть хотя бы 1 =, то это не та структура
			\\{	\\MRT	equ	0 \\}

		if	\MRT	eq	1
			mov	AX,\Ad
			stosw
			mov	AX,\As
			stosw
		else
		end if
\}
;****************************  ТРИ ОПЕРАНДА
		common match	=^=-Ad =^=-As  =^=-Bs,arg
		\{					;\arg1	equ	\`As#\`Bs
							;\Print!afall   \Bs
		   \MRT	equ	1
			match aww=^=-ww,\Bs		;если есть хотя бы 1 =, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			mov	AX,\Ad
			stosw
			mov	AX,\As
			stosw
			mov	AX,\Bs
			stosw
		end if
		\}
;****************************  Четыре ОПЕРАНДА
		common match	=^=-Ad =^=-As  =^=-Bs=^=-Cs, arg
		\{				;\arg1	equ	\`As#\`Bs\`Cs
						;\Print!afall   \arg
						;display 10
		   \MRT	equ	1
			match aww=^=-ww,\Cs		;если есть хотя бы 1 =, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			mov	AX,\Ad
			stosw
			mov	AX,\As
			stosw
			mov	AX,\Bs
			stosw
			mov	AX,\Cs
			stosw
		end if
		\}
;****************************  ПЯТЬ ОПЕРАНДОВ
		common match  =^=-Ad  =^=-As  =^=- Bs =^=-Cs =^=-Ks,arg	;4 аргумента
		\{					;\arg1	equ	\`As#\`Bs\`Cs\`Ds
							; \Print!afall   \Ks
		\MRT	equ	1
			match aww=^=-ww,\Ks		;если естьхотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
			mov	AX,\Ad
			stosw
			mov	AX,\As
			stosw
			mov	AX,\Bs
			stosw
			mov	AX,\Cs
			stosw
			mov	AX,\Ks
			stosw
		end if
		\}
;****************************  ШЕСТЬ ОПЕРАНДОВ
		common match	=^=-Ad =^=-As=^=- Bs =^=-Cs =^=-Ks=^=-Hs,arg	; 6 аргументов чтения
		\{\arg1	equ	\`As#\`Bs\`Cs\`Ks\`Hs
		   \MRT	equ	1
			match aww=^=-ww,\Hs		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			mov	AX,\Ad
			stosw
			mov	AX,\As
			stosw
			mov	AX,\Bs
			stosw
			mov	AX,\Cs
			stosw
			mov	AX,\Ks
			stosw
			mov	AX,\Hs
			stosw
		else
		end if
		\}
;****************************  СЕМЬ ОПЕРАНДОВ
		common match	=^=-Ad =^=-As =^=- Bs =^=-Cs=^=-Ks=^=-Hs =^=-Ls,arg	; 7 аргум чтения
		\{\arg1	equ	\`As#\`Bs\`Cs\`Ks\`Hs\`Ls
		   \MRT	equ	1
			match aww=^=-ww,\Ls		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			mov	AX,\Ad
			stosw
			mov	AX,\As
			stosw
			mov	AX,\Bs
			stosw
			mov	AX,\Cs
			stosw
			mov	AX,\Ks
			stosw
			mov	AX,\Hs
			stosw
			mov	AX,\Ls
			stosw
		else
	 		end if
		\}
;****************************  восемЬ ОПЕРАНДОВ
	common match	=^=-Ad =^=-As =^=- Bs=^=-Cs =^=-Ks=^=-Hs =^=-Ls =^=-Ms,arg	; 8 аргум чтения
		\{\arg1	equ	\`As#\`Bs\`Cs\`Ks\`Hs\`Ls\`Ms
		   \MRT	equ	1
			match aww=^=-ww,\Ms		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			mov	AX,\Ad
			stosw
			mov	AX,\As
			stosw
			mov	AX,\Bs
			stosw
			mov	AX,\Cs
			stosw
			mov	AX,\Ks
			stosw
			mov	AX,\Hs
			stosw
			mov	AX,\Ls
			stosw
			mov	AX,\Ms
			stosw
		else
		end if
		\}
;****************************  девять ОПЕРАНДОВ
common match	=^=-Ad =^=-As =^=- Bs =^=-Cs =^=-Ks =^=-Hs  =^=-Ls =^=-Ms =^=-Ns,arg	; 9 аргум чтения
		\{\arg1	equ	\`As#\`Bs\`Cs\`Ks\`Hs\`Ls\`Ms\`Ns
		   \MRT	equ	1
			match aww=^=-ww,\Ns		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			mov	AX,\Ad
			stosw
			mov	AX,\As
			stosw
			mov	AX,\Bs
			stosw
			mov	AX,\Cs
			stosw
			mov	AX,\Ks
			stosw
			mov	AX,\Hs
			stosw
			mov	AX,\Ls
			stosw
			mov	AX,\Ms
			stosw
			mov	AX,\Ns
			stosw
		else
		Print!afall   "ERROR now only 9 argument Write in macro S!tosByte_From"		 			end if
		\}
	POP	EAX
}
;****************************************************** 9 ****