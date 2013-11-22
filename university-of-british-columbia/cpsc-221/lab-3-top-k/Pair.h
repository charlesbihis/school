// file: Pair.h
// Pair class

#ifndef PAIR_H
#define PAIR_H

#include <iostream>
using namespace std;

template <class Left, class Right>
class Pair

   // This class defines a pair class. And it has default constructor, copy
   //   constructor, assignment operator, and == operator, and < operator.
{
  public:

    Pair();
    // Default constructor.
    // POST: A new pair is constructed.

    Pair( const Pair& otherPair );
    // Copy constructor.
    // POST: A new pair is constructed with the same value.

    Pair( const Left& otherLeft, const Right& otherRight);
    // Parametrized constructor.
    // POST: A new pair is constructed with the given left and right portions.

    ~Pair();
    // Destructor
    // POST: The Pair object is destroyed

    Pair& operator=( const Pair& otherPair );
    // POST:  The contents of 'otherPair' are copied into the current Pair

    Left getLeft() const;
    // POST: The left portion is returned.

    Right getRight() const;
    // POST: The right portion is returned.

    void setLeft( Left leftValue );
    // POST: left portion has been set to leftValue

    void setRight( Right rightValue );
    // POST: right portion has been set to rightValue

    bool operator<( const Pair& otherPair ) const;
    // Operator that compares just the 'left' part of the two pairs.
    // POST: It returns the result of comparing the 'left' pair of the two pairs.
    //
    // This makes this pair ideal for storing a pair of key and value,
    // and then to sort them by just comparing them!

    friend ostream& operator<< <> ( ostream& stream, const Pair& thePair );
    // friend ostream& operator<<( ostream& stream, const Pair& thePair );  // use this version with MS compiler
    // PRE:   stream is a valid ostream object
    // POST:  thePair is written to ostream.

  private:

    Left left;    // The left portion.
    Right right;  // The right portion.
};

//#include "Pair.cpp"

#endif


