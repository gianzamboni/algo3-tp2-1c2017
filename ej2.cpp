#include <iostream>
#include <list>
#include <vector>
#include "dsu.h"
using namespace std;

//ESTRUCTURAS
struct Eje
{
	int inicio;
	int fin;
	int costo;

	Eje(int i, int f, int c): inicio(i), fin(f), costo(c) {}

};

struct Nodo
{

	int id;
	list<Eje> incidentes;

	Nodo(): id(-1), incidentes(list<Eje>()){};
	Nodo(int id):id(id), incidentes(list<Eje>()){};

	void agregar_eje(int nodo2, int costo){
		incidentes.push_back(Eje(id,nodo2,costo));
	}
};

struct Grafo
{
	int n;
	int m;
	vector<Nodo> nodos;

	Grafo(int n, int m): n(n), m(m), nodos(vector<Nodo>(n,Nodo())){};

	void agregar_eje(int nodo1, int nodo2, int costo){
		nodos[nodo1].agregar_eje(nodo2, costo);
	}
};

//PROTOPIPOS
int subsidiar(Grafo* g);
int main() {
	
	int n, m, n1, n2, c;
	cin >> n >> m;
	
	while(n != -1 && m != -1){
		Grafo g(n,m);
		for(int i = 0; i < m; i++){
			cin >> n1 >> n2 >> c;
			g.nodos[n1].id = n1;
			g.nodos[n2].id = n2;
			g.agregar_eje(n1, n2, c);
		}

		int valor_max = subsidiar(&g);

		cout << valor_max << endl;
	}
}


int subsidiar(Grafo* g){
	return 0;
}