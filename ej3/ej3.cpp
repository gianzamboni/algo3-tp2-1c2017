#include <iostream>
#include <vector>
#include <algorithm>
#include "dsu.cpp"

using namespace std;

struct Ruta{
	int c1;
	int c2;
	int costo;
	Ruta(){}
	Ruta(int ciu1, int ciu2, int cost) : 
		c1(ciu1),c2(ciu2),costo(cost)
		{};
};

bool comp(Ruta r1, Ruta r2){
	return r1.costo < r2.costo;
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
		//cout << llamada(n, v);
		cin >> n;
	}
	return 0;
}

void kruskal(unsigned int n,vect<ruta> rutas){
	int res=0;	
	dsu conj(n);
	while(!rutas.empty()){
		ruta r=ruta.top();
		ruta.pop();
		int c1=r.c1();
		int c2=r.c2();
		if(conj.find(c1) != conj.find(c2)){
			int costo= abs(ruta.costo());
			res=res+costo;
			conj.unir(c1,c2);
		}
	}

}