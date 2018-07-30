    .data

N:  .word 20
spc:.asciiz "\n"
str:.ascii "Estou somando: "
    .text
    .globl main

main:   la $t0, N                   # t0 <- &N
        lw $t1, 0($t0)              # t1 <- N
        
        li $t0, 1                   # i = 0
        li $s0, 0                   # soma = 0
        li $t2, 2                   # t2 <- 2
        li $t3, 8                   # t3 <- 8

loop:   sub $t4, $t1, $t0           # t4 <- N - i
        beq $t4, $zero, fim         
	
        div $t0, $t2                # lo = i / 2; hi = i % 2
        mfhi $t4                    # t4 <- (i % 2)
        bne $t4, $zero, somar       # se resto != 0, entao impar -> somar

        div $t0, $t3                # lo = i / 8; hi = i % 8
        mfhi $t4                    # t4 <- (i % 8)
        beq $t4, $zero, somar       # se resto 0, multiplo de 8 -> somar

                                    # se nao for impar nem multiplo 8
        addi $t0, $t0, 1            # i++
        j loop                      # pula pra próxima iteração do loop

somar:  
	la $a0, str
	li $v0, 4
	syscall
	
	move $a0, $t0
	li $v0, 1
	syscall

	la $a0, spc
	li $v0, 4
	syscall
	
        add $s0, $s0, $t0           # s0 <- s0 + t0
        addi $t0, $t0, 1            # i++
        j loop                      

fim:    move $a0, $s0               # a0 <- s0 (soma)
        li $v0, 1
        syscall                     # syscall(1) = print integer
