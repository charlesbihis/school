#include <iostream>
#include <ctype.h>
#include "queue_class.h"
#include "stack_class.h"
#include "cs221_header.h"
using namespace std;

const int MAX_NAME_SIZE = 30;

int main ()
{
  string 
    car_one = "\nlocomotive",
    car_two = "\ncoal",
    car_three = "\nuranium",
    car_four = "\nliquefied natural gas",
    car_five = "\ncrude oil",
    car_six = "\noriented strand board";
  StackType <string> the_stack;
  QueueType <string> the_queue;
  QueueType <string> out_list;
  
  SayHello ();
  
  cout << "INCOMING RAILWAY CARS:"
       << car_one << car_two 
       << car_three << car_four 
       << car_five << car_six << endl;
  
  cout << "\nCARS PUSHED ONTO THE STACK:";		// cars pushed onto the stack and displayed
  the_stack.Push (car_one);
  the_stack.Push (car_two);
  the_stack.Push (car_three);
  the_stack.Push (car_four);
  the_stack.Push (car_five);
  the_stack.Push (car_six);
  the_stack.ShowContents ();
  
  cout << "\n\nCARS POPPED OFF THE STACK:";		// cars popped off the stack being printed as
  cout << out_list.Enqueue (the_stack.Pop ())	// they are popped
       << out_list.Enqueue (the_stack.Pop ())
       << out_list.Enqueue (the_stack.Pop ())
       << out_list.Enqueue (the_stack.Pop ())
       << out_list.Enqueue (the_stack.Pop ())
       << out_list.Enqueue (the_stack.Pop ());
  //out_list.ShowContents ();					// would also work with this member function call
  
  cout << "\n\nENQUEUED:";
  the_queue.Enqueue (out_list.Dequeue ());		// enqueue those cars which have been popped
  the_queue.Enqueue (out_list.Dequeue ());		// and display the contents of the queue
  the_queue.Enqueue (out_list.Dequeue ());
  the_queue.Enqueue (out_list.Dequeue ());
  the_queue.Enqueue (out_list.Dequeue ());
  the_queue.Enqueue (out_list.Dequeue ());
  the_queue.ShowContents ();
  
  cout << "\n\nDEQUEUED:";
  cout << the_queue.Dequeue ()
       << the_queue.Dequeue ()
       << the_queue.Dequeue ()
       << the_queue.Dequeue ()
       << the_queue.Dequeue ()
       << the_queue.Dequeue ();
  
  cout << "\n\nFINAL CONTENTS OF THE STACK: ";
  the_stack.ShowContents ();
  cout << "\n\nFINAL CONTENTS OF THE QUEUE: ";
  the_queue.ShowContents ();
  SayGoodbye ();
    
  return EXIT_SUCCESS;
}  // main
