# implementacao sem otimizacao exemplo 3.12 apostila

#int fun(int g, int h, int i , int j){
#    int f = 0;
#    
#    f = (g+h) - (i+j);
#    return (f*4);
#}

        la s0, g
        la s1, h
        la s2, i
        la s3, j

        move a0, s0
        move a1, s1
        move a2, s2
        move a3, s3
        jal fun
        move s4, v0

fun:    addiu sp, sp, -8    #aloca f na pilha
        sw $zero, 0(sp)        # f <- 0
        add t0, a0, a1
        add t1, a2, a3
        sub t0, t0, t1
        sw t0, 0(sp)
        lw t1, 0(sp)
        sll v0, t1, 2
        addiu sp, sp, 8
        jr ra
