#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Ruta {

	uint c1;
	uint c2;
	bool premium;
	int dist;

	Ruta(){}
	Ruta(uint ciu1, uint ciu2, bool prem, int d): 
		c1(ciu1), c2(ciu2), premium(prem), dist(d) 
		{}

};


int delivery(int n, vector<Ruta> v, int origen, int destino, int k);

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	while (n != -1){
		int m;
		cin >> m;
		vector<Ruta> v(m);
		int origen, destino, k;
		cin >> origen >> destino >> k;
		for (int i = 0; i < m; ++i){
			int c1, c2, d;
			bool p;
			cin >> c1 >> c2 >> p >> d;
			v[i] = Ruta(c1, c2, p, d);
		}

		//cout << delivery(n, v, origen, destino, k) << endl;
		cin >> n;
	}
	return 0;
}
