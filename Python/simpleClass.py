#create a class
	#give it a global field name
	#give it a constructor __init__(self)
		#give it an instnace field state
	#give it a function to change the instance field
	#give it a function to change the global field

class Simple:
	name = "Bug"

	def __init__(self):
		self.state = "caterpiller"

	def metamorphisis(self):
		print "metamorphisis"
		self.state = "butterfly"

	def change(self):
		name = "insect"

x = Simple()
y = Simple()
print "x name =" + x.name
print "x state =" + x.state
print "y name =" + y.name
print "y state =" +y.state
y.metamorphisis()
x.change()
print "x name =" + x.name
print "x state =" + x.state
print "y name =" + y.name
print "y state =" +y.state

