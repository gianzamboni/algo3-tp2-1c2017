#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <limits>
using namespace std;

struct Nodo;


//vector externo habla del nivel k, y adentro tenes el grafo con n nodos en ese nivel.
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
//iterador de ruta, facilita la lectura
typedef list<Ruta>::iterator ItRuta;

int delivery(Grafo& g, int origen, int destino, int k, int n);
//busca el nodo de la lista de nodos que tiene el eje menos pesado con el nodo origen, y guarda el valor del eje en dist
Nodo* buscarMin(const vector<Nodo*>& nodos, const vector<int>& distancias, int& dist_Min, int n);

void sacar(vector<Nodo*>& ls,Nodo* valor);
//devuelve el peso del eje que va del nodo_Origen al aux, si no hay devuelve -1
int buscador(const vector<int>& distancias,Nodo* aux, int n);
//aunque nos gustaria usar generar vecino, tal vez ya es vecino el nodo origen y el aux, entonces solo queremos cambiar el valor.(esto por ahi tendria que estar en una struct.
void generar_Ruta(vector<int>& distancias, Nodo* aux, int dist, int n);
//devuelve el valor minimo entre todos los nodos destinos, si no existe valor devuelve -1
int buscar_Destinos(const vector<int>& distancias, int destino, int n, int k);

void imprimir_Vecinos(const Nodo& nod);

void imprimir_Nivel(const Grafo& g);

void imprimir_Grafo(const Grafo& g);

void imprimir_Distancias(const vector<int>& distancias, int n);

int main(int argc, char const *argv[]) {
	int n;
	cin >> n;
	while (n != -1){
		int m;
		int origen, destino, k;
		cin >> m >> origen >> destino >> k;

		Grafo grafo_nivelado(k+1, vector<Nodo> (n, Nodo()));
		int c1, c2, d;
		bool p;

		for(int nivel = 0; nivel <= k; nivel++){
			for(int id = 0; id < n; id++){
				grafo_nivelado[nivel][id].id = id;
				grafo_nivelado[nivel][id].nivel = nivel;
			}
		}

		//cout << "Grafo iniciazializado" << endl;
		for (int i = 0; i < m; ++i){// m*k
			cin >> c1 >> c2 >> p >> d;
			c1--;
			c2--;
			if(p == 0) {
				for(int nivel = 0; nivel <= k; nivel++){
					grafo_nivelado[nivel][c1].agregarVecino(c2, nivel, d, &grafo_nivelado);
					//grafo_nivelado[nivel][c2].agregarVecino(c1, nivel, d, &grafo_nivelado);
				}
			} else {
				for(int nivel = 0; nivel < k; nivel++){
					grafo_nivelado[nivel][c1].agregarVecino(c2, nivel+1, d, &grafo_nivelado);
				}
			}
			//cout << "Eje " << c1 << " " << c2 << " procesado" << endl;
		}

		//cout << "Grafo armado a partir de input" << endl;
		cout << delivery(grafo_nivelado, origen, destino, k, n) << endl;
		cin >> n;
	}
	return 0;
}


//Si hay bug buscar los id de los nodos del grafo y los indices de la matriz de ady y nodosseguros|
//copia de dijkstra pero con forma de Gian, faltan implementar las funciones serias y ver el tema de referenccia y copia que seguro van a estar mal.
int delivery(Grafo& g, int origen, int destino, int k, int n){
	if(origen == destino) return 0;
	unsigned int cant_Nodos = n*(k+1);
	Nodo* nodo_Origen = &(g[0][origen-1]);
	vector<int> distancias(cant_Nodos, -1);
	for(ItRuta it = (nodo_Origen->adyacente).begin(); it != (nodo_Origen->adyacente).end();++it){
		Ruta* ruta_Aux = &(*it);
		int dist_Aux, id_Aux, nivel_Aux;
		dist_Aux = ruta_Aux -> dist;
		id_Aux = ruta_Aux -> destino -> id;
		nivel_Aux = ruta_Aux -> destino -> nivel;
		distancias[id_Aux + (n*nivel_Aux)] = dist_Aux;
	}
	vector<Nodo> nodos_Seguros;
	vector<Nodo*> nodos_No_Seguros;
	for(int i = 0; i<g.size(); i++){//recorre los niveles con el i
		for(int j = 0; j<g[i].size(); j++){//recorre el grafo en el nivel i
			nodos_No_Seguros.push_back(&g[i][j]);
		}
	}
	//O(n*(k+1)^2 + (n*(k+1)^2 * m)
	while(nodos_Seguros.size() != cant_Nodos){//n*(k+1)
		int dist_Min;//la distancia del Nodo_Min
		Nodo* nodo_Min = buscarMin(nodos_No_Seguros, distancias, dist_Min, n);//los nodos no seguros y el Nodo origen O(vecinos de origen) aumentan en 1 O(n*k)
		if( dist_Min == -1 || nodo_Min->id == destino -1) break; //fijares bien esta condicion
		nodos_Seguros.push_back(*nodo_Min);
		sacar(nodos_No_Seguros, nodo_Min); //O(n*k)
		list<Ruta>& ady = nodo_Min->adyacente;
		for(ItRuta it = ady.begin(); it != ady.end(); ++it){//O(m)
			Ruta* rutaAux = &(*it);
			Nodo* aux = rutaAux -> destino;
			int dist_Act = buscador(distancias, aux, n);//O(1)
			int dist_Posible = dist_Min + rutaAux->dist;
			if(dist_Act > dist_Posible || dist_Act== -1) generar_Ruta(distancias, aux, dist_Posible, n);//O(n*k)
		}
	}
	int tiempo = buscar_Destinos(distancias, destino, n, k);
	return tiempo;
}

Nodo* buscarMin(const vector<Nodo*>& nodos,const vector<int>& distancias, int& dist_Min, int n){
	Nodo* res= NULL;
	dist_Min = -1;
	int id_Aux, nivel_Aux;
	for(int i = 0; i< nodos.size(); i++){
		id_Aux = nodos[i] -> id;
		nivel_Aux = nodos[i] -> nivel;
		int dist_Aux = distancias[id_Aux + (n * nivel_Aux)];
		if((dist_Min > dist_Aux || dist_Min == -1) && dist_Aux!=-1){
			res = nodos[i];
			dist_Min = dist_Aux;
		}
	}
	return res;
}

void sacar(vector<Nodo*>& ls,Nodo* valor){
	for(int i = 0; i<ls.size(); i++){
		if(ls[i] -> id == valor -> id && ls[i] -> nivel == valor -> nivel){
			ls[i] = ls[ls.size() -1];
		}
	}
	ls.resize(ls.size()-1);
}

int buscador(const vector<int>& distancias,Nodo* aux, int n){
	int id_Aux = aux-> id;
	int nivel_Aux = aux -> nivel;
	return distancias[id_Aux +(nivel_Aux * n)];
}

void generar_Ruta(vector<int>& distancias, Nodo* aux, int distancia, int n){
	int id_Aux = aux-> id;
	int nivel_Aux = aux -> nivel;
	distancias[id_Aux +(nivel_Aux * n)] = distancia;
}

//devuelve el valor minimo entre todos los nodos destinos, si no existe valor devuelve -1
int buscar_Destinos(const vector<int>& distancias, int dest, int n, int k){
	int min= -1;
		for (int i = 0; i<= k; i++){
		int minPar= distancias[dest-1 + (i*n)];
		if ((minPar<min || min == -1) && minPar !=-1){
			min= minPar;
		}
	}
	return min;
}

void imprimir_Vecinos(const Nodo& nod){
	cerr<<"el nodo "<<nod.id <<"("<<nod.nivel<<") tiene de vecinos a: ";
	list<Ruta> rut = nod.adyacente;
	for(ItRuta it =rut.begin(); it != rut.end(); ++it){
		//desref *it
		Ruta aux = *it;
		cerr<<"["<<aux.destino -> id<<"("<<aux.destino->nivel<<"), d: "<<aux.dist<<" p: "<<aux.premium<<"] ";
	}
	cerr<<endl;
}

void imprimir_Nivel(const Grafo& g, int i){
	vector<Nodo> nivel = g[i];
	for(int j = 0; j<nivel.size();j++){
		imprimir_Vecinos(nivel[j]);
		cerr<<endl;
	}
	cerr<<endl;
}

void imprimir_Grafo(const Grafo& g){
	for(int i = 0; i<g.size(); i++) imprimir_Nivel(g, i);
	cerr<<endl;
}

void imprimir_Distancias(const vector<int>& distancias, int n){
	cerr<<"La distancias son: [";
	for(int i = 0; i< distancias.size(); i++){
		int ide = i % n;
		int nive = i/n;
		cerr<< ide<<"("<<nive<<") d="<<distancias[i]<<", ";
	}
	cerr<<"]\n";
}
