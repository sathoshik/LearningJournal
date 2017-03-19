/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  spkumara@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  sprint 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
using namespace std;

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
    void adjust_null_path_length();
    void traverse(Leftist_node *); 
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}


template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

template<typename Type>
Type Leftist_node<Type>::retrieve() const {
  return element;
}

template<typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const {
  return left_tree;
}

template<typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const {
  return right_tree;
}

template<typename Type>
int Leftist_node<Type>::null_path_length() const {
  if (empty()) {
    return -1;
  } else {
    return heap_null_path_length;
  }
}

//TODO
template<typename Type>
int Leftist_node<Type>::count( Type const &obj ) const {

 int sum = 0;

 if (this == nullptr) {
   return 0;
 }

 if (element == obj ) {
   sum ++;
 }
 return (left_tree -> count(obj) + right_tree -> count(obj) + sum) ;
}

template<typename Type>
void Leftist_node<Type>::push( Leftist_node<Type> *new_heap, Leftist_node<Type> *&ptr_to_this ) {
  if (new_heap == nullptr) {
    return;
  } else {
  //insert onto heap
    if ( ptr_to_this == nullptr ) {
      ptr_to_this = new_heap;
      return;
    } 
    if ( ptr_to_this -> retrieve() <= new_heap -> retrieve() ) {
      right_tree -> push( new_heap, right_tree );
      ptr_to_this -> adjust_null_path_length();
     
      if (left_tree -> null_path_length() < right_tree -> null_path_length() ) {
        std::swap(left_tree,right_tree); 
      }
    } else {
      new_heap -> push( ptr_to_this, new_heap);
      ptr_to_this = new_heap;
    }
  }
}

template<typename Type>
void Leftist_node<Type>::clear() {
 if (this == nullptr) {
  return;
 } else {
  left_tree -> clear();
  right_tree -> clear();
  delete this;
 }
}

template<typename Type>
void Leftist_node<Type>::adjust_null_path_length() {
  heap_null_path_length = std::min(left_tree -> null_path_length(), right_tree -> null_path_length()) + 1 ;
}

template<typename Type>
void Leftist_node<Type>::traverse(Leftist_node *node) {
  if (node == nullptr) {
    return;
  }
  
  traverse(node -> left());
  cout << node -> retrieve() << " ";
  traverse(node -> right());
}

#endif
