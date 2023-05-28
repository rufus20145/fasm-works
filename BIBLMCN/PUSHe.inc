;1    УпряталиРегистры
;2    ВосстановилиРегистры
;3    УпрятатьРегистры
;4    ВостановитьРегистры
;5    CrPUSH                эквивалентно 1 и 3
;6    CrPOP                эквивалентно 2 и 4
;Находится                                'C:\FASM\BIBLMCN\PUSHe.inc'
;******************************************************************
;7  PUSHе               Маркировочное упрятывание. ПРИМЕР:  PUSHе  EBP,1
;8    POPe            Проверка на маркировочное упрятывание и, если хорошо,восстановление
;9    CrPUSHs
;10    CrPOPs
;11 CrPUSHе
;12    CrPOPe
;Находится                                'C:\FASM\BIBLMCN\PUSHREG\CrPUSHs.inc'
;******************************************************************
MACRO УпряталиРегистры     [string]        ;PUSH    string
{   common
    forward
    PUSH string
}
;*************************4***********
MACRO ВосстановилиРегистры [string]
{   common
    reverse
    POP string
}
;*************************4***********
;********************** 5  ***************
    MACRO УпрятатьРегистры [string]        ;PUSH    string
{   common
    forward
    PUSH string
}
;*********************** 6 *************************
MACRO ВостановитьРегистры [string]        ;POP    string
{   common
    reverse
    POP string
}
;********************** 7  ****************************
MACRO CrPUSH [string]        ;A C D B   нумерация регистров
{     common
    forward
    PUSH string
}
;************************ 8 ***************
MACRO CrPOP [string]                    ;POP    string
{    reverse
    POP string
}
;**********************