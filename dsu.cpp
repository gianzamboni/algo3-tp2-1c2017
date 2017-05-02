#include "dsu.h"
#include <vector>
#include <iostream> 

dsu::dsu(unsigned int n ){
  for (int i = 0; i < n; i++) {
    padre.push_back(i);
    altura.push_back(1);
  }
}

int dsu::find(unsigned int x){
	if(padre[x]!=x)
		padre[x]=find(padre[x]);

	return padre[x];
}

void dsu::unir(unsigned int x, unsigned int y){
	x=find(x);
	y=find(y);
	if(altura[x]<altura[y])
		padre[x]=y;
	else
		padre[y]=x;
	if(altura[x]==altura[y])
		altura[x]+=1;
}

void dsu::mostrar(){
	cout << "pad: [";
	for (int i = 0; i < padre.size(); ++i)
		cout << ' ' << padre[i]; 
	cout << " ]" << endl;

	cout << "alt: [";
	for (int i = 0; i < altura.size(); ++i)
		cout << ' ' << altura[i];
	cout << " ]" << endl;
}

