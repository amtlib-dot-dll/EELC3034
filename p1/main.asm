second equ 30h
count equ 31h

org 00h
ljmp start

org 0bh
ljmp int_t0

start:
mov second,#00h
mov count,#00h

mov dptr, #table
mov p0, #0
mov p2, #0
mov tmod, #0
mov th0,#(65536-50000)/256
mov tl0,#(65536-50000) mod 256
setb tr0
setb et0
setb ea

mov ie,#82h
ljmp $

int_t0:
mov th0,#(65536-50000)/256
mov tl0,#(65536-50000) mod 256
inc count
mov a,count
cjne a,#20,i2
mov count,#00h
inc second
mov a,second
cjne a,#60,i1
mov second,#00h
i1:
mov a,second
mov b,#10
div ab
movc a,@a+dptr
mov p0,a
mov a,b
movc a,@a+dptr
mov p2,a
i2:
reti

table:
db 3fh,06h,5bh,4fh,66h
db 6dh,7dh,07h,7fh,6fh

end
