
#include <vector>

using namespace std;

class dsu{


public:

	dsu(unsigned int n);

	
	int find(unsigned int x);

	void unir(unsigned int x, unsigned int y);



private:

	vector<unsigned int> padre;
	vector<unsigned int> altura;


};
