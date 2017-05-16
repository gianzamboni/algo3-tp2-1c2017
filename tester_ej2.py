from random import *
import subprocess
import os
from timeit import default_timer as timer

''' Generating Tests and Executing '''
N = 30	# from B to N size node
C = 30  # maximum cost
Z = 10	# how many times each size
R = 10  # how many times each case

def generar_grafo(N,M,C):
	file = str(N) + ' ' + str(M) + ' '
	lista = []
	for n in range(1,N):
		for x in range(n+1,N+1):
			ls = ''
			ls += str(n) + ' ' + str(x) + ' ' 
			ls += str(randrange(C)) + ' '
			lista.append(ls)
	lista = sample(lista,M)
	for i in lista:
		file += i
	return file + str(-1) + str(-1)

open("res2", 'w').close()
csvEj2 = open("./timesEj2.csv", "a")

for n in range(2, N):
	print (n)
	M = int(n*((n-1))/2)
	print (M)
	for m in range(1, M+1):
		for c in range(1,C+1):
			for z in range(Z):
				grafo = generar_grafo(n,m,c);
				test2 = open("test2", 'w')
				test2.write(grafo)
				test2.close()

				comm = "cat test2 | ./Ej2 >> res2"
				for r in range(R):
					startEj = timer()
					os.system(comm)
					endEj = timer()
					timeEj = endEj - startEj
					csvEj2.write('%s,%s,%s,%s\n'%(str(n),str(m),str(c),str(timeEj)))

csvEj2.close()
