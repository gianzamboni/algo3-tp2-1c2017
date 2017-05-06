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


};

//PROTOPIPOS
bool bellman(Grafo* g, int n, int costo);
int busqueda_binaria(int max, list<Grafo*>* c_conexas);
bool check_bellman(list<Grafo*>* componente_conexa, int k);
int subsidiar(Grafo* g, int max_c);

list<Grafo*>* generar_conexas(Grafo* g);


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

		int valor_max = subsidiar(&g, max_c);
		cout << valor_max << endl;
		cin >> n >> m;
	}

	return 0;
}

int subsidiar(Grafo* g, int max_c){
	list<Grafo*>* c_conexas = generar_conexas(g);
	int k = busqueda_binaria(max_c+1, c_conexas);

	while(!c_conexas->empty()){
		delete c_conexas->front();
		c_conexas->pop_front();
	}
	delete c_conexas;

	return k;
}

list<Grafo*>* generar_conexas(Grafo* g){
	dsu uf(g->n);
	// Union find O(m)
	for(Eje e : g->ejes){
		if(uf.find(e.inicio) != uf.find(e.fin) ) 
				uf.unir(e.inicio, e.fin);
	}

	vector<uint> cantidades(g->n, 0);
	// Contamos la cantidad de nodos que tiene cada componente conexa O(n)
	for(int i = 0; i < g->n; i++){
		cantidades[uf.find(i)]++;
	}

	vector<Grafo*> componentes_t(g->n, new Grafo(0));

	// Inicializamos los valores de las componentes conexas que nos importan O(n)
	for(int i = 0; i < g->n; i++){
		if (cantidades[i] > 0) {
			componentes_t[i]->n = cantidades[i];
			componentes_t[i]->rep = i;
			componentes_t[i]->tiene_rep = true;
		}
	}

	// Agregamos los ejes a la correspondiente componente conexa O(m)
	for(Eje e : g->ejes){
		componentes_t[uf.find(e.inicio)]->agregar_eje(e);
	}

	// Filtramos todas las componentes conexas que no tienen ejes O(n)
	list<Grafo*>* c_conexas = new list<Grafo*>();
	for(Grafo* g : componentes_t){
		if(g->tiene_rep) c_conexas->push_back(g);
	}

	return c_conexas;
};

int busqueda_binaria(int max, list<Grafo*>* componentes_conexas){
	// Armar las compenentes conexas
	int min = 0;
	while(min + 1 < max){
		int k = min + (max-min)/2;
		if(check_bellman(componentes_conexas, k)){
			max = k;
		} else {
			min = k;
		}
	}

	return min;
}

bool check_bellman(list<Grafo*>* componente_conexa, int k){
	bool res = true;
	for(Grafo* c : *componente_conexa){
		res = res && bellman(c, c->rep,k);
	}
	return res;
}

bool bellman(Grafo* g, int nodeId, int costo) {

	vector<uint> distancia(g->n,UINT_MAX);
	vector<uint> predecesor(g->n, 0);

	distancia[nodeId] = 0;              // Except for the Source, where the Weight is zero 
   
   	for(unsigned int i = 0; i < g->n; i++){
		for(Eje eje : g->ejes){
   			if( distancia[eje.inicio] + eje.costo - costo < distancia[eje.fin]){
   				distancia[eje.fin] = distancia[eje.inicio] + eje.costo - costo;
   				predecesor[eje.fin] = eje.inicio;
   			}
   		}
	}

	for(Eje eje: g->ejes){
		if (distancia[eje.inicio] + eje.costo - costo < distancia[eje.fin]) {
			return true;
		}
	}

	return false;
}; 
