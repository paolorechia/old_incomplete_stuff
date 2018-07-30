#x = f(a, b*c, d=(e+f)*c, fib(d), d/2, a=5, d-a)

        la s0, a
        la s1, b
        la s2, c
        la s3, d
        la s4, e
        la s5, f
        la s6, x


        add t0, s4, s5          #t0 <- e + f        
        mult t0, s2             #lo <- (e+f) * c
        mflo s3                 #s3 <- d modificado 

        move a0, s3             #a0 <- d
        jal fib                 #pula para fib
        move a3, v0             #a3 <- retorno de fib

        move a2, s3             #a2 <- d
         
        move a0, s0             #a0 <- a

        mult s1, s2             #lo <- b*c 
        mflo a1                 #a1 <- b*c

        addi sp, sp, -12        # espaco para args 5,6,7
        sra t0, s3, 1           # t0 <- d/2
        sw t0, 0(sp)            # salva arg 5

        li s0, 5                # a <- 5
        sw s0, 4(sp)            # salva arg 6
        
        sub t0, s3, s0          # t0 <- d - a
        sw t0, 8(sp)

        jal f

        move s6, v0

        addi sp, sp, 12
