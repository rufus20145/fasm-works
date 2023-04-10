;Набор макросов для определения различных КонстантыПод_Именем через dd
;1	DfCntAdD					определение 1 КонстантыПод_Именем
;2	DfCntAdDM					определение множество КонстантыПод_Именем
;3 	ОпределитьКонстантыDПод_Именем		~2
;4	DfCntAdDGr					Определить групповую константу
;5	DfCntAdDGrM				Определить множество групповых КонстантыПод_Именем				
;6	ОпределитьГрупповыеКонстантыDПод_Именем ~5
;7	ЗадалиДвуСловныеЦелые
;8	D!ef_D_D_I				Английский вариант ЗадалиДвуСловныеЦелые
;9 	Dfn_one_D_D_I			Опрделить одну переменную Размерность=4 и Тип=1
;******************1*********************
;		DfCntAdD	Т1=2		T1 equ 2 
MACRO	DfCntAdD  ARG
{  common	match nm1 == nm2,ARG 		;
 	\{ \nm1 dd \nm2 \}					;на выходе Tl=2
	common	match  == nm2,ARG 		; 
 	\{  dd \nm2 \}	
}
;**************************************
;******************2********************
	MACRO	DfCntAdDM		[Spisok]	;Т1=2,Т2=4,Т3=7
 { forward
	DfCntD	Spisok }
;**************************************
;******************3*********************
	MACRO	ОпределитьКонстантыDПод_Именем	[Spisok]
 {forward 	DfCntAdDM	Spisok}
;*************************************** 
;******************4********************
;Пример:		DfCntAdDGr	Groppa,Т1=2	Определить групповую константу
;++++++++++++++++++++++++++++++++++++++
MACRO	DfCntAdDGr  Groppa,Spis
{   common	match nn ( nnm == nma2 ),Groppa Spis 		; nma='PR'  nma1=f  nma2=0
 	\{\nn#_\#\nnm dd \nma2								;Groppa_T1=1
	\}
}
;***************************************
;*******************5********************
;Назначение: Определить множество групповых констант
;Пример:		DfEqCntDGrM	Groppa,Т1=2,Т2=4,Т3=7
;+++++++++++++++++++++++++++++++++++++++
	MACRO	DfCntAdDGrM	SGroppa,[Spisok]
 {forward 	DfCntAdDGr	SGroppa,Spisok}
;***************************************
;********************6*******************
;ОпределитьГрупповыеКонстантыDПод_Именем	SGroppa,[Spisok]
;
;****************************
	MACRO	ОпределитьГрупповыеКонстантыDПод_Именем	SGroppa,[Spisok]
 {forward 	DfCntAdDGr	SGroppa,Spisok}
;**************************** одно обращение из списка De!fRcnst1 PR,(Ala=21)
;*******		РУССКИЙ  ВАРИАНТ  ЗадатьДанныеБайтЦелое
	MACRO	ЗадалиДвуСловныеЦелые	Groppa,[Spisok]
{
common
if ~Groppa eq
label	Groppa	word
else
end if
forward
 	Dfn_one_D_D_I	Spisok
}
;+++++++
;*********	Английский вариант
MACRO	D!ef_D_D_I		Groppa,[Spisok]
{
label	Groppa	word
 forward
	Dfn_one_D_D_I	Spisok
}
;++++++++
;*****************  Определение одиночной константы в скобках
;****************************
MACRO 	Dfn_one_D_D_I	Spis	;Определение одиночной константы
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
\nnm	dd \nm2
\nnm\#_r=4						;Размерность данных 4 байта
\nnm\#_t=1						;Тип данных Целое без знака
	else
\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
}


