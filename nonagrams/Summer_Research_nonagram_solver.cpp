////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This program contains a nonagram solver for all square nonagrams up to the size 5 by 5.
//
//Created by Michael Cranwill at Coe College, Cedar Rapids IA
//SCRiMP Fellowship Summer 2011.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>

using namespace std;

const int UNERREICHT=0;
const int RICHTIG=107;
const int FALSCH=6;
const int BORDER=23;
const int gridSize=5;

int GUI();
void Grid_Helper_Primer(int grid[][gridSize+2], bool helper[gridSize]);
void Hints_Solutions_Primer(int Hints_Solutions[][gridSize+2],int);
void Check_Input(int grid[][gridSize+2],int);
void Count_Groups_Sizes(int grid[][gridSize+2],int rowSolutions[][gridSize+2],int currentRow);
bool Simple_Boxes_Test(int grid[][gridSize+2],int BoundForRows,int rowHints[][gridSize+2],int colHints[][gridSize+2]);
void Simple_Boxes(int grid[][gridSize+2],int, bool, int );
bool Simple_Boxes_Improved_Test(int grid[][gridSize+2],int BoundForRows,int rowHints[][gridSize+2], int colHints[][gridSize+2]);
void Simple_Boxes_Improved(int grid[][gridSize+2], int Hints[][gridSize+2], bool,int);
void Swap(int, int);
void Fill_In_Known_Stuff(int grid[][gridSize+2],int rowOrCol, bool IsRow,bool IsBox);
void Input_Hints(int Hints[][gridSize+2]);

int main()
{
	cout << "Would you like to play a game? (In creepy somewhat maniacal voice)" << endl << " Y for yes, N for no."<< endl;
	GUI();
	
	//Initialize all arrays to be worked with.
	int grid[gridSize+2][gridSize+2];
	bool  helper[gridSize];
	int rowHints[(gridSize/2)+3][gridSize+2];
	int colHints[(gridSize/2)+3][gridSize+2];
	int rowSolutions[(gridSize/2)+3][gridSize+2];
	

	//Prime all of those arrays to be filled with zeroes and borders.
	Grid_Helper_Primer(grid, helper);
	Hints_Solutions_Primer(rowSolutions,(gridSize/2)+3);
	Hints_Solutions_Primer(rowHints,(gridSize/2)+3);
	Hints_Solutions_Primer(colHints,(gridSize/2)+3);
	int BoundForRows=(gridSize/2)+3;

	//Function Testing
	Count_Groups_Sizes(grid, rowSolutions,2);
	
	Check_Input(grid,gridSize+2);
	//Check_Input(rowHints,BoundForRows);

	rowHints[1][1]=4;
	rowHints[1][2]=4;
	rowHints[1][3]=3;
	rowHints[2][3]=1;
	Check_Input(rowHints,(gridSize/2)+3);

	//Control Structure
	bool FlagTouched=true;
	int count=0;

	while(FlagTouched && count < 4)
	{
		//FlagTouched=false;
		
		//Simple Boxes Test
		FlagTouched=Simple_Boxes_Test(grid, BoundForRows,rowHints, colHints);

		//Simple Boxes Improved Test
		FlagTouched=Simple_Boxes_Improved_Test(grid,BoundForRows,rowHints, colHints);
		
		count++;
	}
	  Check_Input(grid,gridSize+2);
  return 0;
}



int GUI()
{
	int size;
	cout<< "Please enter the size of nonagram" << endl << "(Please note that the number you enter will result in a square of your size X your size )" << endl;
	cin>> size;

	return size;
}
//Priming Funcions that input zeroes and borders into arrays.
void Grid_Helper_Primer(int grid[][gridSize+2],bool helper[])
{
	/*This function prepares the Grid and the helper of the grid to be worked on
and used by setting everything to 0 or false and filling in any borders that 
might also be necessary.*/

	//The following two sections of code fill in the BORDER of the grid
	//The first section fills in the top and bottom row of the border.
	int now=0; int newNow=0;
	while (now < gridSize+2)
	{
		newNow=0;
		while (newNow < gridSize+2)
		{
			grid[now][newNow]=BORDER;
			newNow++;
		}
		now=now+gridSize+1;
		
	}
	//This section fills in the first and last column of all the middle rows.
	now=1;
	while (now<gridSize+1)
	{
		newNow=0;
		while (newNow<gridSize+2)
		{
			grid[now][newNow]=BORDER;
			newNow=newNow+gridSize+1;
		}
		now++;
	}

	//This next section fills in the actual grid spaces as UNTOUCHED
	for(int i=1; i<gridSize+1;i++)
		{for(int j=1; j<gridSize+1;j++)
			{grid[i][j]=UNERREICHT;}
	}
	for(int i=0;i<gridSize-1;i++)
		helper[i]=false;

}
void Hints_Solutions_Primer(int Hints_Solutions[][gridSize+2],int BoundforRows)
{

	for(int i=1; i<BoundforRows-1;i++)
		{
			for(int j=1; j<(gridSize+1);j++)
			{Hints_Solutions[i][j]=UNERREICHT;}
		}

	//The following two sections of code fill in the BORDER of the grid
	//The first section fills in the top and bottom row of the border.
	int now=0; int newNow=0;
	while (now < BoundforRows)
	{
		newNow=0;
		while (newNow < gridSize+2)
		{
			Hints_Solutions[now][newNow]=BORDER;
			newNow++;
		}
		now=now+BoundforRows-1;
		
	}
	//This section fills in the first and last column of all the middle rows.
	now=1;
	while (now<BoundforRows-1)
	{
		newNow=0;
		while (newNow<gridSize+2)
		{
			Hints_Solutions[now][newNow]=BORDER;
			newNow=newNow+gridSize+1;
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
			for(int j=0; j<gridSize+2;j++)
			{
				cout<< setw(5)<< input[i][j];
				
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

void Simple_Boxes(int grid[][gridSize+2],int hint, bool IsRow,int rowOrCol)
{
	int FindHint=gridSize-1; int steps=1;

	while (FindHint != hint)
	{
		steps++;
		FindHint--;
	}
	int numMarkTrue=(-2)*steps+gridSize;
	int changer=steps+1;
	int count=0;
	
	while (count<numMarkTrue)
		{
		if(IsRow)
			grid[rowOrCol][changer]=RICHTIG;		
		else
			grid[changer][rowOrCol]=RICHTIG;
		changer++;
		count++;
		}
}
bool Simple_Boxes_Test(int grid[][gridSize+2],int BoundForRows,int rowHints[][gridSize+2], int colHints[][gridSize+2])
{
	bool FlagTouched=false;
	for(int PseudoColumn=1;PseudoColumn<BoundForRows-2;PseudoColumn++)
			{for(int PseudoRow=1;PseudoRow<gridSize+1;PseudoRow++)
			{
				if(rowHints[PseudoColumn][PseudoRow]/float(gridSize)>=.5)
					{
						Simple_Boxes(grid,rowHints[PseudoColumn][PseudoRow], true,PseudoRow);
						FlagTouched=true;
					};
				if(colHints[PseudoColumn][PseudoRow]/float(gridSize)>=.5)
					{
						Simple_Boxes(grid,rowHints[PseudoColumn][PseudoRow], false,PseudoRow);
						FlagTouched=true;
					};
		}}
	return FlagTouched;
}
void Simple_Boxes_Improved(int grid[][gridSize+2], int Hints[][gridSize+2], bool IsRow,int rowOrCol)
{
	int gridTester[2][gridSize+2];
	
	//Load into gridTester
	int s=0;
	while(s<2)
	{
		int changer=0;
		for(changer;changer<gridSize+2;changer++)
		{
		if (IsRow)
			gridTester[s][changer]=grid[rowOrCol][changer];
		else
			gridTester[s][changer]=grid[changer][rowOrCol];
		}
		s++;
	}

	//Test for simple case where there is nothing in array
	bool isEasy=true; s=0; int changer=1;
	while(gridTester[s][changer]!=23 && isEasy)
	{
		if(gridTester[s][changer]==0)
			isEasy=true;
		else
			isEasy=false;

		changer++;
	}

	//Input Extremes
	int current=1; int limit=0;
		
	while(Hints[current][rowOrCol]!=0)			//Then use current to go the other way filling in from extreme on right.
	{
		changer=1;
		int hint=Hints[current][rowOrCol];
		//Test to find clear spaces for hint.
		int potentialSpace=0;
		if (isEasy)
		{
			int filledIn=0; 
			if (limit>0)
				changer=limit;
		while(filledIn<hint)
		{
			gridTester[s][changer]=current;
			filledIn++;
		}
		
		}
		else
		{
			changer=1;
			if (limit>0)
				changer=limit;
			cout<< "Rabble Rabble." << endl;
			while(potentialSpace<hint && gridTester[s][changer]!=BORDER)
			{
				if(gridTester[s][changer]==UNERREICHT)
					{
						potentialSpace++;
						changer++;
					}
				else if (gridTester[s][changer]==FALSCH)
					{changer++;
				potentialSpace=0;}
				else if (gridTester[s][changer]==RICHTIG)
				{
					potentialSpace++;
					changer++;
				};
				limit=changer;
			}
			if(potentialSpace==hint)
			{
				if(gridTester[s][changer]==FALSCH||gridTester[s][changer]==UNERREICHT|| gridTester[s][changer]==BORDER)
				{
					changer--; int count=0;
					while(count<hint)
					{
						gridTester[s][changer]=current;
						count++;
						changer--;
					}
				}
			}
		}
		if (gridTester[s][limit]!=BORDER && gridTester[s][limit]!=RICHTIG )
			gridTester[s][limit]=FALSCH;
		
		current++;
	}
	current--; s++; 
	
	//Find beginning of BORDER
	changer=1;
	while(gridTester[1][changer]!=BORDER)
		changer++;
	changer--;
	Check_Input(gridTester,1);
	limit=0;
	//Fill in extreme values from the right.
	while(Hints[current][rowOrCol]!=UNERREICHT && Hints[current][rowOrCol]!=BORDER)			
	{
		int hint=Hints[current][rowOrCol];
		//Test to find clear spaces for hint.
		int potentialSpace=0;
		if (isEasy)
		{
			int filledIn=0; 
		while(filledIn<hint)
		{
			gridTester[s][changer]=current;
			filledIn++;
		}
		}
		else
		{
			changer=5;
			if (limit>0)
				changer=limit;
			cout<< "Rabble Rabble." << endl;
			while(potentialSpace<hint && gridTester[s][changer]!=BORDER)
			{
				if(gridTester[s][changer]==UNERREICHT)
					{
						potentialSpace++;
						changer--;
					}
				else if (gridTester[s][changer]==FALSCH)
					{changer--;
				potentialSpace=0;}
				else if (gridTester[s][changer]==RICHTIG)
				{
					potentialSpace++;
					changer--;
				};
				limit=changer;
			}
			if(potentialSpace==hint)
			{
				if(gridTester[s][changer]==FALSCH||gridTester[s][changer]==UNERREICHT|| gridTester[s][changer]==BORDER)
				{
					changer++; int count=0;
					while(count<hint)
					{
						gridTester[s][changer]=current;
						count++;
						changer++;
					}
				}
			}
		}
		if (gridTester[s][limit]!=BORDER && gridTester[s][limit]!=RICHTIG )
			gridTester[s][limit]=FALSCH;
		
		
		current--;
	}
	Check_Input(gridTester,2);
	changer=1;
	//Test Extreme cases and make call to fill them in.
	while(gridTester[0][changer]!=BORDER)
	{
		if(gridTester[0][changer]==gridTester[1][changer] && gridTester[0][changer]!=FALSCH)
		{
			if(IsRow)
				grid[changer][rowOrCol]=RICHTIG;
			else
				grid[rowOrCol][changer]=RICHTIG;

		};
		if(gridTester[0][changer]==gridTester[1][changer] && gridTester[0][changer]==FALSCH)
		{
			if(IsRow)
				grid[changer][rowOrCol]=FALSCH;
			else
				grid[rowOrCol][changer]=FALSCH;
		}

			changer++;
		
	}
	Check_Input(grid,gridSize+2);
}
bool Simple_Boxes_Improved_Test(int grid[][gridSize+2],int BoundForRows,int rowHints[][gridSize+2], int colHints[][gridSize+2])
{
	bool FlagTouched=false;
	for(int PseudoColumn=1;PseudoColumn<BoundForRows+1;PseudoColumn++)
			
			{
				int PseudoRow=1; float accumulator=0; int count=0;
				while(rowHints[PseudoRow][PseudoColumn]!=0)
				{
					count++;
					accumulator=rowHints[PseudoRow][PseudoColumn]+accumulator;
					PseudoRow++;
					
					if(rowHints[PseudoRow][PseudoColumn]!=0)
						accumulator=accumulator+1;
				}
				
				if(accumulator/gridSize>=.6 && count>1)
					{
						Simple_Boxes_Improved(grid,rowHints, true,PseudoRow);
						FlagTouched=true;
					}

				accumulator=0; PseudoRow=1; count=0;
				while(colHints[PseudoRow][PseudoColumn]!=0)
				{
					count++;
					accumulator=colHints[PseudoRow][PseudoColumn]+accumulator;
					PseudoRow++;

					if(colHints[PseudoRow][PseudoColumn]!=0)
						accumulator=accumulator+1;
				}
			
				if(accumulator/gridSize>=.6 && count>1)
					{
						Simple_Boxes_Improved(grid,colHints, false,PseudoRow);
						FlagTouched=true;
					}
	}
		
	return FlagTouched;
}
void Input_Hints(int Hints[][gridSize+2], int modifiedGridSize)
{
	int input; int i; int s;
	cin>>input;
	while (s < gridSize)
	{
		while(input!='/n')
		{
		Hints[i][s]=input;
		cin>>input;
		i++;
		}
		cin>>input;
		s++;
	}
}
void Swap(int r, int s)
{
	int temp=r;
	r=s; 
	s=temp;
	
}




//helpful test code that can be used to test a row or column.
/*int i=1;
	
		for(i;i<3;i++)
			grid[2][i]=RICHTIG;
		int s=i;
		
		for(s;s<(i+1);s++)
			grid[2][s]=FALSCH;
		i=s;
		for(i;i<gridSize+1;i++)
			grid[2][i]=RICHTIG;*/