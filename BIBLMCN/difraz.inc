;difraz.inc
;1.Суммировал
;2.СчиталПоРазмеру
;3.RRAZM	adr,REG
;4.ЗаписалПоРазмеру
;5.WRAZM	adr,REG
;6.Разность			положительная дельта пока между 2 значениями
;7.З_ОПИСЬ	Тип,Топология,МХМХ,МNМХ,MXMN,MNMN
;8.УчитываяОтношенияЗаписать
;9.UC!ABC_W  Ga,Gb,Gc,A1,Z1,A2,Z2,A3,Z3,A4,Z4,A5,Z5,A6,Z6,A7,Z7,A8,Z8,\
;			 A9,Z9,A10,Z10,A11,Z11,A12,Z12,A13,Z13,PMX,PMN,Sboy
;10.ИзОтношенийПолучи	A,B,C,Tpol,MX,MN Это 8 при фикс.Tpol=A1=A2...=A13
;11.
;************************************* 1 ***************************
 ;[L_UPRIM]= [Rh0_i0]+[Ri0_j0]+ [Rb_c]+[Rc_d]+[Rd_e]+[Re_f]+[Rf_g]+[Rg_h]+[Rh_i]+[Ri_j]

macro Суммировал Params&
{  local parsed
  parsed equ 0
		push	EAX
		push	EBX
		xor	EAX,EAX
		xor	EBX,EBX
  match =0 Rez==ar1 =+ ar2 =+ar3 =+ ar4 =+ar5 =+ ar6 =+ar7 =+ ar8 =+ar9=+ar10, parsed Params
  \{
						;Print!afall	"ar1=" \ar1
						;display 13,10
	СчиталПоРазмеру	EBX,\ar1
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar2
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar3
	add	EAX,EBX

	СчиталПоРазмеру	EBX,ar4
	add	EAX,EBX

	СчиталПоРазмеру	EBX,ar5
	add	EAX,EBX

	СчиталПоРазмеру	EBX,ar6
	add	EAX,EBX

	СчиталПоРазмеру	EBX,ar7
	add	EAX,EBX

	СчиталПоРазмеру	EBX,ar8
	add	EAX,EBX

	СчиталПоРазмеру	EBX,ar9
	add	EAX,EBX
	СчиталПоРазмеру	EBX,ar10
	add	EAX,EBX
	ЗаписалПоРазмеру	\Rez,EAX		;mov	Rez,EAX
    parsed equ 1					;Чтобы далее не сверялось
  \}

  match =0 Rez == ar1 =+ ar2 =+ar3 =+ ar4 =+ar5 =+ ar6 =+ ar7 =+ ar8 =+ ar9 , parsed Params
  \{
	СчиталПоРазмеру	EBX,\ar1
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar2
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar3
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar4
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar5
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar6
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar7
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar8
	add	EAX,EBX

	СчиталПоРазмеру	EBX,ar9
	add	EAX,EBX
	ЗаписалПоРазмеру	\Rez,EAX		;mov	Rez,EAX
    parsed equ 1
  \}
   match =0 Rez == ar1 =+ ar2 =+ar3 =+ ar4 =+ar5 =+ ar6 =+ ar7=+ ar8, parsed Params
  \{
	СчиталПоРазмеру	EBX,\ar1
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar2
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar3
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar4
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar5
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar6
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar7
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar8
	add	EAX,EBX
	ЗаписалПоРазмеру	\Rez,EAX		;mov	Rez,EAX
	   parsed equ 1					;Чтобы далее не сверялось
  \}
   match =0 Rez == ar1 =+ ar2 =+ar3 =+ ar4 =+ar5 =+ ar6 =+ ar7, parsed Params
  \{
	СчиталПоРазмеру	EBX,\ar1
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar2
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar3
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar4
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar5
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar6
	add	EAX,EBX
		СчиталПоРазмеру	EBX,\ar7
	add	EAX,EBX
	ЗаписалПоРазмеру	\Rez,EAX		;mov	Rez,EAX
	   parsed equ 1					;Чтобы далее не сверялось
  \}
    match =0 Rez == ar1 =+ ar2 =+ar3 =+ ar4 =+ar5 =+ar6, parsed Params
  \{
	СчиталПоРазмеру	EBX,\ar1
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar2
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar3
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar4
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar5
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar5
	add	EAX,EBX
	ЗаписалПоРазмеру	\Rez,EAX		;mov	Rez,EAX
	   parsed equ 1					;Чтобы далее не сверялось
  \}
	match =0 Rez == ar1 =+ ar2 =+ar3 =+ ar4 =+ ar5, parsed Params
  \{
	СчиталПоРазмеру	EBX,\ar1
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar2
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar3
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar4
	add	EAX,EBX
	СчиталПоРазмеру	EBX,\ar5
	add	EAX,EBX
	ЗаписалПоРазмеру	\Rez,EAX		;mov	Rez,EAX
	   parsed equ 1					;Чтобы далее не сверялось
  \}
  match =0 Rez == ar1 =+ ar2 =+ar3 =+ar4, parsed Params
  \{
	СчиталПоРазмеру	EBX,\ar1
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar2
	add	EAX,EBX

   	СчиталПоРазмеру	EBX,\ar3
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar4
	add	EAX,EBX
	ЗаписалПоРазмеру	\Rez,EAX		;mov	Rez,EAX
	   parsed equ 1					;Чтобы далее не сверялось
  \}
 match =0 Rez == ar1 =+ ar2 =+ ar3, parsed Params
  \{
	СчиталПоРазмеру	EBX,\ar1
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar2
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar3
	add	EAX,EBX
	   parsed equ 1					;Чтобы далее не сверялось
  \}
   match =0 Rez == ar1 =+ ar2, parsed Params
  \{
	СчиталПоРазмеру	EBX,\ar1
	add	EAX,EBX

	СчиталПоРазмеру	EBX,\ar2
	add	EAX,EBX
	ЗаписалПоРазмеру	\Rez,EAX		;mov	Rez,EAX
	   parsed equ 1					;Чтобы далее не сверялось
  \}
  match =0 , parsed \{Print!Rfall 'Суммировал=> Ни один из синтаксисов не соблюдён.' \}

	pop	EBX
	pop	EAX
}
;************************************* 2 ***************************
;Пример СчиталПоРазмеру EBX,ar1
macro СчиталПоРазмеру REG,Par
{local pars
  pars equ 0
	common  match =0	=[ adr =],pars	Par
	\{
	;Print!afall	"adr="
	;Print!afall	adr
	;display 13,10
		RRAZM	\adr,REG
		pars equ 1					;Чтобы далее не сверялось
	\}
	common  match =0  adr,pars	Par
	\{
	Print!afall	"adr="
	Print!afall	adr
	display 13,10
	mov	REG,\adr
		pars equ 1					;Чтобы далее не сверялось
	\}
}
;************************************* 3 ***************************
MACRO RRAZM	adr,REG
{
If adr#_r=1 & REG eq EAX			;Одновременная проверка на размерностьи правой и левой частей
		mov	al,[adr]
		else
	If adr#_r=1 & REG eq EBX
		mov	bl,[adr]
		else
		If adr#_r=1 & REG eq ECX
		mov	cl,[adr]
		else
		If adr#_r=1 & REG eq EDX
		mov	dl,[adr]
		else
				if adr#_r=2 & REG eq EAX
					mov	ax,[adr]
				else
					if adr#_r=2 & REG eq EBX
					mov	bx,[adr]
					else
						if adr#_r=2 & REG eq ECX
						mov	cx,[adr]
						else
							if adr#_r=2 & REG eq EDX
							mov	dx,[adr]
							else
								if adr#_r=4
								mov	REG,[adr]
								else
								Print!Rfall   "Ошибка: macro СчиталПоРазмеру  "
								Print!afall	adr
								display 13,10
								end if
							end if
						end if
				   end if
			  end if
end if
end if
end if
end if
}
;************************************* 4 ***************************
;Пример ЗаписалПоРазмеру ar1,EBX
MACRO ЗаписалПоРазмеру Par,REG
{	local pars
  pars equ 0
	common  match =0	=[ adr =],pars	Par
	\{
	;Print!afall	"adr="
	;Print!afall	adr
	;display 13,10
		WRAZM	\adr,REG
		pars equ 1					;Чтобы далее не сверялось
	\}
		common  match =0  adr,pars	Par
	\{
	Print!afall	"adr="
	Print!afall	adr
	display 13,10
	mov	\adr,REG
		pars equ 1					;Чтобы далее не сверялось
	\}
}

;************************************* 5 ***************************
MACRO WRAZM	adr,REG
{
If adr#_r=1 & REG eq EAX
		mov	[adr],al
		else
	If adr#_r=1 & REG eq EBX
		mov	[adr],bl
		else
		If adr#_r=1 & REG eq ECX
		mov	[adr],cl
		else
		If adr#_r=1 & REG eq EDX
		mov	[adr],dl
		else
				if adr#_r=2 & REG eq EAX
					mov	[adr],ax
				else
					if adr#_r=2 & REG eq EBX
					mov	[adr],bx
					else
						if adr#_r=2 & REG eq ECX
						mov	[adr],cx
						else
							if adr#_r=2 & REG eq EDX
							mov	[adr],dx
							else
								if adr#_r=4
								mov	[adr],REG
								else
								Print!Rfall   "Ошибка: macro СчиталПоРазмеру  "
								Print!afall	adr
								display 13,10
								end if
							end if
						end if
				   end if
			  end if
end if
end if
end if
end if
}
;************************************* 6 ***************************
macro Разность Param&
{  local parsed
  parsed equ 0
		push	EAX
		push	EBX
		xor	EAX,EAX
		xor	EBX,EBX
  match =0 Rez==ar1 =- ar2,parsed	Param
  \{
	СчиталПоРазмеру	EBX,\ar1
	mov	EAX,EBX

	СчиталПоРазмеру	EBX,\ar2
		sub	EAX,EBX
	jge	@F
		neg	EAX							;при отриц.резул. делаем полож.число
@@:
	ЗаписалПоРазмеру	\Rez,EAX		;mov	Rez,EAX
	   parsed equ 1					;Чтобы далее не сверялось
  \}
 ;Здесь можно дополнять список разницы множества параметров
  match =0 ,parsed \{ Print!Rfall "Разность=>Ни один из синтаксисов не соблюдён."\}
	pop	EBX
	pop	EAX
}
;************************************* 7 ***************************
; Макрос записи описателя структуры 16 параметров по ESI - З_ОПИСЬ
;+++++++++	Описатель Структуры и параметров УНИПРИМа на 32 байта ++++++++++++
;Общая метка по описатедю УНИПРИМа					Op_UPRIM
;0Ссылка на след.УНИПРИМа По ссылкам можно будет редактировать	S_UNIPRIM	2
;1Номер фиксируемого УНИПРИМа									N_UNIPRIM	2		 4б
;
;3Вид примитива из 41 возможных									T_ip		1*
;4Ном. тополог.первоосновы 4рр=>ТОПМАК 4рр=>ТОПМИН - из 169 вар	N_topol		1*
;2ДЛИОБЩ количество отсчетов (общее) между крайними точками		L_UPRIM		2
;5Дельта амплитуд от миним.максимума максим.минимума-узк.полоса	DlMnMxMxMn	2 узкая полоса
;6Дельта амплитуд от макс.максимума миним.минимума-широк.полоса	DlMxMxMnMn	2 полоса 8б

;+++++++ИНФОРМАЦИЯ по МАКСИМУМАМ						    12б
;7Длина между 2 первыми максимумами в отсчетах					L_b_f_max	2
;8Длина между 2 следующими максимумами в отсчетах				L_f_j_max	2
;9 максимальное значение максимума								Mx_Mx		2*
;10 минимальное значение максимума								Mn_Mx		2*
;11Дельта амплитуд максимумов от максимального  до минимального	Del_MAX		2 		10б

;+++++++ИНФОРМАЦИЯ по Минимумам
;12Длина между 2 первыми минимумами в отсчетах					L_a_d_min	2 длина
;13Длина между 2 следующими минимумами в отсчетах				L_d_h_min	2
;14  максимальное значение минимума								Mx_Mn		2*
;15  минимальное значение минимума								Mn_Mn		2*
;16Дельта амплитуд минимумов от максимального  до минимального	Del_MIN		2 		10б

;Заполнениеописателя  [MX_MX] = [Sj] [MN_MX] = [Sj0] [MX_MN]=[Sh] [MN_MN] = [Sd]

;ЗАПОП	099h,022h,Sj,Sj0,Sh,Sd
;inc	[Tek_UNI]
;++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;З_ОПИСЬ	[Tek_UNI],[Tek_UNI],[T_ip],[N_topol],[L_UPRIM],[DlMnMxMxMn],[DlMxMxMnMn],\
;[L_b_f_max],[L_f_j_max],[MX_MX],[MN_MX],[Del_MAX],[L_a_d_min],[L_d_h_min],[MX_MN],[MN_MN],[Del_MIN]
;*****************************************************
MACRO З_ОПИСЬ	P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16
{	local	NTek_AdO

			mov		EAX,[Tek_AdO]
			and		EAX,0FFFFFFFFh
		je	NTek_AdO							;Работаем без ф-ла Описателя УНИПРИМОв
			push	EDI
			mov		EDI,[Tek_AdO]				;Установка текущего адреса для Файла Ofile
			inc		[Tek_UNI]					;Номер текущего Униприма
 Записали 	([P0]=[Tek_UNI]) ([P1]=[P0])				;P0=[Tek_UNI] P1=[Tek_UNI]
 Print!Rfall "НУ НУ"
			inc	[P1]							;[S_UNIPRIM]
			mov	AX,[P0]
			stosw								;P0
			mov	AX,[P1]
			stosw								;P1=[Tek_UNI]+1
			mov	al,[P2]							;P2=[T_ip]		ТИП
			stosb
			mov	al,[P3]							;P3=[N_topol]		Топология
			stosb
	Суммировал	P4 =  [Rb_c]+[Rc_d]+[Rd_e]+[Re_f]+[Rf_g]+[Rg_h]+[Rh_i]+[Ri_j]
			mov	AX,P4							;[Rh0_i0]+[Ri0_j0]+
			stosw								;P4=[L_UPRIM]
	Разность	P5=[MN_MX]-[MX_MN]
			mov	AX,P5
			stosw								;P5=[DlMnMxMxMn]
	Разность	P6=[MX_MX]-[MN_MN]
			mov	AX,P6							;P6=[DlMxMxMnMn]
			stosw
;***** MAX
	Суммировал	P7=[Rb_c]+[Rc_d]+[Rd_e]+[Re_f]
			mov	AX,P7							;P7=[L_b_f_max]
			stosw
	Суммировал	P8=[Rf_g]+[Rg_h]+[Rh_i]+[Ri_j]
			mov	AX,P8							;P8=[L_f_j_max]
			stosw
			mov	AX,P9							;P9=[MX_MX]
			stosw
			mov	AX,P10							;P10=[MN_MX]
			stosw
	Разность	P11 =P9-P10						;[MX_MX]-[MN_MX]
			mov	AX,P11							;P11=[Del_MAX]
			stosw
;*******************MIN
	Суммировал	P12=[Rh0_i0]+[Ri0_j0]+[Rb_c]+[Rc_d]
			mov	AX,P12							;P12=[L_a_d_min]
			stosw
	Суммировал	P13=[Rd_e]+[Re_f]+[Rf_g]+[Rg_h]
			mov	AX,P13							;P13=[L_d_h_min]
			stosw

			mov	AX,P14							;P14=[MX_MN]
			stosw

			mov	AX,P15							;P15=[MN_MN]
			stosw
	Разность	P16 =P14-P15					;[MX_MN]-[MN_MN]
			mov	AX,P16							;P16=[Del_MIN]
			stosw
					mov		[Tek_ADR],EDI		;Фиксация текущего адреса для Файла Ofile
					pop		EDI					;ВосстановилиРегистр
NTek_AdO:
}
;************************************* 8 ***************************
;Определяем ТОПОЛОГИЮ и MN_MX	MX_MN
;*****************************************************
;************************************** UC!ABC_W   Запись 1/2 Топологии с учетом 3-х значений
;			УчитываяОтношенияЗаписать\
;				[Sj0] ? [Sf] ? [Sj] ?\
;						$<\>Real=> TpolMX=1\
;						   $</>Real=>TpolMX=2\
;							  $<_>Real=>TpolMX=3\
;								 $</``>Real=>TpolMX=4\
;									$<__/>Real=>TpolMX=5\
;									   $<``\>Real=>TpolMX=6\
;										  $Real<\__> =>TpolMX=7\
;											$</\>Real =>TpolMX=9\
;											   $</\.>Real=>TpolMX=10\
;												  $<./\>Real=>TpolMX=11\
;													 $<\/>Real=>TpolMX=12\
;														$<`\/>Real=>TpolMX=13\
;														   $<\/`>Real=>TpolMX=14\
;															  $МаксиМакс=>MX_MX\
;																$МиниМакс=MX_MX\
;																$bad=>ExiPloxo
;************************************** пара(Ai,Zi) Ai - адрес записи, Zi - записываемое значение
;
;************************************
MACRO УчитываяОтношенияЗаписать	arg
{  common match A =? B =? C =? F_1 ==> P1==Z1  F_2==> P2==Z2  F_3==> P3==Z3  F_4==> P4==Z4 F_5==>P5==Z5 F_6==>P6==Z6\
   F_7==>P7==Z7  F_8==>P8==Z8  F_9==>P9==Z9  F_10==>P10==Z10 F_11==>P11==Z11  F_12==> P12==Z12  F_13==> P13==Z13\
   F_14=>M_x F_15=>M_n	F16==>Sboy,arg
		\{
			;\display 0Dh,0ah
			;\Print!Rfall   \Z13
			;\display 0Dh,0ah
			;Print!afall   \P13
			;\display 0Dh,0ah
			;\Print!afall   F_13
			;\display 0Dh,0ah
			;\Print!afall   F_9
 \UC!ABC_W  \A,\B,\C,\P1,\Z1,\P2,\Z2,\P3,\Z3,\P4,\Z4,\P5,\Z5,\P6,\Z6,\P7,\Z7,\P8,\Z8,\P9,\Z9,\P10,\Z10,\P11,\Z11,\P12,\Z12,\P13,\Z13,M_x,M_n,\Sboy
			;display	"10",0Dh,0ah
			;Print!afall   \P13
		\}
}
;************************************* 9 ***************************
;**************************************MX_MN MX_MN  	MX_MN MN_MN
macro UC!ABC_W  Ga,Gb,Gc,A1,Z1,A2,Z2,A3,Z3,A4,Z4,A5,Z5,A6,Z6,A7,Z7,A8,Z8,A9,Z9,A10,Z10,A11,Z11,A12,Z12,A13,Z13,PMX,PMN,Sboy
{	local  HGK,CSZ,JmJ1,JgJ1,MEXI,MEXI1,JmJ2,JeJ2,JgJ2,JmJ3,JeJ3,JgJ3,\
			SJMP,NBl,NBl1,P1,P2,P3,P4,P5,P6,P7,GEXI
			;Print!Rfall   Z13
			;display 0Dh,0ah
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
		mov al,00b
	je	MEXI						;JeJ 11 оба операнда A=B ==> нет отличающихся разрядов
		and	BX,-1					; BX=  A&M выделения маской отличающиеся разряды B
	jne	@F							;13 B маскированное пересекаетсZ с B  маскированное
		mov al,01b
	jmp	MEXI						;JmJ 		;14  in A(bl)=0 A<B [5*]
@@:		ror	EBX,16					;EBX= A&M B&M
		and	BX,-1					;15 B после выделения маской отличающиеся разряды B
		mov al,2					;34  A>B	JgJ:
	je	MEXI						;JgJ							;16 in   B(bh)=0	A>B
;**************************			;17 остались операнды только с единичками в разных разр¤дах
			mov	ECX,080008000h		;рр 32&16
@@:		test	EBX,ECX					;EBX= A&M B&M
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	ECX,1
	jmp	@B
@@:		and	EBX,ECX
		xor	EBX,ECX					;обр.0 у кого ст.ед
		and	BX,-1					;32 EBX= (A&M cm.рр) B&M&(0FFFF)
	jne	MEXI						;JgJ33	Уже есть mov al,2  B=1 A=0  =>A>B
;***********   Общий блок 				B=1 A=0  => A<B
		mov al,1					;34  A<B
									;JmJ 		;14  in A(bl)=0 A<B
MEXI:	POP	ECX
;**************************
;*** 3
					movzx	EBX,CX	;BX ? CX\
					POP	ECX			;$Признак_AL<-2_or_признак_0_1_2_в=:al
;*** 4
;*********  Основная часть    **************
		shl	ECX,16  				;16 чтобы  ECX= И(ECXст.рр)  B(BL) были в одной строке
		or	EBX,ECX					;   EBX= B  A
		mov	ECX,EBX					;9  	    AX = AL    AL
		ror	ECX,16					;10 ECX= A  B
		xor	ECX,EBX					;маска   M  M
		and	EBX,ECX					;EBX=   B&M  A&M
									;or al,0000b можно не делать
	je	MEXI1						;JeJ1  11 оба операнда A=B ==> нет отличающихся разрядов
		and	BX,-1					; BX=  A&M выделения маской отличающиеся разряды B
	jne	@F							;13 B маскированное пересекаетсZ с B  маскированное
JmJ1:
		or al,100b
	jmp	MEXI1						;JmJ1   14  in A(bl)=0 A<B [5*]
@@:		ror	EBX,16					;EBX= A&M B&M
		and	BX,-1					;15 B после выделения маской отличающиеся разряды B
	je	JgJ1						;16 in   B(bh)=0	A>B
;**************************			;17 остались операнды только с единичками в разных разр¤дах
			mov	ECX,080008000h		;рр 32&16
@@:		test	EBX,ECX					;EBX= A&M B&M
	jne	@F							; ZF=1 if 0   на выx  посмотреть флаг PF   XNOR разряды TEMP[0-7]
		shr	ECX,1
	jmp	@B
@@:		and	EBX,ECX
		xor	EBX,ECX					;обр.0 у кого ст.ед
		and	BX,-1					;32 EBX= (A&M cm.рр) B&M&(0FFFF)
	jne	JgJ1						;33	B=1 A=0  =>A>B
;***********   Общий блок 				B=1 A=0  => A<B
	JMP	JmJ1						;  60
JgJ1:								;POP	EBX
		or al,1000b						;34  A>B
;++++++++++++++
MEXI1:
;**************************
;*** 5
		and	EAX,0FFh
		cmp AL,1010b			;Число max  1010b=Ah   переключателей

	JG	Sboy
		shl	EAX,3				;EBX,3  через 8 байт команды
		add	EAX,SJMP
	jmp	EAX
label	SJMP	dword		;72+ 4*13  =72+52 =124
	POP		ECX			;восстановили С
	POP		EBX			;A 0
	POP		EAX			;B
	jmp	near	P3		;243C	0  jmp	near	P3 занимает 5 байт
	POP		ECX			;восстановили С
	POP		EBX			;A 1
	POP		EAX			;B
	jmp	near	P5		;24B8		1  __/
	POP		ECX			;восстановили С
	POP		EBX			;A 2
	POP		EAX			;B
	jmp	near	P6		;24F6		2
	POP		ECX			;восстановили С
	POP		EBX			;A 3
	POP		EAX			;B
	jmp	near	Sboy		;Sb		;26D1		3
	POP		ECX			;восстановили С
	POP		EBX			;A
	POP		EAX			;B 4
	jmp	near	P4		;						247A		4
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
	jmp	near	Sboy	;Sb		;2685
	POP		ECX			;восстановили С
	POP		EBX			;A 8
	POP		EAX			;B
	jmp	near	P7		;;23C6
	POP		ECX			;восстановили С
	POP		EBX			;A 9
	POP		EAX			;B
	jmp	near	CSZ		;2454
	POP		ECX			;восстановили С
	POP		EBX			;A 10
	POP		EAX			;B
	jmp	near	P1		;2321
;*** 6				;72+ 4*13  =72+52 =124     Для перхода в среднем 72+4 v  +60
CSZ:		;СучетомОтношений_A?B_Перейти\
			;		AX ? CX\
			;			=P11 >P12  < P13
;*******************
	УпряталиРегистры	EAX,EBX
		mov BX,CX						;2-й операнд
;**************************
		and	ah,0FFh
	jne	@F
		and	bh,0FFh
	jne	JmJ2								;A=0 B#0 => A<B закончили
	jmp	NBl								;Ah=0  Bh=0 На следующий блок из 0,1,2,3 на 2
@@:		and	bh,0FFh
	je	JgJ2								;A#0 B=0 A>B
		shl	EAX,8						;временно
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
	je	JeJ2							;оба операнда A=B ==>
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
	jmp	-4							;Такого не должно быть только сбой компьюьера
@@:		and	AL,0FFh					;A(ah)  B(al)  A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ2						;B=1 A=0  =>A<B
;***********Общий ВЫХОД*************;B=0 A=1  =>A>B
JgJ2:								;`\/
	ВосстановилиРегистры	EAX,EBX
		Записали	(PMX=Sj0),(PMN=Sf)		;Максимальная и минимальная амплитуды
				if  A12  eqtype AL
		mov	A12,Z12
		else
		mov	[A12],Z12
		end if								;mov	[A12],Z12
	jmp	GEXI
JeJ2:								;\/
	ВосстановилиРегистры	EAX,EBX
		Записали	(PMX=Sj0),(PMN=Sf)		;Sj0,Sf,Sj Максимальная и минимальная амплитуды
		if  A11  eqtype AL
		mov	A11,Z11
		else
		mov	[A11],Z11
		end if								;mov	[A11],Z11
	jmp	GEXI
JmJ2:								; \/`
	ВосстановилиРегистры	EAX,EBX
		Записали	(PMX=Sj),(PMN=Sf)		;Максимальная и минимальная амплитуды
		if  A13  eqtype AL
		mov	A13,Z13
		else
		mov	[A13],Z13
		end if								;mov	[A13],Z13
	jmp	GEXI
;*** 7
HGK:		;СучетомОтношений_A?B_Перейти\
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
	jne	JmJ3								;A=0 B#0 => A<B закончили
	jmp	NBl1								;Ah=0  Bh=0 На следующий блок из 0,1,2,3 на 2
@@:		and	bh,0FFh
	je	JgJ3								;A#0 B=0 A>B
		shl	EAX,8						;временно
		mov	al,ah
		xor	al,bh						;проверка на равенство старших байт
		shr	EAX,8
	je	@F 								; Если равны то будем сравнивать мл.байты
		ror	AX,8						;по старшим разрядам 9-16 они перейдут в мл.рр
		ror	BX,8						;вернулм младшие на место
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
		mov	BH,AL  					;чтобы A(bh)  B(bl) были в одной строке
		mov	AH,AL
		xor	AH,BL					;в AH маска
	je	JeJ3							;оба операнда A=B ==>
		and	BL,AH					;после выделения маски A
	jne	@F							;A маскированное пересекается с B  маскированное
	jmp	JgJ3 						;in B=0 A>B [5*] они не зависимы и надо продолжать
@@:		and	BH,AH					;	A(bh)
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
	jmp	-4							;Такого не должно быть только сбой компьюьера
@@:		and	AL,0FFh					;A(ah)  B(al)  A=0 B#0  => A<B  else A>B   BL=?
	jne	JmJ3						;B=1 A=0  =>A<B
;***********Общий ВЫХОД*************;B=0 A=1  =>A>B
JgJ3:										;/\.
	ВосстановилиРегистры	EAX,EBX
		Записали	(PMX=Sf),(PMN=Sj)		;Максимальная и минимальная амплитуды
			if  A9  eqtype AL
		mov	A9,Z9
		else
		mov	[A9],Z9
		end if			;mov	[A9],Z9
	jmp	GEXI
JeJ3:
	ВосстановилиРегистры	EAX,EBX			;/\
		Записали	(PMX=Sf),(PMN=Sj0)		;(PMN=Sj)Максимальная и минимальная амплитуды
		if  A8  eqtype AL
		mov	A8,Z8
		else
		mov	[A8],Z8
		end if									;mov	[A8],Z8
	jmp	GEXI
JmJ3:										;./\
	ВосстановилиРегистры	EAX,EBX
		Записали	(PMX=Sf),(PMN=Sj0)		;Максимальная и минимальная амплитуды
											;mov	[A10],Z10
		if  A10  eqtype AL
		mov	A10,Z10
		else
		mov	[A10],Z10
		end if
	jmp	GEXI
P1:												;\
		Записали	(PMX=Sj0),(PMN=Sj)		;Максимальная и минимальная амплитуды в ТОПОЛОГИИ
		if  A1  eqtype AL
		mov	A1,Z1
		else
		mov	[A1],Z1
		end if
	jmp	GEXI
P2:												;/
		Записали	(PMX=[Sj]),(PMN=[Sj0])		;Максимальная и минимальная амплитуды
				if  A2  eqtype AL
		mov	A2,Z2
		else
		mov	[A2],Z2
		end if
	jmp	GEXI
P3:												;__
		Записали	(PMX=Sj),(PMN=Sf)		;Максимальная и минимальная амплитуды
		if  A3  eqtype AL
		mov	A3,Z3
		else
		mov	[A3],Z3
		end if
	jmp	GEXI
P4:												;/``
		Записали	(PMX=Sf),(PMN=Sj0)		;Максимальная и минимальная амплитуды
		if  A4  eqtype AL
		mov	A4,Z4
		else
		mov	[A4],Z4
		end if
	jmp	GEXI
P5:												;__/
		Записали	(PMX=Sj),(PMN=Sf)		;Максимальная и минимальная амплитуды
		if  A5  eqtype AL
		mov	A5,Z5
		else
		mov	[A5],Z5
		end if
	jmp	GEXI
P6:												;``\
		Записали	(PMX=Sf),(PMN=Sj)		;Максимальная и минимальная амплитуды
		if  A6  eqtype AL
		mov	A6,Z6
		else
		mov	[A6],Z6
		end if
	jmp	GEXI
P7:												;\__
		Записали	(PMX=Sj0),(PMN=Sf)		;Максимальная и минимальная амплитуды
		if  A7  eqtype AL
		mov	A7,Z7
		else
		mov	[A7],Z7
		end if
GEXI:						;Общий выход
}

;******************************************** 10  ******************************
;		ИзОтношенийПолучи	[Sj0],[Sf],[Sj]\
;				al,[MX_MX],[MN_MX]			;[TpolMX]
;*****************************************
;		ИзОтношенийПолучи	[Si0],[Sd],[Si]\
;				bl,[MX_MN],[MN_MN]			;[TpolMN]
;+++++++++++++++++++++++++++++++++++++++++
MACRO ИзОтношенийПолучи	A,B,C,Tpol,MX,MN
	{
			УчитываяОтношенияЗаписать\
				[Sj0] ? [Sf] ? [Sj] ?\
						$<\>Real=> Tpol=1\
						   $</>Real=>Tpol=2\
							  $<_>Real=>Tpol=3\
								 $</``>Real=>Tpol=4\
									$<__/>Real=>Tpol=5\
									   $<``\>Real=>Tpol=6\
										  $Real<\__> =>Tpol=7\
											$</\>Real =>Tpol=9\
											   $</\.>Real=>Tpol=10\
												  $<./\>Real=>Tpol=11\
													 $<\/>Real=>Tpol=12\
														$<`\/>Real=>Tpol=13\
														   $<\/`>Real=>Tpol=14\
															  $МаксиМакс=MX\
																$МиниМакс=MN\
																$bad=>ExiPloxo
}
;*******************************
;	ИзДвухОдин	REZ=P1 ^ -4 v P2		"^" - сдвиг  "-" влево "+" вправо "v"  операция or
;Пример			ИзДвухПолучиОдин	[TpolMX],4,[TpolMN],[N_topol]
MACRO ИзДвухПолучиОдин	P1,Sd,P2,REZ
{
				mov		al,P1
				shl		al,Sd
				or		al,P2
				mov		REZ,al
				pop		EAX
}
;*******************************
;	ПолучениеТопологии\
;	inmax=Sb inmax=Sf inmax=Sj\
;	inmin=Sa inmin=Sd inmin=Si\
;	outMX_MX=MX_MX outMN_MX=MN_MX\
; 	outMX_MN=MX_MN outMN_MN=MN_MN\
;	outНомерТопологии=N_topol
;*************************** Получение топологии
			macro ПолучениеТопологии	arg
{	push	EAX
	push	EBX
common match P0$==Sj0 P01$==Sf P02$==Sj P03$==Si0 P04$==Sd P05$==Si\
			 M0$==MX_MX M01$==MN_MX 	M02$==MX_MN 	M03$==MN_MN\
			 T0==N_topol,arg
	\{		Print!Rfall "НО НО"
		ИзОтношенийПолучи	[\Sj0],[\Sf],[\Sj],\
				al,[\MX_MX],[\MN_MX]
;*****************************************
		ИзОтношенийПолучи	[\Si0],[\Sd],[\Si],\
				bl,[\MX_MN],[\MN_MN]
		ИзДвухПолучиОдин	al,4,bl,[\N_topol]
;*****************************************
	\}
	pop		EBX
	pop		EAX
}