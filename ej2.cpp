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
		n = ids->size();
		m = 0;
		for(int id : *ids){
			nodos.push_back(g->nodos[id]);
			m += g->nodos[id].incidentes.size();
		}
	}

	void agregar_eje(uint nodo1, uint nodo2, int costo){
		m++;
		nodos[nodo1].agregar_eje(nodo2, costo);
	}
};

//PROTOPIPOS
int subsidiar(Grafo* g, int max_c);
int min(list<int> v);
bool bellman(Grafo* g, int n, int costo);
int busqueda_binaria(int max, list<Grafo*>* componentes_conexas);
int check_bellman(list<Grafo> componente_conexa, int k);
void generar_conexas(Grafo* g, list<Grafo*>* componentes_conexas);


int main() {
	int n, m, n1, n2;
	int c;
	cin >> n >> m;
	int max_c = 0;
	while(n != -1 && m != -1){
		Grafo g(n);
		for(int i = 0; i < m; i++){
			cin >> n1 >> n2 >> c;
			g.nodos[n1-1].id = n1-1;
			g.nodos[n2-1].id = n2-1;
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

	for(uint i = 1; i < padres_ordenados.size(); i++){
		if(padres_cc.back() != padres_ordenados[i]) {
			padres_cc.push_back(padres_ordenados[i]);
		}
	}

	vector< list<int> > componentes_conexas(padres_cc.size(), list<int>());

	for(Nodo nodo : g->nodos){
		int i = 0;
		for(int padre : padres_cc){
			if(union_find.find(nodo.id) == padre) {
				componentes_conexas[i].push_back(nodo.id);
			}
			i++;
		}
	}

/*	list<int> maximos_costos; */

/*	for(list<int> cc : componentes_conexas){
		//Armar el subgrafo de la cc;
		Grafo componente_conexa(&cc, g);

		int min = 0;
		// k == max_c + 1 nos asegura que tiene ciclos. (Esto lo agregamos para el caso todos iguales)
		int max = max_c + 1;		

		//Invariante del ciclo k == max tiene ciclos negativos.
		while(min + 1 < max) {
			int c = min + (max-min)/2;
			cout << "costo: " << c;
			bool hay_ciclo = bellman(&componente_conexa, componente_conexa.nodos[0].id, c);
			//bool hay_ciclo = bellman(g, g->nodos[0].id, c);
			cout << ", ciclos: " << hay_ciclo;
			if(hay_ciclo) {
				max = c;
			} else {
				min = c;
			}
			cout << ", Min: " << min << " Max: " << max << endl;

		}

		maximos_costos.push_back(min);

	}
*/

	int k = busqueda_binaria(max_c+1, componentes_conexas);

	return k;
}


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
		res = res && bellman(c, k);
	}
	return res;
}


int min(list<int> v){
	int m = *(v.begin());
	for(int e : v) {
		if (m > e) m = e;
	}

	return m;
}

bool bellman(Grafo* g, int nodeId, int costo) {

	vector<uint> distancia(g->n,UINT_MAX);
	vector<uint> predecesor(g->n, 0);

	distancia[nodeId] = 0;              // Except for the Source, where the Weight is zero 
   
   	for(unsigned int i = 1; i < g->n; i++){
		//cout << "Iteracion " << i << " de " << g->n - 1 << endl;
   		for(Nodo nodo : g->nodos){
   			//cout << "\tNodo nº " << nodo.id << " con " << nodo.incidentes.size() << " vecinos" << endl;
   			for(Eje eje : nodo.incidentes){
   				//cout << "\t\tEje " << eje.inicio << " " << eje.fin << " " << eje.costo << endl;
   				if( distancia[eje.inicio] + eje.costo - costo < distancia[eje.fin]){
   					distancia[eje.fin] = distancia[eje.inicio] + eje.costo - costo;
   					predecesor[eje.fin] = eje.inicio;
   				}
   			}
   			//cout << "\t\tTerminado" << endl;
   		}
   	}



	for(Nodo nodo: g->nodos){
		for(Eje eje: nodo.incidentes){
			if (distancia[eje.inicio] + eje.costo - costo < distancia[eje.fin]) {
				return true;
			}
		}
	}

	return false;
}; 