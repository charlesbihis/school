//////////////////////////////////////////////////////////////////////
// Name: Charles Bihis							Course: Cpsc 221	//
// Student #: 43180009							Class Section: 201	//
// Date: March 5, 2005							Lab Section L2M		//
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctype.h>
#include "cs221_header.h"
#include "queue_class.h"
#include "stack_class.h"

using namespace std;

void ShowState (StackType <int> &the_stack, QueueType <int> &the_queue, int cars);

int main ()
{
  int cars = 1;
  char input_char = ' ';
  StackType <int> the_stack;
  QueueType <int> the_queue;
  QueueType <int> out_list;
  QueueType <char> op_sequence;
  
  SayHello ();
  ShowState (the_stack, the_queue, cars);
  
  while (true)
  {
    cin >> input_char;
    input_char = toupper (input_char);
    
    switch (input_char)
    {
      case 'I': the_stack.Push (cars);
                op_sequence.Enqueue ('I');
                cars++;
                ShowState (the_stack, the_queue, cars);
                cout << the_stack.TopValue () << " has been pushed\n\n";
                break;
      case 'O': out_list.Enqueue (the_stack.Pop ());
                op_sequence.Enqueue ('O');
                ShowState (the_stack, the_queue, cars);
                cout << out_list.TailValue () << " has been popped\n\n";
                break;
      case 'E': the_queue.Enqueue (cars);
                op_sequence.Enqueue ('E');
                cars++;
                ShowState (the_stack, the_queue, cars);
                cout << the_queue.TailValue () << " has been enqueued\n\n";
                break;
      case 'D': out_list.Enqueue (the_queue.Dequeue ());
                op_sequence.Enqueue ('D');
                ShowState (the_stack, the_queue, cars);
                cout << out_list.TailValue () << " has been dequeued\n\n";
                break;
      case 'P': ShowState (the_stack, the_queue, cars);
                cout << "After ";
                op_sequence.ShowContents ();
                cout << "\nQueue: ";
                the_queue.ShowContents ();
                cout << "\nStack: ";
                the_stack.ShowContents ();
                cout << "\nOut: ";
                out_list.ShowContents ();
                cout << "\n\n";
                break;
      case 'Q': SayGoodbye ();
                exit (0);
      default: cout << "\nERROR: Invalid operation\n";
               break;
    }  // switch statement
  }  // while loop
  SayGoodbye ();
  
  return EXIT_SUCCESS;
}  // main

// Purpose: to give a visual representation of the railyard
// Inputs   the_stack - the stack that is to be outputted
//          the_queue - the queue that is to be outputted
//          cars - the value of the next car to be enqueued or pushed
// Outputs: the current state of the railyard is displayed
void ShowState (StackType <int> &the_stack, QueueType <int> &the_queue, int cars)
{
  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
       << "                          <Stack>\n"
       << "           ------------------------------------------------\n"
       << " Stack -> \t"; the_stack.ShowContents (); cout << "|\n"
       << "               --------------------------------------------\n"
       << "          |   |\n"
       << "   -------     -------------------------------------------------------------\n"
       << "                                                              " << cars << "\t<-next car\n"
       << "   -------     --------------------------------------------     ------------\n"
       << "          |   |                                            |   |\n"
       << "          |    --------------------------------------------\n"
       << " Queue -> |\t"; the_queue.ShowContents (); cout << "\n"
       << "           ---------------------------------------------------\n"
       << "                          <Queue>\n"
       << "\n\n"
       << "Please enter operation or sequence of operations...\n\n"
       << "I: Push\nO: Pop\nE: Enqueue\nD: Dequeue\nP: Print railyard state\nQ: Quit"
       << "\n\n\n";
}  // ShowState

