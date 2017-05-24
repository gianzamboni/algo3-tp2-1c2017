#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <limits>
using namespace std;

struct Nodo;


//vector externo habla del nivel k, y adentro tenes el grafo con n nodos en ese nivel.
typedef vector<vector<Nodo> >  Grafo;


//esta matriz tiene n*(k+1) de cada lado.
typedef vector<vector<int> > MatAdy;

MatAdy lecturaDatos(int& origen, int& destino, int& k, int& n);
//para que funcione tenes que pasar lecturaDatos, asi crea la matAdy.
int delivery_MatAdy(MatAdy& g, int origen, int destino, int k, int n);

int buscarMin_MatAdy(const vector<int>& nodos, const vector<int>& filaAdy);

void sacar_MatAdy(vector<int>& ls, int valor);

void imprimir_Mat(const MatAdy& g, int n, int k);
//viene con la lectura de datos incluida, para testear eso se lo tendriamos que sacar.
int solMatAdy();

int main(int argc, char const *argv[]) {
	int origen, destino, k, n = 0;
	while(cin >> n && n != -1){
		MatAdy g = lecturaDatos(origen, destino, k, n);

		//imprimir_Mat(g, n, k);
		int sol = delivery_MatAdy(g, origen, destino, k, n);
		cout<< sol<<endl;
		//g.clear();
	}
	return 0;
}

int solMatAdy(){
	int origen, destino, k, n;
	MatAdy g = lecturaDatos(origen, destino, k, n);
	//imprimir_Mat(g, n, k);
	//cerr<<"origen, destino, k , n "<< origen<<" "<<destino<<" "<<k<<" "<<n<<endl;
	int sol = delivery_MatAdy(g, origen, destino, k, n);
	return sol;
}

int delivery_MatAdy(MatAdy& g, int origen, int destino, int k, int n){
	//-1 implica que no son vecinos, y un numero naturla mayor a cero indica el peso del pasar por ahi
	//este frena cuando encuentra el minimo en n.
	//es la implementacion de dijkstra usando arreglos leer principio de archivo para entender la matriz del digrafo.
	if(origen == destino) return 0;
	unsigned int cant_Nodos = n*(k+1);//n+(k+1)
	vector<int> nodos_Seguros;
	vector<int> nodos_No_Seguros;
	for(unsigned int i = 0;i< cant_Nodos;i++) nodos_No_Seguros.push_back(i);//O(n)
	while(nodos_Seguros.size() != cant_Nodos){//while se hace n veces
		int nodo_Min;
		//copiar bien buscarMin
		nodo_Min = buscarMin_MatAdy(nodos_No_Seguros, g[origen-1]);//O(nodos.size())  **1**
		//cerr<<"busque minimo es "<<nodo_Min<<endl;
		//que la estacion 1 no este conectada a ninguna, de las que todavia no calculo el minimo
		//si es n entonces ya no tengo por que actualizar otros nodos, ya que n estaria en la zona segura.
		if(nodo_Min == -1 || nodo_Min % n== destino-1) break;
		nodos_Seguros.push_back(nodo_Min);
		sacar_MatAdy(nodos_No_Seguros, nodo_Min);//O(nodos.size())**2**
		for(unsigned int i = 0; i<nodos_No_Seguros.size();i++){//O(nodos.size())**3**
			int pos = nodos_No_Seguros[i];
			//cerr<<"Actualizando posibles "<<pos<<endl;
			int dist_Act = g[origen-1][pos];
			int dist_Posible = g[origen-1][nodo_Min] + g[nodo_Min][pos];
			//hay eje quiero actualizar?
			if(g[nodo_Min][pos] != -1){
				if(dist_Act > dist_Posible || dist_Act == -1){
					//cerr<<"Actualice la posicione "<<origen-1 <<" "<<pos <<" con el valor "<<dist_Posible<<endl;
					g[origen-1][pos] = dist_Posible;
				}
			}
		}
	}
	int tiempo = numeric_limits<int>::max();
	bool sol = false;
	for(int i = 0; i<=k; i++){
		int tiempo_Aux = g[origen-1][destino-1+ i*n];
		if(tiempo < tiempo_Aux || tiempo_Aux != -1){
			sol = true;
			tiempo = tiempo_Aux;
		}
	}
	if(!sol) tiempo = -1;
	g.clear();
	return tiempo;
}

MatAdy lecturaDatos(int& origen, int& destino, int& k, int& n){
	int m;
	cin >> m >> origen >> destino >> k;
	vector<int> aux(n*(k+1), -1);
	MatAdy g(n*(k+1),aux);
	//acordate que las ciudades estan numeradas del 1 al n, entonces le restamos 1.
	int c1, c2, d;
	bool p;
	for(int i = 0; i<m; i++){
		cin >> c1 >> c2 >> p >> d;
		c1--;
		c2--;
		//si es premium quiero que el eje que se agrega sea del nodonivel1 al nodonivel2..
		for(int j = 0; j<=k; j++){
			if(p){
				if(j == k) continue;
				g[c1 + (j*n)][c2 + ((j+1)*n)] = d;

			}else{
				g[c1 + (j*n)][c2+(j*n)] = d;
			}
		}
	}
	return g;
}

/*
busca la tupla que tenga el valor minimo(sin contar el -1) en el primer elemento
de la tupla y devuelve la posicion. solo busca en las posiciones que estan en nodos.
*/
int buscarMin_MatAdy(const vector<int>& nodos, const vector<int>& filaAdy){//O(nodos.size())
	int min = numeric_limits<int>::max();/*
   como peor caso es que tenemos que recorrer las n estaciones y que todas pesen 1000, filaAdy es n+1 entonces min nunca va a ser un valor valido
   */
   int sol = -1;
   for(unsigned int i = 0; i<nodos.size(); i++){
	   int pos = nodos[i];
	   int tiempo = filaAdy[pos];
	   if(tiempo != -1 && min > tiempo){
			min = tiempo;
			sol = pos;
		}
   }
   return sol;
}

//funcion que saca el elemento ls[pos]
void sacar_MatAdy(vector<int>& ls, int valor){//O(ls.size())
   int pos;
   for(unsigned int i = 0; i< ls.size();i++){
	   if(ls[i]== valor){
		   pos = i;
		   break;
	   }
   }
   ls[pos] = ls[ls.size()-1];
   ls.pop_back();
}

void imprimir_Mat(const MatAdy& g, int n, int k){
	cerr<<"La matriz tiene "<<n<< "nodos, en "<< k<<" niveles, su tamaño: "<<g.size()<<" tendria que ser "<<n*(k+1)<<"\n";
	for(int i = 0; i<=k; i++){
	cerr<<"de nivel "<<i<<" a validos"<<endl;
		for(int j = 0+n*i; j<n+ n*i; j++){
			for(int l= 0+ n*i; l<n+ (n*(i+1)); l++){
				if(l >= g.size()) continue;
				cerr<<g[j][l]<<" ";
			}
			cerr<<endl;
		}
		cerr<<endl;
		cerr<<endl;
	}
}
