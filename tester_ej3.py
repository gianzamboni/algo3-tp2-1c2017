from random import *
import subprocess
import os
from timeit import default_timer as timer

''' Generating Tests and Executing '''
Size = 550	# from B to N size   MAX 550
Z = 20	# how many times each size
R = 10  # how many times each case

open("res3", 'w').close()
csvEj3 = open("./timesEj3.csv", "a")

for N in range(2,Size):
    if(N % 5 == 0):
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

        test3 = open("test3", 'w')
        test3.write(file)
        test3.close()
       
        comm = "cat test3 | ./ej3 >> res3" 
        for i in range(0,R):
            startEj = timer()
            os.system(comm)
            endEj = timer()
            timeEj = endEj - startEj
            csvEj3.write('%s, %s\n'%(str(N),str(timeEj)))



csvEj3.close()