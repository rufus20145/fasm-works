;Набор макросов для определения различных констан   Описание в файле
;****************************1*****D!efineConst*******
	MACRO	ОпределитьКонстанты	SGroppa,[Spisok]
 {forward 	DefCnst1	SGroppa,Spisok}
;****************************
	MACRO	D!efineConst	SGroppa,[Spisok]
 {forward 	DefCnst1	SGroppa,Spisok}
;****************************
	MACRO	D!efCnst		Groppa,[Spisok]
 { forward
	DefCnst1	Groppa,Spisok }
;************************** одно обращение из списка De!fRcnst1 PR,(Ala=21)
	MACRO	DefCnst1  Groppa,Spis
{  common	match nn ( nnm == nma2 ),Groppa Spis 	; nma='PR'  nma1=f  nma2=0

 	\{\nn\#\nnm=\nma2						;*
	\nnm=\nma2	\}		;на выходе Ala=21		 *
}								;*
;*******************************************D!efineConst**********************
;****************************2*********
	MACRO	ОпределитьЭквивалентности	SGroppa,[Spisok]
 {forward 	DefEnst1	SGroppa,Spisok}
	MACRO	D!efineEqualConst	SGroppa,[Spisok]
 {forward 	DefEnst1	SGroppa,Spisok}
;****************************
	MACRO	D!efEcnst		Groppa,[Spisok]
 {forward
	DfEcnst1	Groppa,Spisok
}
;***************
	MACRO DfEcnst1		Gropp,Spis
{common	match  nn (nnm == nm2),Gropp Spis 		; nma='PR'  nma1=f  nma2=0
 \{ \nn\#\nnm	equ	\nm2
	\nnm	equ	\nm2  \}
}
;***************************3 **********
;*******************Определение данных в виде байта и имя метки без _b в виде константы**********
	MACRO	ОпределитьДанныеБайтные	SGroppa,[Spisok]
 {forward 	DfDcnt1b	SGroppa,Spisok}
;****************************
	MACRO	D!efineDataConsb	SGroppa,[Spisok]
 {forward 	DfDcnt1b	SGroppa,Spisok}
;************************************
MACRO	D!efineDataConstb	SGroppa,[Spisok]
 {forward 	DfDcnt1b	SGroppa,Spisok}
;************************************
	MACRO	D!fDcntb	SGroppa,[Spisok]
 {forward
	DfDcnt1b	SGroppa,Spisok
}
;***************
	MACRO 	DfDcnt1b	SGroppa,Spis
{common
		db	'b'		;тип данных байт
match  nn (nnm == nm2),SGroppa Spis 		; nma='PR'  nma1=f  nma2=0
 \{
label	\nnm	byte			;короткое имя константы	\nnm
\nn\#\nnm\#_b	db	\nm2		;длинное имя константы	\nn\#\nnm\#_b
		db	"$"\#\`nn	;полное имя предыдущей константы в виде текстовой последовательности байт
		db	\`nnm\#"$"
 \}
}
;***************************4**********
;***************************Определение данных в виде слова и имя метки без _w в виде константы**********
	MACRO	ОпределитьДанныеСловные	SGroppa,[Spisok]
 {forward 	DfDcnt1w	SGroppa,Spisok}
;****************************
	MACRO	D!efineDataConsw	SGroppa,[Spisok]
 {forward 	DfDcnt1w	SGroppa,Spisok}
;************************************
	MACRO	D!fDcntw	SGroppa,[Spisok]
 {forward
	DfDcnt1w	SGroppa,Spisok
}
;***************
	MACRO 	DfDcnt1w	SGroppa,Spis
{common
		db	'w'		;тип данных  слово
match  nn (nnm == nm2),SGroppa Spis 		; nma='PR'  nma1=f  nma2=0
 \{
\label	\nnm	\word
;\nnm:
\nn\#\nnm\#_w	dw	\nm2
		db	"$"\#\`nn		;,32\nnm\#\uuu
		db	\`nnm\#"$"
 \}
}
;****************************5*********
;************************Определение данных в виде слова и имя метки без _d (двойное) в виде константы**********
	MACRO	ОпределитьДанныеДвухсловные	SGroppa,[Spisok]
 {forward 	DfDcnt1d	SGroppa,Spisok}
;****************************
;***********************5b
	MACRO	D!efineDataConstd	SGroppa,[Spisok]
 {forward 	DfDcnt1d	SGroppa,Spisok}
;*********************** 5c
	MACRO	D!fDcntd	SGroppa,[Spisok]
 {
forward
	DfDcnt1d	SGroppa,Spisok
}
;***************
	MACRO 	DfDcnt1d	SGroppa,Spis
{common
		db	'd'		;тип данных - двойное слово
	match  nn (nnm == nm2),SGroppa Spis 		; nma='PR'  nma1=f  nma2=0
 \{
\label	\nnm	\dword
\nn\#\nnm\#_d	dd	\nm2
		db	"$"\#\`nn		;,32\nnm\#\uuu  -  полное имя метки
		db	\`nnm\#"$"
 \}
}
;*****************************6********
; Имена эквивалентных макросов
;Префикс (Prefics) именует предметную область к которой относяться константы
;D!efineDataConsq	Prefics,(имя константы1=значение1),(имя константы2=значение2),(имя константы3=значение3)
;D!efineDataConsq	Prefics,(имя константы1=значение1),(имя константы2=значение2),(имя константы3=значение3)
;D!fDcntq	Prefics,(имя константы1=значение1),(имя константы2=значение2),(имя константы3=значение3)
;************************6a************
	MACRO	ОпределитьДанныеЧетырехсловные	SGroppa,[Spisok]
 {forward 	DfDcnt1q	SGroppa,Spisok}
;***********************6b
	MACRO	D!efineDataConstq	SGroppa,[Spisok]
 {forward 	DfDcnt1q	SGroppa,Spisok}
;************************6c************
	MACRO	D!efineDataConsq	SGroppa,[Spisok]
 {forward 	DfDcnt1q	SGroppa,Spisok}
;************************6d***Определение данных в виде слова и имя метки без _q  в виде константы**********
	MACRO	DfDcntq	SGroppa,[Spisok]
 {forward 	DfDcnt1q	SGroppa,Spisok}
;***************
	MACRO 	DfDcnt1q	SGroppa,Spis
{common
	db	'q'		;тип данных - 64 рр слово
match  nn (nnm == nm2),SGroppa Spis 		; nma='PR'  nma1=f  nma2=0
 \{\label	\nnm	\qword
\nn\#\nnm\#_q	dq	\nm2
		db	"$"\#\`nn		;,32\nnm\#\uuu
		db	\`nnm\#"$"
 \}
}
;**********************
;*******************	ОпределитьКонстантыДанные
	MACRO	ОпределитьКонстантыДанные  	SGroppa,[Spisok]
{common
	db	'd'			;тип данных - 64 рр слово
match  nn (nnm == nm2),SGroppa Spis 		; nma='PR'  nma1=f  nma2=0
 \{\label	\nnm	\dword
\nn\#\nnm\#_d	dd	\nm2
		db	"$"\#\`nn		;,32\nnm\#\uuu
		db	\`nnm\#"$"
		db	" = "\#\`nm2	;значение в текстовом виде
 \}
}
;************************
	MACRO	DefineConstantData  	SGroppa,[Spisok]
{common
	db	'd'			;тип данных - 64 рр слово
match  nn (nnm == nm2),SGroppa Spis 		; nma='PR'  nma1=f  nma2=0
 \{\label	\nnm	\dword
\nn\#\nnm\#_d	dd	\nm2
		db	"$"\#\`nn		;,32\nnm\#\uuu
		db	\`nnm\#"$"
		db	" = "\#\`nm2	;значение в текстовом виде
 \}
}