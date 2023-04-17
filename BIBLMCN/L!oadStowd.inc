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

;**********************  Первая выборка  ЗагрузитьбайтЕсли0УходИначеПрисвоить  =>P0\
;				 =AL  =BL  =CL
;			L!oad_and_WriteRG_If_0_Go	P1,[Rg1]
;;	+	Bыгрузить_и_ЗаписатьРег_Если_0_Перейти	 =>P1 = al   = bl  = CL = dl
;	+	Bыгрузить_и_ЗаписатьРег_Если_0_Перейти	 =>P1 = al   = bl  = CL
;	+	Bыгрузить_и_ЗаписатьРег_Если_0_Перейти	 =>P1 = al   = bl
;	+	Bыгрузить_и_ЗаписатьРег_Если_0_Перейти	 =>P1 = dl   = bl  = CL = bh
;	+	Bыгрузить_и_ЗаписатьРег_Если_0_Перейти	 =>P1 = dl   = bl  = CL = bh =dh
;	Bыгрузить_и_ЗаписатьРег_Если_0_Перейти	 =>P1\
;	 => dl   => bl  => CL => bh =>dh => ch
;	ПрочитатьРег_и_Загрузить_Если_0_Перейти	 =>P1\
;	 <= dl   <= bl  <= CL <= bh <=dh <= ch
;**********************************************************************************
;***************************************  1  *******************************
;Исправить для  AL и EAX
		MACRO	L!oad_and_WriteRG_If_0_Go	P1,[Rg1]
{
forward
    if  Rg1   in <al,bl,cl,dl,ah,bh,ch,dh>
						;Print!afall   "ERROR AL not use in macro L!oad_and_WriteRG_If_0_Go"
			if  ~Rg1   in <al>
			push	EAX
			else
			end if
		lodsb										; число в AL
		and	EAX,0FFh								;Выделяем только байт
		mov	Rg1,AL								;СТАРШИЕ РАЗРЯДЫ ОБНУЛЯЕМ
			if  ~Rg1   in <al>
			pop		EAX
			else
			end if
						IF ~P1	eq
						and	Rg1,0FFh
						je	P1								; Нулевое значение массив кончился
						else
						Print!Rfall   "Нет адреса перехода"
						end if
    else
		if  Rg1	 in <AX,BX,CX,DX,SI,DI,BP>
							if  ~Rg1   in <AX>
							push	EAX
							else
							end if
					lodsw
					and	EAX,0FFFFh					;Выделяем только слово
					mov	Rg1,AX
							if  ~Rg1   in <AX>
							pop		EAX
							else
							end if
						IF ~P1	eq
						and	Rg1,0FFFFh
						je	P1							; Нулевое значение массив кончился
						else
						Print!Rfall   "Нет адреса перехода"
						end if
		else
				if  Rg1	 in <EAX,EBX,ECX,EDX,EDI,ESI,EBP>
								if  ~Rg1   in <EAX>
								PUSH	EAX
								else
								end if
						lodsd							; число в EAX
						mov	Rg1,EAX
								if  ~Rg1   in <EAX>
								POP	EAX
								else
								end if
						IF ~P1	eq
						and	Rg1,0FFFFFFFFh
					je	P1							; Нулевое значение массив кончился
						else
						end if
				else
		Print!afall   "ERROR Write not RG in macro L!oad_and_WriteRG_If_0_Go"
				end if
		end if
	end if
common
}
;*********************************************  2  ******
		MACRO	Bыгрузить_и_ЗаписатьРег_Если_0_Перейти  arg
{		common match	==>Ad  ==>As,arg
		\{
		   \MRT	equ	1
			match aww==ww,\As			;если  MRT= 1, то это наша структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			\L!oad_and_WriteRG_If_0_Go	\Ad,\As
		end if
		\}
		common match	==>Ad  ==>As  ==> Bs,arg
		\{ \MRT	equ	1
			match aww==ww,\Bs			;если  MRT= 1, то это наша структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			\L!oad_and_WriteRG_If_0_Go	\Ad,\As,\Bs
		end if
		\}
		common match	==>Ad ==>As ==> Bs ==> Ct,arg			;3 аргумента
		\{
		   \MRT	equ	1
			match aww==ww,\Ct			;если есть хотя бы 1 =, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
		\L!oad_and_WriteRG_If_0_Go		\Ad,\As,\Bs,\Ct
		end if
		\}
		common match  ==>Ad  ==>As  ==> Bs ==> Cs ==> Ks,arg	;4 аргумента
		\{	\MRT	equ	1
			match aww==ww,\Ks			;если естьхотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
		\L!oad_and_WriteRG_If_0_Go	\Ad,\As,\Bs,\Cs,\Ks
		end if
		\}
		common match	==>Ad  ==> As  ==> Bs ==>Cs ==>Ks ==>Hs,arg	; 5 аргументов чтения
		\{\arg1	equ	\`As#\`Bs\`Cs\`Ks\`Hs
		   \MRT	equ	1
			match aww==ww,\Hs			;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
		 \L!oad_and_WriteRG_If_0_Go	\Ad,\As,\Bs,\Cs,\Ks,\Hs
		else
		Print!afall   "ERROR only 5 argument Write in macro L!oad_and_WriteRG_If_0_Go"		 		end if
		\}
}
;*******************************         3
	MACRO	Загрузка_по_размерности	Ad
{			if Ad#_r =1
			mov	al,[Ad]
				stosb
			else
				if	Ad#_r =2
				mov	AX,[Ad]
				stosw
				else
					if	Ad#_r =4
						mov	EAX,[Ad]
						stosd
					else
						if Ad	eqtype  al
							mov	al,Ad
							stosb
						else
							if Ad	eqtype  AX
								mov	AX,Ad
								stosw
							else
								if Ad	eqtype  EAX
									mov	EAX,Ad
									stosd
								else
									Print!Rfall   "Ошибка: Загрузка_по_размерности Ad="
									Print!afall	Ad
									display 13,10
								end if
							end if
						end if
					end if
				end if
			end if
}
;-------------------------------------------------    3
; *********************  Для загрузки всех размерностей данных
;*********************************                    4
	MACRO ЗагрузилиДанныеИзЯчеек	arg
{
		push	EAX
	common match	=^=-Ad  =^=-As,arg
	\{		   \MRT	equ	1
			match aww=^=-ww,\As			;если есть хотя бы 1 =, то это не та структура
			\\{	\\MRT	equ	0 \\}
			if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
			end if
\}
;****************************  ТРИ ОПЕРАНДА
		common match	=^=-Ad =^=-As  =^=-Bs,arg
		\{								;\arg1	equ	\`As#\`Bs
										;\Print!afall   \Bs
		   \MRT	equ	1
			match aww=^=-ww,\Bs			;если есть хотя бы 1 =, то это не та структура
			\\{	\\MRT	equ	0 \\}
										;\Print!afall   "MRT2="				;
										;\Print!afall   \MRT
										;display 10
		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
		end if
		\}
;****************************  Четыре ОПЕРАНДА
		common match	=^=-Ad =^=-As  =^=-Bs=^=-Cs, arg
		\{								;\arg1	equ	\`As#\`Bs\`Cs
										;\Print!afall   \arg
										;display 10
		   \MRT	equ	1
			match aww=^=-ww,\Cs			;если есть хотя бы 1 =, то это не та структура
			\\{	\\MRT	equ	0 \\}

		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
		end if
		\}
;****************************  ПЯТЬ ОПЕРАНДОВ
		common match  =^=-Ad  =^=-As  =^=- Bs =^=-Cs =^=-Ks,arg	;4 аргумента
		\{
		\MRT	equ	1
			match aww=^=-ww,\Ks		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
									;\Print!afall   "MRT4="
									;\Print!afall   \MRT
									;display 10
		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
		end if
		\}
;****************************  ШЕСТЬ ОПЕРАНДОВ
		common match	=^=-Ad =^=-As=^=- Bs =^=-Cs =^=-Ks =^=-Hs,arg	; 6 аргументов чтения
		\{		   \MRT	equ	1
			match aww=^=-ww,\Hs			;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
										;\Print!afall   "MRT6="
										;\Print!afall   \MRT
										;display 10
		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
	Загрузка_по_размерности	\Hs
		else
		end if
		\}
;****************************  СЕМЬ ОПЕРАНДОВ
		common match	=^=-Ad =^=-As =^=- Bs =^=-Cs =^=-Ks =^=-Hs =^=-L_s,arg	; 7 аргум чтения
		\{	   \MRT	equ	1
										;\Print!afall   \L_s
			match aww =^ =- ww,\L_s		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0
										;\\Print!afall   \\ww
			\\}
										;\Print!afall   "MRT7="
										;\Print!afall   \MRT
										;display 10
		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
	Загрузка_по_размерности	\Hs
	Загрузка_по_размерности	\L_s
		else
	 	end if
		\}
;****************************  восемЬ ОПЕРАНДОВ
	common match	=^=-Ad =^=-As =^=- Bs=^=-Cs =^=-Ks =^=-Hs =^=-Ls =^=-Ms,arg	; 8 аргум чтения
		\{		   \MRT	equ	1
			match aww=^=-ww,\Ms			;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
										;\Print!afall   "MRT9="
										;\Print!afall   \MRT
										;display 10
		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
	Загрузка_по_размерности	\Hs
	Загрузка_по_размерности	\Ls
	Загрузка_по_размерности	\Ms
		else
		end if
		\}
;****************************  девять ОПЕРАНДОВ
common match	=^=-Ad =^=-As =^=-Bs =^=-Cs =^=-Ks =^=-Hs  =^=-Ls =^=-Ms =^=-Ns,arg	; 9 аргум чтения
		\{		   \MRT	equ	1
			match aww=^=-ww,\Ns			;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
										;\Print!afall   "MRT9="
										;\Print!afall   \MRT
										;display 10
		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
	Загрузка_по_размерности	\Hs
	Загрузка_по_размерности	\Ls
	Загрузка_по_размерности	\Ms
	Загрузка_по_размерности	\Ns
		else
		end if
		\}
;****************************  деcять ОПЕРАНДОВ
common match	=^=-Ad =^=-As =^=-Bs =^=-Cs =^=-Ks =^=-Hs  =^=-Ls =^=-Ms =^=-Ns\
	=^=-Os,arg							; 9 аргум чтения
		\{		   \MRT	equ	1
			match aww=^=-ww,\Os			;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
										;\Print!afall   "MRT10="
										;\Print!afall   \MRT
										;display 10
		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
	Загрузка_по_размерности	\Hs
	Загрузка_по_размерности	\Ls
	Загрузка_по_размерности	\Ms
	Загрузка_по_размерности	\Ns
	Загрузка_по_размерности	\Os
		else
		end if
;****************************  11 ОПЕРАНДОВ
	common match	=^=-Ad =^=-As =^=- Bs =^=-Cs =^=-Ks =^=-Hs  =^=-Ls =^=-Ms =^=-Ns\
	=^=-Os	=^=-Ps,arg									; 9 аргум чтения
		\{		   \MRT	equ	1
			match aww=^=-ww,\Ps			;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
										;\Print!afall   "MRT11="
										;\Print!afall   \MRT
										;display 10
		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
	Загрузка_по_размерности	\Hs
	Загрузка_по_размерности	\Ls
	Загрузка_по_размерности	\Ms
	Загрузка_по_размерности	\Ns
	Загрузка_по_размерности	\Os
	Загрузка_по_размерности	\Ps
		else
		end if
		\}
;****************************  12 ОПЕРАНДОВ
	common match	=^=-Ad =^=-As =^=-Bs =^=-Cs =^=-Ks =^=-Hs  =^=-Ls =^=-Ms =^=-Ns\
	=^=-Os	=^=-Ps =^=-Qs,arg									; 9 аргум чтения
		\{		   \MRT	equ	1
			match aww=^=-ww,\Qs			;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
										;\Print!afall   "Qs12="
										;\Print!afall   arg
										;display 10
		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
	Загрузка_по_размерности	\Hs
	Загрузка_по_размерности	\Ls
	Загрузка_по_размерности	\Ms
	Загрузка_по_размерности	\Ns
	Загрузка_по_размерности	\Os
	Загрузка_по_размерности	\Ps
	Загрузка_по_размерности	\Qs
		else
		end if
\}
;****************************  13 ОПЕРАНДОВ
	common match	=^=-Ad =^=-As =^=-Bs =^=-Cs =^=-Ks =^=-Hs  =^=-Ls =^=-Ms =^=-Ns\
	=^=-Os	=^=-Ps	=^=-Qs =^=-Rs,arg									; 9 аргум чтения
		\{		   \MRT	equ	1
			match aww=^=-ww,\Rs			;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
										;\Print!afall   "Rs13="
										;\Print!afall   arg
										;display 10
		if	\MRT	eq	1

	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
	Загрузка_по_размерности	\Hs
	Загрузка_по_размерности	\Ls
	Загрузка_по_размерности	\Ms
	Загрузка_по_размерности	\Ns
	Загрузка_по_размерности	\Os
	Загрузка_по_размерности	\Ps
	Загрузка_по_размерности	\Qs
	Загрузка_по_размерности	\Rs
		else
		end if
\}
;****************************  14 ОПЕРАНДОВ
	common match	=^=-Ad =^=-As =^=- Bs =^=-Cs =^=-Ks =^=-Hs  =^=-Ls =^=-Ms =^=-Ns\
	=^=-Os	=^=-Ps =^=-Qs	=^=-Rs	=^=-Ss,arg									; 9 аргум чтения
		\{		   \MRT	equ	1
										;\Print!afall   "Rs14="
										;\Print!afall   arg
										;display 10
			match aww=^=-ww,\Ss			;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
	Загрузка_по_размерности	\Hs
	Загрузка_по_размерности	\Ls
	Загрузка_по_размерности	\Ms
	Загрузка_по_размерности	\Ns
	Загрузка_по_размерности	\Os
	Загрузка_по_размерности	\Ps
	Загрузка_по_размерности	\Qs
	Загрузка_по_размерности	\Rs
	Загрузка_по_размерности	\Ss
		else
		end if
\}
;****************************  15 ОПЕРАНДОВ
	common match	=^=-Ad =^=-As =^=-Bs =^=-Cs =^=-Ks =^=-Hs  =^=-Ls =^=-Ms =^=-Ns\
	=^=-Os	=^=-Ps =^=-Qs	=^=-Rs	=^=-Ss	=^=-Ts,arg									; 9 аргум чтения
		\{		   \MRT	equ	1
			match aww=^=-ww,\Ts		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
	Загрузка_по_размерности	\Hs
	Загрузка_по_размерности	\Ls
	Загрузка_по_размерности	\Ms
	Загрузка_по_размерности	\Ns
	Загрузка_по_размерности	\Os
	Загрузка_по_размерности	\Ps
	Загрузка_по_размерности	\Qs
	Загрузка_по_размерности	\Rs
	Загрузка_по_размерности	\Ss
	Загрузка_по_размерности	\Ts
		else
		end if
	\}
;****************************  16 ОПЕРАНДОВ
	common match	=^=-Ad =^=-As =^=-Bs =^=-Cs =^=-Ks =^=-Hs  =^=-Ls =^=-Ms =^=-Ns\
	=^=-Os	=^=-Ps =^=-Qs	=^=-Rs	=^=-Ss	=^=-Ts	=^=-Vs,arg									; 9 аргум чтения
		\{		   \MRT	equ	1
			match aww=^=-ww,\Vs		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
			if	~\Vs	eq
	Загрузка_по_размерности	\Ad
	Загрузка_по_размерности	\As
	Загрузка_по_размерности	\Bs
	Загрузка_по_размерности	\Cs
	Загрузка_по_размерности	\Ks
	Загрузка_по_размерности	\Hs
	Загрузка_по_размерности	\Ls
	Загрузка_по_размерности	\Ms
	Загрузка_по_размерности	\Ns
	Загрузка_по_размерности	\Os
	Загрузка_по_размерности	\Ps
	Загрузка_по_размерности	\Qs
	Загрузка_по_размерности	\Rs
	Загрузка_по_размерности	\Ss
	Загрузка_по_размерности	\Ts
	Загрузка_по_размерности	\Vs
			else
			end if
		else
		Print!afall   "ERROR now only 16 argument Write in macro S!tosData_From"
		end if
		\}
		POP	EAX
}
;*********************************                  конец 6
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>