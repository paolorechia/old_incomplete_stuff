	.data

str_ent: .space 20
eh_p:	.asciiz "Eh palindromo"
nao_p:	.asciiz "Nao eh palindromo"


	.text
	.globl main


main:	la $a0, str_ent		# endereco onde salvar string a ser lida
	li $a1, 20		# tamanho maximo da string
	li $v0, 8		
	syscall			# syscall(8) - leitura de string
	
	la $t0, str_ent		# t0 <- &str_ent
	lb $t1, 0($t0)		# t1 <- str_ent[0]
	
				# loop para contar tamanho da string
loop:	beq $t1, $zero, fim	# se t1 == 0, sai do loop
	addi $t0, $t0, 1	# t0++ (t0 == endereço == ponteiro)
	lb $t1, 0($t0)		# t1 <- *t0 (pega o valor apontado por t0, no caso, um caracter)
	
	j loop
				# a string lida está no formato: "string\n\0"
				# nesse ponto, t0 aponta para o '\0' da string
				
fim:	addi $t0, $t0, -2	# agora t0 aponta para última letra lida (antes do \n) 
	la $t1, str_ent		# t1 <- &str_ent 
	
	
loop2:	slt $t5, $t0, $t1	# seta t5 quando os ponteiros cruzarem
	bne $t5, $zero, fim2	# sai do loop quando t5 == 1
	
	lb $t2, 0($t0)		# t2 <- *t0
	lb $t3, 0($t1)		# t3 <- *t1
	
	sub $t4, $t2, $t3	# t4 <- t2 - t3
	bne $t4, $zero, fim3	# se t4 != 0, entao nao eh palindromo
	
	addi $t0, $t0, -1	# t0--
	addi $t1, $t1, 1	# t1++
	
	j loop2
	
fim2:	la $a0, eh_p
	li $v0, 4
	syscall			# syscall(4) - impressao de string
	li $v0, 10
	syscall			# syscall(10) - termino do programa

fim3:	la $a0, nao_p
	li $v0, 4
	syscall			# syscall(4) - impressao de string
