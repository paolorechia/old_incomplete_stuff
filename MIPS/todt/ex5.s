		.data

string: 	.asciiz "Esta eh uma string de teste"
substr:		.asciiz "str"
msg_achou:	.asciiz "Substring achada no endereco: "
msg_n_achou:	.asciiz "Substring nao encontrada"
		.text
		.globl main

main:		la $t0, string
		la $t1, substr	
		
		lb $t5, 0($t0)
		lb $t6, 0($t1)	
		
loop1:		beq $t5, $zero, n_achou	
		
		sub $t3, $t6, $t5
		beq $t3, $zero, prim_igual
		
		addi $t0, $t0, 1
		lb $t5, 0($t0)
		
		j loop1

prim_igual:	move $t2, $t0
		move $t3, $t1

loop2:		addi $t2, $t2, 1
		addi $t3, $t3, 1
			
		lb $t6, 0($t3)	
		beq $t6, $zero, achou
		lb $t5, 0($t2)
		sub $t4, $t6, $t5
		beq $t4, $zero, loop2

		addi $t0, $t0, 1
	
		lb $t5, 0($t0)
		lb $t6, 0($t1)	

		j loop1


achou:		la $a0, msg_achou
		li $v0, 4
		syscall

		move $a0, $t2
		li $v0, 1
		syscall
		
		li $v0, 10
		syscall
		
n_achou: 	la $a0, msg_n_achou
		li $v0, 4
		syscall
