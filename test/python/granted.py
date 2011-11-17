#!/usr/bin/python
database=[
	['albert','1234'],
	['dlbert','2345'],
	['smith','9090'],
	['jones','9999']
		]
username=raw_input("name:")
pin=raw_input("pin:")
if [username,pin] in database:
	print 'Access granted!'
else:
	print 'Access denyed!'


