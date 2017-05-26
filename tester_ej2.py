from random import *
import subprocess
import os
from timeit import default_timer as timer

''' Generating Tests and Executing '''
N = 250	# from B to N size node
C = 1550  # maximum cost
Z = 20	# how many times each size
R = 20  # how many times each case

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
csvEj2M = open("./timesEj2M.csv", "a")
csvEj2NM = open("./timesEj2NM.csv", "a")
csvEj2C = open("./timesEj2C.csv", "a")

'''
###	Size fijo, Costo_Max fijo, M variable
print("M")
n = N
M = int(n*((n-1))/2)
for m in range(1, M):
	if (m % 5 == 0):
		print (m)
	c = 10
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
			csvEj2M.write('%s,%s\n'%(str(m),str(timeEj)))


###	Size variable, Costo_Max fijo, M=N
print("MN")
for n in range(2,N):
	if (n % 5 == 0):
		print (n)
	m = n-1
	c = 30
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
			csvEj2NM.write('%s,%s\n'%(str(n),str(timeEj)))
'''


###	Size variable, Costo_Max fijo, M=N
print("C")
n = 25
m = n-1
for c in range(1,C):
	if (c % 10 == 0):
		print (c)
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
			csvEj2C.write('%s,%s\n'%(str(c),str(timeEj)))


csvEj2M.close()
csvEj2NM.close()
csvEj2C.close()
