// file: MapBST.h
// Rooter file for the template version of MapBST class
//  that uses a binary search tree.

#ifndef MAPBST_H
#define MAPBST_H

#include "MapAbstract.h"
#include "Pair.h"

template <class Key, class Value>
struct MapBSTNode
{
    Key key;
    Value value;
    MapBSTNode* left;
    MapBSTNode* right;
};

template <class Key, class Value>
class MapBST : public MapAbstract< Key, Value >

   // The MapBST class defines a mapping of 'keys' to 'values'.
   // It has both default and copy constructor.

   // Requirement:
   // - "Key" for this container must have
   //      default constructor
   //      copy constructor
   //      assignment operator
   //      == operator
   //      < operator
   // - "Value" for this container must have
   //      default constructor
   //      copy constructor
   //      assignment operator
{
  public:

    MapBST( );
    // Default constructor
    // POST: An empty MapBST is created

    MapBST( const MapBST& originalMapBST );
    // Copy constructor
    // POST: A new MapBST is created containing the same elements as originalMapBST

    ~MapBST();
    // Destructor
    // POST: The MapBST object is destroyed

    MapBST& operator=( const MapBST& someMapBST );
    // Member operator function
    // POST:  The contents of 'otherMapBST' are copied into the current MapBST

    bool empty( const Key& key ) const;
    // Pre: key has been initialized
    // Post: if the key is not in the map true is returned; otherwise
    // false is returned 

    void erase( const Key& key );
    // Pre: key has been initialized
    // Post: if key is in the map it has been removed; otherwise
    // map is not changed.

    Value& operator[] ( const Key& key );
    // Pre: key has been initialized
    // Post: if key is in the map, reference to value corresponding to key 
    //       has been returned; otherwise key has been added to map with 
    //       corresponding default value
    // Exception: if map is full, map_full has been thrown

    const Value& operator[] ( const Key& key ) const;
    // Pre: key is in the map
    // Post: const reference to value corresponding to key has been returned
    // Exception: if the key is not in the map, not_valid_key has been thrown

    void dump(Pair<Key,Value>* array) const;
    // Pre: array is an array of pairs of Key and Value
    //      array must be at least size() elements long
    // Post: key and value pairs have been written into the array

  private:

    MapBSTNode<Key,Value>*  root;   // Points to the top-most node

    int dumpHelper( MapBSTNode<Key,Value>* ptr, Pair<Key,Value>* array ) const;
    // Helper function that stores the keys and values of a particular SUBTREE
    //   into a user supplied array.
    // PRE:  ptr is a pointer (which may or may not be NULL)
    //       array is an array of at least 'size()' element long.
    //
    // POST: All <key,value> pairs in the subtree is written into the array.
    //       The number of pairs written is returned as the function return value.

    void copy( const MapBST& someMapBST );
    // Helper function used by MapBST( const MapBST& someMapBST )
    // and operator=( const MapBST& someMapBST )
    // PRE:  Another MapBST object 'someMapBST' is valid
    // POST: The contents of 'someMapBST' are copied into the current MapBST

    void copySubTree( MapBSTNode<Key,Value>& root, const MapBSTNode<Key,Value>& otherRoot );
    // Private helper function that copies all values from 'otherRoot' into this root,
    //   including all child nodes.
    // PRE:   root and otherRoot are two trees.
    // POST:  All child nodes and keys and values are copied from 'otherRoot' into 'root'.

    void eraseTree( MapBSTNode<Key,Value>* ptr );
    // Private helper function that deletes a node and all children.
    // POST:  If the pointer is NULL, then nothing happens.
    //        otherwise, the node and all children are deleted.
};

//#include "MapBST.cpp"

#endif

