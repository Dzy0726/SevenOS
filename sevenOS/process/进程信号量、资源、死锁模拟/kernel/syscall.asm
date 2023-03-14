
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                               syscall.asm
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                                                     Forrest Yu, 2005
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

%include "sconst.inc"

_NR_get_ticks       equ 0 ; 要跟 global.c 中 sys_call_table 的定义相对应！
_NR_apply_resrc     equ 1
_NR_print_resrc     equ 2
_NR_release_resrc   equ 3
INT_VECTOR_SYS_CALL equ 0x90

; 导出符号
global	get_ticks
global  apply_resrc
global  print_resrc
global  release_resrc

bits 32
[section .text]

; ====================================================================
;                              get_ticks
; ====================================================================
get_ticks:
	mov	eax, _NR_get_ticks
	int	INT_VECTOR_SYS_CALL
	ret

; ====================================================================
;                              apply_resrc
; ====================================================================
apply_resrc:
        mov	eax, _NR_apply_resrc
        mov    ebx,[esp+4]
	int	INT_VECTOR_SYS_CALL
	ret

; ====================================================================
;                              print_resrc
; ====================================================================
print_resrc:
        mov	eax,_NR_print_resrc
	int	INT_VECTOR_SYS_CALL
	ret
	
; ====================================================================
;                              release_resrc
; ====================================================================
release_resrc:
        mov	eax, _NR_release_resrc
        mov    ebx,[esp+4]
	int	INT_VECTOR_SYS_CALL
	ret
