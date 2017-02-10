/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  spkumara @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2020
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    - extra test cases: jj2park
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
  private:
    int entry_count; //number of elements in the stack
    int max_count; //number of elements in the maximum array
    int min_count; //number of elements in the mimimum array
    int initial_capacity; //initial size
    int current_capacity; //current size

    int *stack_array; //stack array
    int *maximum_array; //max array
    int *minimum_array; //min array

    // You may wish to include a number of helper functions
    // in order to abstract out some operations

  public:
    Dynamic_range_stack( int = 10 );
    Dynamic_range_stack( Dynamic_range_stack const & );
    ~Dynamic_range_stack();

    int top() const;
    int size() const;
    bool empty() const;
    int capacity() const;

    int maximum() const;
    int minimum() const;

    void push( int const & );
    int pop();
    void clear();

    // Friends

    friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};
//This is the constructor. Dynamic range stack takes a n size of 10 initially
Dynamic_range_stack::Dynamic_range_stack( int n ):
  entry_count( 0 ), // entry size is originally 0
  min_count( 0 ), // min count is initally 0 
  max_count( 0 ), //max count is initially 0
  initial_capacity( std::max( 1, n ) ), // tax the max of n vs 1 to ensure that array of atleast 1 is always created
  current_capacity( initial_capacity ),
  stack_array( new int[current_capacity] ),
  maximum_array( new int[current_capacity] ),
  minimum_array( new int[current_capacity] ) {
    // empty constructor
  }

Dynamic_range_stack::~Dynamic_range_stack() {
  //deallocat al memory thats allocated
  delete[] maximum_array;
  delete[] minimum_array;
  delete[] stack_array;
}

int Dynamic_range_stack::top() const {
  //Check if the stack is empty. if not, return value at current_capacity
  if (!empty()) {
    return stack_array[entry_count-1]; 
  } else {
    throw underflow(); 
  }
}

int Dynamic_range_stack::maximum() const {

  if (!empty()) {
    return maximum_array[max_count-1];
  } else {
    throw underflow();
  }
}

int Dynamic_range_stack::minimum() const {
  //return the minimum object currently in the stack
  if(!empty()) {
    return minimum_array[min_count-1];
  } else {
    throw underflow();
  }
}

int Dynamic_range_stack::size() const {
  //returns the number of elements currently stored in the stack
  return entry_count;
}

bool Dynamic_range_stack::empty() const {
  //return true if the entry_count = <= 0 and false if else
  return (entry_count <= 0);
}

int Dynamic_range_stack::capacity() const {
  //return the current capacity of the arrays
  return current_capacity;
}



void Dynamic_range_stack::push( int const &obj ) {

  if (entry_count == 0) {
    // if the entry count is one. Cant distinguish between max and min.
    // add entry onto all three arrays
    maximum_array[entry_count] = obj;
    max_count ++;
    minimum_array[entry_count] = obj;
    min_count ++;
    stack_array[entry_count] = obj;
    entry_count ++;
    return;
  } 

  if (entry_count >= current_capacity) {
    // create new arrays of size n*2, copy over all the entries and delete the old arrays
    int *temp_stack_array = new int[current_capacity * 2]; //stack array doubles in size
    int *temp_maximum_array = new int[current_capacity * 2];
    int *temp_minimum_array = new int[current_capacity * 2];


    for (int x = 0; x < current_capacity; x++) {
      /*for the entry count to be >= current_capacity, the stack_array should not have any 
        empt indexes.*/
      temp_stack_array[x] = stack_array[x];

      if (x < max_count) {
        temp_maximum_array[x] = maximum_array[x];
      }

      if (x < min_count) {
        temp_minimum_array[x] = minimum_array[x];
      }
    }

    delete[] stack_array;
    delete[] maximum_array;
    delete[] minimum_array;

    stack_array = temp_stack_array;
    maximum_array = temp_maximum_array;
    minimum_array = temp_minimum_array;
    temp_stack_array = NULL;
    temp_maximum_array = NULL;
    temp_minimum_array = NULL;

    current_capacity = current_capacity * 2;

  } 

  //This case is for when 0 < entry_count < current_capacity
  stack_array[entry_count] = obj;
  entry_count++;
  if (obj > maximum_array[max_count-1]) { 
    maximum_array[max_count] = obj;
    max_count ++;
  } else if (obj < minimum_array[min_count-1]) {
    minimum_array[min_count] = obj;
    min_count ++;
  }

  return;
}

int Dynamic_range_stack::pop() {
  if(!empty()) {
    int value = stack_array[entry_count - 1];
    entry_count --;
    if ( value == maximum_array[max_count - 1]) {
      max_count --;
    } 
    if (value == minimum_array[min_count - 1]) {
      min_count --;
    }
    return value;
  } else {
    throw underflow();
  }
}

void Dynamic_range_stack::clear() {
  // if the current size of the stacks are not the same, re-size and create new arrays
  if (current_capacity > initial_capacity) {
    delete[] stack_array;
    stack_array = new int[initial_capacity];
    delete[] maximum_array;
    maximum_array = new int[initial_capacity];
    delete[] minimum_array;
    minimum_array = new int[initial_capacity];
    current_capacity = initial_capacity;
  }

  max_count = 0;
  min_count = 0;
  entry_count = 0;

  return;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {
  // Print out your stacks

  return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
