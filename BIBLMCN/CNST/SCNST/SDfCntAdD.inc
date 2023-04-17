;	1 SDfCntAdD
;	2 SDfCntAdDM
;	3 ОтладочныеГрупповыеКонстантыDПод_Именем
;************************ Специальные константы для отладки
	MACRO	SDfCntAdD  	SGroppa,Spis
{common
		db	'd'						;тип данных байт
match  nn (nnm == nm2),SGroppa Spis ; nma='PR'  nma1=f  nma2=0
 \{\label	\nnm	\dword			;короткая метка nnm
\nn\#\nnm\#_d	dd	\nm2			;длинное имя константы	\nn\#\nnm\#_b
		db	"$"\#\`nn				;,32\nnm\#\uuu
		db	\`nnm\#"$"
		db	" = "\#\`nm2			;значение в текстовом виде
\nnm#.size=3						;размерность операнда тип=3 т.е. 4 байта
 \}
}
;************************************
	MACRO	SDfCntAdDM	SGroppa,[Spisok]
 {forward
	SDfCntAdB	SGroppa,Spisok
}
;************************************
;*******************	Специальные отладочные константы для отладки
	MACRO	ОтладочныеГрупповыеКонстантыDПод_Именем  	SGroppa,[Spisok]
{forward
	SDfCntAdB	SGroppa,Spisok
}