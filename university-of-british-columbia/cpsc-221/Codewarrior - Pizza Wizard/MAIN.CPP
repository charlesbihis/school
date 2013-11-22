#include <iostream.h>
#include <ctype.h>

void SayHello ();
void SayGoodbye ();
void CalculatePizza ();
double UnitPrice (double diameter, double price);


void main ()
{
  char answer = 'f';

  SayHello ();
  do
  {
    CalculatePizza ();
    cout << "\n\nWould you like to calculate another pizza? (y/n) ";
    cin >> answer;
    if (tolower (answer) == 'n')
      break;
    cout << "\n       ***********************************************************************************************\n";
  }  // do statement
  while (true);
  SayGoodbye ();  
}  // main


// purpose: introduces the program
// input: none
// output: greeting message
void SayHello ()
{
  cout << "                 ***************************************************************************\n"
       << "                 ***************************************************************************\n"
       << "                 ************************Welcome to the Pizza Wizard************************\n"
       << "                 ***************************************************************************\n"
       << "                 ***************************************************************************\n\n\n\n";
}  // SayHello


// purpose: indicates program termination
// input: none
// output: goodbye message
void SayGoodbye ()
{
  cout << "\n       ***************************************Thank You************************************************\n";
}  // SayGoodbye


// purpose: calculates the price per square inch of a pizza and displays it on screen
// inputs: none
// outputs: the price per square inch of pizza is outputted
void CalculatePizza ()
{
  double diameter = 0;
  double price = 0.0;

  cout.setf (ios::fixed);
  cout.setf (ios::showpoint);
  cout.precision (2);
  cout << "\nPlease enter the diameter of the pizza in inches: ";
  cin >> diameter;
  cout << "\nPlease enter the price of the pizza: $";
  cin >> price;
  cout << "\nThe cost of this pizza is $"
       << UnitPrice (diameter, price) << " per square inch.";
}  // CalculatePizza


// purpose: returns the price per square inch of a pizza
// input: the diameter of the pizza (diameter), and the 
//        price of the pizza (price)
// output: returns the price per square inch of a pizza
double UnitPrice (double diameter, double price)
{
  const double PI = 3.14159;
  double radius = diameter / 2;
  double area = -1;
  
  area = PI * pow (radius, 2);
  return (price / area);
}  // UnitPrice