/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  spkumara@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Spring 2017
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

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"
#include <iostream>

using namespace std;

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		
		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();
    void traverse();

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};


template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}


template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}


template<typename Type>
bool Leftist_heap<Type>::empty() const {
  return !(heap_size > 0);
}

template<typename Type>
int Leftist_heap<Type>::size() const {
  return heap_size;
}

template<typename Type>
int Leftist_heap<Type>::null_path_length() const {
  return root_node -> null_path_length();
} 

//Return the number of instances of the argument in the heap.
//count how many times obj occurs in the heap.
template<typename Type>
int Leftist_heap<Type>::count(Type const &obj) const {
  return root_node -> count(obj);
}

//The top of the heap will always be the root.
template<typename Type>
Type Leftist_heap<Type>::top() const {
  if (!empty()) {
    return root_node -> retrieve();
  } else {
    throw underflow();
  }
}

template<typename Type>
void Leftist_heap<Type>::push( Type const &obj ) {
  Leftist_node<Type> *new_node;
  new_node = new Leftist_node<Type>(obj);

  root_node -> push(new_node,root_node);
/*  Leftist_node<Type> * temp;

  cout << "root: " << root_node -> retrieve() << " null path " << root_node -> null_path_length() << endl;
  if (root_node -> left() != nullptr) {
    cout << "Lnode: " << root_node -> left() -> retrieve() << " null path " << root_node -> left() -> null_path_length() << endl;
    temp = root_node -> left();
  

    if (temp -> left() != nullptr) {
      cout << "LLnode: " << temp -> left() -> retrieve() << " null path " << temp -> left() -> null_path_length() << endl;
    }

    if (temp -> right() != nullptr) {
      cout << "LRnode: " << temp -> right() -> retrieve() << " null path " << temp -> right() -> null_path_length() << endl;
    }
  }

  if (root_node ->right() != nullptr) {
    cout << "Rnode: " << root_node -> right() -> retrieve() << " null path " << root_node -> right() -> null_path_length() << endl;
    temp = root_node -> right();
  

    if (temp -> left() != nullptr) {
      cout << "RLnode: " << temp -> left() -> retrieve() << " null path " << temp -> left() -> null_path_length() << endl;
    }

    if (temp -> right() != nullptr) {
      cout << "RRnode: " << temp -> right() -> retrieve() << " null path " << temp -> right() -> null_path_length() << endl;
    }
  }
*/
  heap_size ++ ;
  return;
}

template<typename Type>
Type Leftist_heap<Type>::pop() {

  if (empty()) {
    throw underflow();
  } else {
    
    Type value  = root_node -> retrieve();
    
    Leftist_node<Type> *right_node = root_node -> right();
    Leftist_node<Type> *left_node = root_node -> left();
    
    delete root_node;

    root_node = left_node;
    root_node -> push(right_node, root_node );
    heap_size --;
    
    return value;
   

  }
}

template<typename Type>
void Leftist_heap<Type>::clear() {
  root_node -> clear();
  root_node = nullptr;
  heap_size = 0;
}

template<typename Type>
void Leftist_heap<Type>::traverse() {
  root_node -> traverse(root_node);
}

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}
// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
