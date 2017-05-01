#include "dsu.h"
#include <vector>
#include<iostream> 

dsu::dsu(unsigned int n ){
  for (int i = 0; i < n; i++) {
    padre.push_back(i);
    altura.push_back(1);
  }
}



int dsu::find(unsigned int x){
//cout<<"entre al find " << endl;

//cout<< "el padre de "<< x <<endl;
//cout<<" es " << padre[x+1]<<endl;
	if(padre[x]!=x){
		
		padre[x]=find(padre[x]);
	}
	return padre[x];
}

void dsu::unir(unsigned int x, unsigned int y){
	x=find(x);
	y=find(y);
	if(altura[x]<altura[y]){
		padre[x]=y;
	}
	else{
		padre[y]=x;
	}
	if(altura[x]==altura[y]){
		altura[x]+=1;
	}

}

