org 0000h
ljmp main
org 00f0h
main:
mov r7, #0
loop:
mov r6, #0
djnz r6, $

djnz r6, $
djnz r6, $
djnz r6, $
djnz r7, loop

cpl p1.0 
sjmp main

end
