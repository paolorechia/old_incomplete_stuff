#funcoes
#exercicio 16
#apostila

#int fun (int a, int b, int c, int d, int e, int f);
#    ...
#    int a, p, q, z, w, v[N];
#    ...
#    x = fun(16*a, z*w, p^q, (z=v[3], v[3*z], z-2);

        la s0, a            # programa principal
        la s1, b            # inicializacao das variaveis
        la s2, c            # antes da chamada da funcao
        la s3, d
        la s4, e
        la s5, f    
        la s6, x

        ...
        # preparar os argumentos

        move a0, s0         
        move a1, s1
        move a2, s2
        move a3, s3

        addi sp, sp -8      #aloca espaco na pilha para args 5 e 6
        sw s4, 0(sp)        # 0(sp) <- e
        sw s5, 4(sp)        # 4(sp) <- f

        jal fun             # pula para fun e joga PC+4 em ra
        move s6, v0

fun:    lw t0, 0(sp)        # t0 = e
        lw t1, 4(sp)        # t1 = f
        addi sp, sp, 8      # desaloca args 5 e 6
        
        addi sp, sp -(20 + N * 4) # aloca espaco para as variaveis locais
        ...
        lw t0, 0(sp)        # t0 = a
        sll a0, t0, 4       # a0 = a * 16

        lw t0 12(sp)        # t0 = z
        lw t1 16(sp)        # t1 = w
        mult t0, t1
        mflo a1, lo         # a1 = z*w

        lw t1 4(sp)         # t1 = p
        lw t2 8(sp)         # t2 = q
        or a2, t1, t2       # a2 = p^q

        lw t1 20(sp)        # t1 = &v
        addi t2, $zero, 3   # t2 = 3
        sll t3, t2, 2
        add t3, t2, t1      # t3 <- &v + 12 
        lw a3, 0(t2)        # a3 = <- v[3] 
        sw a3, 12(sp)       # z <- a3
        
        mult a3, t2         # z * 3
        mflo t3             # t3 <- z * 3
        add t3, t3, t1      # t3 <- t3 + t1
        lw t2, 0(t3)        # t2 <- v[3*z]
        
        addi t1, a3, -2     # t1 <- z - 2
        
        ...
        add sp, sp, -12    #aloca espaco para empilhar ra e args
        sw t2, 0(sp)        # 0(sp) <- v[3*z]
        sw t1, 4(sp)        # 4(sp) <- z - 2
        sw ra, 8(sp)        # 8(sp) <- ra
        jal fun
        ...
        addi sp, sp (20 + N * 4) #desaloca as var locais desse nivel

        # como os args 5 e 6 sao desalocados no inicio da funcao
        # sobrou apenas uma pilha de ra
         
        lw ra, 0(sp)    # carrega o ultimo ra salvo
        addi sp, sp, 4  # ajusta sp para o proximo ra
        jr ra           # pula para o ra salvo
