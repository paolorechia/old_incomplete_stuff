# void main(void) { // fatorial iterativo

#    int i,j;
	.data			# area de dados
vi:	.word 1			# aloca espaco para variaveis globais
vj:	.word 1			# apenas como exemplo...
	
resp:	.asciiz "fatorial de 5 = "	# constante tipo string
	
	.text			# area de código
	.globl main		# define main como nome global
main:

#       j=1;
	addi $t1, $zero, 1
	
#       for(i=1; i <= n; i++)
	addi $t4, $zero, 1

for:	slti $t7,$t4,6		# n < 6    fat(5)
	beq $t7,$zero,fimfor

#       j = j*i;
	mult $t1,$t4
	mflo $t4

	addi $t4, $t4, 1

	j for

fimfor:	li $v0, 4		# imprime resposta
	la $a0, resp		# syscall(4) = imprime string
	syscall

	li $v0, 1		# imprime inteiro
	move $a0, $t1		# syscall(1) = imprime inteiro
	syscall
	
#    return(0);
	li $v0, 10		# termina programa
	syscall			# syscall(10) = termina programa
	
# }
