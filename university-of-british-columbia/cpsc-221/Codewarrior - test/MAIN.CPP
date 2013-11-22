#include <iostream>
using namespace std;

void MakeGrid (const int m, const int n);

int main (void)
{
  string array [5][5];
  
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      array[i][j] = "i";
  
  cin >> array [3][4];
  
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
      cout << array[i][j];
    
    cout << endl;
  }  // for loop
  
  MakeGrid (6, 6);
  
  
  return EXIT_SUCCESS;
}


void MakeGrid (const int m, const int n)
{
  //string **some_array = new string *[m];
  
  //for (int i = 0; i < m; i++)
  //  some_array [i] = new string [n];
  
  string *some_array = new string [m];
  
  for (int i = 0; i < m; i++)
  {
    string *another_array = new string [n];
    some_array [i] = *another_array;
  }  // for loop
  
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      some_array[i][j] = "hello";
  
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
      cout << some_array[i][j];
    
    cout << some_array [3] << endl;
    some_array [3] = "dude";
    cout << some_array[3];
  }  // for loop
}  // MakeGrid