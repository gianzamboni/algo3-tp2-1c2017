CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
OFLAGS= -c -g -ggdb -Wall
CFLAGS=-std=c++11 -g -ggdb -Wall

SOURCESE1=ej1.o
SOURCESE1G= ej1G.o
SOURCESE2=ej2.o
SOURCESE3=dsu.o ej3.o
#SOURCESTIEMPOS=

tp:
	make ej1
	make ej1G
	make ej2
	make ej3
	#make tiempos

ej1: $(SOURCESE1)
	$(CC) $(CFLAGS) $(SOURCESE1) -o Ej1

ej1G: $(SOURCESE1G)
		$(CC) $(CFLAGS) $(SOURCESE1G) -o Ej1G

ej2: $(SOURCESE2)
	$(CC) $(CFLAGS) $(SOURCESE2) -o Ej2

ej3: $(SOURCESE3)
	$(CC) $(CFLAGS) $(SOURCESE3) -o Ej3

# tiempos: $(SOURCETIEMPOS)
# 	$(CC) $(CFLAGS) $(SOURCESE3) -o tiempos

*.o: *.cpp *.hpp
	$(CC) $(OFLAGS) *.cpp

clean:
	rm *.o
	rm Ej1
	rm Ej1G
	rm Ej2
	rm Ej3
	rm tiempos
