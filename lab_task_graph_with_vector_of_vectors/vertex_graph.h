#include <vector>
#include "stack_queue.h"

using namespace std;

#define SIZE 1
#define DEBUG 0
#define NEIGHBORS 0

class Vertex
{
public:
	vector<int> neighbors; // list of neighbors of the vertex
	int degree; // total number of neighbors of the vertex
	int label; // label of the  vertex

	Vertex();
	bool isEmpty() { return(degree == 0); };
	int addNeighbor(int);
	int remNeighbor(int);
	int doesExistNeighbor(int);
	void printNeighbors();
};

class Graph
{
public:
	vector<Vertex> graph; // list of vertices in the graph
	int size; // total number of vertices in graph 

	Graph(int);
	int addVertex(int);
	int remVertex(int);
	int addEdge(int, int);
	int remEdge(int, int);
	void printGraph();
	void neighbors(int);
	int position(int);
	int index(int);
	int maxDeg(bool);
	int minDeg(bool);
	bool isEulerian(bool);
	bool isConnected(bool);
	int v_count(bool);
	int e_count(bool);
	int dfs_recursive(int, int, vector<bool>* = NULL);
	int bfs_recursive(int, int, vector<bool>* = NULL, Queue* = NULL);
};