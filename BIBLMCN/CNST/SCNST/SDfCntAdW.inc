;	1 SDfCntAdW
;	2 SDfCntAdWM
;	3 ОтладочныеГрупповыеКонстантыWПод_Именем
;************************ Специальные константы для отладки
	MACRO	SDfCntAdW  	SGroppa,Spis
{common
		db	'w'						;тип данных байт
match  nn (nnm == nm2),SGroppa Spis ; nma='PR'  nma1=f  nma2=0
 \{\label	\nnm	\dword			;короткая метка nnm
\nn\#\nnm\#_d	dw	\nm2			;длинное имя константы	\nn\#\nnm\#_b
		db	"$"\#\`nn				;,32\nnm\#\uuu
		db	\`nnm\#"$"
		db	" = "\#\`nm2			;значение в текстовом виде
\nnm#.size=2						;размерность операнда тип=2 т.е. 2 байта
 \}
}
;************************************
	MACRO	SDfCntAdWM	SGroppa,[Spisok]
 {forward
	SDfCntAdB	SGroppa,Spisok
}
;************************************
;*******************	Специальные отладочные константы для отладки
	MACRO	ОтладочныеГрупповыеКонстантыWПод_Именем  	SGroppa,[Spisok]
{forward
	SDfCntAdB	SGroppa,Spisok
}