#include "triangle.cpp"
#include <iostream>

#define TEST printf("TEST: %s: %d\n", __FILE__, __LINE__); fflush(stdout);

using namespace std;

int main(){
	Triangle now;
	now.display_depth();
	now.print_triangle();
	
	return 0;
}
