;	D_fb				1+
;	D_fw				2*
;	D_fd				3*
;	Dfn_one_D_B_I		4*
;	Dfn_one_D_W_I		5*
;	Dfn_one_D_D_I		6*
;	ЗадалиБайтныеЦелые	7*
;	ЗадалиСловныеЦелые	8*
;	ЗадалиДвухСловныеЦелые 9*
;	D!efM_D_B_I			10*
;	D!efM_D_W_I			11*
;	D!efM_D_D_I			12*
;******************************* 1
	MACRO	D_fb	Ar,Br,tp,up,np		;t-тип u-верхний предел  n-нижний предел
{
Ar	db	Br							;;имя = константа
Ar#_r=1								;Размерность данных байт
	If ~tp eq
Ar#_t=tp							;Тип данных Целое без знака=3
	else
Ar#_t=3
	end if
		If ~up eq
Ar#_u=up 							;Предельное значение UP  -1 max
		else
Ar#_u=-1
		end if
			If ~np eq
Ar#_n=np 							;n=0 min Начальное значение Ar#_u-Ar#_n=Диапазон изменения
			else
Ar#_n=0
			end if
}
;*******************************  2
	MACRO	D_fw	Ar,Br,tp,up,np
{
;1.Длинное слово с атрибутами для отладки сначало имя,затем значение
Ar	dw	Br							;имя = константа
;2.Размерность в байтах 
Ar#_r=2								;Размерность данных слово
;3.Тип данных 
	If ~tp eq
Ar#_t=tp
	else
Ar#_t=3								;Тип данных Целое без знака=3
	end if
;4.Верхний предел значений**************
		If ~up eq
Ar#_u=up							;Верхний предел данных
		else
Ar#_u=-1							;Предельное значение UP  -1 max
		end if
;4.Нижний предел значений*************		
			If ~np eq
Ar#_n=np 							;Начальное значение Ar#_u-Ar#_n=Диапазон изменения
			else
Ar#_n=0								;n=0 min 
			end if
}
;*********************************
;*******************************  3
	MACRO	D_fd	Ar,Br,tp,up,np
{
Ar	dd	Br							;имя = константа
Ar#_r=4								;Размерность данных слово
	If ~tp eq
Ar#_t=tp							;Тип данных Целое без знака=3
	else
Ar#_t=3
	end if
		If ~up eq
Ar#_u=up 						;Предельное значение UP  -1 max
		else
Ar#_u=-1
		end if
			If ~np eq
Ar#_n=np 						;n=0 min Начальное значение Ar#_u-Ar#_n=Диапазон изменения
			else
Ar#_n=0
			end if
}
;********************************  3   *
;****************************  4
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
	D_fb		\nnm,\nm2,,,
	else
\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
 ;***
	match =( nnm1 == nm2 !nnm2 == nm3 !nnm3 == nm4 !nnm3 == nm5 =) ,Spis 		; nma='PR'  nma1=f  nma2=0
 \{
	if	~\nm2	eq
	D_fb	\nnm1,\nm2,\nm3,\nm4,\nm5
	else
				\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
  ;***
		match =( nnm1 == nm2 =!Тег == nm3  =),Spis 					; nma='PR'  nma1=f  nma2=0
 \{
	if	~\nm2	eq
	D_fb	\nnm1,\nm2,\nm3,,
	else
				\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
 }
;****************************  4
;****************************	5
MACRO 	Dfn_one_D_W_I	Spis	;Определение одиночной константы
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
	D_fw	\nnm,\nm2,,,
	else
\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
 ;***
	match  =( nnm1 == nm2 =!Тег == nm3 =!Макс == nm4 =!Мин == nm5 =),Spis 		; nma='PR'  nma1=f  nma2=0
 \{
	if	~\nm2	eq
	D_fw	\nnm1,\nm2,\nm3,\nm4,\nm5
	else
				\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
  ;***
	match =( nnm1 == nm2 =!Тег == nm3  =),Spis 				; nma='PR'  nma1=f  nma2=0
 \{
	if	~\nm2	eq
	D_fw	\nnm1,\nm2,\nm3,,
	else
				\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
}
;******************************* 5
;****************************	6
MACRO 	Dfn_one_D_D_I	Spis	;Определение одиночной константы
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
	D_fd	\nnm,\nm2,,,
	else
				\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
 ;***
	match  =( nnm1 == nm2 =!Тег == nm3 =!Макс == nm4 =!Мин == nm5 =),Spis 		; nma='PR'  nma1=f  nma2=0
 \{
	if	~\nm2	eq
	D_fd	\nnm1,\nm2,\nm3,\nm4,\nm5
	else
				\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
  ;***
		match =( nnm1 == nm2 =!Тег == nm3  =),Spis 					; nma='PR'  nma1=f  nma2=0
 \{
	if	~\nm2	eq
	D_fd	\nnm1,\nm2,\nm3,,
	else
				\Print!afall   " ?=?  PUSTO  here"
	end if
 \}
}
;******************************* 6
;******************************* 7
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
;******************************  7
;******************************  8
;*******		РУССКИЙ  ВАРИАНТ  ЗадатьСловныеЦелое
	MACRO	ЗадалиСловныеЦелые	Groppa,[Spisok]
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
;********************************  8
;******************************  9
;*******		РУССКИЙ  ВАРИАНТ  ЗадатьСловныеЦелое
	MACRO	ЗадалиДвухСловныеЦелые	Groppa,[Spisok]
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
;********************************  9

;*********	Английский вариант		10
MACRO	D!efM_D_B_I		Groppa,[Spisok]
{
label	Groppa	dword
 forward
	Dfn_one_D_B_I	Spisok
}
;********************************  10
;*********	Английский вариант		11
MACRO	D!efM_D_W_I		Groppa,[Spisok]
{
label	Groppa	word
 forward
	Dfn_one_D_W_I	Spisok
}
;********************************  11
;*********	Английский вариант		12
MACRO	D!efM_D_D_I		Groppa,[Spisok]
{
label	Groppa	word
 forward
	Dfn_one_D_D_I	Spisok
}
;********************************  12