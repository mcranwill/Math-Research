// Test driver
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int UNERREICHT=0;
const int RICHTIG=107;
const int FALSCH=6;
const int BORDER=23;
const int MAX = 50;
const int gridSize=45;

int GUI();
void Grid_Primer(int grid[][gridSize+2], int);
void Solutions_Primer(int Hints_Solutions[][gridSize+2],int);
void Check_Input(int grid[][gridSize+2],int);
void Count_Groups_Sizes(int grid[][gridSize+2],int rowSolutions[][gridSize+2],int currentRow);
int Get_Random_Number(int upperBound, int lowerBound);


int main()
{
	
	int modifiedGridSize=GUI();
	int grid[gridSize+2][gridSize+2];
	int rowSolutions[(gridSize/2)+3][gridSize+2];
	int colSolutions[(gridSize/2)+3][gridSize+2];
	int BoundforRows=(modifiedGridSize/2)+3;

	Grid_Primer(grid,modifiedGridSize );
	Solutions_Primer(rowSolutions,modifiedGridSize);
	Solutions_Primer(colSolutions,modifiedGridSize);
	//Check_Input(grid,modifiedGridSize+2);
	//Check_Input(rowSolutions,modifiedGridSize+2);
	//Check_Input(colSolutions,modifiedGridSize+2);
	
	//Input boxes randomly into grid.
		//Generate random number which will be the percentage filled in of the nonagram.
		float percentage=Get_Random_Number(50, 30)*.01;

		int iterator=(modifiedGridSize*modifiedGridSize)*percentage;
		int i=0;
		int temp1=Get_Random_Number(modifiedGridSize,1);
			int temp2=Get_Random_Number(modifiedGridSize,1);
			int repeat=0;
		while (i<iterator && repeat<8)
		{
			
			if (grid[temp1][temp2]==RICHTIG)
				{
					i--;
					repeat++;
				}
			grid[temp1][temp2]=RICHTIG;

			temp1=Get_Random_Number(modifiedGridSize,1);
			temp2=Get_Random_Number(modifiedGridSize,1);
			i++;
		}
		Check_Input(grid,modifiedGridSize+2);

		//Generate actual boxes. and  if a square is already filled in. step through grid until not filled in.

	//Count groups and sizes and store in appropriately named arrays of Solutions.

	//Print out all information to file.

	//Repeat until satisfied.

 
  return 0;
}
int Get_Random_Number(int upperBound, int lowerBound)
{
// seed the random number generator
	srand((unsigned int) time(0));  

	// print NUM random values between 1 and MAX
	int myRandomValue=rand()%upperBound + lowerBound;
	return myRandomValue;
	
	
}
int GUI()
{
	int size;
	cout<< "Please enter the size of nonagram you would like to create." << endl << "(Please note that the number you enter will result in a square of your size X your size )" << endl;
	cin>> size;

	return size;
}
//Priming Funcions that input zeroes and borders into arrays.
void Grid_Primer(int grid[][gridSize+2],int modifiedGridSize)
{
	/*This function prepares the Grid and the helper of the grid to be worked on
and used by setting everything to 0 or false and filling in any borders that 
might also be necessary.*/

	//The following two sections of code fill in the BORDER of the grid
	//The first section fills in the top and bottom row of the border.
	int now=0; int newNow=0;
	while (now < modifiedGridSize+2)
	{
		newNow=0;
		while (newNow < modifiedGridSize+2)
		{
			grid[now][newNow]=BORDER;
			newNow++;
		}
		now=now+modifiedGridSize+1;
		
	}
	//This section fills in the first and last column of all the middle rows.
	now=1;
	while (now<modifiedGridSize+1)
	{
		newNow=0;
		while (newNow<modifiedGridSize+2)
		{
			grid[now][newNow]=BORDER;
			newNow=newNow+modifiedGridSize+1;
		}
		now++;
	}

	//This next section fills in the actual grid spaces as UNTOUCHED
	for(int i=1; i<modifiedGridSize+1;i++)
		{for(int j=1; j<modifiedGridSize+1;j++)
			{grid[i][j]=UNERREICHT;}
	}
	

}
void Solutions_Primer(int Hints_Solutions[][gridSize+2],int modifiedGridSize)
{
	int BoundforRows=(modifiedGridSize/2)+3;

	for(int i=1; i<BoundforRows+1;i++)
		{
			for(int j=1; j<(modifiedGridSize+1);j++)
			{Hints_Solutions[i][j]=UNERREICHT;}
		}

	//The following two sections of code fill in the BORDER of the grid
	//The first section fills in the top and bottom row of the border.
	int now=0; int newNow=0;
	while (now < BoundforRows+2)
	{
		newNow=0;
		while (newNow < modifiedGridSize+2)
		{
			Hints_Solutions[now][newNow]=BORDER;
			newNow++;
		}
		now=now+BoundforRows+1;
		
	}
	//This section fills in the first and last column of all the middle rows.
	now=1;
	while (now<BoundforRows+1)
	{
		newNow=0;
		while (newNow<modifiedGridSize+2)
		{
			Hints_Solutions[now][newNow]=BORDER;
			newNow=newNow+modifiedGridSize+1;
		}
		now++;
	}

	

}

//Print Function that prints to screen everything in the array including borders.
void Check_Input(int input[][gridSize+2],int BoundforRows)
{
	//This function prints out everything that is stored in the grid.
	for (int i=0;i<BoundforRows;i++)
		{
			for(int j=0; j<BoundforRows;j++)
			{
				cout<< setw(3)<< input[i][j];
				
			}
			cout << endl;
		}
	cout << endl << endl;
}

//Test functions and aids to those test functions.
void Count_Groups_Sizes(int grid[][gridSize+2],int rowSolutions[][gridSize+2],int currentRow)
{
	int s=1; int i=currentRow; int currentCount=0; int j=1;
	bool currentGroup=false;

	if(grid[i][j]==107)
	{
		currentGroup=true;
		currentCount=1;
	}

	for(j=2;j<gridSize+1;j++)
		{
			if(currentGroup)
			{
				currentCount++;
				j++;
				if (grid[i][j] !=107)
				{
					rowSolutions[s][i]=currentCount;
					currentCount=0;
					currentGroup=false;
					s++;
				}
				j--;
			}
			else
			{
				if(grid[i][j]==107)
					{
						currentGroup=true;
						currentCount=1;
						if(j+1>=gridSize+1)
							rowSolutions[s][i]=currentCount;
					}
			}
	}
}




//if (grid[temp1][temp2]!=RICHTIG)
//				grid[temp1][temp2]=RICHTIG;
//			else 
//			{
//				while(grid[temp1][temp2]==RICHTIG ||grid[temp1][temp2]==BORDER)
//				{
//					if(grid[temp1+1][temp2]==RICHTIG||grid[temp1+1][temp2]==UNERREICHT)
//						temp1=temp1+1;
//					else if(grid[temp1-1][temp2]==RICHTIG||grid[temp1-1][temp2]==UNERREICHT)
//						temp1=temp1-1;
//					else if(grid[temp1][temp2+1]==RICHTIG||grid[temp1][temp2+1]==UNERREICHT)
//						temp2=temp2+1;
//					else if(grid[temp1][temp2-1]==RICHTIG||grid[temp1][temp2-1]==UNERREICHT)
//						temp2=temp2-1;
//				}
//				grid[temp1][temp2]=RICHTIG;
//			}