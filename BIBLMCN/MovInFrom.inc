;
	MACRO	M!ov_In_From arg		;[FlSizN]<=[FlSizN]<=[FlDli]
{
	Продвинули arg
}
;**************1.5***Продвинули    [FlSizN]<=[FlSizN]<=[FlDli]
	MACRO	Продвинули arg
{	common match	T@1 =<== T@2,arg
		\{	\arg1	equ	\`T@1#\`T@2	
		   \MRT	equ	1
			match aww=<==ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
		\Двигал   \T@1,\T@2
		end if
		\}
		common match	T@1 =<== T@2=<== T@3,arg
		\{	\arg1	equ	\`T@1#\`T@2\`T@3	
		   \MRT	equ	1
			match aww=<==ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0 \\}
		if	\MRT	eq	1
		     	\Двигал   \T@1,\T@2
			\Двигал   \T@2,\T@3
		end if
		\}
		common match	T@1 =<== T@2=<==T@3  =<==T@4,arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4	
		   \MRT	equ	1
							;\Print!afall   \arg1
			match aww=<==ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
			;\Print!afall   \T@2
			;display 10
		     	\Двигал   \T@1,\T@2
			;Print!afall   \T@3
			;display 10
			\Двигал   \T@2,\T@3
			;\Print!afall   \T@4
			;display 13,10
			\Двигал   \T@3,\T@4
		end if
		\}
		common match	T@1=<== T@2=<==T@3=<==T@4=<==T@5,arg
		\{\arg1	equ	\`T@1#\`T@2\`T@3\`T@4\`T@5	
		   \MRT	equ	1
			match aww=<==ww,\arg1		;если есть хотя бы 1 +, то это не та структура
			\\{	\\MRT	equ	0\\}
		if	\MRT	eq	1
		    \Двигал   \T@1,\T@2
			\Двигал   \T@2,\T@3
			\Двигал   \T@3,\T@4
			\Двигал   \T@4,\T@5
		else
				Print!afall   "ERROR now only 5 expresion in macro REMOVING" 
		end if
		\}
	}
;*******************1.6*********************
	MACRO	Двигал   dest,src
{
  if  dest  src eqtype [0] [0]		;[FlSizN]=[FlDli]
    push	src
    pop	dest
;Print!afall   "N"
  else
	if  dest  in <al,bl,cl,dl,ah,bh,ch.dh,AX,BX,CX,DX,SI,DI,BP>			;eqtype EAX EBX
		if  src  in <al,bl,cl,dl,ah,bh,ch.dh,AX,BX,CX,DX,SI,DI,BP>
			mov	dest,src
				;Print!afall   "N"
				;Print!afall   src
				;display 10
		else
			;mov	dest,[src]
				Print!afall   "M"
				display 10
		end if
	else
		 if  dest   eqtype [0]
			mov	dest,src
			Print!afall   "L"
		else
			Print!afall   "K"
			mov	[dest],src	
		Print!afall   "NERROR"
		display 10
		end if				
	end if
  end if
}
