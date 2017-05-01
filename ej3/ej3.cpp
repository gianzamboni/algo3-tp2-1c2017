#include <iostream>
#include <vector>
#include <algorithm>
#include "dsu.cpp"

using namespace std;



struct ruta{
	int c1;
	int c2;
	int costo;
	ruta(){}
	ruta(int ciu1, int ciu2, int cost) : 
		c1(ciu1),c2(ciu2),costo(cost)
		{};
};

bool comp(ruta r1, ruta r2){
	return r1.costo < r2.costo;
}

//declaracion funciones
void kruskal(unsigned int n, vector<ruta> rutas);

//funciones

void kruskal(unsigned int n, vector<ruta> rutas){
	int res=0;	
	vector<ruta> solu;
	dsu conj(n);
	for (int i = 0; i < rutas.size(); ++i){
		ruta r=rutas[i];		
		int c1=r.c1;
		int c2=r.c2;
		int costo= r.costo;
		if(conj.find(c1) != conj.find(c2)){				
			if(costo>0){
				res=res+costo;
			}	
			solu.push_back(r);
			conj.unir(c1,c2);
		}
		else{
			if(costo<0){
				res= res+ abs(costo);
			}
		}
	}

	cout<< res << " "<< solu.size()<< " ";
	for(int i=0; i<solu.size(); i++){
		ruta actual= solu[i];
		cout<< actual.c1<<" "<<actual.c2<< " ";
	}
	cout << endl;
}


int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	while (n != -1){
		int lineas = (n*(n-1))/2;
		vector<ruta> v(lineas);
		for (int i = 0; i < lineas; ++i){
			int c1, c2, e, p;
			cin >> c1 >> c2 >> e >> p;
			if(e)
				v[i] = ruta(c1, c2, -p);
			else
				v[i] = ruta(c1, c2, p);
		}

		sort(v.begin(), v.end(), comp);
		kruskal(n, v);
		cin >> n;
	}
	return 0;
}

