
#include <vector>

using namespace std;

class dsu{


public:

	dsu(unsigned int n);

	
	int find(unsigned int x);

	void unir(unsigned int x, unsigned int y);

	vector<unsigned int> get_padre() {
		return padre;
	};

	vector<unsigned int> get_altura() {
		return padre;
	};
private:

	vector<unsigned int> padre;
	vector<unsigned int> altura;


};
