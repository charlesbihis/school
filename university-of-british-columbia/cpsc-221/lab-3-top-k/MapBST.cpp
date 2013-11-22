#include "MapBST.h"

// file: MapBST.cpp
// Template implementation file for the MapBST class


template <class Key, class Value>
MapBST<Key,Value>::MapBST( )
// Default constructor
// POST: An empty MapBST is created
{
   root = NULL;
}


template <class Key, class Value>
MapBST<Key,Value>::MapBST( const MapBST<Key,Value>& someMapBST )
// Copy constructor
// POST: A new MapBST is created containing the same elements as originalMapBST
{
   copy( someMapBST );
}


template <class Key, class Value>
MapBST<Key,Value>::~MapBST()
// Destructor
// POST: The MapBST object is destroyed
{
   eraseTree( root );
}


template <class Key, class Value>
MapBST<Key,Value>& MapBST<Key,Value>::operator=( const MapBST<Key,Value>& someMapBST )
// Member operator function
// POST:  The contents of 'otherMapBST' are copied into the current MapBST
{
   if ( &someMapBST != this )
   {
      eraseTree( root );
      copy( someMapBST );
   }

   return *this;
}


template <class Key, class Value>
bool MapBST<Key,Value>::empty( const Key& key ) const
// Pre: key has been initialized
// Post: if the key is not in the map true is returned; otherwise
// false is returned 
{
   MapBSTNode<Key,Value>* ptr = root;

   while(ptr != NULL)
   {
     if (ptr->key == key)
     {
        return false;
     }

     if (ptr->key < key)
     {
        ptr = ptr->right;
     }
     else
     {
        ptr = ptr->left;
     }
   }

   return true;
}


template <class Key, class Value>
void MapBST<Key,Value>::erase( const Key& key )
// Pre: key has been initialized
// Post: if key is in the map it has been removed; otherwise
// map is not changed.
{
   // === Searching Phase ===

   MapBSTNode<Key,Value>** parent = &root;
   MapBSTNode<Key,Value>*  node = root;

   if (node == NULL)
   {
      return;   // No such key in the map. So do nothing.
   }

   if (node->key != key)
   {
      while(true)
      {
         if (node->key < key)
         {
            if (node->right == NULL)
            {
               return;     // No such key in the map. So do nothing.
            }

            if (node->right->key == key)   // Found it!
            {
               parent = &(node->right);
               node = node->right;
               break;
            }

            node = node->right;
         }
         else
         {
            if (node->left == NULL)
            {
               return;      // No such key in the map. So do nothing.
            }

            if (node->left->key == key)    // Found it!
            {
               parent = &(node->left);
               node = node->left;
               break;
            }

            node = node->left;
         }
      }
   }

   // === Deletion Phase ===

   // Decrement the counter
   count--;

   // If it does not have a left child...
   if (node->left == NULL)
   {
      *parent = node->right;
      delete node;
      return;
   }

   // If it does not have a right child...
   if (node->right == NULL)
   {
      *parent = node->left;
      delete node;
      return;
   }

   // Has both children. So let's find its predecessor...

   // If the left child IS the predecesor...
   if (node->left->right == NULL)
   {
      *parent = node->left;
      node->left->right = node->right;
      delete node;
      return;
   }

   // Else, search for the predecessor...
   MapBSTNode<Key,Value>* ptr = node -> left;
   while(true)
   {
      if (ptr->right->right == NULL)  // Found the predecessor
      {
         *parent = ptr->right;
         ptr->right = ptr->right->left;
         (*parent)->right = node->right;
         (*parent)->left  = node->left;
         delete node;
         return;
      }

      ptr = ptr->right;
   }
}


template <class Key, class Value>
Value& MapBST<Key,Value>::operator[]( const Key& key )
// Pre: key has been initialized
// Post: if key is in the map, reference to value corresponding to key 
//       has been returned; otherwise key has been added to map with 
//       corresponding default value
// Exception: if map is full, map_full has been thrown
{
   MapBSTNode<Key,Value>* ptr;

	try
	{
	   if (root == NULL)  // No such key. So add it.
	   {
		 count ++;
		 root = new MapBSTNode<Key,Value>;
		 root->key = key;
		 root->left = NULL;
		 root->right = NULL;
		 return root->value;
	   }

	   ptr = root;

	   while( true )
	   {
		 if (ptr->key == key)
		 {
			return ptr->value;
		 }

		 if (ptr->key < key)
		 {
			if (ptr->right == NULL)  // No such key. So add it.
			{
			   count++;
			   ptr->right = new MapBSTNode<Key,Value>;
			   ptr->right->key = key;
			   ptr->right->left = NULL;
			   ptr->right->right = NULL;
			   return ptr->right->value;
			}
			ptr = ptr->right;
		 }
		 else
		 {
			if (ptr->left == NULL)  // No such key. So add it.
			{
			   count++;
			   ptr->left = new MapBSTNode<Key,Value>;
			   ptr->left->key = key;
			   ptr->left->left = NULL;
			   ptr->left->right = NULL;
			   return ptr->left->value;
			}
			ptr = ptr->left;
		 }
	   }
	}
	catch( bad_alloc& )
	{
	   throw map_full();
	}
}


template <class Key, class Value>
const Value& MapBST<Key,Value>::operator[]( const Key& key ) const
// Pre: key is in the map
// Post: const reference to value corresponding to key has been returned
// Exception: if the key is not in the map, not_valid_key has been thrown
{
   MapBSTNode<Key,Value>* ptr;

   if (root == NULL)
   {
     throw not_valid_key();
   }

   ptr = root;

   while( true )
   {
     if (ptr->key == key)
     {
        return ptr->value;
     }

     if (ptr->key < key)
     {
        if (ptr->right == NULL)
        {
			throw not_valid_key();
        }
        ptr = ptr->right;
     }
     else
     {
        if (ptr->left == NULL)
        {
           throw not_valid_key();
        }
        ptr = ptr->left;
     }
   }
}


template <class Key, class Value>
void MapBST<Key,Value>::dump( Pair<Key,Value>* data ) const
// Pre: array is an array of pairs of Key and Value
//      array must be at least size() elements long
// Post: key and value pairs have been written into the array
{
   dumpHelper( root, data );
}


template <class Key, class Value>
int MapBST<Key,Value>::dumpHelper( MapBSTNode<Key,Value>* ptr, Pair<Key,Value>* data) const
// Helper function that stores the keys and values of a particular SUBTREE
//   into a user supplied array.
// PRE:  ptr is a pointer (which may or may not be NULL)
//       array is an array of at least 'size()' element long.
//
// POST: All <key,value> pairs in the subtree is written into the array.
//       The number of pairs written is returned as the function return value.
{
   int offset;

   if (ptr == NULL)
   {
      return 0;
   }

   if (ptr->left != NULL)
   {
      offset = dumpHelper(ptr->left, data );
   }
   else
   {
      offset = 0;
   }

   data[offset].setLeft( ptr->key );
   data[offset].setRight( ptr->value );

   offset++;

   return offset + dumpHelper(ptr->right, data + offset);
}


template <class Key, class Value>
void MapBST<Key,Value>::copy( const MapBST<Key,Value>& someMapBST )
// Helper function used by MapBST( const MapBST& someMapBST )
// and operator=( const MapBST& someMapBST )
// PRE:  Another MapBST object 'someMapBST' is valid
// POST: The contents of 'someMapBST' are copied into the current MapBST
{
   count = someMapBST.count;

   if (someMapBST -> root == NULL)
   {
      root = NULL;
   }
   else
   {
      root = new MapBSTNode<Key,Value>;
      copySubTree(root, someMapBST->root);
   }
}


template <class Key, class Value>
void
MapBST<Key,Value>::copySubTree( MapBSTNode<Key,Value>& root, const MapBSTNode<Key,Value>& otherRoot )
// Private helper function that copies all values from 'otherRoot' into this root,
//   including all child nodes.
// PRE:   root and otherRoot are two trees.
// POST:  All child nodes and keys and values are copied from 'otherRoot' into 'root'.
{
   root->key = otherRoot->key;
   root->value = otherRoot->value;

   if (otherRoot->left != NULL)
   {
      root->left = new MapBSTNode<Key,Value>;
      copySubTree( root->left, otherRoot->left );
   }
   else
   {
      root->left = NULL;
   }

   if (otherRoot->right != NULL)
   {
      root->right = new MapBSTNode<Key,Value>;
      copySubTree( root->right, otherRoot->right );
   }
   else
   {
      root->right = NULL;
   }
}


template <class Key, class Value>
void
MapBST<Key,Value>::eraseTree( MapBSTNode<Key,Value>* ptr )
// Private helper function that deletes a node and all children.
// POST:  If the pointer is NULL, then nothing happens.
//        otherwise, the node and all children are deleted.
{
   if (ptr != NULL)
   {
      eraseTree( ptr -> left );
      eraseTree( ptr -> right );
      delete ptr;
   }
}

