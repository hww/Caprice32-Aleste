;; (c) Copyright Kevin Thacker 2015-2016
;; This code is part of the Arnold emulator distribution.
;; This code is free to distribute without modification
;; this copyright header must be retained.
;;
;; NEEDS TESTING ON A REAL MACHINE

include "../lib/testdef.asm"

org &100
start:
kl_l_rom_disable equ &b909
kl_l_rom_enable equ &b906
kl_u_rom_enable equ &b900
kl_u_rom_disable equ &b903
kl_rom_select equ &b90f

ld hl,result_buffer
ld e,l
ld d,h
inc de
ld (hl),0
ld bc,&a700-&9001
ldir

ld a,2
call &bc0e
ld ix,tests
call run_tests
ret

tests:
;; have no idea why author testing CPC with Aleste mapper
;; who knows .... maybe he on the reverse engineering :)
;;DEFINE_TEST "CPC128 RAM (MAPMOD=0) (c0-ff) (7bxx)",aleste_ram_7c
;;DEFINE_TEST "CPC128 RAM (MAPMOD=0) (c0-ff) (7cxx)",aleste_ram_7d
;;DEFINE_TEST "CPC128 RAM (MAPMOD=0) (c0-ff) (7exx)",aleste_ram_7e
;;DEFINE_TEST "CPC128 RAM (MAPMOD=0) (c0-ff) (7fxx)",aleste_ram_7f
;DEFINE_TEST "Aleste RAM (MAPMOD=1) (MEM=0000) (7cxx)",aleste_ram_0000
DEFINE_TEST "Aleste RAM (MAPMOD=1) (MEM=4000) (7dxx)",aleste_ram_4000
;; DON'T DO IT FOR NEXT PAGE!!!! here is the test code
;;DEFINE_TEST "Aleste RAM (MAPMOD=1) (MEM=8000) (7exx)",aleste_ram_8000
;DEFINE_TEST "Aleste RAM (MAPMOD=1) (MEM=C000) (7fxx)",aleste_ram_c000
DEFINE_END_TEST

aleste_ram_7c:
	ld d,&7c
	jr aleste_ram

aleste_ram_7d:
	ld d,&7d
	jr aleste_ram

aleste_ram_7e:
	ld d,&7e
	jr aleste_ram

aleste_ram_7f:
	ld d,&7f
	jr aleste_ram

;; ================================================
;; single bank test function
;; arguments
;; d - is mapper port address 7c..7f 
;; ================================================
aleste_ram:


	push de
	call ram_init	;; put the page number at 1000H address of each RAM_[0..X][1000] block 
	pop de

	;; disable map mod
	ld bc,&fabf
	ld a,%1000	
	out (c),a

	di
	ld ix,result_buffer
	ld b,64
	xor a
ar1:
	push bc
	push af
	ld c,a
	;; skip 2
	and &7
	cp 2
	jr z,ar2
	;; cpc style 
	ld b,d
	ld a,c
	or %11000000
	out (c),a

	;; now read mapper and the memory
	
	call read_mapper
	;; read from ram
	call read_ram
	jr ar3

ar2:
	ld (ix+0),0
	inc ix
	inc ix
	ld (ix+0),0
	inc ix
	inc ix
	ld (ix+0),0
	inc ix
	inc ix
	ld (ix+0),0
	inc ix
	inc ix
	ld (ix+0),0
	inc ix
	inc ix
	ld (ix+0),0
	inc ix
	inc ix
	ld (ix+0),0
	inc ix
	inc ix
	ld (ix+0),0
	inc ix
	inc ix
	ld (ix+0),0
	inc ix
	inc ix

ar3:
	pop af
	inc a
	pop bc
	djnz ar1
	ld ix,result_buffer
	ld bc,&fabf
	ld a,%1000	;; disable map mod
	out (c),a

	ld bc,&7fc0
	out (c),c
	ei

	ld ix,result_buffer
	ld bc,8*64
	call simple_results
	ret

;; ========================================================
;; Aleste code here
;; ========================================================
;; test Aleste mapper page 0000
aleste_ram_0000:
	ld d,&7c
	jr aleste_ram2

;; test Aleste mapper page 4000
aleste_ram_4000:
	ld d,&7d
	jr aleste_ram2

;; test Aleste mapper page 8000
aleste_ram_8000:
	ld d,&7e
	jr aleste_ram2
	
;; test Aleste mapper page C0000
aleste_ram_c000:
	ld d,&7f
	jr aleste_ram2
	
;; test one page access with Aleste mapper
;; D is the mapper address
aleste_ram2:
	push de
	call ram_init	;; fill all the pages by it's number
	pop de

	ld ix,result_buffer

	di
	ld bc,&fabf
	ld a,%1100	;; enable mapper mod
	out (c),a
	
	;;;  iterate over all pages
	ld b,64		;; 64 pages of mapper 512KB
	xor a		;; A = 0,1,....,63
arm1:
	push bc
	push af
	ld b,d
	or %1100000
	out (c),a	;; page number to the mapper

	call read_mapper ;; read from mapper
	
	call read_ram ;; read from ram

	pop af
	pop bc
	
	inc a
	djnz arm1

	;; disable mapper now
	ld bc,&fabf
	ld a,%1000	
	out (c),a

	;; enable RAM_1 at 4000H
	ld bc,&7fc0
	out (c),c
	ei

	ld ix,result_buffer
	ld bc,64*8
	call simple_results
	ret

;; ------------------------------------------
;; Rad mapper's values
;; put them to IX pointer. Update IX += 8
;; MEM[IX+0] = MAPPER[7CXX]
;; MEM[IX+2] = MAPPER[7DXX]
;; MEM[IX+4] = MAPPER[7EXX]
;; MEM[IX+5] = MAPPER[7FXX]
;; IX+= 8
;; ------------------------------------------

read_mapper:
	;; read from mapper
	ld b,&7c
	in a,(c)
	ld (ix+0),a
	inc ix
	inc ix
	ld b,&7d
	in a,(c)
	ld (ix+0),a
	inc ix
	inc ix
	ld b,&7e
	in a,(c)
	ld (ix+0),a
	inc ix
	inc ix
	ld b,&7f
	in a,(c)
	ld (ix+0),a
	inc ix
	inc ix
	ret

;; ------------------------------------------
;; Rad control words from the memory pages
;; put them to IX pointer. Update IX += 8
;; MEM[IX+0] = MEM[1000]
;; MEM[IX+2] = MEM[5000]
;; MEM[IX+4] = MEM[9000]
;; MEM[IX+5] = MEM[D000]
;; IX+= 8
;; ------------------------------------------

read_ram:
	ld hl,&1000
	ld a,(hl)
	ld (ix+0),a
	inc ix
	inc ix
	ld hl,&5000
	ld a,(hl)
	ld (ix+0),a
	inc ix
	inc ix
	ld hl,&9000
	ld a,(hl)
	ld (ix+0),a
	inc ix
	inc ix
	ld hl,&d000
	ld a,(hl)
	ld (ix+0),a
	inc ix
	inc ix
	ret


;; ================================================
;; Out to 7FXX bits of register A
;; A[0..1] select the page RAM_4  RAM_5  RAM_6  RAM_7
;;          at the 4000-7FFF address space
;; A[4..2] select the 0..7 bank (does not effect at CPC128)  
;; 7FXX =	1	1	a4	a3	a2	1	a1	a0
;;          |   |	|   |   |   |   |   |
;;          |   |	|   |   |   +---+---+-- Ram Configure
;;			|	|	|	|	|			allow to select one of next 
;;			|	|	|	|	|			configurations
;;          |   |	|   |   |               -------------------------------------------------------------------
;;			|	|	|	|	|			 -Address-     0      1      2      3      4      5      6      7
;;			|	|	|	|	|			 0000-3FFF   RAM_0  RAM_0  RAM_4  RAM_0  RAM_0  RAM_0  RAM_0  RAM_0
;;			|	|	|	|	|			 4000-7FFF   RAM_1  RAM_1  RAM_5  RAM_3  RAM_4  RAM_5  RAM_6  RAM_7
;;			|	|	|	|	|			 8000-BFFF   RAM_2  RAM_2  RAM_6  RAM_2  RAM_2  RAM_2  RAM_2  RAM_2
;;			|	|	|	|	|			 C000-FFFF   RAM_3  RAM_7  RAM_7  RAM_7  RAM_3  RAM_3  RAM_3  RAM_3
;;          |   |	|   |   |
;;          |   |	+---+---+-------------- Additional 64K-512K memory selection 
;;          |   |	                        bank number (0..7); always 0 on an unexpanded CPC6128, 0-7 on
;;          |   |
;;          |   |
;;          |   |
;;          |   |
;;          |   |
;;          +---+-------------------------- RAM Memory Management
 
;; ================================================

ram_sel:
	push bc
	push af
	push af
	and %11100  ;;	0	0	0	a4	a3	a2	0	0
	add a,a		;;	0	0	a4	a3	a2	0	0	0
	ld c,a
	pop af
	and &3		;;	0	0	0	0	0	0	a1	a0
	add a,4		;;	0	0	0	0	0	1	a1	a0
	or c		;;	0	0	a4	a3	a2	1	a1	a0	
	or &c0		;;	1	1	a4	a3	a2	1	a1	a0
	ld b,&7f
	out (c),a
	pop af
	pop bc
	ret

	;; -------------------------------------------
	;; at every RAM page + 1000H put the number 
	;; of this page
	;; RAM_0[1000] = 1
	;; RAM_1[1000] = 2
	;; ................
	;; RAM_3[1000] = 4
	;; RAM_5[1000] = 5
	;; ................ etc
	
ram_init:
	ld hl,&5000
;	ld b,32			;; Original test! 32 pages
;	ld a,31			;; Original test! RAM_5 BANK_6	
	ld b,4			;; Aleste supports only CPC128
	ld a,0			;; Aleste supports only CPC128
ri1:
	call ram_sel	;; RAM_5 BANK_6 at 4000-7FFF
	push af
	add a,5
	ld (hl),a		;; MEM[50000] = a + 5
	pop af
	
	
	;; copy this code to target page
	;;push hl
	;;push de
	;;push bc
	;;ld hl, &9001
	;;ld de, &5001
	;;ld bc, &1FFF
	;;ldir	
	;;pop bc
	;;pop de
	;;pop hl
	
	dec a			;; a = 30, 2F, 2E 
	djnz ri1
	
	
	;; enable RAM_1 at 4000-7FFF
	;; so the map will be RAM_0,RAM_1,RAM_2,RAM3
	ld bc,&7fc0
	out (c),c		;; RAM_1 at 4000-7FFF
	
	
	;; now do main ram
	ld hl,&1000
	ld (hl),&01		;; MEM[1000] = 1

	ld hl,&5000
	ld (hl),&02		;; MEM[5000] = 2

	ld hl,&9000
	ld (hl),&03		;; MEM[9000] = 3

	ld hl,&d000
	ld (hl),&04		;; MEM[D000] = 4

	ld c,1
	call kl_rom_select
	call kl_l_rom_enable
	call kl_u_rom_enable
	ld a,(&1000)
	ld (lowrom_byte),a
	ld a,(&d000)
	ld (highrom_byte),a
	call kl_u_rom_disable
	call kl_l_rom_disable
	ret
	
	;; for switch to Aleste mapper will be safer to 
	;; copy this code to all pages (was better way without
	;; bios. I do not remember

	push hl
	push de
	push bc

	ld hl, &9001
	ld de, &1001
	ld bc, result_buffer - start
	ldir			;; to RAM_0

	ld hl, &9001	;; origin
	ld de, &5001
	ld bc, result_buffer - start
	ldir			;; to RAM_1

	ld hl, &9001	;; origin
	ld de, &d001	
	ld bc, result_buffer - start
	ldir			;; to RAM_3

	pop bc
	pop de
	pop hl
	ret

lowrom_byte:
	defb 0
highrom_byte:
	defb 0

rom_byte:
	defb 0

test_config:
	defw 0

;;-----------------------------------------------------

include "../lib/mem.asm"
include "../lib/report.asm"
include "../lib/test.asm"
include "../lib/outputmsg.asm"
include "../lib/outputhex.asm"
include "../lib/output.asm"
include "../lib/hw/psg.asm"
;; firmware based output
include "../lib/fw/output.asm"
include "../lib/int.asm"

result_buffer: equ $



end start
