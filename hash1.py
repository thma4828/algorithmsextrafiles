#!python3
import random
f_dict = {'A':1, 'B':2, 'C':3, 'D':4, 'E':5, 'F':6, 'G':7, 'H':8,'I':9,'J':10,'K':11,'L':12,'M':13,
'N':14,'O':15,'P':16,'Q':17,'R':18,'S':19,'T':20,'U':21,'V':22,'W':23,'X':24,'Y':25,'Z':26}


def h(x, L):
	ss = 0
	for i in range(len(x)-1):
		ss = ss + f_dict[x[i]]
	return ss % L 

names = []
random_names = []
f1 = open("lastn.txt", 'r')
for line in f1:
	s = str(line)
	for i in range(len(s)):
		if(s[i] == " "):
			s = s[:i]
	names.append(s)

ccount = len(names)
r1 = ccount
l1 = 200
print("ccount = ", ccount)
good_hashes = []
indc_histogram = [0 for i in range(l1)]
while ccount > 0:
	rand_index = random.randint(0, len(names)-1)
	random_names.append(names[rand_index]) #select random name from the table with random index
	ccount = ccount - 1

for nm in names:
	hash1 = h(nm, 200)
	good_hashes.append(hash1)
	indc_histogram[hash1] += 1

for e in good_hashes:
	print e

print("max collisions: ", max(indc_histogram), "r1 = ", r1)

tablef = True
for i in range(200):
	if i not in set(good_hashes):
		print i
		tablef = False

if tablef:
	print "\ntable full!"
else:
	print "\ntable not full!"