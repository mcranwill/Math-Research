/////////////////////////////////////////////////
//The integer we are computing the possible partitions
//of is k*m**n into powers of m.
/////////////////////////////////////////////////
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <cstdlib>
#include <math.h>

const int m=3;

using namespace std;
int t_mnk(int n,int k);

int main(int argc,char *argv[]){

		if(argc <2){
		cout<< "Usage Error: Please enter 3 elements";
		
	}
	int k = atoi(argv[1]);
	int n = atoi(argv[2]);
	cout << k << "*" << m << "**" << n << "=" << k*(pow(m,n)) << endl; 
	cout << "the number of partitions this can be broken into is: ";
	cout << t_mnk(n,k) << endl;
	return 0;
}


int t_mnk(int n,int k){
	if(n==1)
		return k +1;
	else if(k==0)
		return 1;
	else{
		return t_mnk(n,k-1) + t_mnk(n-1,(k*m));
	}
}
