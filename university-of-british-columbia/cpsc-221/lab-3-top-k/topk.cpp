////////////////////////////////////////////////////////////////////
//	Name: Charles Bihis												Course: Cpsc 221		//
//	Student #: 43180009												Class Section: 201	//
//	Date: April 2, 2005												Lab Section: L2M		//
////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <stdlib.h>
#include "Pair.cpp"			
#include "MapBST.cpp"
#include "CHeap.h"
using namespace std;


int main (int argc, char *argv[])
{
  string temp_word;
	MapBST<string, int> word_tree;
	CHeap word_heap;

	if (argc != 2)															// checks if usage
	{																						// is correct
		cout << "Usage: topk <input int>\n";
		exit (0);
	}  // if statement

	int limit = atoi (argv[1]);

	while (cin >> temp_word)										// reads in words
	{																						// and stores them
		if (!word_tree.empty(temp_word))					// in a BST
			word_tree[temp_word]++;
		else
			word_tree[temp_word] = 1;
	}  // while loop
  Pair<string, int> array[word_tree.size ()];
  word_tree.dump(array);					

  for (int i = 0; i < word_tree.size (); i++)	// inserts words
		word_heap.Insert (array[i]);							// into a heap

  if (limit > word_tree.size ())
	{
		cout << "\nThere are only " << word_tree.size ()
			   << " in the heap, not " << limit
				 << ", so we'll only return " << word_tree.size () << ".\n";
		limit = word_tree.size ();
	}  // if statement

  cout << endl << "The top " << limit 
		   << " most frequently occuring words in the file are:\n";

  for (int i = 0; i < limit; i++)
  {
    Pair<string, int> temp_pair = word_heap.RemoveMax ();
    cout << i + 1 << ".\t" << temp_pair.getRight () << " occurrences of:  " 
			   << temp_pair.getLeft () << endl;
  }  // for loop

  cout << endl << "After removing the top " << limit
		   << " items from the heap, there are " << word_heap.GetSize () 
			 << " pairs left." << endl;

	return EXIT_SUCCESS;
}  // main
