# fonte: 
# Michael S. Kirkpatrick
# https://w3.cs.jmu.edu/kirkpams
#
#
#
# add_nums.s
# Purpose:  Illustrates a MIPS equivalent of:
#
#  int p = 5;
#  int q = 10;
#  int r = 3;
#  
#  int add_nums (int a, int b, int c, int d)
#    {
#      /* These are local variables for add_nums */
#      int x = 1;
#      int y = 2;
#      int result;
#  
#      result = (a + b) * x - (c + d) * y;
#  
#      return result;
#    }
#  
#  int main (int argc, char ** argv)
#    {
#      /* These are local variables for main */
#      int s = 7;
#      int value;
#  
#      value = add_nums (p, q, r, s);
#  
#      return 0;
#    }

	.data
# global variables
p:	.word 5
q:	.word 10
r:	.word 3

	.text
# main function
main:
	# ignoring argc and argv
	# use $s0 for int s and $s1 for value
	addi $s0, $s0, 7
		
	# start setting up the arguments
	# add_nums (p, q, r, s)	
	# so p will go in $a0, etc.
	
	# load p
	la $t0, p		# &p
	lw $a0, 0($t0)		# *p
	
	# load q
	la $t0, q
	lw $a1, 0($t0)
	
	# load r
	la $t0, r
	lw $a2, 0($t0)
	
	# copy s into $a3
	add $a3, $zero, $s0
	
	jal add_nums
	# move return value from $v0 into value...$s1
	add $s1, $zero, $v0
	
	# exit program
	li $v0, 10
	syscall
	
	# now comes the add_nums procedure
add_nums:
	# use $s0 for x, $s1 for y, and $s2 for result
	# NOTE:  this conflicts with the use of $s0 and
	# $s1 in main...
	
	# prologue:  save the old $fp, and adjust the 
	# $sp accordingly.  to do this, we write $fp's
	# value to the word just below $sp.  then, we
	# change $fp to point to the address it just wrote
	# to.
	sw $fp, -4($sp)
	addi $fp, $sp, -4
	# now, we're going to change $sp to be 12 bytes
	# below $fp...this allocates space for 3 ints to save
	addi $sp, $fp, -12
	# now we can save the registers $s0, $s1, and $s2...
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	
	# x = 1
	addi $s0, $zero, 1
	# y = 2
	addi $s1, $zero, 2
	
	# $t0 = (a + b)
	add $t0, $a0, $a1
	# remember that $t0-$t9 are callER-save...so we
	# can clobber them at will
	# $t0 = (a + b) * x
	mul $t0, $t0, $s0
	
	# $t1 = (c + d)
	add $t1, $a2, $a3
	# $t1 = (c + d) * y
	mul $t1, $t1, $s1
	
	# result = $t0 - $t1
	sub $s2, $t0, $t1
	
	# function return procecure...
	# first, let's set the return value into $v0
	# we're returning result, which is in $s2
	add $v0, $zero, $s2
		
	# now we need to undo the prologue
	# first, that means restoring $s0-$s2
	lw $s2, 8($sp)
	lw $s1, 4($sp)
	lw $s0, 0($sp)
	# restore old stack pointer...pay close attention here...
	addi $sp, $fp, 4
	lw $fp, -4($sp)
	
	# $ra stores the return address that we want to get back to
	jr $ra
