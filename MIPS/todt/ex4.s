        .data

T:        .word 6

vetor:  .space 24
msg:    .asciiz "Entre com "
msg2:   .asciiz " elementos do vetor\n"
msg3:   .asciiz "Insira número a ser buscado: "
msg4:   .asciiz " encontrado "
msg5:   .asciiz " vezes."
newl:   .asciiz "\n"


        .text
        .globl main


        #carrega endereços nos registradores
main:   la $t0, vetor
        la $t1, T
        lw $t1, 0($t1)
        

        # imprime mensagem inicial
        la $a0, msg
        li $v0, 4
        syscall
        
        move $a0, $t1
        li $v0, 1
        syscall
    
        la $a0, msg2
        li $v0, 4
        syscall

        # leitura dos valores
        move $t2, $t1           	#t2 = T
        addi $t2, $t2, -1
	sll $t2, $t2, 2			#t2 = T * 4
	add $t2, $t2, $t0		# t2 =  &string[T]	
loop1:  slt $t3, $t2, $t0           # loop1 armazena os valores
        bne $t3, $zero, fim_l1      # de trás para frente
                                    # no vetor
        li $v0, 5
        syscall

        sw $v0, 0($t2)
        
        addi $t2, $t2, -4
        j loop1 

        # Le N a ser buscado
fim_l1:
        la $a0, msg3
        li $v0, 4
        syscall

        li $v0, 5
        syscall
        
        move $t7, $v0

        la $a0, newl
        li $v0, 4
        syscall

        # loop de busca
        move $t2, $t1           	#t2 = T
        addi $t2, $t2, -1
	sll $t2, $t2, 2			#t2 = T * 4
	add $t2, $t2, $t0		# t2 =  &string[T]	
        add $t5, $zero, $zero       # t5 representa quantas vezes N 
                                    # será achado
loop2:  slt $t3, $t2, $t0 
        bne $t3, $zero, fim_l2
        
        lw $t4, 0($t2)
        sub $t6, $t7, $t4
        beq $t6, $zero, achou

        addi $t2, $t2, -4
        j loop2

achou:  addi $t5, $t5, 1  

        addi $t2, $t2, -4
        j loop2
        
fim_l2: move $a0, $t7
        li $v0, 1
        syscall

        la $a0, msg4
        li $v0, 4
        syscall

        move $a0, $t5
        li $v0, 1
        syscall

        la $a0, msg5
        li $v0, 4
        syscall
