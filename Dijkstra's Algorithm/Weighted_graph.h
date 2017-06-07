/*****************************************
 * UW User ID:  spkumara
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include <cstring>
#include "Exception.h"

using namespace std;

struct vertex;
struct adjacentNode;

struct vertex {
  double depth;
  adjacentNode *adjacentList;
  int degree;
  int heapIndex;
  int tailIndex;

  vertex():
      adjacentList(nullptr),
      degree(0),
      heapIndex(0),
      tailIndex(-1){
      }

};

struct adjacentNode {
  adjacentNode *next;
  double weight;

  adjacentNode():
      weight(0),
      next(nullptr){
      }

};

/*---------------------------------------------------------------------------------------
 * HEAP ADT
 * --------------------------------------------------------------------------------------
 */

class Heap {
  private:
    int *array;
    int size;
    int initialSize;
    vertex *vertices;

  public:
    Heap( int, int, vertex *);
    ~Heap();
    int left( int ) const;
    int right( int ) const;
    int parent( int ) const;
    int heapSize() const;
    int top() const;

    void insert( int );
    bool isEmpty() const;
    void heapify( int );
    int extractMin();
    void modifyKey(int);

    void print();

};

Heap::Heap(int m, int s, vertex *graph):
  size(1), //always create a heap of size 1 initially
  initialSize(m),
  vertices(graph),
  array ( new int[m +1] ) {
 
    array[0] = 0;
    array[1] = s;
    vertices[s].heapIndex = 1;
}

Heap::~Heap() {
  delete[] array;
}

int Heap::left( int i ) const {
  
  if ( 2*i > size + 1) {
    return i;
  } else {
    return 2*i;
  }
}

int Heap::right( int i ) const {
  if ((2*i +1 ) > size +1 ){
    return i;
  } else {
    return 2*i + 1;
  }
}

int Heap::parent( int i ) const {
  if ( i <= 1 ) {
    return 1;
  }

  return std::floor(i/2);
}

bool Heap::isEmpty() const {
  //heap actually starts at index 1. This anything below the size of 2 is useless.
  return !(size >= 1);
}

int Heap::heapSize() const {
  return size;
}

int Heap::top() const{
  
  if (isEmpty()) {
    throw underflow();
  }

  return array[1];

}

void Heap::heapify( int i ) {
  while (i <= size ) {
    //cout << "Starting to heapify at " << i << endl;
    //print();
    //heapify starting at index i
    int l = left(i);
    //cout << "left index of i is " << l << endl;
    int r = right(i);
    //cout << "right index of i is " << r << endl;
    int smallestIndex = 0;
 
    if ( l <= size && vertices[array[l]].depth < vertices[array[i]].depth ) {
      //cout << "no seg fault smallest is (" << l << "," << i << ")" << endl;
      //cout << "left depth " <<vertices[array[l]].depth << endl;
      //cout << "i depth " << vertices[array[i]].depth << endl;
      smallestIndex = l;
    } else {
      smallestIndex = i;
    }

    if ( r <= size && vertices[array[r]].depth < vertices[array[smallestIndex]].depth ) {
      smallestIndex = r;
      //cout << "no seg faul is (" << r << "," << i <<")" << endl;
      //cout << "right depth " <<vertices[array[r]].depth << endl;
      //cout << "i depth " << vertices[array[i]].depth << endl;
    }

    if (smallestIndex != i) {
      std::swap(array[i],array[smallestIndex]);
      vertices[array[smallestIndex]].heapIndex = smallestIndex;
      vertices[array[i]].heapIndex = i;
      //cout << "no seg faul " << endl;
      i = smallestIndex;
    } else {
      break;
    }
  }
}

int Heap::extractMin() {
  if (isEmpty()){
    throw underflow();
  }

  int min = array[1];

  //update the value of the heap index in the vertex array
  vertices[array[1]].heapIndex = -1;
  array[1] = array[size];
  vertices[array[1]].heapIndex = 1;
  size --;
  //cout << "Extract min value of index of " << min << endl;
  //call heapify on the first index.
  heapify(1);
    
  return min;
}

void Heap::modifyKey(int i) {

  if ( vertices[array[parent(i)]].depth >= vertices[array[i]].depth) {
    while ( i > 1 && vertices[array[parent(i)]].depth > vertices[array[i]].depth ) {

      int temp = parent(i);
      std::swap(array[i],array[temp]);
      vertices[array[i]].heapIndex = i;
      vertices[array[temp]].heapIndex = temp;
      i = temp;
    }
  } else {
  
   heapify(i);
 
 }
}

void Heap::insert(int node) {

  if ( size >= initialSize ) {
    throw overflow();
  }

  size ++;
  int i = size;
  
  while ( i > 1 && vertices[array[parent(i)]].depth > vertices[node].depth ) {
    array[i] = array[parent(i)];
    vertices[array[i]].heapIndex = i; //update heapIndex
    i = parent(i);
  }

  array[i] = node; //insert node into the heap.
  vertices[node].heapIndex = i; //update the heapIndex on the vertex

}

void Heap::print() {

  cout << endl;
  cout << "Heap -> " ;
  for (int i = 1 ; i < size +1 ; i ++ ) {
    cout << " |" << array[i] << "," << vertices[array[i]].depth ;
  }

  cout << endl;

  cout << "Vertex Heap Index -> ";

  for (int i = 0; i < initialSize; i++ ) {
    cout << " |" << i << "," <<  vertices[i].heapIndex;
  }
  cout << endl;
  cout << endl;
}


/*----------------------------------------------------------------------------------
 * WEIGHTED GRAPH
 * ---------------------------------------------------------------------------------
 */

class Weighted_graph {
	private:
    int verticesCount;
    int edges;
    vertex *vertices;
    adjacentNode **matrix;
    int previousIndex;
    Heap *pq;

		static const double INF;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int ) ;

		void insert( int, int, double );
    void relax(vertex, adjacentNode *, int) const;
    void print() const; // TODO

    double shortestPath(int, int) ;

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

Weighted_graph::Weighted_graph(int n):
  verticesCount(std::max(1,n)),
  edges(0),
  pq(nullptr),
  previousIndex(-1),
  vertices( new vertex[verticesCount]),
  matrix( new adjacentNode*[verticesCount]) {
    //initialize the matrix of pointers
    for ( int i=0; i< verticesCount; i++){
      matrix[i]= new adjacentNode[verticesCount];
    }
}

Weighted_graph::~Weighted_graph() {
  //clean up memory
  for (int i = 0 ; i < verticesCount ; i ++ ){
    delete[] matrix[i];
  }

  delete[] matrix;
  delete[] vertices;
  delete pq;
}

int Weighted_graph::degree(int n) const {
  return vertices[n].degree;
}

int Weighted_graph::edge_count() const {
  return edges;
}

double Weighted_graph::adjacent(int m, int n) const {
 
  if (m < 0 || m >= verticesCount || n < 0 || n >= verticesCount ) {
    throw illegal_argument();
  }

  if ( m == n){
      return 0;
  }
  
  if (matrix[m][n].weight > 0 ) {
    return matrix[m][n].weight;
  } else {
    return INF;
  }
}

double Weighted_graph::shortestPath(int m, int n) {
    
  if ( previousIndex == -1 || previousIndex != m) {
    for (int i = 0; i < verticesCount; i++) {
      //Initialize the depth all vertices to INF 
      vertices[i].depth = INF; 
      vertices[i].heapIndex = -5;
    }

    vertices[m].depth = 0;
    previousIndex = m;
    
    //clean up any garbage heap
    delete pq;
    pq = new Heap(verticesCount,m, vertices);
  } else if ( vertices[n].heapIndex == -1 ) {
    return vertices[n].depth;
  }
  while (!(pq -> isEmpty())) {
    
    int peakCurrentNodeIndex = pq -> top();

    if (peakCurrentNodeIndex == n) {
      return vertices[peakCurrentNodeIndex].depth;
    }

    int currentNodeIndex = pq -> extractMin();
    adjacentNode *visitingNode = vertices[currentNodeIndex].adjacentList;

    while (visitingNode != nullptr ){
       
      if (vertices[visitingNode - matrix[currentNodeIndex]].heapIndex == -1) {
        visitingNode = visitingNode -> next;
          continue;
        }

      if (vertices[visitingNode - matrix[currentNodeIndex]].heapIndex == -5 ) {
        //have not yet been discovered.
        //insert into the que
        relax(vertices[currentNodeIndex], visitingNode, currentNodeIndex);
        pq -> insert(visitingNode - matrix[currentNodeIndex]);

      } else {
        relax(vertices[currentNodeIndex], visitingNode, currentNodeIndex);
        pq -> modifyKey(vertices[visitingNode - matrix[currentNodeIndex]].heapIndex);
      }
        visitingNode = visitingNode -> next;
    }
  }
  //cleanup the heap
  return INF;
}

double Weighted_graph::distance( int m, int n){
  
  if (m < 0 || m > verticesCount || n < 0 || n > verticesCount ) {
    throw illegal_argument();
  }

  if ( m == n) {
    return 0.0;
  }

  if ( vertices[m].degree <=0 || vertices[n].degree <= 0) {
    return INF;
  }

  return shortestPath(m,n);
 
}

void Weighted_graph::insert(int m, int n, double w) {
  //if new insert is made, reset the pq.
  previousIndex = -1;

  if (w <= 0 ) {
    throw illegal_argument();
  } if ( m == n ) {
    throw illegal_argument();
  }

  if (m < 0 || m >= verticesCount || n < 0 || n >= verticesCount ) {
    throw illegal_argument();
  }
  //check if the edge exists already.
   if (matrix[m][n].weight > 0 ) {
   //edge between m and n exists
   //If edge already exists, its same to assume that its already in the linked list.
   //simply update the weight between the two edges.
   matrix[m][n].weight = w;
   matrix[n][m].weight = w;
   
  } else {
  
    if ( vertices[m].degree <=0 ) {
      //m x n relationship
      vertices[m].adjacentList = &matrix[m][n];
      vertices[m].degree ++;
      vertices[m].tailIndex = n;
      matrix[m][n].weight = w; //add weight between two edges
    } else {
       // m x n relationship
      matrix[m][vertices[m].tailIndex].next = &matrix[m][n]; //add new edge to linked list
      vertices[m].degree ++;
      vertices[m].tailIndex = n;
      matrix[m][n].weight = w;
    }

    if (vertices[n].degree <= 0 ) {
      //n x m relationship
      vertices[n].adjacentList = &matrix[n][m];
      vertices[n].degree ++;
      vertices[n].tailIndex = m;
      matrix[n][m].weight = w;
    } else {
      //cout << vertices[n].tailIndex << endl;
      matrix[n][vertices[n].tailIndex].next = &matrix[n][m]; //add new edge to linked list
      vertices[n].degree ++;
      vertices[n].tailIndex = m;
      matrix[n][m].weight = w;
    }
      //cout << "added new edge between " << m << " and " << n << endl;
      edges ++; 
  } 
}

void Weighted_graph::relax(vertex u, adjacentNode *v, int currentNodeIndex) const{
  vertices[v - matrix[currentNodeIndex]].depth = std::min((u.depth + v -> weight),( vertices[v - matrix[currentNodeIndex]].depth));
  return;
}

void Weighted_graph::print() const {

  //printing adjacency list of each vertex. 
  for(int i = 0; i < verticesCount ; i ++ ) {
    cout << "vertex " << i << " with degree " << vertices[i].degree << endl;

    adjacentNode *temp = vertices[i].adjacentList;
    while (temp != nullptr) {
      cout << " " << temp -> weight;
      temp = temp -> next;
    }
    cout << endl;
  }
}

#endif
