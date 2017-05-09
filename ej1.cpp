#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

struct Nodo;

typedef vector<vector<Nodo> >  Grafo;

struct Ruta {

	Nodo* destino;
	int dist;
	bool premium;

	Ruta(): destino(NULL), dist(-1), premium(-1){}
	Ruta(Nodo* destino, int d, bool prem): 
		destino(destino),dist(d), premium(prem) {}

};

struct Nodo {

	int id, nivel;
	list<Ruta> adyacente;
	Nodo() : id(-1), nivel(-1), adyacente(list<Ruta>()){};
	Nodo(int id, int nivel) : id(id), nivel(nivel), adyacente(list<Ruta>()){};

	void agregarVecino(Nodo* nodo, int dist) {
		bool prem = false;
		if(this->nivel != nodo->nivel){
			prem = true;
		};
		adyacente.push_back(Ruta(nodo, dist, prem));
	}

	void agregarVecino(int id, int nivel, int dist, Grafo* g){
		agregarVecino(&(*g)[nivel][id], dist);
	}
};

int delivery(Grafo* g, int origen, int destino, int k);

int main(int argc, char const *argv[]) {
	int n;
	cin >> n;
	while (n != -1){
		int m;
		int origen, destino, k;
		cin >> m >> origen >> destino >> k;
		
		Grafo grafo_nivelado(k, vector<Nodo> (n, Nodo()));
		int c1, c2, d;
		bool p;
	
		for(int nivel = 0; nivel < k; nivel++){
			for(int id = 0; id < n; id++){
				grafo_nivelado[nivel][id].id = id;
				grafo_nivelado[nivel][id].nivel = nivel;
			}
		}

		cout << "Grafo iniciazializado" << endl;
		for (int i = 0; i < m; ++i){
			cin >> c1 >> c2 >> p >> d;
			c1--;
			c2--;
			if(p == 0) {
				for(int nivel = 0; nivel < k; nivel++){
					grafo_nivelado[nivel][c1].agregarVecino(c2, nivel, d, &grafo_nivelado);
					grafo_nivelado[nivel][c2].agregarVecino(c1, nivel, d, &grafo_nivelado);
				}
			} else {
				for(int nivel = 0; nivel < k-1; nivel++){
					grafo_nivelado[nivel][c1].agregarVecino(c2, nivel+1, d, &grafo_nivelado);
				}
			}
			cout << "Eje " << c1 << " " << c2 << " procesado" << endl;
		}

		cout << "Grafo armado a partir de input" << endl;
		cout << delivery(&grafo_nivelado, origen, destino, k) << endl;
		cin >> n;
	}
	return 0;
}

int delivery(Grafo* g, int origen, int destino, int k){
	return 0;
};
