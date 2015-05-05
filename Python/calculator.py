#lets make a program that functions as a calculator

#lets have it take in 3 arguments, 2 integers and 1 operator
	#the operators can be + - * /

#lets use what we know
	#create a function that takes as arguments 2 integers and 1 operator
	#use if statements to select which operation to perform
	#return an interger
def calculatorIF(one, two, operator):
	output = 0
	if (operator == '+'):
		output = one + two
	elif (operator == '-'):
		output = one - two
	elif (operator == '/'):
		output = one / two
	elif (operator == 'm'):
		output = one * two
	return output


#we need to validate the arguments first, they must be of the form int int {+ - * /}
import sys
print sys.argv[3]
if(len(sys.argv) == 4):
	if (type(int(sys.argv[1])) is int and type(int(sys.argv[2])) is int):
		if(sys.argv[3] == '+' or sys.argv[3] == '-' or sys.argv[3] == '/' or sys.argv[3] == 'm'):
			print calculatorIF(int(sys.argv[1]), int(sys.argv[2]), sys.argv[3])
			sys.exit()
		else: 
			print "invalid arguments: please type arguments of the form int int {m - + /}"
			sys.exit()
	else: 
		print "invalid arguments: please type arguments of the form int int {m - + /}"
		sys.exit()
else:
	print "invalid arguments: please type arguments of the form int int {m - + /}"
	sys.exit()
print "op"

