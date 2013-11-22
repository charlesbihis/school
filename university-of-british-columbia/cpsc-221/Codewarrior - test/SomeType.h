#ifndef SOME_TYPE_H
#define SOME_TYPE_H
#include <iostream.h>
#include <iomanip.h>


//typedef int item_type;
template <class item_type>
class SomeType
{
  public:
    SomeType ();
    ~SomeType ();
    
    inline  bool IsEmpty ();
    inline void ShowContents ();
    inline void Enqueue (const item_type new_value);
    inline item_type Dequeue ();
    inline int GetSize ();
    inline int HeadValue ();
    inline int TailValue ();
    inline int GetValue ();
    inline int SetValue (const int new_value);
  
  private:
    struct node
    {
      item_type element_value;
      node *next;
    } ;  // struct declaration
    int queue_size;
    node *head;
    node *some_node;
    
} ;  // class declaration
///*
template <class item_type>
SomeType <item_type> :: SomeType ()
{
  queue_size = 0;
  head = new node;
  head = NULL;
  some_node = new node;
}  // SomeType
//*/

template <class item_type>
SomeType <item_type> :: ~SomeType ()
{
  delete head;
  delete some_node;
}  // SomeType

template <class item_type>
inline bool SomeType <item_type> :: IsEmpty ()
{
  if (queue_size == 0)
    return true;

  return false;
}  // IsEmpty

template <class item_type>
inline void SomeType <item_type> :: ShowContents ()
{
  node *temp_node;
  temp_node = head;
  item_type temp_value;
  //cout << left << setw (30);
  if (IsEmpty ())
    cout << "empty";
  else
  {
    while (temp_node != NULL)
    {
      temp_value = temp_node->element_value;
      cout << temp_value << "  ";
      temp_node = temp_node->next;
    }  // while loop
  }  // else statement
}  // ShowContents

template <class item_type>
inline void SomeType <item_type> :: Enqueue (const item_type new_value)
{
  node *temp_node;
  temp_node = head;
  some_node = new node;
  queue_size++;

  if (head == NULL)
  {
    //cout << "****";
    cout << "* " << new_value << " is enqueued\n";
    head = some_node;
    some_node->element_value = new_value;
    some_node->next = NULL;
    //cout << "^^^\n";
  }  // if statement
  else
  {
   //cout << "&&&&";
   cout << "* " << new_value << " is enqueued\n";
   while (temp_node->next != NULL)
     temp_node = temp_node->next;
     
   temp_node->next = some_node;
   some_node->element_value = new_value;
   some_node->next = NULL;
   //cout << "%%%\n";
  }  // else statement
}  // Enqueue

template <class item_type>
inline item_type SomeType <item_type> :: Dequeue ()
{
  item_type temp_value;

  if (IsEmpty ())
  {
    cout << "\nERROR: Queue is empty\n";
    exit (0);
  }  // if statement
  else
  {
    temp_value = head->element_value;
    node *temp_node = head;
    cout << "* " << head->element_value << " is dequeued\n";
    head = head->next;
    delete temp_node;
    queue_size--;
  }  // else statement
  
  return temp_value;
}  // Dequeue

template <class item_type>
inline int SomeType <item_type> :: GetSize ()
{
  cout << "GetSize is " << queue_size << endl;
  return queue_size;
}  // GetSize

template <class item_type>
inline int SomeType <item_type> :: HeadValue ()
{
  cout << "\nHeadValue is -1";
  return -1;
}  // HeadValue 

template <class item_type>
inline int SomeType <item_type> :: GetValue ()
{
  cout << "\nElementValue = " << (*head).element_value;
  return (*head).element_value;
}  // ElementValue

template <class item_type>
inline int SomeType <item_type> :: TailValue ()
{
  cout << "\nTailValue is -2";
  return -2;
}  // TailValue

template <class item_type>
inline int SomeType <item_type> :: SetValue (const int new_value)
{
  cout << "\nValue has been set to " << new_value;
  (*head).element_value = new_value;
  return 1;
}  // SetValue

#endif