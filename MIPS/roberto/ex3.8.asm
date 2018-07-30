#exercicio 3.8 swbas Roberto
#traduzir o seguinte código de C para assembly MIPS
# int a, i;
# int X[2048], y[256];
# i =0; a=0;
# while (i < 1024) {
#   a = a + x[i] + y [ (x[i] % 256 ]
#    i = i +1;
#}
##########
# Mapeamento das variáveis
# a = s0; i = s1; x = s2; y = s3;
##########
        la $s2, $x
        la $s3, $y
        add $s0, $s0, $0          # i <- 0;
        add $s1, $s1, $0          # a <- 0;


        addi $t0, $t0, 1024       # t0 <- 1024
comeco: stl $t1, $s0, $t0          # t1 <- 1 (se i < 1024) ou 0 (se i >= 1024) 
        beq $t1, $0, fim         # se t0 == falso, pula para o fim
        sll t2, s0, 2           # t2 <- i * 4
        add t2, t2, s2          # t2 <- t2 + &x
        lw t3, 0(t2)            # t3 <- x[i]
        andi t2, t3, 255        # t2 <- X[i] % 256
        sll t2, t2, 2           # t2 <- t2 * 4
        add t2, t2, s3          # t2 <- t2 + &y
        lw t4, 0(t2)            # t4 <- y[(x[i] % 256)]
        add s1, s1, t3          # a <- a + x[i]
        add s1, s1, t4          # a <- a + y[...]
        addi s0, s0, 1          # i = i + 1
        j comeco

fim:    nop    
        
