from math import sqrt
for n in range(99,80,-1):
	root = sqrt(n)
	if root == int(root):
		print n
		break
else:
	print "Didn't found it!"
