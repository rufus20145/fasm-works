;Набор макросов для определения различных Эквивалентности через equ
;1	DfEqCnt					определение 1 Эквивалентности
;2	DfEqCntM					определение множество Эквивалентности
;3 	ОпределитьЭквивалентности		~2
;4	DfEqCntGr					Определить групповую константу
;5	DfEqCntGrM				Определить множество групповых Эквивалентности
;6	ОпределитьГрупповыеЭквивалентности ~5
;******************1*********************
;		DfEqCnt	Т1=2		T1 equ 2
MACRO	DfEqCnt  ARG
{  common	match nm1 == nm2,ARG 	;
 	\{ \nm1 equ \nm2 \}					;на выходе Tl=2
}
;**************************************
;******************2********************
	MACRO	DfEqCntM		[Spisok]	;Т1=2,Т2=4,Т3=7
 { forward
	DfCnt	Spisok }
;**************************************
;******************3*********************
	MACRO	ОпределитьКонстанты	[Spisok]
 {forward 	DfEqCntM	Spisok}
;***************************************
;******************4********************
;Пример:		DfCntGr	Groppa,Т1=2	Определить групповую константу
;++++++++++++++++++++++++++++++++++++++
MACRO	DfCntGr  Groppa,Spis
{   common	match nn ( nnm == nma2 ),Groppa Spis 	; nma='PR'  nma1=f  nma2=0
 	\{\nn#_\#\nnm equ \nma2								;Groppa_T1=1
	\}
}
;***************************************
;*******************5********************
;Назначение: Определить множество групповых констант
;Пример:		DfEqCntGrM	Groppa,Т1=2,Т2=4,Т3=7
;+++++++++++++++++++++++++++++++++++++++
	MACRO	DfCntGrM	SGroppa,[Spisok]
 {forward 	DfEqCntGr	SGroppa,Spisok}
;***************************************
;********************6*******************
;ОпределитьГрупповыеКонстанты	SGroppa,[Spisok]
;
;****************************
	MACRO	ОпределитьГрупповыеКонстанты	SGroppa,[Spisok]
 {forward 	DfEqCntGr	SGroppa,Spisok}
;**************************** одно обращение из списка De!fRcnst1 PR,(Ala=21)

