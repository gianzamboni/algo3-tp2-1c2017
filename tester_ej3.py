from random import *
import subprocess
import os
from timeit import default_timer as timer

''' Generating Tests and Executing '''
Size = 150	# from B to N size
Z = 25	# how many times each size
R = 10  # how many times each case

open("res3", 'w').close()
csvEj3 = open("./timesEj3.csv", "a")

for N in range(1,Size):
    print(N)
    for z in range(Z):
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
            csvEj3.write('%s, %s\n'%(str(N),str(timeEj)))



csvEj3.close()