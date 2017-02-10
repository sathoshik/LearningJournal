#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"
#include <stdio.h>
#include <iostream> 

using namespace std;

enum state { 
  EMPTY, 
  OCCUPIED, 
  DELETED 
}; 

template<typename T> class DoubleHashTable {
  private: 
    int count; 
    int power; 
    int array_size; 
    T *array; state *array_state; 
    int h1( T const & ) const; // first hash function
    int h2( T const & ) const; // second hash function
    int hash( T const & , int) const;

  public:
    DoubleHashTable( int = 5 );
    ~DoubleHashTable();
    int size() const;
    int capacity() const;		
    bool empty() const;
    bool member( T const & ) const;
    T bin( int ) const;

    void print() const;

    void insert( T const & );
    bool remove( T const & );
    void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
  count( 0 ), power( m ),
  array_size( 1 << power ),
  array( new T [array_size] ),
  array_state( new state[array_size] ) {

    for ( int i = 0; i < array_size; ++i ) {
      array_state[i] = EMPTY;
    }
  }

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
  delete[] array;
  delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
  return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
  return array_size;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
  return !(count > 0);
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
  int k = static_cast<int>(obj);
  int mod = k%array_size;
  if (mod < 0 ) { mod += array_size; }
  return mod;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
  int k = static_cast<int>(obj);
  int mod = (k/array_size)%array_size;
  if ( mod < 0) { mod += array_size; }
  if ( mod%2 == 0) { mod ++; }
  return mod;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
  if (size() > 0) {
    int i = 0;
    while(array_state[hash(obj,i)] != EMPTY && !(array[hash(obj,i)] == obj && array_state[hash(obj,i)] ==  OCCUPIED ) && i < capacity()) {
      i++;	
    }

    if (array[hash(obj,i)] == obj && array_state[hash(obj,i)] ==  OCCUPIED) {
      return true;
    } else {
      return false;
    }

  } else {
    return false;
  }
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
  return array[n]; 
}

template<typename T > 
void DoubleHashTable<T >::insert( T const &obj ) {
  if ( size() < capacity() ) {
    int i = 0;
    while (array_state[hash(obj,i)] == OCCUPIED) {
      i++;
      if ( i > capacity() ) {
        //this is probably a redundent check.
        throw overflow();
      }
    }

    array[hash(obj,i)] = obj;
    array_state[hash(obj,i)] = OCCUPIED;
    count++;
    return;
  } else { 
    throw overflow();  
  }
} 

template<typename T > 
bool DoubleHashTable<T >::remove( T const &obj ) {
  if ( size() > 0 ) {
    int i = 0;
    while(array_state[hash(obj,i)] != EMPTY && !(array[hash(obj,i)] == obj && array_state[hash(obj,i)] ==  OCCUPIED ) && i < capacity()) {
      i++;	
    }

    if (array[hash(obj,i)] == obj && array_state[hash(obj,i)] ==  OCCUPIED) {
      array_state[hash(obj,i)] = DELETED;
      count--;
      return true;
    } else {
      return false;
    }



  } else {
    return false;
  }

}

template<typename T >
void DoubleHashTable<T >::clear() {
  std::memset(array_state, EMPTY, array_size * sizeof(int));
  count = 0;
  return ; 
}

template<typename T >
void DoubleHashTable<T >::print() const {
  // enter your implemetation here 	
  return;
}

template<typename T>
int DoubleHashTable<T >::hash( T const &obj, int i ) const{
  return (h1(obj) + (i*h2(obj)))%array_size;
}


#endif
