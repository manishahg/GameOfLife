/*
 * program01.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: manisha
 */
#include "gameofLife.h"

// OpenInputFile -- opens file whose name is stored in filename
void OpenInputFile(string filename, ifstream& inFile)
{
	inFile.open(filename);
	return;
}

/** LoadConstraints -- loads only simulation constraints from inFile after skipping header comment.
Constraints input in order num, birth string, survival string**/
void LoadConstraints(ifstream& inFile, int& num, string& bstring, string& sstring)
{

	string line;
	char msg[100];
	int i, count=0;

	while (getline(inFile, line))
	{
		count++;

		if(count==3)
		{
			i=0;
			while(line[i]!='\0')
			{
				msg[i]=line[i];
				i++;
			}
			msg[i]='\0';
			sscanf(msg, "%d", &num);
		}

		if(count==5)
			bstring=line;


		if(count==7)
			sstring=line;

		if(count==8)
			break;

	}
	return;
}

// LoadGrid -- loads the cell grid from inFile
void LoadGrid(ifstream& inFile, int grid[][CMAX])
{

	string line;

	for (int r = 0; r < RMAX; r++)
	{
		int c = 0;

	    // keep reading until we hit a space
	    char ch = inFile.get();
	    while (ch != '\n')
	    {
	        if(ch==EOF)
	        	break;
	        if(ch==' ')
	        {
	            ch = inFile.get();
                continue;
	        }

	        grid[r][c] = ch-'0';
	        c++;
	        ch = inFile.get();
	     }
	 }

	return;

}

// Outputs grid in desired format
void PrintGrid(int grid[][CMAX])
{
  for(int r = 0; r < RMAX; r++)
  {
    for(int c = 0; c < CMAX; c++)
    {
      switch (grid[r][c])
      {
        case 0:  cout << ' ' << '-';   break;

        default:  cout << ' ' << grid[r][c]; break;
      }
    }
    cout << endl;
  }
}

/**ComputeNextGrid -- uses current generation to compute next generation using constraints
specified in birth and survival arrays**/
void ComputeNextGrid(int current[][CMAX], int next[][CMAX], int birth[], int survival[])
{
	int countType1=0;
	int countType2=0;
	int count=0;

	for(int i = 0; i < RMAX; i++)
		for(int j = 0; j < CMAX; j++)
		{
			countType1=CountType1Neighbors(current,i,j);
			countType2=CountType2Neighbors(current,i,j);
			if(!current[i][j])
				count=countType1+countType2;
			else if(current[i][j]==1)
				count=countType1;
			else
				count=countType2;

			int k=0;
			while(survival[k])
			{
				//The cell dies.
				if(count < survival[k] || count > survival[k])
					next[i][j] = 0;
				//The cell stays the same.
				else
				{
					next[i][j] = current[i][j];
					break;
				}
				k++;
			}

			//The cell either stays alive, or is "born".
			k=0;
			if(!current[i][j])
			{
				while(birth[k])
				{
					if(count == birth[k])

					{
						next[i][j] = 1;
						break;
					}
					k++;
				}
			}

			else if(current[i][j]==1)
			{
				while(birth[k])
				{	if((count == birth[k])&&(count>countType2))
					{
						next[i][j] = 1;
						break;
					}
					k++;
				}
			}
			else
			{
				while(birth[k])
				{	if((count == birth[k])&&(count>countType1))
					{
						next[i][j] = 2;
						break;
					}
					k++;
				}
			}
		}
}

// CopyGrid -- copies contents of source array into destination array
void CopyGrid(const int source[][CMAX], int destination[][CMAX])
{
	int i,j;

	for(i=0;i<RMAX; i++)
	{
		for(j=0;j<CMAX; j++)
			destination[i][j]=source[i][j];
	}
	return;
}

/**CountType1Neighbors -- counts the total number of LIVING Type1 neighbors for the cell
at the grid position specified by row and col.**/
int  CountType1Neighbors(int current[][CMAX], int row, int col)
{
	int count = 0;

	if(row==0)
	{
		if(col==0)
			{	count = (current[RMAX-1][col]%2)+(current[RMAX-1][CMAX-1]%2)+(current[RMAX-1][col+1]%2)\
						+(current[row+1][col]%2)+(current[row+1][col+1]%2)+(current[row+1][CMAX-1]%2)+(current[row][CMAX-1]%2)+(current[row][col+1]%2);//top(3)+bottom(3)+left+right
			//cout<<"count:"<<count<<endl;
			}
			else if(col>0 && col<(CMAX-1))
				count = (current[RMAX-1][col]%2)+(current[RMAX-1][col-1]%2)+(current[RMAX-1][col+1]%2)\
						+(current[row+1][col]%2)+(current[row+1][col-1]%2)+(current[row+1][col+1]%2)+(current[row][col-1]%2)+(current[row][col+1]%2);
			else
				count = (current[RMAX-1][col]%2)+(current[RMAX-1][col-1]%2)+(current[RMAX-1][0]%2)\
						+(current[row+1][col]%2)+(current[row+1][col-1]%2)+(current[row+1][0]%2)+(current[row][col-1]%2)+(current[row][0]%2);


	}
	else if(row>0 && row<(RMAX-1))
	{

			if(col==0)
				count = (current[row-1][col]%2)+(current[row-1][CMAX-1]%2)+(current[row-1][col+1]%2)\
						+(current[row+1][col]%2)+(current[row+1][CMAX-1]%2)+(current[row+1][col+1]%2)+(current[row][CMAX-1]%2)+(current[row][col+1]%2);//top+bottom+left+right
			else if(col>0 && col<(CMAX-1))
				count = (current[row-1][col]%2)+(current[row-1][col-1]%2)+(current[row-1][col+1]%2)\
						+(current[row+1][col]%2)+(current[row+1][col-1]%2)+(current[row+1][col+1]%2)+(current[row][col-1]%2)+(current[row][col+1]%2);
			else
				count = (current[row-1][col]%2)+(current[row-1][col-1]%2)+(current[row-1][0]%2)\
						+(current[row+1][col]%2)+(current[row+1][col-1]%2)+(current[row+1][0]%2)+(current[row][col-1]%2)+(current[row][0]%2);
	}
	else
	{
			if(col==0)
				count = (current[row-1][col]%2)+(current[row-1][col+1]%2)+(current[row-1][CMAX-1]%2)\
						+(current[0][col]%2)+(current[0][col+1]%2)+(current[0][CMAX-1]%2)+(current[row][CMAX-1]%2)+(current[row][col+1]%2);//top+bottom+left+right
			else if(col>0 && col<(CMAX-1))
				count = (current[row-1][col]%2)+(current[row-1][col+1]%2)+(current[row-1][col-1]%2)\
						+(current[0][col]%2)+(current[0][col+1]%2)+(current[0][col-1]%2)+(current[row][col-1]%2)+(current[row][col+1]%2);
			else
				count = (current[row-1][col]%2)+(current[row-1][col-1]%2)+(current[row-1][0]%2)\
						+(current[0][col]%2)+(current[0][col-1]%2)+(current[0][0]%2)+(current[row][col-1]%2)+(current[row][0]%2);
	}
	return count;
}

/**CountType2Neighbors -- counts the total number of LIVING Type2 neighbors for the cell
at the grid position specified by row and col.**/
int  CountType2Neighbors(int current[][CMAX], int row, int col)
{
	int count = 0;

	if(row==0)
	{
		if(col==0)
			count = (current[RMAX-1][col]/2)+(current[RMAX-1][CMAX-1]/2)+(current[RMAX-1][col+1]/2)\
					+(current[row+1][col]/2)+(current[row+1][col+1]/2)+(current[row+1][CMAX-1]/2)+(current[row][CMAX-1]/2)+(current[row][col+1]/2);//top(3)+bottom(3)+left+right
		else if(col>0 && col<(CMAX-1))
			count = (current[RMAX-1][col]/2)+(current[RMAX-1][col-1]/2)+(current[RMAX-1][col+1]/2)\
					+(current[row+1][col]/2)+(current[row+1][col-1]/2)+(current[row+1][col+1]/2)+(current[row][col-1]/2)+(current[row][col+1]/2);
		else
			count = (current[RMAX-1][col]/2)+(current[RMAX-1][col-1]/2)+(current[RMAX-1][0]/2)\
					+(current[row+1][col]/2)+(current[row+1][col-1]/2)+(current[row+1][0]/2)+(current[row][col-1]/2)+(current[row][0]/2);
	}
	else if(row>0 && row<(RMAX-1))
	{
		if(col==0)
			count = (current[row-1][col]/2)+(current[row-1][CMAX-1]/2)+(current[row-1][col+1]/2)\
					+(current[row+1][col]/2)+(current[row+1][CMAX-1]/2)+(current[row+1][col+1]/2)+(current[row][CMAX-1]/2)+(current[row][col+1]/2);//top+bottom+left+right
		else if(col>0 && col<(CMAX-1))
			count = (current[row-1][col]/2)+(current[row-1][col-1]/2)+(current[row-1][col+1]/2)\
					+(current[row+1][col]/2)+(current[row+1][col-1]/2)+(current[row+1][col+1]/2)+(current[row][col-1]/2)+(current[row][col+1]/2);
		else
			count = (current[row-1][col]/2)+(current[row-1][col-1]/2)+(current[row-1][0]/2)\
					+(current[row+1][col]/2)+(current[row+1][col-1]/2)+(current[row+1][0]/2)+(current[row][col-1]/2)+(current[row][0]/2);
	}
	else
	{
		if(col==0)
			count = (current[row-1][col]/2)+(current[row-1][col+1]/2)+(current[row-1][CMAX-1]/2)\
					+(current[0][col]/2)+(current[0][col+1]/2)+(current[0][CMAX-1]/2)+(current[row][CMAX-1]/2)+(current[row][col+1]/2);//top+bottom+left+right
		else if(col>0 && col<(CMAX-1))
			count = (current[row-1][col]/2)+(current[row-1][col+1]/2)+(current[row-1][col-1]/2)\
					+(current[0][col]/2)+(current[0][col+1]/2)+(current[0][col-1]/2)+(current[row][col-1]/2)+(current[row][col+1]/2);
		else
			count = (current[row-1][col]/2)+(current[row-1][col-1]/2)+(current[row-1][0]/2)\
					+(current[0][col]/2)+(current[0][col-1]/2)+(current[0][0]/2)+(current[row][col-1]/2)+(current[row][0]/2);
	}
	return count;
}

/** ParseRequirementsString -- takes a birth or survival string and converts it
to integer array assumes that the B or S appears as the first character.**/
void ParseRequirementsString(string requirements, int reqs[])
{
	int i=1;

	while( requirements[i]!='\0')
	{
		reqs[i-1]=requirements[i]-'0';
		i++;
	}
	return ;
}
