//////////////////////////////////////////////////////////////////////
// Name: Charles Bihis							Course: Cpsc 221	//
// Student #: 43180009							Class Section: 201	//
// Date: March 5, 2005							Lab Section L2M		//
//////////////////////////////////////////////////////////////////////

#ifndef QUEUE_CLASS_H
#define QUEUE_CLASS_H
#include <iostream>
#include <iomanip>

using namespace std;

template <class item_type>
class QueueType
{
  public:			// constructors & destructors
    QueueType ();
    ~QueueType ();

    				// accessors    				
    inline item_type HeadValue ();
    inline item_type TailValue ();
    inline int GetSize ();
    inline bool IsEmpty ();
    inline void ShowContents ();
      
    				// mutators
    inline item_type Enqueue (const item_type new_value);
    inline item_type Dequeue ();

  private:
    struct item
    {
      item_type item_value;
      item *next;
    } ;  // struct declaration
    int queue_size;
    item *head;
    item *some_item;
    item_type tail_value;
} ;  // class declaration


				// *** Constuctor ***
// Purpose: to construct the queue
// Inputs:  none
// Outputs: a queue is constructed and initialized
template <class item_type>
QueueType <item_type> :: QueueType ()
{
  queue_size = 0;
  head = new item;
  head = NULL;
}  // QueueType


				// *** Destructor ***
// Purpose: to destroy the queue
// Inputs:  none
// Outputs: the queue is deleted
template <class item_type>
QueueType <item_type> :: ~QueueType ()
{
  delete head;
}  // QueueType


				// *** Accessors ***
// Purpose: to get the value of the head item
// Inputs:  none
// Outputs: the value of the head item is returned
template <class item_type>
inline item_type QueueType <item_type> :: HeadValue ()
{
  return head->item_value;
}  // HeadValue 


// Purpose: to get the value of the tail item
// Inputs:  none
// Outputs: the value of the tail item is returned
template <class item_type>
inline item_type QueueType <item_type> :: TailValue ()
{
  return tail_value;
}  // TailValue


// Purpose: to get the size of the entire queue
// Inputs:  none
// Outputs: the size of the queue is returned
template <class item_type>
inline int QueueType <item_type> :: GetSize ()
{
  return queue_size;
}  // GetSize


// Purpose: to determine whether or not the queue is empty
// Inputs:  none
// Outputs: true is returned if the queue is empty
//          false is returned otherwise
template <class item_type>
inline bool QueueType <item_type> :: IsEmpty ()
{
  if (queue_size == 0)
    return true;

  return false;
}  // IsEmpty


// Purpose: to display the contents of the entire queue
// Inputs:  none
// Outputs: the contents of the queue are displayed
template <class item_type>
inline void QueueType <item_type> :: ShowContents ()
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
// Purpose: to enqueue in item of the queue
// Inputs:  new_value - the item value that is to be enqueued
//                    - it is templatized so it can be of varying type
// Outputs: the value of the item enqueued is returned
template <class item_type>
inline item_type QueueType <item_type> :: Enqueue (const item_type new_value)
{
  item *temp_item;
  temp_item = head;
  some_item = new item;
  queue_size++;

  if (head == NULL)
  {
    head = some_item;
    some_item->item_value = new_value;
    some_item->next = NULL;
    tail_value = new_value;
  }  // if statement
  else
  {
   while (temp_item->next != NULL)
     temp_item = temp_item->next;
     
   temp_item->next = some_item;
   some_item->item_value = new_value;
   some_item->next = NULL;
   tail_value = new_value;
  }  // else statement
  
  return new_value;
}  // Enqueue


// Purpose: to dequeue an item in the queue
// Inputs:  none
// Outputs: the value of the item dequeued is returned
template <class item_type>
inline item_type QueueType <item_type> :: Dequeue ()
{
  item_type temp_value;

  if (IsEmpty ())
  {
    cout << "\nERROR: Queue is empty\n";
    exit (0);
  }  // if statement
  else
  {
    temp_value = head->item_value;
    item *temp_item = head;
    head = head->next;
    delete temp_item;
    queue_size--;
  }  // else statement
  
  return temp_value;
}  // Dequeue

#endif
