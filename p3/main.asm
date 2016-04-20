clk equ p1.0
dina equ p1.1
dinb equ p1.2
clr164 equ p1.3

org 0000h
ljmp main
org 0100h

main:
mov sp,#60h
nop
clr clk
setb dinb
clr clr164
setb clr164
mov a,#05bh
mov r4,#08h
slchg:
rlc a
mov dina,c
setb clk
nop
clr clk
nop
djnz r4,slchg
sjmp $

end
