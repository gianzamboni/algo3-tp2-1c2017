from random import *
import subprocess
import os
from timeit import default_timer as timer

''' Generating Tests and Executing '''
N = 30	# from B to N size node
C = 30  # maximum cost
Z = 10	# how many times each size
R = 10  # how many times each case

def generar_grafo(N,M,K,C):
	## Creo un digrafo fuertemente conexo de 2*(n-1)
	file = str(N) + ' ' + str(M) + ' '
	file += str(1) + ' ' + str(randrange(N-1)+2) + ' ' + str(K) + ' '
	lista = set()
	count = 0
	for n in range(2,N+1):
		i = str(randrange(n-1)+1)
		lida = str(n) + ' ' + i + ' '
		lista.add(lida)
		lvuelta = i + ' ' + str(n) + ' '
		lista.add(lvuelta)
		count += 2

	## agrego ejes al azar hasta llegar a m
	for _ in range(M-count):
		c = count
		while(count == c):
			i = randrange(N)+1
			j = randrange(N)+1
			ruta = str(i) + ' ' + str(j) + ' '
			if (i != j and ruta not in lista):
				lista.add(ruta)
				count += 1
	for i in lista:
		file += i + str(randrange(2)) + ' ' + str(randrange(C)) + ' '
	return file + str(-1) + ' ' + str(-1)


open("res1", 'w').close()
csvEj1 = open("./timesEj3.csv", "a")


grafo = generar_grafo(30,75,0,50);
test1 = open("test1", 'w')
test1.write(grafo)
test1.close()

csvEj1.close()