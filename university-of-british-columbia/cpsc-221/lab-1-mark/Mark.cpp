#include <iostream>
#include "Mark.h"
using namespace std;

// Purpose: to construct a default mark
// Input: none
// Output: a default mark in constructed
Mark :: Mark ()
{
  outOf = 0;
  weight = 0;
}  // Mark

// Purpose: to construct a mark with the given values set as the
//          private data members
// Input: int setOutOf - the value to set the private data member
//                       'outOf'
//        int setWeight - the value to set the private data member
//                        'weight'
Mark :: Mark (int setOutOf, int setWeight)
{
  outOf = setOutOf;
  weight = setWeight;
}  // Mark

// Purpose: to get the value of the private data member 'outOf'
// Input: none
// Output: the value of the private data member 'outOf' is returned
double Mark :: getOutOf () const
{
  return outOf;
}  // getOutOf

// Purpose: to get the value of the private data member 'weight'
// Input: none
// Output: the value of the private data member 'weight' is returned
double Mark :: getWeight () const
{
  return weight;
}  // getWeight

// Purpose: calculates a percent grade given a particular grade
// Input: double someGrade - the input grade used in calculating
//                           the appropriate percent grade
// Output: the value of percent grade for the particular input grade
//         is returned
double Mark :: calculatePercentGrade (double someGrade)
{
  return someGrade / outOf;
}  // calculatePercentGrade

// Purpose: calculates the weight of a grade in terms of percent
// Input: double someGrade - the input grade used in calculating
//                           the appropriate weighted grade
// Output: the weighted grade for the particular input grade is returned
double Mark :: calculateWeightedGrade (double someGrade)
{
  return (someGrade / outOf) * weight;
}  // calculateWeightedGrade                                   

// Purpose: sets the value of the private data member 'outOf' to a
//          given value
// Input: int setOutOf - the value to which the private data member 
//                       'outOf' is to be set to
// Output: the private data member 'outOf' will be changed accordingly
void Mark :: setOutOf (int setOutOf)
{
  outOf = setOutOf;
}  // setOutOf

// Purpose: sets the value of the private data member 'weight' to a
//          given value
// Input: int setWeight - the value to which the private data member 
//                       'weight' is to be set to
// Output: the private data member 'outOf' will be changed accordingly
void Mark :: setWeight (int setWeight)
{
  weight = setWeight;
}  // setWeight
