#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "triangle.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

#ifndef _TRIANGLE_CPP_
#define _TRIANGLE_CPP_

#define TEST printf("TEST: %s: %d\n", __FILE__, __LINE__); fflush(stdout);

//Constructor
Triangle::Triangle() {
	create_table(4);
	curId=0;
}

Triangle::Triangle(int height){
	if(height <= 0){
		create_table(4);
	}else{
		create_table(height);
	}
	curId=0;
}

void Triangle::create_table(int height){
//Create the background base for the triangle structure and
//display the 
	int length = 1; //Declarations
	vector<nodeInfo> temp_pack;
	nodeInfo temp_node;

	for(int i=0;i<height;i++){	//Iterate through to create a height number of rows.
		for(int j=0;j<length;j++){	//Iterate through to create the proper number of points in each row.
			temp_node.set.push_back(i*10 + j);	//Assign the calculated value to the coordinate.
								//Calculated value puts the row value in the 10's place and
								//the col value in the 1's place. This will be helpful to
								//index the elements.
			temp_pack.push_back(temp_node);		//Push the created temp_node with set to temp_pack.
			temp_node.set.erase(temp_node.set.begin(),temp_node.set.end());		//Clean out temp_node for next iteration
		}
		length++;	//Length needs to go up because each new row has an extra value from the last one.
		table.push_back(temp_pack);	//Push the created temp_pack to the table.
		temp_pack.erase(temp_pack.begin(),temp_pack.end());	//Clean out temp_pack for next iteration.
	}
}

void Triangle::display_depth(){
	cout << "The height is " << table.size() << endl;
	for(int i =0;i<table.size();i++){
		cout << "The number of elements in row " << i<< " is " << table[i].size()<< "."<<endl;
	}
}

void Triangle::print_triangle(){
//Print out the contents of the table and order it by row.
	for(int i = 0;i < table.size();i++){
		for(int j=0;j<table[i].size();j++){
			for(int s=0;s<table[i][j].set.size();s++){
				cout << "(" << table[i][j].set[s]/10 << "," << table[i][j].set[s] % 10 << ")";
			}
		}
		cout << endl;
	}	
}
#endif /*_TRIANGLE_CPP_*/
