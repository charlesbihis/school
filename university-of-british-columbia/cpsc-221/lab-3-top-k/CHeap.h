////////////////////////////////////////////////////////////////////
//	Name: Charles Bihis												Course: Cpsc 221		//
//	Student #: 43180009												Class Section: 201	//
//	Date: April 2, 2005												Lab Section: L2M		//
////////////////////////////////////////////////////////////////////

#ifndef CHEAP_H
#define CHEAP_H

#include <iostream>
using namespace std;

const int START_SIZE = 10;
typedef Pair<string, int> PairType;

class CHeap
{
	public:
				// *** Constructors ***	//
		CHeap ();
		~CHeap ();
				// *** Accessors ***	//
		inline int GetMax ();
		inline int GetSize ();
				// *** Mutators ***	//
		inline void Insert (PairType pair);
		inline PairType RemoveMax ();
		inline void InsertSpecial (PairType pair, int start, int end);

	private:
		int max;
		int size;
		PairType *heap;
} ;  // class declaration


// Purpose: constructs the heap and initializes the private data members
// Inputs/Preconditions: none
// Outputs/Postconditions: the heap is constructed and ready for manipulation
CHeap :: CHeap ()
{
	max = START_SIZE;
	size = 0;
	heap = new PairType[max];
}  // HeapType


// Purpose: destroys the heap
// Inputs/Preconditions: the heap has been constructed
// Outputs/Postconditions: the heap is deleted
CHeap :: ~CHeap ()
{
  delete[] heap;
	size = 0;
}  // ~HeapType


// Purpose: accesses the max size of the heap
// Inputs/Preconditions: none
// Outputs/Postconditions: 'max' is returned
inline int CHeap :: GetMax ()
{
	return max;
}  // GetMax


// Purpose: accesses the size of the heap
// Inputs/Preconditions: none
// Outputs/PostConditions: 'size' is returned
inline int CHeap :: GetSize ()
{
  return size;
}  // GetSize


// Purpose: inserts a pair into the heap
// Inputs/Preconditions: a valid pair is taken in to be inserted
//											 into the heap and then bubbled accordingly
//                       to maintain a valid heap
// Outputs/Postconditions: a valid heap with the argument pair inserted
inline void CHeap :: Insert (PairType pair)
{
	if (size >= max)
  {
    cout << "Heap has been resized to hold up to " << max * 2 << " pairs/entries" << endl;
    max = max * 2;													// double the size of the array
    PairType* temp = new PairType[max];
    for (int i=0; i < size; i++) {
      temp[i] = heap[i];										// copy values to new array.
    }
    delete [] heap;
        heap = temp;												// point to new array

	}  // if statement

	int hole = size;
	int parent = (hole - 1) / 2;

	while (hole > 0 && heap[parent].getRight () < pair.getRight ())
	{
		heap[hole] = heap[parent];
		hole = parent;
		parent = (parent - 1) / 2;
	}

	heap[hole] = pair;
	size++;
}  // Insert


// Purpose: removes the max pair in the heap (ie the top pair)
// Inputs/Preconditions: none
// Outputs/Postconditions: a valid heap with the top pair removed
inline PairType CHeap :: RemoveMax ()
{
	if (size == 0)
	{
		perror(" Heap is empty ");
    return heap[0];  //This is an error; any value is fine
	}  // if statement

  PairType temp = heap[0];
  // remove the largest item

  size--;

  // insert the last item in the heap 
  // whose root is empty 

	InsertSpecial (heap[size], 0, size - 1); 
  return temp;
}  // RemoveMax


// Purpose: inserts a given pair into the heap given a start position
//          and end position from which to start looking to insert
// Inputs/Preconditions: none
// Outputs/Postconditions: a valid heap with the argument pair inserted
inline void CHeap :: InsertSpecial (PairType pair, int start, int end)
{
  int child = 2 * start + 1;   // left child of start 
	
  while (child <= end) 
  {
    if (child <  end && heap[child].getRight () < heap[child + 1].getRight ())
	    child++;   
			// child is the larger child of start 

    if (pair.getRight () > heap[child].getRight ())
	    break;       // item stays in start 
    else 
    {
	    heap[start] = heap[child];
	    start = child;
	    child = 2 * start + 1;
    }  // else statement
  }  // while loop

  heap[start] = pair;
}  // InsertSpecial

#endif
