#define SUB_QUESTION 2

org 0000h
ljmp main
org 0100h

#if SUB_QUESTION == 1

main:
mov a, #0ffh
clr c

mainloop:
call delay
rlc a
mov p1, a
sjmp mainloop

delay:
mov r7, #0
loop:
mov r6, #0
djnz r6, $
djnz r6, $
djnz r6, $
djnz r7, loop
ret

#elif SUB_QUESTION == 2

main:
jb p1.7,setled

clr p1.0
clr p1.1
clr p1.2
clr p1.3
clr p1.4
clr p1.5
clr p1.6
sjmp main

setled:
setb p1.0
setb p1.1
setb p1.2
setb p1.3
setb p1.4
setb p1.5
setb p1.6
sjmp main

#endif
end
