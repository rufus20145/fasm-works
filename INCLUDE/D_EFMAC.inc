; Macroinstructions for defining procedures
;	proc					; 1
;	prologuedef				; 2
;	epiloguedef				; 3
;	define@proc				; 4
;	defargs@proc			; 5
;	deflocal@proc			; 6
;	label					; 7 структура
;	initlocal@proc			; 8
;	endp					; 9
;	local					; 10
;1 *******************************
macro proc [args]			; define procedure
 { common
    match name params, args>
    \{ define@proc name,<params \} }
;1 *******************************
prologue@proc equ prologuedef
;2 *******************************
macro prologuedef procname,flag,parmbytes,localbytes,reglist
 { local loc
   loc = (localbytes+3) and (not 3)
   parmbase@proc equ ebp+8
   localbase@proc equ ebp-loc
   if parmbytes | localbytes
    push ebp
    mov ebp,esp
    if localbytes
     sub esp,loc
    end if
   end if
   irps reg, reglist \{ push reg \} }
;2 *******************************
epilogue@proc equ epiloguedef
;3 *******************************
macro epiloguedef procname,flag,parmbytes,localbytes,reglist
 { irps reg, reglist \{ reverse pop reg \}
   if parmbytes | localbytes
    leave
   end if
   if flag and 10000b
    retn
   else
    retn parmbytes
   end if }
;3 *******************************
close@proc equ
;4 *******************************
macro define@proc name,statement
 { local params,flag,regs,parmbytes,localbytes,current
   if used name
   name:
   match =stdcall args, statement \{ params equ args
				     flag = 11b \}
   match =stdcall, statement \{ params equ
				flag = 11b \}
   match =c args, statement \{ params equ args
			       flag = 10001b \}
   match =c, statement \{ params equ
			  flag = 10001b \}
   match =params, params \{ params equ statement
			    flag = 0 \}
   match =uses reglist=,args, params \{ regs equ reglist
					params equ args \}
   match =regs =uses reglist, regs params \{ regs equ reglist
					     params equ \}
   match =regs, regs \{ regs equ \}
   match prologue:reglist, prologue@proc:<regs> \{ prologue name,flag,parmbytes,localbytes,reglist \}
   virtual at parmbase@proc
   match =,args, params \{ defargs@proc args \}
   match =args@proc args, args@proc params \{ defargs@proc args \}
   parmbytes = $-(parmbase@proc)
   end virtual
   name # % = parmbytes/4
   all@vars equ
   current = 0
   macro locals
   \{ virtual at localbase@proc+current
      macro label def \\{ match . type,def> \\\{ deflocal@proc .,label,<type \\\} \\}
      struc db [val] \\{ \common deflocal@proc .,db,val \\}
      struc du [val] \\{ \common deflocal@proc .,du,val \\}
      struc dw [val] \\{ \common deflocal@proc .,dw,val \\}
      struc dp [val] \\{ \common deflocal@proc .,dp,val \\}
      struc dd [val] \\{ \common deflocal@proc .,dd,val \\}
      struc dt [val] \\{ \common deflocal@proc .,dt,val \\}
      struc dq [val] \\{ \common deflocal@proc .,dq,val \\}
      struc rb cnt \\{ deflocal@proc .,rb cnt, \\}
      struc rw cnt \\{ deflocal@proc .,rw cnt, \\}
      struc rp cnt \\{ deflocal@proc .,rp cnt, \\}
      struc rd cnt \\{ deflocal@proc .,rd cnt, \\}
      struc rt cnt \\{ deflocal@proc .,rt cnt, \\}
      struc rq cnt \\{ deflocal@proc .,rq cnt, \\} \}
   macro endl
   \{ purge label
      restruc db,du,dw,dp,dd,dt,dq
      restruc rb,rw,rp,rd,rt,rq
      current = $-(localbase@proc)
      end virtual \}
   macro ret operand
   \{ match any, operand \\{ retn operand \\}
      match , operand \\{ match epilogue:reglist, epilogue@proc:<regs> \\\{ epilogue name,flag,parmbytes,localbytes,reglist \\\} \\} \}
   macro finish@proc
   \{ localbytes = current
      match close:reglist, close@proc:<regs> \\{ close name,flag,parmbytes,localbytes,reglist \\}
      end if \} }
;4 *******************************
;5 *******************************
macro defargs@proc [arg]
 { common
    if ~ arg eq
   forward
     local ..arg,current@arg
     match argname:type, arg
      \{ current@arg equ argname
	 label ..arg type
	 argname equ ..arg
	 if dqword eq type
	   dd ?,?,?,?
	 else if tbyte eq type
	   dd ?,?,?
	 else if qword eq type | pword eq type
	   dd ?,?
	 else
	   dd ?
	 end if \}
     match =current@arg,current@arg
      \{ current@arg equ arg
	 arg equ ..arg
	 ..arg dd ? \}
   common
     args@proc equ current@arg
   forward
     restore current@arg
   common
    end if }
;5 *******************************
;6 *******************************
macro deflocal@proc name,def,[val] { name def val }
;6 *******************************
;6 *******************************
macro deflocal@proc name,def,[val]
 { common
    match vars, all@vars \{ all@vars equ all@vars, \}
    all@vars equ all@vars name
   forward
    local ..var,..tmp
    ..var def val
    match =?, val \{ ..tmp equ \}
    match any =?, val \{ ..tmp equ \}
    match any (=?), val \{ ..tmp equ \}
    match =label, def \{ ..tmp equ \}
    match tmp : value, ..tmp : val
     \{ tmp: end virtual
	initlocal@proc ..var,def value
	virtual at tmp\}
   common
    match first rest, ..var, \{ name equ first \} }
;6 *******************************
;7 *******************************
struc label type { label . type }
;7 *******************************
;8 *******************************
macro initlocal@proc name,def
 { virtual at name
    def
    size@initlocal = $ - name
   end virtual
   position@initlocal = 0
   while size@initlocal > position@initlocal
    virtual at name
     def
     if size@initlocal - position@initlocal < 2
      current@initlocal = 1
      load byte@initlocal byte from name+position@initlocal
     else if size@initlocal - position@initlocal < 4
      current@initlocal = 2
      load word@initlocal word from name+position@initlocal
     else
      current@initlocal = 4
      load dword@initlocal dword from name+position@initlocal
     end if
    end virtual
    if current@initlocal = 1
     mov byte [name+position@initlocal],byte@initlocal
    else if current@initlocal = 2
     mov word [name+position@initlocal],word@initlocal
    else
     mov dword [name+position@initlocal],dword@initlocal
    end if
    position@initlocal = position@initlocal + current@initlocal
   end while }
;8 *******************************
;9 *******************************
macro endp
 { purge ret,locals,endl
   finish@proc
   purge finish@proc
   restore regs@proc
   match all,args@proc \{ restore all \}
   restore args@proc
   match all,all@vars \{ restore all \} }
;9 *******************************
;10 *******************************
macro local [var]
 { common
    locals
   forward done@local equ
    match varname[count]:vartype, var
    \{ match =BYTE, vartype \\{ varname rb count
				restore done@local \\}
       match =WORD, vartype \\{ varname rw count
				restore done@local \\}
       match =DWORD, vartype \\{ varname rd count
				 restore done@local \\}
       match =PWORD, vartype \\{ varname rp count
				 restore done@local \\}
       match =QWORD, vartype \\{ varname rq count
				 restore done@local \\}
       match =TBYTE, vartype \\{ varname rt count
				 restore done@local \\}
       match =DQWORD, vartype \\{ label varname dqword
				  rq count+count
				  restore done@local \\}
       match , done@local \\{ virtual
			       varname vartype
			      end virtual
			      rb count*sizeof.\#vartype
			      restore done@local \\} \}
    match :varname:vartype, done@local:var
    \{ match =BYTE, vartype \\{ varname db ?
				restore done@local \\}
       match =WORD, vartype \\{ varname dw ?
				restore done@local \\}
       match =DWORD, vartype \\{ varname dd ?
				 restore done@local \\}
       match =PWORD, vartype \\{ varname dp ?
				 restore done@local \\}
       match =QWORD, vartype \\{ varname dq ?
				 restore done@local \\}
       match =TBYTE, vartype \\{ varname dt ?
				 restore done@local \\}
       match =DQWORD, vartype \\{ label varname dqword
				  dq ?,?
				  restore done@local \\}
       match , done@local \\{ varname vartype
			      restore done@local \\} \}
    match ,done@local
    \{ var
       restore done@local \}
   common
    endl }
;10 *******************************