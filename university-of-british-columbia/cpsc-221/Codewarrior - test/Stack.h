#ifndef STACK_H
#define STACK_H
#include <iostream.h>


//typedef int item_type;
template <class item_type>
class Stack
{
  public:
    Stack ();
    ~Stack ();
    
    inline  bool IsEmpty ();
    inline void ShowContents ();
    inline void Push (const item_type new_value);
    inline item_type Pop ();
    inline int GetSize ();
  
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
Stack <item_type> :: Stack ()
{
  queue_size = 0;
  head = new node;
  head = NULL;
  some_node = new node;
}  // SomeType
//*/

template <class item_type>
Stack <item_type> :: ~Stack ()
{
  delete head;
  delete some_node;
}  // SomeType

template <class item_type>
inline bool Stack <item_type> :: IsEmpty ()
{
  if (queue_size == 0)
    return true;

  return false;
}  // IsEmpty

template <class item_type>
inline void Stack <item_type> :: ShowContents ()
{
  node *temp_node;
  temp_node = head;
  item_type temp_value;
  
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
inline void Stack <item_type> :: Push (const item_type new_value)
{
  node *temp_node = new node;
  //temp_node = head;
  some_node = new node;
  queue_size++;

  if (head == NULL)
  {
    cout << "* " << new_value << " is pushed\n";
    head = some_node;
    some_node->element_value = new_value;
    some_node->next = NULL;
  }  // if statement
  else
  {
   cout << "* " << new_value << " is pushed\n";
   temp_node->next = head;
   temp_node->element_value = new_value;
   head = temp_node;

  }  // else statement
}  // Enqueue

template <class item_type>
inline item_type Stack <item_type> :: Pop ()
{
  item_type temp_value;

  if (IsEmpty ())
  {
    cout << "\nERROR: Stack is empty\n";
    exit (0);
  }  // if statement
  else
  {
    temp_value = head->element_value;
    node *temp_node = head;
    cout << "* " << head->element_value << " is popped\n";
    head = head->next;
    delete temp_node;
    queue_size--;
  }  // else statement
  
  return temp_value;
}  // Dequeue

template <class item_type>
inline int Stack <item_type> :: GetSize ()
{
  cout << "GetSize is " << queue_size << endl;
  return queue_size;
}  // GetSize

#endif