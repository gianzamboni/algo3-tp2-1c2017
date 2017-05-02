from random import *
import subprocess
import os
from timeit import default_timer as timer

''' Generating Tests and Executing '''
N = 30	# from B to N size
Z = 20	# how many times each size

open("res3", 'w').close()

for z in range(Z):
    print(z)
    file = str(N) + ' '
    for n in range(1,N):
        for x in range(n+1,N+1):
            ls = ''
            ls += str(n) + ' ' + str(x) 
            ls += ' ' + str(randrange(2)) + ' ' + str(randrange(50))
            file += ls + ' '
    file += str(-1)
    
    comm = "echo %s | ./ej3 >> res3" % (file)
    os.system(comm)

