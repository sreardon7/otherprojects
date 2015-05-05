#prints all prime numbers 1-k
import sys
x = 0
k = int(sys.argv[1])
 
for i in range(1, k):
	y = False
	for j in range(2, i-1):
		if (i % j) == 0:
			y = True
	if y == False:
		print(i)

