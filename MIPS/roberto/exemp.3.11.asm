## exemplo 3.11 da apostila
# implementação de w = g(x,y,z);
# x = t0; y = t1; z = t2; w = s0
        move a0, t0
        move a1, t1
        move a2, t2
        jal g
        move s0, v0
        ...
g:      addiu sp, sp, -32
        sw ra, 12(sp)
        sw a0, 16(sp)
        sw a1, 20(sp)
        sw a2, 24(sp)
        ... 
        move v0, t3
        lw a2, 24(sp)
        lw a1, 20(sp)
        sw a0, 16(sp)
        sw ra, 12(sp)
        addiu sp, sp, 32

        jr ra
    
