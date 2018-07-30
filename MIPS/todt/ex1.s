        .data

N:  	.word 100

        .text
        .globl main

main:   la $t0, N                   # t0 <- &N
        lw $t1, 0($t0)              # t1 <- N
        
        li $t0, 0                   # t0 <- 0 (i = 1)
        li $s0, 0                   # s0 <- 0 (soma = 0)
loop:   sub $t2, $t1, $t0           # t2 <- t1 - t0  (t2 = N - i)
        beq $t2, $zero, fim         # t2 == 0? fim : proxima instrução
        addi $t0, $t0, 1            # i++
        add $s0, $s0, $t0           # s0 <- s0 + t0 (soma = soma + i) 
        j loop

fim:    move $a0, $s0
        li $v0, 1
        syscall
