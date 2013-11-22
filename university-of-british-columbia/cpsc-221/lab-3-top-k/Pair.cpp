#include "Pair.h"

// file: Pair.cpp
// Implementation for Pair template class


template <class Left, class Right>
Pair<Left,Right>::Pair()
// Default constructor.
// POST: A new pair is constructed.
{
   // Nothing needs to be done, since left and right are supposed
   // to have their own default constructors.
}


template <class Left, class Right>
Pair<Left,Right>::Pair( const Pair<Left, Right>& originalPair )
// Copy constructor.
// POST: A new pair is constructed with the same value.
{
   left  = originalPair.left;
   right = originalPair.right;
}


template <class Left, class Right>
Pair<Left, Right>::Pair( const Left& otherLeft, const Right& otherRight )
// Parametrized constructor.
// POST: A new pair is constructed with the given left and right portions.
{
   left = otherLeft;
   right = otherRight;
}


template <class Left, class Right>
Pair<Left, Right>::~Pair()
// Destructor
// POST: The Pair object is destroyed
{
   // Nothing needs to be done, since left and right are supposed
   // to have their own default destructors.
}


template <class Left, class Right>
Pair<Left, Right>& Pair<Left, Right>::operator=( const Pair<Left, Right>& otherPair )
// POST:  The contents of 'otherPair' are copied into the current Pair
{
   left = otherPair.left;
   right = otherPair.right;

   return *this;           // Return a reference to this Pair
}


template <class Left, class Right>
Left Pair<Left, Right>::getLeft( ) const
// POST: The left portion is returned.
{
   return left;
}


template <class Left, class Right>
Right Pair<Left, Right>::getRight( ) const
// POST: The right portion is returned.
{
   return right;
}

template <class Left, class Right>
void Pair<Left, Right>::setLeft( Left leftValue )
// POST: left portion has been set to leftValue
{
	left = leftValue;
}


template <class Left, class Right>
void Pair<Left, Right>::setRight( Right rightValue )
// POST: right portion has been set to rightValue
{
	right = rightValue;
}



template <class Left, class Right>
ostream& operator<<( ostream& stream, const Pair<Left, Right>& thePair )
// Operator that compares just the 'left' part of the two pairs.
// POST: It returns the result of comparing the 'left' pair of the two pairs.
{
   return stream << "Pair[ " << thePair.left << " , " << thePair.right << "]";
}


template <class Left, class Right>
bool Pair<Left, Right>::operator<( const Pair<Left, Right>& otherPair ) const
// PRE:   stream is a valid ostream object
// POST:  thePair is written to ostream.
{
   return  left < otherPair.left;
}

