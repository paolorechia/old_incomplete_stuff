	.data

str_ent: .space 20
eh_p:	.asciiz "Eh palindromo"
nao_p:	.asciiz "Nao eh palindromo"


	.text
	.globl main

main:
	la $a0, str_ent		# endereco onde salvar string a ser lida
	li $a1, 20		# tamanho maximo da string
	li $v0, 8		
	syscall			# le string (syscall(8))
	
	li $t5, 0 		# i = 0
	la $t0, str_ent		# t0 <- & str_ent
	lb $t1, 0($t0)		# t1 <- str_ent[0]
	
	# imprime string lida
	move $a0, $t0
	li $v0, 4
	syscall
	###
				# loop para contar tamanho da string
loop:	beq $t1, $zero, fim	# se t1 == 0, sai do loop
	addi $t5, $t5, 1	# i++
	add $t2, $t5, $t0	# t2 <- &str_ent + i
	lb $t1, 0($t2)		# t1 <- str_ent[i]
	
	j loop
fim:
	
				# t1 == 0 nesse ponto
				# t5 = tamanho da string
				# t0 = & str_ent
				
	addi $t5, $t5, -2	# volta o i para o ultimo caracter antes de '\0'
	la $t4, str_ent		# t4 <- &str_ent	
	
	
loop2:	slt $t8, $t5, $zero	# sai quando t5 == -1
	bne $t8, $zero, fim2 
	add $t2, $t5, $t0	# t2 = &str_ent + i (começa pelo último elemento)
	add $t3, $t4, $t0	# t3 = &str_ent + j (começa pelo primeiro)
	lb $t1, 0($t2)		# t1 <- str_ent[i]
	lb $t6, 0($t3)		# t6 <- str_ent[j]
	sub $t7, $t1, $t6	# t7 = t1 - t6
	bne $t7, $zero, fim3	# se t7 != 0, entao nao eh palindromo
	addi $t5, $t5, -1	# i = i - 1
	addi $t4, $t4, 1	# j = j + 1
	j loop2
	
fim2:	la $a0, eh_p
	li $v0, 4
	syscall
	li $v0, 10
	syscall

fim3:	la $a0, nao_p
	li $v0, 4
	syscall
	
