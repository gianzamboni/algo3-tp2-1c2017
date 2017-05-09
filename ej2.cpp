#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <limits.h>
#include "dsu.hpp"
using namespace std;



typedef unsigned int uint;
//ESTRUCTURAS
struct Eje {
	
	uint inicio;
	uint fin;
	int costo;

	Eje(uint i, uint f, int c): inicio(i), fin(f), costo(c) {}

};


struct Grafo {
	
	uint n;
	uint rep;

	bool tiene_rep;

	list<Eje> ejes;

	Grafo(int n): n(n), rep(0), tiene_rep(0), ejes(list<Eje>()){};
	
	void agregar_eje(uint nodo1, uint nodo2, int costo){
		ejes.push_back(Eje(nodo1, nodo2, costo));
	};

	void agregar_eje(Eje eje){
		ejes.push_back(eje);
	};

	void mostrar(){
		cout << "Nodos: " << n << endl;
		cout << "Ejes: " << ejes.size() << endl;
		cout << "Rep: " << rep << endl;
		cout << "Hay Rep: " << tiene_rep << endl;
		cout << "Ejes" << endl;
		cout << "======================" << endl;
		for (list<Eje>::iterator it=ejes.begin(); it != ejes.end(); ++it){
			cout << (*it).inicio << " " << (*it).fin << " " << (*it).costo << endl;
		}
	}
};

//PROTOPIPOS
void agregar_nodo_fictio(Grafo* g);
bool hay_ciclos_negativos(Grafo* g, int n, int costo);
int busqueda_binaria(int max, Grafo* c_conexas);
int subsidiar(Grafo* g, int max_c);


int main() {
	int n, m, n1, n2;
	int c;
	cin >> n >> m;
	int max_c = 0;
	while(n != -1 && m != -1){
		Grafo g(n);
		for(int i = 0; i < m; i++){
			cin >> n1 >> n2 >> c;
			g.agregar_eje(n1-1, n2-1, c);

			if( c > max_c ) max_c = c;
		}

		//g.mostrar();
		int valor_max = subsidiar(&g, max_c);
		cout << valor_max << endl;
		cin >> n >> m;
	}

	return 0;
}

int subsidiar(Grafo* g, int max_c){
	agregar_nodo_fictio(g);
	int k = busqueda_binaria(max_c+1, g);
	return k;
}

void agregar_nodo_fictio(Grafo* g){
	g->n++;

	for(uint i = 0; i < g->n - 1; i++){
		g->agregar_eje(g->n-1, i, 1);
	}
};

int busqueda_binaria(int max, Grafo* g){
	// Armar las compenentes conexas
	int min = 0;
	while(min + 1 < max){
		int k = min + (max-min)/2;
		if(hay_ciclos_negativos(g, g->n - 1, k)){
			max = k;
		} else {
			min = k;
		}
	}

	return min;
}

bool hay_ciclos_negativos(Grafo* g, int nodeId, int costo) {  // Bellman

	vector<uint> distancia(g->n,UINT_MAX);
	vector<uint> predecesor(g->n, 0);

	distancia[nodeId] = 0;              // Except for the Source, where the Weight is zero 
   
   	for(unsigned int i = 0; i < g->n; i++){
		for (list<Eje>::iterator it=g->ejes.begin(); it != g->ejes.end(); ++it){
   			if( distancia[(*it).inicio] + (*it).costo - costo < distancia[(*it).fin]){
   				distancia[(*it).fin] = distancia[(*it).inicio] + (*it).costo - costo;
   				predecesor[(*it).fin] = (*it).inicio;
   			}
   		}
	}

	for (list<Eje>::iterator it=g->ejes.begin(); it != g->ejes.end(); ++it){
		if (distancia[(*it).inicio] + (*it).costo - costo < distancia[(*it).fin]) {
			return true;
		}
	}

	return false;
}; 
