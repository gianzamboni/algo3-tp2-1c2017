#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "dsu.h"
using namespace std;


typedef unsigned int uint;
//ESTRUCTURAS
struct Eje {
	uint inicio;
	uint fin;
	int costo;

	Eje(uint i, uint f, int c): inicio(i), fin(f), costo(c) {}

};

struct Nodo {

	int id;
	list<Eje> incidentes;

	Nodo(): id(-1), incidentes(list<Eje>()){};
	Nodo(uint id):id(id), incidentes(list<Eje>()){};

	void agregar_eje(uint nodo2, int costo){
		incidentes.push_back(Eje(id,nodo2,costo));
	}
};

struct Grafo {
	uint n;
	uint m;
	vector<Nodo> nodos;

	Grafo(int n): n(n), m(0), nodos(vector<Nodo>(n,Nodo())){};

	Grafo(list<int>* ids, Grafo* g){

	}

	void agregar_eje(uint nodo1, uint nodo2, int costo){
		m++;
		nodos[nodo1].agregar_eje(nodo2, costo);
	}
};

//PROTOPIPOS
int subsidiar(Grafo* g, int max_c);
int min(list<int> v);
int bellman(Grafo g, Nodo n, int costo);

int main() {
	
	uint n, m, n1, n2;
	int c;
	cin >> n >> m;
	int max_c = 0;
	while(n != -1 && m != -1){
		Grafo g(n);
		for(int i = 0; i < m; i++){
			cin >> n1 >> n2 >> c;
			g.nodos[n1].id = n1;
			g.nodos[n2].id = n2;
			g.agregar_eje(n1, n2, c);

			if( c > max_c ) max_c = c;
		}

		int valor_max = subsidiar(&g, max_c);

		cout << valor_max << endl;
	}
}


int subsidiar(Grafo* g, int max_c){

	dsu union_find(g->n);
	// El for este funciona a partir c++11
	for(Nodo nodo : g->nodos){
		for(Eje e : nodo.incidentes){
			if(union_find.find(e.inicio) != union_find.find(e.fin) ) 
				union_find.unir(e.inicio, e.fin);
		}
	}

	vector<uint> padres_ordenados = union_find.get_padre();
	sort(padres_ordenados.begin(), padres_ordenados.end());

	list<uint> padres_cc;
	padres_cc.push_back(padres_ordenados[0]);

	for(int i = 1; i < padres_ordenados.size(); i++){
		if(padres_cc.back() != padres_ordenados[i]) 
			padres_cc.push_back(padres_ordenados[i]);
	}

	vector< list<int> > componentes_conexas(padres_cc.size(), list<int>());

	for(Nodo nodo : g->nodos){
		int i = 0;
		for(uint padre : padres_cc){
			if(union_find.find(nodo.id) == padre) 
				componentes_conexas[i].push_back(nodo.id);
			i++;
		}
	}

	list<int> maximos_costos;

	for(list<int> cc : componentes_conexas){
		//Armar el subgrafo de la cc;
		Grafo componente_conexa(&cc, g);
		int min = 0;
		int max = max_c;

		while(min + 1 < max){
			int c = min + (max-min)/2;

			bool hay_ciclo = bellman(componente_conexa, componente_conexa.nodos[0].id, c);

			if(hay_ciclo) {
				max = c;
			} else {
				min = c;
			}
		}

		maximos_costos.push_back(min);
	}

	return min(maximos_costos);
}

int min(list<int> v){
	int m = *(v.begin());
	for(int e : v) {
		if (m > e) m = e;
	}

	return m;
}
int bellman(Grafo g, Nodo n, int costo) {
	return 0;
};