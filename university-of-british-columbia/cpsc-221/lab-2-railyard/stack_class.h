//////////////////////////////////////////////////////////////////////
// Name: Charles Bihis							Course: Cpsc 221	//
// Student #: 43180009							Class Section: 201	//
// Date: March 5, 2005							Lab Section L2M		//
//////////////////////////////////////////////////////////////////////

#ifndef STACK_CLASS_H
#define STACK_CLASS_H
#include <iostream>
#include <string.h>

using namespace std;

template <class item_type>
class StackType
{
  public:			// constructors & destructors
    StackType ();
    ~StackType ();
    
    				// accessors
    item_type TopValue ();
    item_type BottomValue ();
    int GetSize ();
    bool IsEmpty ();
    void ShowContents ();

					// mutators    
    item_type Push (const item_type new_value);
    item_type Pop ();

  private:
    struct item
    {
      item_type item_value;
      item *next;
    } ;  // struct declaration
    int stack_size;
    item *head;
    item *some_item;
    item_type bottom_value;
} ;  // class declaration


				// *** Constructor ***
// Purpose: to construct the stack
// Inputs:  none
// Outputs: a stack is constructed and initialized
template <class item_type>
StackType <item_type> :: StackType ()
{
  stack_size = 0;
  head = new item;
  head = NULL;
}  // SomeType


				// *** Destructor ***
// Purpose: to destroy the stack
// Inputs:  none
// Outputs: the stack is deleted
template <class item_type>
StackType <item_type> :: ~StackType ()
{
  delete head;
}  // SomeType


				// *** Accessors ***
// Purpose: to get the value of the top item
// Inputs:  none
// Outputs: the value of the top item is returned
template <class item_type>
inline item_type StackType <item_type> :: TopValue ()
{
  if (!IsEmpty ())
    return head->item_value;
  
  return -1;
}  // Top Value


// Purpose: to get the value of the bottom item
// Inputs: none
// Outputs: the value of the bottom item is returned
template <class item_type>
inline item_type StackType <item_type> :: BottomValue ()
{
  return bottom_value;
}  // BottomValue


// Purpose: to get the size of the entire stack
// Inputs:  none
// Outputs: the size of the stack is returned
template <class item_type>
inline int StackType <item_type> :: GetSize ()
{
  cout << "GetSize is " << queue_size << endl;
  return queue_size;
}  // GetSize


// Purpose: to determine whether or not the stack is empty
// Inputs:  none
// Outputs: true is returned if the stack is empty
//          false is returned otherwise
template <class item_type>
inline bool StackType <item_type> :: IsEmpty ()
{
  if (stack_size == 0)
    return true;

  return false;
}  // IsEmpty


// Purpose: to display the contents of the entire stack
// Inputs:  none
// Outputs: the contents of the stack are displayed
template <class item_type>
inline void StackType <item_type> :: ShowContents ()
{
  item *temp_item;
  temp_item = head;
  item_type temp_value;
  
  if (IsEmpty ())
    cout << "empty";
  else
    while (temp_item != NULL)
    {
      temp_value = temp_item->item_value;
      cout << temp_value << "  ";
      temp_item = temp_item->next;
    }  // while loop
}  // ShowContents


				// *** Mutators ***
// Purpose: to push an item into the stack
// Inputs:  new_value - the item value that is to be pushed
//                    - it is templatized so it can be of varying type
// Outputs: the value of the item pushed is returned
template <class item_type>
inline item_type StackType <item_type> :: Push (const item_type new_value)
{
  item *temp_item = new item;
  some_item = new item;
  stack_size++;

  if (IsEmpty ())
  {
    head = some_item;
    some_item->item_value = new_value;
    some_item->next = NULL;
    bottom_value = new_value;
  }  // if statement
  else
  {
   temp_item->next = head;
   temp_item->item_value = new_value;
   head = temp_item;
  }  // else statement
  
  return new_value;
}  // Enqueue


// Purpose: to pop an item from the stack
// Inputs:  none
// Outputs: the value of the item popped is returned
template <class item_type>
inline item_type StackType <item_type> :: Pop ()
{
  item_type temp_value;

  if (IsEmpty ())
  {
    cout << "\nERROR: Stack is empty\n";
    exit (0);
  }  // if statement
  else
  {
    temp_value = head->item_value;
    item *temp_item = head;
    head = head->next;
    delete temp_item;
    stack_size--;
  }  // else statement

  return temp_value;
}  // Dequeue

#endif
