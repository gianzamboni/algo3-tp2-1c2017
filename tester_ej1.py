from random import *
import subprocess
import os
from timeit import default_timer as timer

''' Generating Tests and Executing '''
Size = 150	# from B to N size node
Cmax = 30  	# maximum cost
Kmax = 150	# maximum premium roads
Z 	 = 20	# how many times each size
R 	 = 1  	# how many times each case

completeness = (False,True)
solvable = (False,True)
premiums = ("all","none","any")

def generar_grafo_complete(N):
	lista = set()
	for n in range(1,N):
		for x in range(n+1,N+1):
			ls = str(n) + ' ' + str(x) + ' '
			lista.add(ls)
			ls = str(x) + ' ' + str(n) + ' ' 
			lista.add(ls)
	return lista

def generar_grafo_non_complete(N):
	## Creo un digrafo fuertemente conexo de 2*(n-1)
	lista = set()
	count = 0
	for n in range(2,N+1):
		i = str(randrange(n-1)+1)
		lida = str(n) + ' ' + i + ' '
		lista.add(lida)
		lvuelta = i + ' ' + str(n) + ' '
		lista.add(lvuelta)
		count += 2

	'''
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
	'''
	return lista

def generar_grafo(N,K,C,complete,is_solvable,qty_premium):
	if(is_solvable):
		if(complete):
			file = str(N+1) + ' ' + str(N*(N+1)) + ' '
			file += str(1) + ' ' + str(randrange(N)+1) + ' ' + str(K) + ' '
			ejes = generar_grafo_complete(N+1)
		else:
			file = str(N+1) + ' ' + str(2*N) + ' '
			file += str(1) + ' ' + str(randrange(N)+1) + ' ' + str(K) + ' '
			ejes = generar_grafo_non_complete(N+1)

	else:
		if(complete):
			file = str(N+1) + ' ' + str(N*(N-1)) + ' '
			file += str(1) + ' ' + str(N+1) + ' ' + str(K) + ' '
			ejes = generar_grafo_complete(N)
		else:
			file = str(N+1) + ' ' + str(2*(N-1)) + ' '
			file += str(1) + ' ' + str(N+1) + ' ' + str(K) + ' '
			ejes = generar_grafo_non_complete(N)

	for i in ejes:
		if(qty_premium == "none"):
			file += i + str(0)
		elif(qty_premium == "all"):
			file += i + str(1)
		else:
			file += i + str(randrange(2))
		file += ' ' + str(randrange(C)) + ' '

	file += str(-1) + ' ' + str(-1)

	test1 = open("test1", 'w')
	test1.write(file)
	test1.close()
	return 


def test_N():
	# Test peor caso de m (completo en ambos sentidos)
	# 	y cantidad de vertices fijo

	open("res1", 'w').close()
	csvEj1NC = open("./timesEj1NC.csv", "a")
	csvEj1NnC = open("./timesEj1NnC.csv", "a")

	for n in range(2,Size):
		if (n % 5 == 0):
			print(n)
		for z in range(Z):
			lineC = "%s"%(str(n))
			linenC = "%s"%(str(n))
			for comp in completeness:
				for solv in solvable:
					for prem in premiums:
						generar_grafo(n,15,Cmax,comp,solv,prem)

						comm = "cat test1 | ./Ej1 >> res1" 
						for i in range(0,R):
							startEj = timer()
							os.system(comm)
							endEj = timer()
							timeEj = endEj - startEj
							if (comp):
								lineC += ',%s'%(str(timeEj))
							else:	
								linenC += ',%s'%(str(timeEj))
			lineC += '\n'
			linenC += '\n'
			csvEj1NC.write(lineC)
			csvEj1NnC.write(linenC)

	csvEj1NC.close()
	csvEj1NnC.close()


def test_K():
	# Test peor caso de m (completo en ambos sentidos)
	# 	y cantidad de vertices fijo

	open("res1", 'w').close()
	csvEj1KC = open("./timesEj1KC.csv", "a")
	csvEj1KnC = open("./timesEj1KnC.csv", "a")

	for k in range(Kmax):
		if (k % 5 == 0):
			print(k)
		for z in range(Z):
			lineC = "%s"%(str(k))
			linenC = "%s"%(str(k))
			for comp in completeness:
				for solv in solvable:
					for prem in premiums:
						generar_grafo(50,k,Cmax,comp,solv,prem)

						comm = "cat test1 | ./Ej1G >> res1" 
						for i in range(0,R):
							startEj = timer()
							os.system(comm)
							endEj = timer()
							timeEj = endEj - startEj
							if (comp):
								lineC += ',%s'%(str(timeEj))
							else:	
								linenC += ',%s'%(str(timeEj))
			lineC += '\n'
			linenC += '\n'
			csvEj1KC.write(lineC)
			csvEj1KnC.write(linenC)

	csvEj1KC.close()
	csvEj1KnC.close()


test_N()
test_K()


