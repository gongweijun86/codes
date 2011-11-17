def fibs(num):
	result=[0,1]
	for i in range(num - 2):
		result.append(result[-1] + result[-2])
	return result
num = input('input fibinacci num: ')
print fibs(num)

