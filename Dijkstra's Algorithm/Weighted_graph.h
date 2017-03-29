/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
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

using namespace std;

enum state {
  WHITE,
  GRAY,
  BLACK
};

struct vertex;
struct adjacentNode;

struct vertex {
  state color; // visited, currently visiting or have yet to visit
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
      //nothing happens in the constructor
      }

};

struct adjacentNode {
  adjacentNode *next;
  double weight;
  vertex *reference;

  adjacentNode():
      weight(0) {
      //nothing happens in the construct
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
    vertex *vertices;

  public:
    Heap( int, int, vertex *);
    ~Heap();
    int left( int ) const;
    int right( int ) const;
    int parent( int ) const;
    int heapSize() const;

    bool isEmpty() const;
    void heapify( int );
    int extractMin();
    void modifyKey(int);

    //TODO
    void print();

};


Heap::Heap(int m, int s, vertex *graph):
  size(m),
  vertices(graph),
  array ( new int[m +1] ) {
 
    array[0] = 0;
    array[1] = s;
    vertices[s].heapIndex = 1;

    //initialize heap array with starting node at top of heap. everything else infinity
    int count = 0;
    for (int i = 2; i < size + 1; i ++ ) {
      
      if ( count == s) {
        count++;
      }

      array[i] = count;
      vertices[count].heapIndex = i;
      count ++;
    }

    cout << "Finished Initializing new Heap" << endl;
    print();
}

Heap::~Heap() {
  delete[] array;
}

int Heap::left( int i ) const {
  return 2*i;
}

int Heap::right( int i ) const {
  return 2*1 + 1;
}

int Heap::parent( int i ) const {
  if ( i <= 1 ) {
    return 1;
  }

  return std::floor(i/2);
}

bool Heap::isEmpty() const {
  //heap actually starts at index 1. This anything below the size of 2 is useless.
  return !(size > 1);
}

int Heap::heapSize() const {
  return size;
}

void Heap::heapify( int i ) {

  cout << "Starting to heapify " << endl;
  print();
  //heapify starting at index i
  int l = left(i);
  int r = right(i);
  int smallestIndex = 0;

  if ( l <= size && vertices[array[l]].depth < vertices[array[i]].depth ) {
    smallestIndex = l;
  } else {
    smallestIndex = i;
  }

  if ( r <= size && vertices[array[r]].depth < vertices[array[smallestIndex]].depth ) {
    smallestIndex = r;
  }

  if (smallestIndex != i) {
    std::swap(array[i],array[smallestIndex]);
    vertices[array[smallestIndex]].heapIndex = smallestIndex;
    vertices[array[i]].heapIndex = i;
    heapify(smallestIndex);
  }

  //finished heapifying
  return;

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
  cout << "Extract min value of index of " << min << endl;
  //call heapify on the first index.
  heapify(1);

  cout << "After reorganizing heap from extracting min " << endl;
  print();

  return min;
}

void Heap::modifyKey(int i) {

 cout << "parent of " << i << " is " << parent(i) << endl;
 cout << "left of "<< i <<" is " << left(i) << endl;
 cout << "right of " << i << " is " << right(i) << endl;

 if ( vertices[array[parent(i)]].depth >= vertices[array[i]].depth) {
  cout << " Reference depth is >= depth of node currenlty comparing " << endl;
  cout << "Upward fix " << endl;
  print();
  while ( i > 1 && vertices[array[parent(i)]].depth > vertices[array[i]].depth ) {
    

    int temp = parent(i);
    std::swap(array[i],array[temp]);
    vertices[array[i]].heapIndex = i;
    vertices[array[temp]].heapIndex = temp;
    i = temp;
  }

  cout << "End of upward fix " << endl;
  print();

 } else {
  
   cout << "Downward fix " << endl;
   
   heapify(i);
 
 }
}

void Heap::print() {

  cout << endl;
  cout << "Heap -> " ;
  for (int i = 1 ; i < size +1 ; i ++ ) {
    cout << " |" << array[i] << "," << vertices[array[i]].depth ;
  }

  cout << endl;

  cout << "Vertex Heap Index -> ";

  for (int i = 0; i < 50; i++ ) {
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

		static const double INF;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int ) const;

		void insert( int, int, double );
    void relax(vertex, adjacentNode *) const;
    void print() const; // TODO

    //TODO test method for shortestDistance
    double shortestPath(int, int) const;
	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

Weighted_graph::Weighted_graph(int n):
  verticesCount(std::max(1,n)),
  edges(0),
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
}

int Weighted_graph::degree(int n) const {
  return vertices[n].degree;
}

int Weighted_graph::edge_count() const {
  return edges;
}

double Weighted_graph::adjacent(int m, int n) const {
  if ( m == n){
      return 0;
  }

  if (m < 0 || m > verticesCount || n < 0 || n > verticesCount ) {
    throw illegal_argument();
  }

  return matrix[m][n].weight;
}

double Weighted_graph::shortestPath(int m, int n) const{

  for (int i = 0; i < verticesCount; i++) {
    //Initialize the depth all vertices to INF 
    vertices[i].depth = INF; 
  }

  vertices[m].depth = 0;
  
  //initialize New Heap. 
  Heap *pq = new Heap(verticesCount,m, vertices);

  while (!(pq -> isEmpty())) {

    int currentNodeIndex = pq -> extractMin();

    if (currentNodeIndex == n) {
      delete pq; //cleanup heap that was created.
      return vertices[currentNodeIndex].depth;
    }

    adjacentNode *visitingNode = vertices[currentNodeIndex].adjacentList;

    while (visitingNode != nullptr ){
      if(visitingNode -> reference -> heapIndex < 0) {
        //If the heapIndex of the visiting Node is < 0, that means we have extracted it from the heap. Thus skip to next node
        visitingNode = visitingNode -> next;
        continue;
      }
      cout << "Currently visiting node " << visitingNode -> reference - vertices;
      cout << " with weight " << visitingNode -> weight << endl;
      relax(vertices[currentNodeIndex], visitingNode);
      cout << "Finished relaxing. Weight have been updated " << endl;
      pq -> modifyKey(visitingNode -> reference -> heapIndex);
      visitingNode = visitingNode -> next;
    }
  }
}

double Weighted_graph::distance( int m, int n) const{
  
  if (m < 0 || m > verticesCount || n < 0 || n > verticesCount ) {
    throw illegal_argument();
  }

  if ( m == n) {
    return 0.0;
  }

  //implement distance algorithm.
  return shortestPath(m,n);
 
}

void Weighted_graph::insert(int m, int n, double w) {
  if (w <= 0 ) {
    throw illegal_argument();
  }

  if ( m < 0 || m > verticesCount || n < 0 || n > verticesCount ) {
    throw illegal_argument();
  }
  //check if the edge exists already.
   if (matrix[m][n].weight > 0 ) {
    //edge between m and n exists
   cout << "edge between " << m << " and " << n << " already exists" << endl;
   //If edge already exists, its same to assume that its already in the linked list.
   //simply update the weight between the two edges.
   matrix[m][n].weight = w;
   matrix[n][m].weight = w;
   
   cout << "updated weights between " << m << " and " << n << endl;
  } else {
  
    if ( vertices[m].degree <=0 ) {
      cout << "vertex " << m << " has no edges yet. Create new adjacency list" << endl;
      //m x n relationship
      vertices[m].adjacentList = &matrix[m][n];
      vertices[m].degree ++;
      vertices[m].tailIndex = n;
      matrix[m][n].reference = &vertices[n]; // backwards reference.
      matrix[m][n].weight = w; //add weight between two edges
    } else {
      cout << "vertex " << m << " has adjacencies. Insert edge into list" << endl;
       // m x n relationship
      matrix[m][vertices[m].tailIndex].next = &matrix[m][n]; //add new edge to linked list
      vertices[m].degree ++;
      vertices[m].tailIndex = n;
      matrix[m][n].reference = &vertices[n];
      matrix[m][n].weight = w;
    }

    if (vertices[n].degree <= 0 ) {
      cout << "vertex " << n << " has no edges yet. Create new adjacency list" << endl;
      //n x m relationship
      vertices[n].adjacentList = &matrix[n][m];
      vertices[n].degree ++;
      vertices[n].tailIndex = m;
      matrix[n][m].reference = &vertices[m]; // backwards reference.
      matrix[n][m].weight = w;
    } else {
      cout << "vertex " << n << " has adjacencies. Insert edge into list" << endl;
      //n x m relationshop
      cout << vertices[n].tailIndex << endl;
      matrix[n][vertices[n].tailIndex].next = &matrix[n][m]; //add new edge to linked list
      vertices[n].degree ++;
      vertices[n].tailIndex = m;
      matrix[n][m].reference = &vertices[m];
      matrix[n][m].weight = w;
    }
      cout << "added new edge between " << m << " and " << n << endl;
      edges ++; 
  } 
}

void Weighted_graph::relax(vertex u, adjacentNode *v) const{

  // if the depth of v is greater than the depth of u + weight,
  // update depth
  cout << "current Node Depth = " << u.depth << " visiting node depth = " << v -> reference -> depth << endl;
  if (( v -> reference -> depth) > (u.depth + v -> weight)) {
    v -> reference -> depth = (u.depth + v -> weight);
    cout << "Update Weight to " <<  v -> reference -> depth << endl;
  } else {
    cout << "Keep weight the same at " << v -> reference -> depth << endl;
  }

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
