// file: MapAbstract.h
// Abstract base class for map classes

// Author: Paul Carter
// Date: June 20, 2001

#ifndef _MAPABSTRACT_H_
#define _MAPABSTRACT_H_

#include <stdexcept>
#include "Pair.h"
using namespace std;

class not_valid_key : public logic_error
{
public:
   not_valid_key() : logic_error( "Key not valid!" ) {};
   // Post: error message has been initialized
};

class map_full : public runtime_error
{
public:
    map_full() : runtime_error( "Map is full!" ) {};
    // Post: error message has been initialized
};


template< class Key, class Value >
class MapAbstract
{
public:
    MapAbstract( ) : count( 0 ) {}
    // Post: count is zero

    virtual ~MapAbstract() {}
    // Post: memory allocated to map has been released

    virtual bool empty( const Key& key ) const = 0;
    // Pre: key has been initialized
    // Post: if the key is not in the map true is returned; otherwise
    // false is returned

    virtual void erase( const Key& key ) = 0;
    // Pre: key has been initialized
    // Post: if key is in the map it has been removed; otherwise
    // map is not changed

    virtual Value& operator[]( const Key& key ) = 0;
    // Pre: key has been initialized
    // Post: if key is in the map, reference to value corresponding to key 
    //       has been returned; otherwise key has been added to map with 
    //       corresponding default value

    virtual const Value& operator[]( const Key& key ) const = 0;
    // Pre: key is in the map
    // Post: const reference to value corresponding to key has been returned
    // Exception: if the key is not in the map, not_valid_key has been thrown

    virtual int size() const { return count; }
    // Post: number of elements in the map has been returned

    virtual void dump( Pair< Key, Value >* array ) const = 0;
    // Pre: array is an array of pairs of Key and Value
    //      array must be at least size() elements long
    // Post: key and value pairs have been written into the array
    
protected:
    int count;      // number of elements in the map
};

#endif
