## computer organization, hennessy, exercises
# 2.1
addi $t0, $zero, 1
addi $t1, $zero, 2
addi $t2, $zero, 3
addi $t3, $zero, 4

sub $t0, $t1, $t2
subi $t3, $t2, 5
add $t0, $t1, $t3

#2.2
addi $t0, $zero, 1
addi $t1, $zero, 2
addi $t2, $zero, 3
addi $t3, $zero, 4

sub $t0, $t1, $t0
subi $t2, $t2, 2
add $t0, $t3, $t2

#2.3
addi $t0, $zero, 1
addi $t1, $zero, 2
addi $t2, $zero, 3
addi $t3, $zero, 4

sub $t0, $zero, $t0
sub $t0, $t0, $t1
sub $t0, $zero, $t0
sub $t0, $t0, 5
add $t0, $t1, $t0

#2.4
sub $t0, $zero, $s1 ## -g
lw $t1, 16($s6) ## load A[4] to $t1
sub  $s0, $t0, $t1 ## f = -g -A[4]
sub $t0, $s3, $s4 ## $t0 = i - j
sll $t0, $t0, 2 ## $t0 * 4
add $t1, $t0, $s6 ## $t1 = (i - j) + base address of A
lw $t0, 0($t1) ## load A[i -j]
sw $t0, 32($7) ## B[8] = A[i-j]

#2.5


