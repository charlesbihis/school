#ifndef MARK_H
#define MARK_H

#include <iostream>
using namespace std;

class Mark
{
  public:		// *** Constructors ***
    Mark ();
    Mark (int setOutOf, int setWeight);
    			// *** Accessors - standard ***
    double getOutOf () const;
    double getWeight () const;
    			// *** Accessors - manipulator ***
    double calculatePercentGrade (double someGrade);
    double calculateWeightedGrade (double someGrade);
    			// *** Mutators ***
    void setOutOf (int setOutOf);
    void setWeight (int setWeight);
  
  private:
    int
      outOf,
      weight;
};  // class declaration

#endif
