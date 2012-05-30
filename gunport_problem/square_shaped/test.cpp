#include "matrix.cpp"
#include <iostream>

#define TEST printf("TEST: %s: %d\n", __FILE__, __LINE__); fflush(stdout);

using namespace std;

int main(){
	Matrix test;
	test.add_node(3,4,"blue");
	test.add_node(3,2,"red");
	test.print_matrix();
	for(int i=0;i<4;i++)
		test.add_node(i,2,"blue");
	cout << endl;

	test.print_matrix(); 
	test.add_node(3,4,"blue");
	test.add_node(5,5,"blue");
	cout << endl;
	test.print_matrix(); 
	return 0;
}
