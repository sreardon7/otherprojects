#lets make a recursive function
	#recursion is when a function that calls itself
	#we need to set up a base case so that the function eventually terminates
	#then we set up the recursive case

	#lets make a power function
	#we need to raise a base by a power
	#we can do this by multiply the base by the recursive function called on itself with the power reduced by 1
	#note this isnt the best way to compute power
	#we need to make sure that the recursion eventually terminates, beware of infinite loop


#be sure to test the function!!

def simpleRecursivePowerFunction(base, power):
	if (power == 1):
		return base
	elif (power == 0):
		return 1
	else:
		return base * simpleRecursivePowerFunction(base, power-1)

print(simpleRecursivePowerFunction(2, 0))
print(simpleRecursivePowerFunction(2, 1))
print(simpleRecursivePowerFunction(2, 2))
print(simpleRecursivePowerFunction(2, 3))
print(simpleRecursivePowerFunction(2, 4))
print(simpleRecursivePowerFunction(2, 5))
print(simpleRecursivePowerFunction(2, 6))
print(simpleRecursivePowerFunction(2, 7))
print(simpleRecursivePowerFunction(2, 8))
print(simpleRecursivePowerFunction(2, 9))
print(simpleRecursivePowerFunction(2, 10))
print(simpleRecursivePowerFunction(2, 20))
print(simpleRecursivePowerFunction(2, 30))
