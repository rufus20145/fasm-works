;Набор макросов для определения различных КонстантыПод_Именем через dw
;1	DfCntAdW					определение 1 КонстантыПод_Именем
;2	DfCntAdWM					определение множество КонстантыПод_Именем
;3 	ОпределитьКонстантыWПод_Именем		~2
;4	DfCntAdWGr					Определить групповую константу
;5	DfCntAdWGrM				Определить множество групповых КонстантыПод_Именем
;6	ОпределитьГрупповыеКонстантыWПод_Именем ~5


; Оконстантил Water=2
; ОконстантилиГруппу		Жидкости(Water=2  Vino=1  Milk=5)
; Обэквивалентил ANGU<=>25  ЗначениеB Dlina:=5 ЗначениеW ТТ:=15
; ОбэквивалентилиГруппу	Primitiv( A<=>1 E<=>2 O<=>1
; ОзначилB Dlina:=5 ТТ:=15 Dlina:=5 ОзначилиW  KKm:=12 Dlina:=5
; ОзначилBГруппу	NICK(Dlina:=5 ТТ:=15 KKm:=12)
;******************1*********************
;ОзначилиW S5:=8090  :=3090 				;:=3090 :=8090
; ОзначилW Dlina:=5 ТТ:=15 Dlina:=5 ОзначилиW  KKm:=12 Dlina:=5
;****************************************
;		DfCntAdW	Т1=2		T1 equ 2
;++++++++++++++++++++++++++++++++++++++++
;******************************
; ОзначилMW Dlina:=5
MACRO ОзначилW ARG
{
common	match nm1 =:== nm2,ARG 					;
 	\{ \nm1 dw \nm2 \}
}
;******************************
macro ОзначилW ARG
{
common	match nm1 =:== nm1,ARG 					;
 	\{ dw \nm1 \}
}
;******************************
;************* ОзначилW *******


macro DfCntAdW  ARG
{  common	match nm1 == nm2,ARG 					;
 	\{ \nm1 dw \nm2 \}								;на выходе Tl=2
					common	match  == nm2,ARG 		;
						\{  dw \nm2 \}
}
;**************************************
;******************2********************
MACRO DfCntAdWM		[Spisok]	;Т1=2,Т2=4,Т3=7
 { forward
	DfCntAdW	Spisok }
;**************************************
;******************3*********************
MACRO ОпределитьКонстантыWПод_Именем	[Spisok]
 {forward 	DfCntAdWM	Spisok}
;***************************************
;******************4********************
;Пример:		DfCntAdWGr	Groppa,Т1=2	Определить групповую константу
;++++++++++++++++++++++++++++++++++++++
macro DfCntAdWGr  Groppa,Spis
{   common	match nn ( nnm == nma2 ),Groppa Spis 		; nma='PR'  nma1=f  nma2=0
 	\{\nn#_\#\nnm dw \nma2								;Groppa_T1=1
	\}
}
;***************************************
;*******************5********************
;Назначение: Определить множество групповых констант
;Пример:		DfCntAdWGrM	Groppa,Т1=2,Т2=4,Т3=7
;+++++++++++++++++++++++++++++++++++++++
MACRO DfCntAdWGrM	SGroppa,[Spisok]
 {forward 	DfCntAdWGr	SGroppa,Spisok}
;***************************************
;********************6*******************
;ОпределитьГрупповыеКонстантыWПод_Именем	SGroppa,[Spisok]
;
;****************************
MACRO ОпределитьГрупповыеКонстантыWПод_Именем	SGroppa,[Spisok]
 {forward 	DfCntAdWGr	SGroppa,Spisok}
;**************************** одно обращение из списка De!fRcnst1 PR,(Ala=21)
;*********************************************************************
;
;*********************************************************************
macro ЗадалСловоЦелое	Groppa,Spisok
{
common
if ~Groppa eq
label	Groppa	word
else
end if
 	Dfn_one_D_W_I	Spisok
}
;*******		РУССКИЙ  ВАРИАНТ  ЗадатьДанныеБайтЦелое
MACRO ЗадалиСловныеЦелые	Groppa,[Spisok]
{
common
if ~Groppa eq
label	Groppa	word
else
end if
forward
 	Dfn_one_D_W_I	Spisok
}
;+++++++
;*********	Английский вариант
macro D!ef_D_W_I		Groppa,[Spisok]
{
label	Groppa	word
 forward
	Dfn_one_D_B_I	Spisok
}
;++++++++
;*****************  Определение одиночной константы в скобках
;****************************
MACRO 	Dfn_one_D_W_I	Spis	;Определение одиночной константы
{
common 	match  nnm,Spis 		; nma='PR'  nma1=f  nma2=0
 \{
 \display	\`nnm
	\Print!afall   " in Dfn_one_D_W_I?  PUSTO?  no data"
\}
common 	match  nnm == ,Spis 		; nma='PR'  nma1=f  nma2=0
 \{
	\display	\`nnm
	\Print!afall   " =?  PUSTO?  no data"
\}
common
	match  == dann,Spis 		; nma='PR'  nma1=f  nma2=0
 \{
	\Print!afall   " ?="
	\display	\`dann
	\Print!afall   " PUSTO?  no name"
\}
common
	match  nnm == nm2,Spis 		; nma='PR'  nma1=f  nma2=0
 \{
	if	~\nm2	eq
;label	\nnm	word			;короткое имя константы	\nnm
\nnm dw \nm2
\nnm\#_r=2						;Размерность данных 2 байта
\nnm\#_t=1						;Тип данных Целое без знака
	else
\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
}
