/*
 * This program takes a user supplied number (from the command line),
 * creates the specified number of binary tree nodes, then inserts
 * them into a binary tree. The key for each node is randomly
 * generated.  After the tree has been constructed, an inorder
 * traversal is performed, which displays all of the nodes in order.
 * Furthermore, the total number of nodes, the maximum
 * height, and the largest and smallest values in the tree are
 * displayed.  
 */


/*
 * Each binary tree node is stored using the following class
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct node {
  struct node  *left;		/* the left child node */
  struct node  *right;          /* the right child node */
  int value;			/* the value in the node */
} node;

/*
 * Variables for recording the various characteristics of the
 * constructed tree.
 */

int max_depth = 1;		/* how many levels in the tree */
int num_nodes = 0;		/* how many nodes in the tree */
int largest = 0;		/* what is the largest value */
int smallest = 1000;		/* what is the smallest value */


/*=================================================================*
 *				randnum				   *
 *=================================================================*/

int randnum(unsigned long *prev_num, unsigned long *new_num)
{
  /*
   * This function generates pseudo-random numbers between 0 and 999.
   * It does this by working through a sequence of numbers that appear
   * random (through the magic of math) and returns the last 3 digits
   * to the user. Each time a new number in the sequence is generated,
   * that number is recorded and is then used to generate the next
   * number when the procedure is called again.
   */


  /*
   * The magical formula to calculate the next pseudo-random number
   */
  *new_num = ((16807 * *prev_num) + 0) % 2147483647;

  /*
   * Record this number for next time
   */
  *prev_num = *new_num;

  /*
   * Return the last 3 digits of the number
   */
  return *new_num % 1000;
}

/*=================================================================*
 *				add_node			   *
 *=================================================================*/

void add_node(node *t,		/* the root of the tree */
	      node **prev,	/* the previous node (if it exists) */
	      int value)	/* the value to add */
{
  /*
   * Create a new binary tree node, with the key being the "value".
   * Search left and right through the tree "t" until the correct place
   * is found, then add the node. the "prev" pointer is used to allow
   * us to correctly link the new node into the parent node.
   */

  node *new_node;		/* the new node */

  /*
   * Firstly, if the tree is currently empty (NULL), or we have reached
   * the bottom of the tree, then create a new node.
   */

  if (t == NULL){		
    /*
     * Allocate storage
     */
    new_node = (node *) malloc(sizeof(node));
    if (new_node == NULL)
      fprintf(stderr,  "Error! new failed in add_node\n");

    /*
     * Set the left and right pointers, and the value
     */
    new_node->left = new_node->right = NULL;
    new_node->value = value;

    /*
     * Link into the parent node, and exit
     */
    *prev = new_node;
    return;
  }
    
  /*
   * Otherwise search left and right through the binary tree
   * to find the correct location. At each point, also pass
   * details of the parent link that will need to be updated
   */

  if (value < t->value){
    node **tmp = &(t->left);
    add_node(t->left, tmp, value);
    
  } else {
    node **tmp = &(t->right);
    add_node(t->right, tmp, value);
  }
}


/*=================================================================*
 *				in_order_check			   *
 *=================================================================*/

void in_order_check(node *t, int depth)
{
  /*
   * Do an in-order traversal of the whole tree. Keep track of
   * the maximum height of the tree, number of nodes, and the
   * largest and smallest values in the tree.
   * The nodes should be printed out in order.
   */

  if (t == NULL)
    return;

  if (t->value > largest)
    largest = t->value;

  if (t->value < smallest)
    smallest = t->value;

  if (depth > max_depth)
    max_depth = depth;

  num_nodes++;

  in_order_check(t->left, depth + 1);
  printf ("%d\n", t->value);		// fixes bug 4
  in_order_check(t->right, depth + 1);
}


/*=================================================================*
 *				main				   *
 *=================================================================*/

int main(int argc, char *argv[])
{
  /*
   * The main program that creates the tree, and then checks it
   */
  node *root = NULL;		// fixes bug 1 - initialized to NULL
  int size_of_tree;		/* the user supplied size */
  unsigned long prev_num, new_num;
  unsigned long *prev_num_pt, *new_num_pt;

  srand (time (0));       	// fixes bug 7
  prev_num = rand () % 1000;
  new_num = 1;			// fixes bug 2
  prev_num_pt = &prev_num;
  new_num_pt = &new_num;
  /*
   * Fetch the number of nodes from the user
   */
  if (argc != 2){
    fprintf(stderr, "Usage: tree <size>\n");
    exit(1);
  }
  size_of_tree = atoi(argv[1]);

  /*
   * Add the correct number of nodes.
   */
  int count;
  if (size_of_tree > 0)		// fixes bug 6
    for (count = 0; count < size_of_tree; count++)
      add_node(root, &root, randnum(prev_num_pt, new_num_pt));
  else
  {
    printf ("Zero nodes makes no tree.\n");
    return 0;
  }

  /*
   * Get and display statistics about the tree
   */
  in_order_check(root, 0);

  
  printf("Maximum depth is %d\n", max_depth);
  printf("Number of nodes is %d\n", num_nodes);	// fixes bug 3
  printf("Smallest is %d\n", smallest);		// fixes bug 5
  printf("Largest is %d\n", largest);		// fixes bug 5
  return 0;
}


/*=================================================================*/



