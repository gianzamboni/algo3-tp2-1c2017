from random import *
import subprocess
import os
from timeit import default_timer as timer

''' Generating Tests and Executing '''
N = 30	# from B to N size
Z = 20	# how many times each size
R = 20  # how many times each case

open("res3", 'w').close()
csvEj3 = open("./timesEj2.csv", "a")

for n in range(1,N):
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
        for i in range(0,R):
            startEj = timer()
            os.system(comm)
            endEj = timer()
            timeEj = endEj - startEj
            csvEj3.write('%s, %s, %s\n'%(str(N),str(timeEj),ls))



csvEj3.close()