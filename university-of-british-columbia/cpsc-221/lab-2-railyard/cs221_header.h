//////////////////////////////////////////////////////////////////////
// Name: Charles Bihis							Course: Cpsc 221	//
// Student #: 43180009							Class Section: 201	//
// Date: March 5, 2005							Lab Section L2M		//
//////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

void SayHello ();
void SayGoodbye ();


// Purpose: to identify the author of the program
// Inputs:  none
// Outputs: the author of the program as well as other relevant
//          information is outputted
void SayHello ()
{
  cout << "*************************************************************\n"
       << "*	Name: Charles Bihis					Course: Cpsc 221	*\n"
       << "*	Student #: 43180009					Class Section: 201	*\n"
       << "*	Date: March 5, 2005					Lab Section: L2M	*\n"
       << "*************************************************************\n\n\n";
}  // SayHello


// Purpose: to signify the end of the program
// Inputs:  none
// Outputs: a message signifying the end of the program is outputted
void SayGoodbye ()
{
  cout << "\n\n**********  End of Program **********\n";
}  // SayGoodbye ()
