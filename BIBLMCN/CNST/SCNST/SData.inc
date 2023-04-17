;Формирование матрицы отношений, где значение отношения занимает 2 разряда
;	MTR
;
	MACRO MTR	mmm,[ar]
{common
mmm:
	FORWARD
		match r1,ar
	\{
			\flag equ	1
		match  a=+b,\r1
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1
		else
		end if
	\}
		match r1=+r2,ar
	\{
			\flag equ	1
		match  a=+b,\r2
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 2 or \r2
		else
		end if
	\}
	match r1=+r2=+r3,ar
	\{
			\flag equ	1
		match  a=+b,\r3
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 4 or \r2 shl 2 or \r3
		else
		end if
	\}
	match r1=+r2=+r3=+r4,ar
	\{
			\flag equ	1
		match  a=+b,\r4
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 6 or \r2 shl 4 or \r3 shl 2 or \r4
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+ r5,ar
	\{
			\flag equ	1
		match  a=+b,\r5
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1
		db	\r2 shl 6 or \r3 shl 4 or \r4 shl 2 or \r5
		else
		end if
	\}
		match r1=+r2=+r3=+r4=+r5=+r6,ar
	\{
			\flag equ	1
		match  a=+b,\r6
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 2 or \r2
		db	\r3 shl 6 or \r4 shl 4 or \r5 shl 2 or \r6
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7,ar
	\{
			\flag equ	1
		match  a=+b,\r7
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 4 or \r2 shl 2 or \r3
		db	\r4 shl 6 or \r5 shl 4 or \r6 shl 2 or \r7
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8,ar
	\{
			\flag equ	1
		match  a=+b,\r8
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 6 or \r2 shl 4 or \r3 shl 2 or \r4
		db	\r5 shl 6 or \r6 shl 4 or \r7 shl 2 or \r8
		else
		end if
	\}
		match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9 ,ar
	\{
			\flag equ	1
		match  a=+b,\r9
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1
		db	\r2 shl 6 or \r3 shl 4 or \r4 shl 2 or \r5
		db	\r6 shl 6 or \r7 shl 4 or \r8 shl 2 or \r9
		else
		end if
	\}
		match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10 ,ar
	\{
			\flag equ	1
		match  a=+b,\r10
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 2 or \r2
		db	\r3 shl 6 or \r4 shl 4 or \r5 shl 2 or \r6
		db	\r7 shl 6 or \r8 shl 4 or \r9 shl 2 or \r10
		else
		end if
	\}
		match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11 ,ar
	\{
			\flag equ	1
		match  a=+b,\r11
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1 shl 4 or \r2 shl 2 or \r3
 		db	\r4 shl 6 or \r5 shl 4 or \r6 shl 2 or \r7
		db	\r8 shl 6 or \r9 shl 4 or \r10 shl 2 or \r11
		else
		end if
	\}
		match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12 ,ar
	\{
			\flag equ	1
		match  a=+b,\r12
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 6 or \r2 shl 4 or \r3 shl 2 or \r4
		db	\r5 shl 6 or \r6 shl 4 or \r7 shl 2 or \r8
		db	\r9 shl 6 or \r10 shl 4 or \r11 shl 2 or \r12
		else
		end if
	\}
		match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13 ,ar
	\{
			\flag equ	1
		match  a=+b,\r13
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1
 		db	\r2 shl 6 or \r3 shl 4 or \r4 shl 2 or \r5
		db	\r6 shl 6 or \r7 shl 4 or \r8 shl 2 or \r9
		db	\r10 shl 6 or \r11 shl 4 or \r12 shl 2 or \r13
		else
		end if
	\}
			match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14 ,ar
	\{
			\flag equ	1
		match  a=+b,\r14
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1 shl 2 or \r2
 		db	\r3 shl 6 or \r4 shl 4 or \r5 shl 2 or \r6
		db	\r7 shl 6 or \r8 shl 4 or \r9 shl 2 or \r10
		db	\r11 shl 6 or \r12 shl 4 or \r13 shl 2 or \r14
		else
		end if
	\}
		match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15 ,ar
	\{
			\flag equ	1
		match  a=+b,\r15
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1 shl 4 or \r2 shl 2 or \r3
 		db	\r4 shl 6 or \r5 shl 4 or \r6 shl 2 or \r7
		db	\r8 shl 6 or \r9 shl 4 or \r10 shl 2 or \r11
		db	\r12 shl 6 or \r13 shl 4 or \r14 shl 2 or \r15
		else
		end if
	\}
		match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16 ,ar
	\{
			\flag equ	1
		match  a=+b,\r16
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 6 or \r2 shl 4 or \r3 shl 2 or \r4
		db	\r5 shl 6 or \r6 shl 4 or \r7 shl 2 or \r8
		db	\r9 shl 6 or \r10 shl 4 or \r11 shl 2 or \r12
		db	\r13 shl 6 or \r14 shl 4 or \r15 shl 2 or \r16
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17 ,ar
	\{
			\flag equ	1
		match  a=+b,\r17
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1
 		db	\r2 shl 6 or \r3 shl 4 or \r4 shl 2 or \r5
		db	\r6 shl 6 or \r7 shl 4 or \r8 shl 2 or \r9
		db	\r10 shl 6 or \r11 shl 4 or \r12 shl 2 or \r13
		db	\r14 shl 6 or \r15 shl 4 or \r16 shl 2 or \r17
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18 ,ar
	\{
			\flag equ	1
		match  a=+b,\r18
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1 shl 2 or \r2
 		db	\r3 shl 6 or \r4 shl 4 or \r5 shl 2 or \r6
		db	\r7 shl 6 or \r8 shl 4 or \r9 shl 2 or \r10
		db	\r11 shl 6 or \r12 shl 4 or \r13 shl 2 or \r14
		db	\r15 shl 6 or \r16 shl 4 or \r17 shl 2 or \r18
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19 ,ar
	\{
			\flag equ	1
		match  a=+b,\r19
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1 shl 4 or \r2 shl 2 or \r3
 		db	\r4 shl 6 or \r5 shl 4 or \r6 shl 2 or \r7
		db	\r8 shl 6 or \r9 shl 4 or \r10 shl 2 or \r11
		db	\r12 shl 6 or \r13 shl 4 or \r14 shl 2 or \r15
		db	\r16 shl 6 or \r17 shl 4 or \r18 shl 2 or \r19
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20 ,ar
	\{
			\flag equ	1
		match  a=+b,\r20
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 6 or \r2 shl 4 or \r3 shl 2 or \r4
		db	\r5 shl 6 or \r6 shl 4 or \r7 shl 2 or \r8
		db	\r9 shl 6 or \r10 shl 4 or \r11 shl 2 or \r12
		db	\r13 shl 6 or \r14 shl 4 or \r15 shl 2 or \r16
		db	\r17 shl 6 or \r18 shl 4 or \r19 shl 2 or \r20
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21 ,ar
	\{
			\flag equ	1
		match  a=+b,\r21
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1
 		db	\r2 shl 6 or \r3 shl 4 or \r4 shl 2 or \r5
		db	\r6 shl 6 or \r7 shl 4 or \r8 shl 2 or \r9
		db	\r10 shl 6 or \r11 shl 4 or \r12 shl 2 or \r13
		db	\r14 shl 6 or \r15 shl 4 or \r16 shl 2 or \r17
		db	\r18 shl 6 or \r19 shl 4 or \r20 shl 2 or \r21
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21=+r22 ,ar
	\{
			\flag equ	1
		match  a=+b,\r22
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1 shl 2 or \r2
 		db	\r3 shl 6 or \r4 shl 4 or \r5 shl 2 or \r6
		db	\r7 shl 6 or \r8 shl 4 or \r9 shl 2 or \r10
		db	\r11 shl 6 or \r12 shl 4 or \r13 shl 2 or \r14
		db	\r15 shl 6 or \r16 shl 4 or \r17 shl 2 or \r18
		db	\r19 shl 6 or \r20 shl 4 or \r21 shl 2 or \r22
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21=+r22=+r23 ,ar
	\{
			\flag equ	1
		match  a=+b,\r23
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1 shl 4 or \r2 shl 2 or \r3
 		db	\r4 shl 6 or \r5 shl 4 or \r6 shl 2 or \r7
		db	\r8 shl 6 or \r9 shl 4 or \r10 shl 2 or \r11
		db	\r12 shl 6 or \r13 shl 4 or \r14 shl 2 or \r15
		db	\r16 shl 6 or \r17 shl 4 or \r18 shl 2 or \r19
		db	\r20 shl 6 or \r21 shl 4 or \r22 shl 2 or \r23
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21=+r22=+r23=+r24 ,ar
	\{
			\flag equ	1
		match  a=+b,\r24
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 6 or \r2 shl 4 or \r3 shl 2 or \r4
		db	\r5 shl 6 or \r6 shl 4 or \r7 shl 2 or \r8
		db	\r9 shl 6 or \r10 shl 4 or \r11 shl 2 or \r12
		db	\r13 shl 6 or \r14 shl 4 or \r15 shl 2 or \r16
		db	\r17 shl 6 or \r18 shl 4 or \r19 shl 2 or \r20
		db	\r21 shl 6 or \r22 shl 4 or \r23 shl 2 or \r24
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21=+r22=+r23=+r24=+r25 ,ar
	\{
			\flag equ	1
		match  a=+b,\r25
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1
 		db	\r2 shl 6 or \r3 shl 4 or \r4 shl 2 or \r5
		db	\r6 shl 6 or \r7 shl 4 or \r8 shl 2 or \r9
		db	\r10 shl 6 or \r11 shl 4 or \r12 shl 2 or \r13
		db	\r14 shl 6 or \r15 shl 4 or \r16 shl 2 or \r17
		db	\r18 shl 6 or \r19 shl 4 or \r20 shl 2 or \r21
		db	\r22 shl 6 or \r23 shl 4 or \r24 shl 2 or \r25
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21=+r22=+r23=+r24=+r25=+r26 ,ar
	\{
			\flag equ	1
		match  a=+b,\r26
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1 shl 2 or \r2
 		db	\r3 shl 6 or \r4 shl 4 or \r5 shl 2 or \r6
		db	\r7 shl 6 or \r8 shl 4 or \r9 shl 2 or \r10
		db	\r11 shl 6 or \r12 shl 4 or \r13 shl 2 or \r14
		db	\r15 shl 6 or \r16 shl 4 or \r17 shl 2 or \r18
		db	\r19 shl 6 or \r20 shl 4 or \r21 shl 2 or \r22
		db	\r23 shl 6 or \r24 shl 4 or \r25 shl 2 or \r26
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21=+r22=+r23=+r24=+r25=+r26=+r27 ,ar
	\{
			\flag equ	1
		match  a=+b,\r27
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1 shl 4 or \r2 shl 2 or \r3
 		db	\r4 shl 6 or \r5 shl 4 or \r6 shl 2 or \r7
		db	\r8 shl 6 or \r9 shl 4 or \r10 shl 2 or \r11
		db	\r12 shl 6 or \r13 shl 4 or \r14 shl 2 or \r15
		db	\r16 shl 6 or \r17 shl 4 or \r18 shl 2 or \r19
		db	\r20 shl 6 or \r21 shl 4 or \r22 shl 2 or \r23
		db	\r24 shl 6 or \r25 shl 4 or \r26 shl 2 or \r27
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21=+r22=+r23=+r24=+r25=+r26=+r27=+r28 ,ar
	\{
			\flag equ	1
		match  a=+b,\r28
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 6 or \r2 shl 4 or \r3 shl 2 or \r4
		db	\r5 shl 6 or \r6 shl 4 or \r7 shl 2 or \r8
		db	\r9 shl 6 or \r10 shl 4 or \r11 shl 2 or \r12
		db	\r13 shl 6 or \r14 shl 4 or \r15 shl 2 or \r16
		db	\r17 shl 6 or \r18 shl 4 or \r19 shl 2 or \r20
		db	\r21 shl 6 or \r22 shl 4 or \r23 shl 2 or \r24
		db	\r25 shl 6 or \r26 shl 4 or \r27 shl 2 or \r28
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21=+r22=+r23=+r24=+r25=+r26=+r27=+r28=+r29 ,ar
	\{
			\flag equ	1
		match  a=+b,\r29
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1
 		db	\r2 shl 6 or \r3 shl 4 or \r4 shl 2 or \r5
		db	\r6 shl 6 or \r7 shl 4 or \r8 shl 2 or \r9
		db	\r10 shl 6 or \r11 shl 4 or \r12 shl 2 or \r13
		db	\r14 shl 6 or \r15 shl 4 or \r16 shl 2 or \r17
		db	\r18 shl 6 or \r19 shl 4 or \r10 shl 2 or \r21
		db	\r22 shl 6 or \r23 shl 4 or \r24 shl 2 or \r25
		db	\r26 shl 6 or \r27 shl 4 or \r28 shl 2 or \r29
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21=+r22=+r23=+r24=+r25=+r26=+r27=+r28=+r29=+r30 ,ar
	\{
			\flag equ	1
		match  a=+b,\r30
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1 shl 2 or \r2
 		db	\r3 shl 6 or \r4 shl 4 or \r5 shl 2 or \r6
		db	\r7 shl 6 or \r8 shl 4 or \r9 shl 2 or \r10
		db	\r11 shl 6 or \r12 shl 4 or \r13 shl 2 or \r14
		db	\r15 shl 6 or \r16 shl 4 or \r17 shl 2 or \r18
		db	\r19 shl 6 or \r20 shl 4 or \r21 shl 2 or \r22
		db	\r23 shl 6 or \r24 shl 4 or \r25 shl 2 or \r26
		db	\r27 shl 6 or \r28 shl 4 or \r29 shl 2 or \r30
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21=+r22=+r23=+r24=+r25=+r26=+r27=+r28=+r29=+r30=+r31 ,ar
	\{
			\flag equ	1
		match  a=+b,\r31
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
		db	\r1 shl 4 or \r2 shl 2 or \r3
 		db	\r4 shl 6 or \r5 shl 4 or \r6 shl 2 or \r7
		db	\r8 shl 6 or \r9 shl 4 or \r10 shl 2 or \r11
		db	\r12 shl 6 or \r13 shl 4 or \r14 shl 2 or \r15
		db	\r16 shl 6 or \r17 shl 4 or \r18 shl 2 or \r19
		db	\r20 shl 6 or \r21 shl 4 or \r22 shl 2 or \r23
		db	\r24 shl 6 or \r25 shl 4 or \r26 shl 2 or \r27
		db	\r28 shl 6 or \r29 shl 4 or \r30 shl 2 or \r31
		else
		end if
	\}
	match r1=+r2=+r3=+r4=+r5=+r6=+r7=+r8=+r9=+r10=+r11=+r12=+r13=+r14=+r15=+r16=+r17=+r18=+r19=+r20=+r21=+r22=+r23=+r24=+r25=+r26=+r27=+r28=+r29=+r30=+r31=+r32 ,ar
	\{
			\flag equ	1
		match  a=+b,\r32
		\\{
			 \\flag equ 0
		\\}
		if \flag eq  1
 		db	\r1 shl 6 or \r2 shl 4 or \r3 shl 2 or \r4
		db	\r5 shl 6 or \r6 shl 4 or \r7 shl 2 or \r8
		db	\r9 shl 6 or \r10 shl 4 or \r11 shl 2 or \r12
		db	\r13 shl 6 or \r14 shl 4 or \r15 shl 2 or \r16
		db	\r17 shl 6 or \r18 shl 4 or \r19 shl 2 or \r20
		db	\r21 shl 6 or \r22 shl 4 or \r23 shl 2 or \r24
		db	\r25 shl 6 or \r26 shl 4 or \r27 shl 2 or \r28
		db	\r29 shl 6 or \r30 shl 4 or \r31 shl 2 or \r32
		else
		end if
	\}
}


