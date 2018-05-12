import math

def int_to_binary(b):
	a = b
	binary_list = []
	while(a > 1):
		print('a is {}'.format(a))
		if a % 2 == 0:
			binary_list.append(0)
			a = a / 2
		if a % 2 != 0:
			binary_list.append(1)
			a = (a - 1)/2
	if(a == 1):
		binary_list.append(1)
		print('a is {}'.format(a))
	else:
		binary_list.append(0)
		print('a is {}'.format(a))
	
	binary_list = binary_list[::-1]
	return binary_list

a = int_to_binary(121)
print('-----')
b = int_to_binary(355674)

print(a)

print(b)

			
		
		
		
