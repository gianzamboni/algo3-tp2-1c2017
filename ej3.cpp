#include <iostream>
#include <vector>
#include <algorithm>
#include "dsu.hpp"
using namespace std;


struct Ruta{
	int c1;
	int c2;
	int costo;
	Ruta(){}
	Ruta(int ciu1, int ciu2, int cost): 
		c1(ciu1),c2(ciu2),costo(cost)
		{};
};

bool comp(Ruta r1, Ruta r2){
	return r1.costo < r2.costo;
}

void kruskal(unsigned int n, vector<Ruta> rutas){
	int res = 0;	
	vector<Ruta> solu;
	dsu conj(n);
	for (unsigned int i = 0; i < rutas.size(); ++i){
		Ruta r = rutas[i];		
		int c1 = r.c1-1;
		int c2 = r.c2-1;
		int costo = r.costo;
		if(conj.find(c1) != conj.find(c2)){				
			if(costo > 0)
				res += costo;
			solu.push_back(r);
			conj.unir(c1,c2);
			conj.mostrar();
		}
		else{
			if(costo < 0)
				res += -costo;
		}
	}

	cout << res << " " << solu.size() << " ";
	for(unsigned int i=0; i<solu.size(); i++){
		Ruta actual = solu[i];
		cout << actual.c1 << " " << actual.c2 << " ";
	}
	cout << endl;
}


int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	while (n != -1){
		int lineas = (n*(n-1))/2;
		vector<Ruta> v(lineas);
		for (int i = 0; i < lineas; ++i){
			int c1, c2, e, p;
			cin >> c1 >> c2 >> e >> p;
			if(e)
				v[i] = Ruta(c1, c2, -p);
			else
				v[i] = Ruta(c1, c2, p);
		}

		sort(v.begin(), v.end(), comp);
		kruskal(n, v);
		cin >> n;
	}
	return 0;
}

