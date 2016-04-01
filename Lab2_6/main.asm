org 8000h
mov a, #74h
mov b, #0f0h
mov dptr, #1234h
mov r0, #78h
mov r1, #79h
mov r2, #7ah
mov r3, #7bh
mov r4, #7ch
mov r5, #7dh
mov r6, #7eh
mov r7, #7fh
mov 40h, #30h
mov 4eh, 40h
mov dptr, #0e000h
movx @dptr, a
sjmp $
end
