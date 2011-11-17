strings = ['hello world!','this','is','a','world']
for index, string in enumerate(strings):
	if 'is' in string:
		strings[index] = 'iiss'
print strings
