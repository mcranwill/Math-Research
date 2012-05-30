#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "matrix.h"
#include <string>
#include <stdlib.h>

#ifndef _MATRIX_CPP_
#define _MATRIX_CPP_

#define TEST printf("TEST: %s: %d\n", __FILE__, __LINE__); fflush(stdout);

//Constructor
Matrix::Matrix(){
    curId=0;			//may not use Id
    increase_size(4,4,true);	//initialization of a 4 X 4 gridsize
}


//Dynamically increase size of matrix to accomodate new nodes
int Matrix::add_node(int r,int c,string color){
	//TODO add failsafes to protect from dirty input
	//protect from other potential issues as well.
	if(r >= matrix.size()){		//test if rows need to be increased.
        	increase_size(r,c,true);
				
	}else if(c >= matrix[0].size()){//this checks edge case that we only
					//need to increase the columns.
	        increase_size(r,c,false);
	}
	matrix[r][c].color=color;	//assign new color to (r,c) in question.
	return 0;			// on success return 0.
}

vector<int> Matrix::neighbors(int id){
    vector<int> temp;
	
    return temp;
}

//function to actually increase the appropriate rows and/or columns.
void Matrix::increase_size(int r, int c,bool is_row){
	vector<packet_info> temp;		//Declare filler row.
	packet_info temp1;			//Declare filler col.
	temp1.color="white";			//Declare filler color.
	
	while(r >= matrix.size() && is_row){	//while we are not at needed row
						//size, then push_back a new row.
		matrix.push_back(temp);
	}
	int i=0;			//set i to 0 so we can affect every
					//row which must be done regardless
					//of whether we only change rows or both
	while(i < matrix.size()){		//iterate over all rows.	
		while(c >= matrix[i].size()){	//adjust all rows to have proper
						//number of columns.
			matrix[i].push_back(temp1);
		}
		i++;			//go to the next row.
	}
}

//print the matrix in a readable form denoting each element and it's color
void Matrix::print_matrix(){
	for(int i=0;i<matrix.size();i++){
        	for(int j=0;j<matrix[i].size();j++){
			cout << "( "<< i<< "," << j << " ) " ;
			cout << setw(5)<< matrix[i][j].color<< " ";
        	}
		cout << endl;
	}
}

void Matrix::print_stats(){

}

#endif /*_MATRIX_CPP_*/
