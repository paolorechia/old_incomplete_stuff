        .data
vetor:	.space 400

N1:     .word 2
N2:     .word 4

        .text
        .globl main

main: 		la $t0, vetor
		la $t1, N1
		la $t2, N2

		lw $t1, 0($t1)
		lw $t2, 0($t2)
		
		beq $t1, $zero, fim_0
		beq $t2, $zero, fim_0

		sub $t7, $t2, $t1
		slt $t8, $t7, $zero
		bne $t8, $zero, fim_1

		li $t4, 1
		li $t5, 1
		
		li $t3, 1
		
		sw $t4, 0($t0)
		sw $t5, 4($t0)

		sub $t7, $t2, $t3
		slt $t8, $t7, $zero
		bne $t8, $zero, pula_loop

loop:		sub $t7, $t2, $t3
		beq $t7, $zero, sai_loop

		add $t6, $t5, $t4
		move $t4, $t5
		move $t5, $t6

		addi $t3, $t3, 1
		sll $t8, $t3, 2
		add $t8, $t0, $t8
		sw $t5, 0($t8)
		
		j loop
	
sai_loop:	nop
pula_loop: 	move $t3, $t1
		addi $t3, $t3, -1

loop2:		sub $t7, $t2, $t3
		beq $t7, $zero, sai_loop2


		sll $t8, $t3, 2
		add $t5, $t0, $t8
		lw $t4, 0($t5)
		
		add $s0, $s0, $t4

		addi $t3, $t3, 1
		j loop2

sai_loop2:	move $a0, $s0
		li $v0, 1
		syscall

		li $v0, 10
		syscall

fim_0:		li $a0, 0
		li $v0, 1
		syscall

		li $v0, 10
		syscall

fim_1:		li $a0, -1
		li $v0, 1
		syscall

		li $v0, 10
		syscall


