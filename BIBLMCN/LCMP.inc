;1 LCMPab Ko,[RE1,RE2,E!Q,N!EQ]
;2 LCMPabc
;3 С_учетом_2_логических_Отношений_Перейти arg 		Доделать!!!!!
;4 L!CMPU
;5 L!CMPUM
;************************************************* 
	MACRO LCMP Ko,[RE1,RE2,E!Q,N!EQ]   		;сравнение списка из 2 переменных
{	forward
		xor RE1,RE2			;Логическое сравнение	Доделать!!!!!
		;xor RE1,[RE2]		;1
		;xor [RE1],RE2		;2
		;push EAX			;3
		;mov	EAX,[RE2]		;
		;xor RE1,EAX
		;pop	EAX
	IF ~Ko EQ
		mov [Ko],RE1		;Если  сравнились [Ko]=0
	ELSE
	END IF
	IF (~E!Q EQ) & IF (~N!EQ EQ)
				IF ~E!Q EQ
		je E!Q				;Если  сравнились
				ELSE
				END IF
					IF ~N!EQ EQ
		jne N!EQ   			;Если не сравнились
					ELSE
					END IF
	ELSE
	END IF					
}
;*******************************************************
;T1: a=b=c  T2:a=b~=c  T3:a~=b=c  T4:(a~=b~=c a=c) T5:(a~=b~=c a~=c)
; С_учетом_логических_Отношений_=_Перейти\
				A=AX B=DX C=BP\
								=>:T1=MET1 T2=MET2 T3=MET3 T4=MET4 T5=MET5
;*******************************************************
MACRO LCMPabc RE1,RE2,RE3,T1,T2,T3,T4,T5,Ko   		;сравнение списка из 2 переменных
{	forward
		xor RE1,RE2			;Логическое сравнение
	jne	@F
			IF ~Ko EQ
		mov [Ko],1
			else
			end if
		xor RE2,RE3
	je	T1					;: a=b=c
			IF ~Ko EQ
		inc	[Ko]
			else
			end if
		xor RE2,RE3
	jmp	T2					;:a=b~=c
@@:
			IF ~Ko EQ
		mov [Ko],3
			else
			end if
		xor RE2,RE3
	je	T3					;:a~=b=c
			IF ~Ko EQ
		inc	[Ko]
			else
			end if
		xor RE1,RE2	
	je	T4					;:(a~=b~=c a=c)
			IF ~Ko EQ
		inc	[Ko]
			else
			end if
	jmp	T5					;:(a~=b~=c a~=c)	
]
;*******************************************************
;С_учетом_логических_Отношений_=_Перейти\
				A=AX B=DX C=BP\
								=>:T1=MET1 T2=MET2 T3=MET3 T4=MET4 T5=MET5
;***********************
;С_учетом_логических_Отношений_=_Перейти\
				A=AX B=DX\
								=>:T1=MET1 T2=MET2								
;*******************************************************
MACRO С_учетом_2_логических_Отношений_Перейти arg 		;сравнение списка из 2 переменных
{

}
;*******************************************************
MACRO L!CMPU RE1,RE2,EQ,NEQ
{		xor RE1,RE2
	je EQ
	jne NEQ 	
}
MACRO L!CMPUM [RE1,RE2,EQ,NEQ]
{forward
 L!CMPU RE1,RE2,EQ,NEQ
}

;**********************************************************								