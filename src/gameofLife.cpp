//============================================================================
// Name        : gameofLife.cpp
// Author      : manisha agrawal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "gameofLife.h"

using namespace std;


int main(int argc, char* argv[])
{

  ifstream  inFile;                    // Input stream for reading grid file
  string    filename;				   // Name of grid file
  string    bstring;                   // Birth requirements as C++ string
  string    sstring;                   // Survival requirement as C++ string
  int       currentgrid[RMAX][CMAX];   // Current cell grid
  int       nextgrid[RMAX][CMAX];      // Next cell grid
  int       num;                       // Number of iterations
  int       birth[9], survival[9];     // Birth and survival look up arrays


  if (argc != 2)
  {
    cout << "Usage:  project01  <gridfile>" << endl;
    return 0;
  }
  else
    filename = argv[1];

  OpenInputFile(filename, inFile);     // Attempt to open grid file
  if (!inFile)
  {
    cout << "\nError: unable to open '" << filename << "' for input\nTerminating now...\n";
    return 1;
  }
  else
    cout << "\nFile '" << filename << "' opened for input..." << endl;

  // Load number of iterations, birth and survival strings
  LoadConstraints(inFile, num, bstring, sstring);

   // Exit if birth or survival requirements not specified, otherwise parse birth and survival strings
   if ((bstring[0] != 'B') || (sstring[0] != 'S'))
   {
     cout << "Error: incorrect file formatting" << endl;
     return 1;
   }
   else
   {
	   // Initialize birth and survival requirements to zero
		for(int k=0; k<9; k++)
		{
			birth[k] = 0;
			survival[k] = 0;
		}

		// Convert bstring and sstring representations into birth and survival look up tables
		ParseRequirementsString(bstring, birth);
		ParseRequirementsString(sstring, survival);

		cout << "\nSimulation Birth/Survival Configuration\n";
		for(int k=0; k<9; k++)
		{
			cout << "birth[" << k << "] = " << birth[k] << "      survival["
				 << k << "] = " << survival[k] << "\n";
		}
   }

   // Populate grid
   LoadGrid(inFile, currentgrid);
   cout << "\nGrid loaded from file.\n\n";

   //Print the current grid
   cout << BARS << endl;
   cout << "Iteration = 0" << endl << endl;
   PrintGrid(currentgrid);
   cout << BARS << endl;

   for(int iteration = 1; iteration <= num; iteration++)
   {
		cout << "Iteration = " << iteration << endl << endl;
		ComputeNextGrid(currentgrid, nextgrid, birth, survival);
		CopyGrid(nextgrid, currentgrid);
		cout << BARS << endl;
		PrintGrid(currentgrid);
		cout << BARS << endl;
   } // End iterations loop

   return 0;

}
