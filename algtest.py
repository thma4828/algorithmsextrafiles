#CSCI 3104, Spring 2018, Theodore Margoles, 0119, PS5
#import matplotlib.pyplot as plot
#import numpy

import random
f_dict = {'A':1, 'B':2, 'C':3, 'D':4, 'E':5, 'F':6, 'G':7, 'H':8,'I':9,'J':10,'K':11,'L':12,'M':13,
'N':14,'O':15,'P':16,'Q':17,'R':18,'S':19,'T':20,'U':21,'V':22,'W':23,'X':24,'Y':25,'Z':26}


def h(x, L):
    ss = 0
    for i in xrange(len(x)-1):
        ss = ss + f_dict[x[i]]
    return ss % L

names = []
random_names = []
f1 = open("lastn.txt", 'r')
for line in f1:
    s = str(line)
    for i in xrange(len(s)):
        if(s[i] == " "):
            s = s[:i]
    names.append(s)

ccount = len(names) // 32
r1 = ccount
l1 = 200
#print("ccount = ", ccount)
good_hashes = []
indc_histogram = [0 for i in xrange(l1)]
while ccount > 0:
    rand_index = random.randint(0, len(names)-1)
    random_names.append(names[rand_index]) #select random name from the table
    ccount = ccount - 1

for nm in random_names:
    hash1 = h(nm, 200)
    good_hashes.append(hash1)
    indc_histogram[hash1] += 1
    #print("indc_histogram adding", hash1)


tablef = True
for i in xrange(200):
    if indc_histogram[i] == 0:
        tablef = False
        
max_c = max(indc_histogram)
print "max collisions: ", max_c, "\ninp size = ", r1
#y_np = numpy.arange(200);
#indc_np = numpy.array(indc_histogram)
#plot.plot(y_np, indc_histogram)
#plot.ylabel("number of collisions,  input size = " + str(r1))
#plot.xlabel("index of hash table 1 to L");
#plot.show()


#max_collisions_ny = [0 for j in xrange(2, 500)]
#max_collisions_nx = numpy.arange(2, 500)

#for i in xrange(2, 500):
    #indc_histogram = [0 for j in xrange(200)]
    #names1 = []
    #for k in xrange(i-2):
        #names1.append(names[k])
    #for name in names1:
        #hashx = h(name, 200)
        #indc_histogram[hashx] += 1
    #max_n = max(indc_histogram)
    #max_collisions_ny[i-2] = max_n
    
#ny = numpy.array(max_collisions_ny)
#plot.plot(max_collisions_nx, ny)
#plot.ylabel("max number of collisions")
#plot.xlabel("number of hashes n");
#plot.show()

#x_array = numpy.arange(2, 500)
#log_of_x = numpy.arange(2, 500)

#import math

#for p in xrange(2, 500):
    #log_of_x[p-2] = math.log(p)
    #print math.log(p)
    
#plot.plot(x_array, log_of_x)
#plot.ylabel("lg(x) = big Oh bound for rbtree")
#plot.xlabel("x = input size")
#plot.show()
