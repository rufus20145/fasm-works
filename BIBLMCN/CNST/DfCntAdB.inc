;Набор макросов для определения различных Эквивалентности через equ
;1	DfCntAdB					определение 1 Эквивалентности
;2	DfCntAdBM					определение множество Эквивалентности
;3 	ОпределитьКонстантыBПод_Именем	~2
;4	DfCntAdBGr					Определить групповую константу
;5	DfCntAdBGrM				Определить множество групповых Эквивалентности
;6	ОпределитьГрупповыеКонстантыBПод_Именем ~5
;7	ЗадалБайтЦелое
;8 ЗадалиБайтныеЦелые
;	D!ef_D_B_I					8*	'C:\FASM\BIBLMCN\CNST\DfCntAdB.inc'
;	Dfn_one_D_B_I				9*	'C:\FASM\BIBLMCN\CNST\DfCntAdB.inc'
;******************1*********************
;		DfCntAdB	Т1=2		T1 equ 2
MACRO	DfCntAdB  ARG
{  common	match nm1 == nm2,ARG 		;
 	\{ \nm1 db \nm2 \}					;на выходе Tl=2
	common	match  == nm2,ARG 		;
 	\{  db \nm2 \}
}
;**************************************
;******************2********************
	MACRO	DfCntAdBM		[Spisok]	;Т1=2,Т2=4,Т3=7
 { forward
	DfCnt	Spisok }
;**************************************
;******************3*********************
	MACRO	ОпределитьКонстантыBПод_Именем	[Spisok]
 {forward 	DfCntAdM	Spisok}
;***************************************
;******************4********************
;Пример:		DfCntAdBGr	Groppa,Т1=2	Определить групповую константу
;++++++++++++++++++++++++++++++++++++++
MACRO	DfCntAdBGr  Groppa,Spis
{   common	match nn ( nnm == nma2 ),Groppa Spis 		; nma='PR'  nma1=f  nma2=0
 	\{\nn#_\#\nnm db \nma2								;Groppa_T1=1
	\}
}
;***************************************
;*******************5********************
;Назначение: Определить множество групповых констант
;Пример:		DfCntAdBGrM	Groppa,Т1=2,Т2=4,Т3=7
;+++++++++++++++++++++++++++++++++++++++
	MACRO	DfCntAdBGrM	SGroppa,[Spisok]
 {forward 	DfCntAdBGr	SGroppa,Spisok}
;***************************************
;********************6*******************
;ОпределитьГрупповыеКонстантыBПод_Именем	SGroppa,[Spisok]
;
;****************************
	MACRO	ОпределитьГрупповыеКонстантыBПод_Именем	SGroppa,[Spisok]
 {forward 	DfCntAdBGr	SGroppa,Spisok}
;**************************** одно обращение из списка De!fRcnst1 PR,(Ala=21)
;*********************************************************************
;Задание числовых констант с метками
;****************************7*****************************************
MACRO	ЗадалБайтЦелое	Groppa,Spisok
{
common
if ~Groppa eq
label	Groppa	byte
else
end if
 	Dfn_one_D_B_I	Spisok
}
;****************************8*****************************************
;*******		РУССКИЙ  ВАРИАНТ  ЗадатьДанныеБайтЦелое
	MACRO	ЗадалиБайтныеЦелые	Groppa,[Spisok]
{
common
if ~Groppa eq
label	Groppa	byte
else
end if
forward
 	Dfn_one_D_B_I	Spisok
}
;+++++++
;*********	Английский вариант
MACRO	D!ef_D_B_I		Groppa,[Spisok]
{
label	Groppa	byte
 forward
	Dfn_one_D_B_I	Spisok
}
;++++++++
;*****************  Определение одиночной константы в скобках
;****************************
MACRO 	Dfn_one_D_B_I	Spis	;Определение одиночной константы
{
common
	match  nnm == ,Spis 		; nma='PR'  nma1=f  nma2=0
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
;label	\nnm	byte			;короткое имя константы	\nnm
\nnm	db	\nm2		;длинное имя константы	\\nnm\#__L_W_SI
\nnm#_r=1						;Размерность данных байт
\nnm#_t=1						;Тип данных Целое без знака
	else
\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
}

