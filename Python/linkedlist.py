#lets make a class for a data structure
	#this one is called a linked list
	#we can use a linked list to store and traverse nodes
	#a node might be a specific entry in a data store
	#or it could be something like information about a phoneme

	#first lets make the node
		#a node only needs to have a constructor (__init__(self, data)) method
		#the data is what is inside of the node, it could be a name, and u can put other stuff into a node too
		#but this is a simple impeplementation
		#it also has a nextNode

	#now lets make the linked list itself.
		#let the constructer take an optional head, which we can set at initialization

		#now lets make a insert method, it takes on node
			#we want it to insert at the begining of the list, so we will need to replace the head
			#then set the nextNode of our node to the previous head
			# ** check to make sure it works!

		#make a size! use a while loop to count the nodes

		#lets also print all the data in order

		#what advantantage do we get by replacing the head of our list with the inserted node,
		#what if we replaced the last member of the list, the tail?
		
class linkedList:
	def __init__(self, head = None):
		self.head = head
	def insert(self, node):
		if self.head == node:
			return
		else:
			node.nextNode = self.head
			self.head = node

	def search(self, LL, name):
		if name == LL.head.name:
			return True
		elif LL.head.nextNode != None:
			return self.search(linkedList(LL.head.nextNode), name)
		else: 
			return False
	def size(self):
		current = self.head
		size = 0
		while current != None:
			size += 1
			current = current.nextNode
		return size

class node:
	def __init__(self, name):
		self.name = name
		self.nextNode = None



x = linkedList()
x.insert(node("aids"))
x.insert(node("faids"))
x.insert(node("jades"))

print x.search(x, "frog")
print x.search(x, "jades")
print x.search(x, "aids")
print x.size()
