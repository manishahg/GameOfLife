/*
 * gameofLife.h
 *
 *  Created on: Feb 3, 2016
 *      Author: manisha
 */

#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;

// Global declarations
# define RMAX	10		// Maximum number of rows in grid
# define CMAX 	10		// Maximum number of columns in grid
# define BARS  	"=========================================================="


// Function prototypes
void OpenInputFile(string filename, ifstream& inFile);
void LoadConstraints(ifstream& inFile, int& num, string& bstring, string& sstring); // Load number of iterations, birth and survival strings
void LoadGrid(ifstream& inFile, int grid[][CMAX]);  // Populate grid from the file
void PrintGrid(int grid[][CMAX]); //Print the current grid
void ComputeNextGrid(int current[][CMAX], int next[][CMAX], int birth[], int survival[]);
void CopyGrid(const int source[][CMAX], int destination[][CMAX]);
int  CountType1Neighbors(int grid[][CMAX], int row, int col);
int  CountType2Neighbors(int grid[][CMAX], int row, int col);
void ParseRequirementsString(string requirements, int reqs[]);  // Convert bstring and sstring into birth and survival look up tables

#endif /* GAMEOFLIFE_H_ */
