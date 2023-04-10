;*********************************m!ss***для слова в 64 разряда********
;		МАКРОС  1  - формирования одной строки с разделителем "+"
macro m!ss arg
{
common match a,arg
\{					\arg1	equ	\`a	
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
					;Print!afall   \NMRuu 
		db	a,0,0,0,0,0,0,0		; xor 0FFh		;одно поле
end if
\}
;************************
common match a=+b,arg
  \{					\arg1	equ	\`a#\`b		;#\`c#\`d#`b
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
					;Print!afall   \NMRuu 
	 	db	a shl 2 or b,0,0,0,0,0,0,0		; xor 0FFh				;2 поле
end if
     \}
;**************************
common match a=+b=+c,arg
  \{					\arg1	equ	\`a#\`b#\`c
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
							;Print!afall   \NMRuu 
 	 	db	a shl 4 or b shl 2 or c,0,0,0,0,0,0,0		;xor 0FFh		;3 поля
end if
     \}
;*************************************
match a=+b=+c=+d,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
							;Print!afall   \NMRuu 
	 	db	a shl 6 or b shl 4 or c shl 2 or d,0,0,0,0,0,0,0		 ;xor 0FFh	;4 поля
end if
     \}
;**************************
match a=+b=+c=+d=+ e,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
							;Print!afall   \NMRuu
    db	b shl 6 or c shl 4 or d shl 2 or e,\
	a,\
	0,0,0,0,0,0					; xor 0FFh	;5 
end if 
     \}
;**************************
match a=+b=+c=+d=+ e=+f,arg
  \{					\arg1	equ	a#\`b#\`c#\`d#\`e#\`f
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
   db	c shl 6 or d shl 4 or e shl 2 or f,\
	a shl 2 or b	,\
	0,0,0,0,0,0			;6
end if   
     \}
;**************************
match a=+b=+c=+d=+ e=+f=+g,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu 
   db	d shl 6 or e shl 4 or f shl 2 or g,\
	a shl 4 or b shl 2 or c,\	
	0,0,0,0,0,0					;7
end if   
     \}
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu 
	 	db	e shl 6 or f shl 4 or g shl 2 or h,\
			a shl 6 or b shl 4 or c shl 2 or d,0,0,0,0,0,0		;8
end if   
     \}
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
    db	f shl 6 or g shl 4 or h shl 2 or i,\
	b shl 6 or c shl 4 or d shl 2 or e,\
	a,\
	0,0,0,0,0			;9
end if   
     \}
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j,arg
  \{						\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu 
   db	g shl 6 or h shl 4 or i shl 2 or j,\
	c shl 6 or d shl 4 or e shl 2 or f,\
	a shl 2 or b	,\
	0,0,0,0,0			;10
end if   
     \}
;****************************
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k,arg
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu 
 db	h shl 6 or i shl 4 or j shl 2 or k,\
	d shl 6 or e shl 4 or f shl 2 or g,\
	a shl 4 or b shl 2 or c,\
	0,0,0,0,0				;11
end if   
     \}
;****************************
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k=+ l,arg
  \{						\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k#\`l
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu 
 db	i shl 6 or j shl 4 or k shl 2 or l,\
	e shl 6 or f shl 4 or g shl 2 or h,\
	a shl 6 or b shl 4 or c shl 2 or d,\
	0,0,0,0,0				;12
end if   
     \}
;****************************
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k=+ l=+ m,arg
  \{				\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu 
 db	j shl 6 or k shl 4 or l shl 2 or m,\
	f shl 6 or g shl 4 or h shl 2 or i,\
	b shl 6 or c shl 4 or d shl 2 or e,\
	a,0,0,0,0			; shl 6 or b shl 4 or c shl 2 or d		;13  ?????
end if   
     \}
;****************************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k=+ l=+ m=+ n,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu 
 db	k shl 6 or l shl 4 or m shl 2 or n,\
	g shl 6 or h shl 4 or i shl 2 or j,\
	c shl 6 or d shl 4 or e shl 2 or f,\
	a shl 2 or b,0,0,0,0				;14?????
end if   
     \}
;****************************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o,arg
  \{				\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu 
 db	l shl 6 or m shl 4 or n shl 2 or o,\
	h shl 6 or i shl 4 or j shl 2 or k,\
	d shl 6 or e shl 4 or f shl 2 or g,\
	a shl 4 or b shl 2 or c,0,0,0,0					;15
end if   
     \}
;****************************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p,arg
  \{			\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu 
     db  	m shl 6 or n shl 4 or o shl 2 or p,\
	i shl 6 or j shl 4 or k shl 2 or l,\
	e shl 6 or f shl 4 or g shl 2 or h,\
	a shl 6 or b shl 4 or c shl 2 or d,0,0,0,0	 				;16
end if   
     \}
;*******************
match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q,arg ;=+ r=+ s=+ t=+u=+ v=+ w=+ x=+ y=+z,arg
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q  ;#\`r#\`s#\`t#\`u#\`v#\`w#\`x#\`y#\`z
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	n shl 6 or o shl 4 or p shl 2 or q,\
	j shl 6 or k shl 4 or l shl 2 or m,\
	f shl 6 or g shl 4 or h shl 2 or i,\
	b shl 6 or c shl 4 or d shl 2 or e,\
	a,0,0,0	 				;17
end if   
     \}
;***************************************

match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q=+ r,arg ;=+ s=+ t=+u=+ v=+ w=+ x=+ y=+z,arg
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r  ;#\`s#\`t#\`u#\`v#\`w#\`x#\`y#\`z
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	o shl 6 or p shl 4 or q shl 2 or r,\
	k shl 6 or l shl 4 or m shl 2 or n,\
	g shl 6 or h shl 4 or i shl 2 or j,\
	c shl 6 or d shl 4 or e shl 2 or f,\
	a shl 2 or b,0,0,0	 				;18
end if   
     \}
;**************
match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q=+ r=+ s,arg ;==+ t=+u=+ v=+ w=+ x=+ y=+z,arg
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s  ;#\`t#\`u#\`v#\`w#\`x#\`y#\`z
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	p shl 6 or q shl 4 or r shl 2 or s,\
	l shl 6 or m shl 4 or n shl 2 or o,\
	h shl 6 or i shl 4 or j shl 2 or k,\
	d shl 6 or e shl 4 or f shl 2 or g,\
	a shl 4 or b shl 2 or c,0,0,0	 				;19
end if   
     \}
match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q=+ r=+ s=+ t  ,arg ;=+u=+ v=+ w=+ x=+ y=+z,arg
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t  ;#\`u#\`v#\`w#\`x#\`y#\`z
\NMRuu	equ	1
;**************
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	q shl 6 or r shl 4 or s shl 2 or t,\
	m shl 6 or n shl 4 or o shl 2 or p,\
	i shl 6 or j shl 4 or k shl 2 or l,\
	e shl 6 or f shl 4 or g shl 2 or h,\
	a shl 6 or b shl 4 or c shl 2 or d,0,0,0	 				;20
end if   
     \}
;**********************
match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q=+ r=+ s=+ t=+u  ,arg ;=+ v=+ w=+ x=+ y=+z,arg
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u  ;#\`v#\`w#\`x#\`y#\`z
\NMRuu	equ	1
;**************
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	r shl 6 or s shl 4 or t shl 2 or u,\
	n shl 6 or o shl 4 or p shl 2 or q,\
	j shl 6 or k shl 4 or l shl 2 or m,\
	f shl 6 or g shl 4 or h shl 2 or i,\
	b shl 6 or c shl 4 or d shl 2 or e,\
	a,0,0	 				;21
end if   
     \}
;**********************
match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q=+ r=+ s=+ t=+u=+ v,arg ;=+ w=+ x=+ y=+z,arg
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u#\`v  ;#\`w#\`x#\`y#\`z
\NMRuu	equ	1
;**************
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	s shl 6 or t shl 4 or u shl 2 or v,\
	o shl 6 or p shl 4 or q shl 2 or r,\
	k shl 6 or l shl 4 or m shl 2 or n,\
	g shl 6 or h shl 4 or i shl 2 or j,\
	c shl 6 or d shl 4 or e shl 2 or f,\
	a shl 2 or b,0,0	 				;22
end if   
     \}
;**********************
match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q=+ r=+ s=+ t=+u=+ v=+ w=+ x  ,arg ;=+ y=+z,arg
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u#\`v#\`w#\`x  ;#\`y#\`z
\NMRuu	equ	1
;**************
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	t shl 6 or u shl 4 or v shl 2 or w,\
	p shl 6 or q shl 4 or r shl 2 or s,\
	l shl 6 or m shl 4 or n shl 2 or o,\
	h shl 6 or i shl 4 or j shl 2 or k,\
	d shl 6 or e shl 4 or f shl 2 or g,\
	a shl 4 or b shl 2 or c,0,0	 				;23
end if   
     \}
;**********************
match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q=+ r=+ s=+ t=+u=+ v=+ w=+ x=+ y,arg ;=+z,arg
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u#\`v#\`w#\`x#\`y  ;#\`z
\NMRuu	equ	1
;**************
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	u shl 6 or v shl 4 or w shl 2 or x,\
	q shl 6 or r shl 4 or s shl 2 or t,\
	m shl 6 or n shl 4 or o shl 2 or p,\
	i shl 6 or j shl 4 or k shl 2 or l,\
	e shl 6 or f shl 4 or g shl 2 or h,\
	a shl 6 or b shl 4 or c shl 2 or d,0,0	 				;24
end if
     \}
;**********************
match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q=+ r=+ s=+ t=+u=+ v=+ w=+ x=+ y,arg ;=+z,arg
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u#\`v#\`w#\`x#\`y  ;#\`z
\NMRuu	equ	1
;**************
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	v shl 6 or w shl 4 or x shl 2 or y,\
	r shl 6 or s shl 4 or t shl 2 or u,\
	n shl 6 or o shl 4 or p shl 2 or q,\
	j shl 6 or k shl 4 or l shl 2 or m,\
	f shl 6 or g shl 4 or h shl 2 or i,\
	b shl 6 or c shl 4 or d shl 2 or e,\
	a,0	 				;25
end if
     \}
;**********************
match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q=+ r=+ s=+ t=+u=+ v=+ w=+ x=+ y=+z,arg 	;
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u#\`v#\`w#\`x#\`y#\`z  ;
\NMRuu	equ	1
;**************
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	w shl 6 or x shl 4 or y shl 2 or z,\
	s shl 6 or t shl 4 or u shl 2 or v,\
	o shl 6 or p shl 4 or q shl 2 or r,\
	k shl 6 or l shl 4 or m shl 2 or n,\
	g shl 6 or h shl 4 or i shl 2 or j,\
	c shl 6 or d shl 4 or e shl 2 or f,\
	a shl 2 or b,0	 				;26
end if
     \}
;**********************
match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q=+ r=+ s=+ t=+u=+ v=+ w=+ x=+ y=+z=+zz,arg 	;
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u#\`v#\`w#\`x#\`y#\`z#\`zz  ;
\NMRuu	equ	1
;**************
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	x shl 6 or y shl 4 or z shl 2 or zz,\
	t shl 6 or u shl 4 or v shl 2 or w,\
	p shl 6 or q shl 4 or r shl 2 or s,\
	l shl 6 or m shl 4 or n shl 2 or o,\
	h shl 6 or i shl 4 or j shl 2 or k,\
	d shl 6 or e shl 4 or f shl 2 or g,\
	a shl 4 or b shl 2 or c,0	 				;27
end if
     \}
;**********************
match a=+b=+c=+d=+ e=+ f=+ g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p =+ q=+ r=+ s=+ t=+u=+ v=+ w=+ x=+ y=+z=+zz=+yy,arg 	;
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u#\`v#\`w#\`x#\`y#\`z#\`zz#\`yy  ;
\NMRuu	equ	1
;**************
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	y shl 6 or z shl 4 or zz shl 2 or yy,\
	u shl 6 or v shl 4 or w shl 2 or x,\
	q shl 6 or r shl 4 or s shl 2 or t,\
	m shl 6 or n shl 4 or o shl 2 or p,\
	i shl 6 or j shl 4 or k shl 2 or l,\
	e shl 6 or f shl 4 or g shl 2 or h,\
	a shl 6 or b shl 4 or c shl 2 or d,0	 				;28
end if
     \}
;**********************
match a=+b=+c=+d=+e=+f=+ g=+h=+i=+j=+ k=+ l=+ m=+ n=+o=+p =+ q=+ r=+ s=+ t=+u=+ v=+ w=+ x=+ y=+z=+zz=+yy=+xx=+ч,arg 	;
\{\arg1  equ  \`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u#\`v#\`w#\`x#\`y#\`z#\`zz#\`yy#\`xx#\`ч ;
\NMRuu	equ	1
;**************
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	z shl 6 or zz shl 4 or yy shl 2 or ч,\
	v shl 6 or w shl 4 or x shl 2 or y,\
	r shl 6 or s shl 4 or t shl 2 or u,\
	n shl 6 or o shl 4 or p shl 2 or q,\
	j shl 6 or k shl 4 or l shl 2 or m,\
	f shl 6 or g shl 4 or h shl 2 or i,\
	b shl 6 or c shl 4 or d shl 2 or e,\
	a					;29
end if
     \}
;**********************
match a=+b=+c=+d=+e=+f=+g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+p =+q=+ r=+ s=+t=+u=+ v=+ w=+ x=+ y=+z=+zz=+yy=+ч=+в,arg ;
\{\arg1 equ   \`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u#\`v#\`w#\`x#\`y#\`z#\`zz#\`yy#\`ч#\`в ;
\NMRuu	equ	1
;**************
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
 db  	zz shl 6 or yy shl 4 or ч shl 2 or в,\
	w shl 6 or x shl 4 or y shl 2 or z,\
	s shl 6 or t shl 4 or u shl 2 or v,\
	o shl 6 or p shl 4 or q shl 2 or r,\
	k shl 6 or l shl 4 or m shl 2 or n,\
	g shl 6 or h shl 4 or i shl 2 or j,\
	c shl 6 or d shl 4 or e shl 2 or f,\
	a shl 2 or b					;30
end if
     \}
;**********************
match a=+b=+c=+d=+e=+f=+g=+h=+i=+j=+k=+l=+m=+n=+o=+p=+q=+r=+s=+t=+u=+v=+w=+x=+y=+z=+zz=+yy=+ч=+в=+ц,arg 	;
\{
\g1 equ \`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u#\`v#\`w#\`x#\`y#\`z#\`zz#\`yy#\`ч#\`в#\`ц# ;
\NMRuu	equ	1
;**************
match aww=+ww,\g1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
 db  	yy shl 6 or ч shl 4 or в shl 2 or ц,\
	x shl 6 or y shl 4 or z shl 2 or zz,\
	t shl 6 or u shl 4 or v shl 2 or w,\
	p shl 6 or q shl 4 or r shl 2 or s,\
	l shl 6 or m shl 4 or n shl 2 or o,\
	h shl 6 or i shl 4 or j shl 2 or k,\
	d shl 6 or e shl 4 or f shl 2 or g,\
	a shl 4 or b shl 2 or c					;31
end if
     \}
;**********************
match a=+b=+c=+d=+e=+f=+g=+h=+i=+j=+k=+l=+m=+n=+o=+p=+q=+r=+s=+t=+u=+v=+w=+x=+y=+z=+zz=+yy=+ч=+в=+ц=+т,arg
\{
\g1 equ \`a#\`b#\`c#\`d#\`e#\`d#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p#\`q#\`r#\`s#\`t#\`u#\`v#\`w#\`x#\`y#\`z#\`zz#\`yy#\`ч#\`в#\`ц#\`т
\NMRuu	equ	1
;**************
match aww=+ww,\g1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
				;Print!afall   \NMRuu 
 db  	ч shl 6 or в shl 4 or ц shl 2 or т,\
	y shl 6 or z shl 4 or zz shl 2 or yy,\
	u shl 6 or v shl 4 or w shl 2 or x,\
	q shl 6 or r shl 4 or s shl 2 or t,\
	m shl 6 or n shl 4 or o shl 2 or p,\
	i shl 6 or j shl 4 or k shl 2 or l,\
	e shl 6 or f shl 4 or g shl 2 or h,\
	a shl 6 or b shl 4 or c shl 2 or d					;32
end if
     \}
;Print!afall   arg1
;	display 13,10
}
;***************
;*********************mss****

;************m!sq  массив 8 байт -  слово******
macro m!sq metms,[arg]	;получение массива с меткой
 { common
Rswtch=0				;'0'  для печати   счетчик по числу строк
metms:				;RR	equ	Rswtch	
				;display RR
				;display 13,10
forward
Rswtch = Rswtch+1   			;В зависимости от кол-ва переменных накапл.счетчик
	m!ss arg
common				;display   Rswtch
        if	Rswtch >64			;32
display 'NE:Number poley > 32',13,10
      else
	if	Rswtch <17			
display 'NE:Number poley < 17;  Use macro - m!sd ',13,10
	end if
     end if
metms#.pole	db	Rswtch
metms#.dlina=metms#.pole-metms
}
;************m!sq  массив 8 байт - слово***********
;		МАКРОС  3  - формирование массива (матрицы) отношений, используя МАКРОС  1
;			но возможно записать 17 отношений для 18 точек, мнимая диагональ начинается <
;			после массива байт длины массива (кол-во строк)+ "<"shl 6 
;***
;		ОБРАЩЕНИЕ:
;	m!sq1 NICK,3+3+3+2+1+0+3+3,\
;		       3+3+3+2+1+0+3,\
;		           3+3+2+1+0+3,\
;		               3+2+1+0+3,\
;		                   2+2+1+0,\
;		                       3+1+0,\
;		                           2+1,\
;		            	             3
;		РЕЗУЛЬТАТ:
;		NICK	dd  ????????
;			. . . . . 	
;			dd   ?
;		NICK.pole	db  N	- кол-во строк +2 shl 6
;		NICK.dlina=число занятых байт
;************m!sd1  массив двойное слово******
macro m!sq1 metms,[arg]		;получение массива с меткой
 { common
Rswtch=0				;'0'  для печати   счетчик по числу строк
metms:				;RR	equ	Rswtch	
				;display RR
				;display 13,10
forward
Rswtch = Rswtch+1   				;В зависимости от кол-ва переменных накапл.счетчик
	m!ss arg
common				;display   Rswtch
        if	Rswtch >64
display 'NE:Number poley > 32',13,10
      else
	if	Rswtch <17			
display 'NE:Number poley < 17;  Use macro - m!sd ',13,10
	end if
     end if
metms#.pole	db	0 shl 7 or Rswtch
metms#.dlina=metms#.pole-metms
}
;************m!sd1  массив двойное слово***********
;************m!sd2 массив двойное слово******
;		МАКРОС  4  - формирование массива (матрицы) отношений c меткой , используя МАКРОС  1
;			но возможно записать 17 отношений для 18 точек, мнимая диагональ начинается >
;			после массива байт длины массива (кол-во строк)+ ">"shl 6 
;***
;		ОБРАЩЕНИЕ:
;	m!sd2 NICK,3+3+3+2+1+0+3+3,\
;		       3+3+3+2+1+0+3,\
;		           3+3+2+1+0+3,\
;		               3+2+1+0+3,\
;		                   2+2+1+0,\
;		                       3+1+0,\
;		                           2+1,\
;		            	             3
;		РЕЗУЛЬТАТ:
;		NICK	dd  ????????
;			. . . . . 	
;			dd   ?
;		NICK.pole	db  N	- кол-во строк +0 shl 6
;		NICK.dlina=число занятых байт
;***********************************
macro m!sq2 metms,[arg]	;получение массива с меткой
 { common
Rswtch=0				;'0'  для печати   счетчик по числу строк
metms:				;RR	equ	Rswtch	
				;display RR
				;display 13,10
forward
Rswtch = Rswtch+1   				;В зависимости от кол-ва переменных накапл.счетчик
	m!ss arg
common
				;display   Rswtch
        if	Rswtch >64
display 'NE:Number poley > 32',13,10
      else
	if	Rswtch <17			
display 'NE:Number poley < 17;  Use macro - m!sd ',13,10
	end if 
     end if
metms#.pole	db	1 shl 7 or Rswtch
metms#.dlina=metms#.pole-metms
}
;*****************************************