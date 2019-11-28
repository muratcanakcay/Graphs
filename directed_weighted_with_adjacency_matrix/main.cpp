#include<iostream>
#include<vector>

using namespace std;

#define SIZE 4
#define MAXSIZE 100

class Graph
{
private:
	int size; // graph size
	vector<vector <float>> graph; //adjecency matrix
	vector<int> labels; // vertex labels

public:
	Graph(int s = SIZE);
	void addVertex(int);
	void remVertex(int);
	int addEdge(int, int, float);
	int remEdge(int, int);
	int isEdge(int, int);
	void findAllNeighbors(int);
	int index(int); // returns the index of the given vertex
	void printGraph();
};
Graph::Graph(int s) //constructor
{
	size = s;
	
	graph.resize(size, vector<float>(size)); // create matrix 
		
	labels.resize(size); // create label list
	for (int i = 0; i < size; i++) // initialize labels
		labels[i] = i + 1;

	cout << "Created graph of size " << size << endl;

	printGraph();
	
	cout << endl;
}
void Graph::addVertex(int label) //function to add a vertex to the graph
{
	if (size == MAXSIZE)
	{
		cout << "Graph at max size. Delete some vertices before adding new ones." << endl;
		return;
	}

	if (index(label) != -1)
	{
		cout << "There's already a vertex with label " << label << endl;
		return;
	}
	
	size++;

	graph.resize(size); // add new row
	for (int i = 0; i < size; i++) // expand each row by 1
		graph[i].resize(size);

	labels.resize(size, label); // add label to list

	cout << "Added new vertex with label " << label << " at index " << size - 1 << endl;
}
void Graph::remVertex(int label) //function to remove a vertex from the graph
{
	int v = index(label);

	if (v == -1)
	{
		cout << "Vertex " << label << " is not in the graph." << endl;
		return;
	}
		
	size--;

	labels.erase(labels.begin() + v); // delete index v from labels
	graph.erase(graph.begin() + v); // delete row v from matrix
	for (int i = 0; i < size; i++) // delete column v from matrix 
		graph[i].erase(graph[i].begin() + v);
	
	cout << "Removed vertex labelled " << label << " at index " << v << endl;
}
int Graph::addEdge(int label1, int label2, float weight) //function to add a weighted edge directed from v1 to v2
{
	int v1 = index(label1);
	int v2 = index(label2);
	
	if (v1 == -1 || v2 == -1)
	{
		cout << "Vertex does not exist" << endl;
		return 0;
	}

	if (graph[v1][v2]!=0)
	{
		cout << "There's already an edge from vertex " << label1 << " to vertex " << label2 << "." << endl << endl;
		return 0;
	}

	graph[v1][v2] = weight;

	cout << "Added edge from vertex " << label1 << " to vertex " << label2 << " with weight " << weight << endl;
	
	return 1;
}
int Graph::remEdge(int label1, int label2) //function to remove an edge between two vertices
{
	int v1 = index(label1);
	int v2 = index(label2);

	if (v1 == -1 || v2 == -1 || graph[v1][v2] == 0)
	{
		cout << "There's no such edge" << endl;
		return 0;
	}

	graph[v1][v2] = 0;

	cout << "Removed edge from vertex " << label1 << " to vertex " << label2 << "." << endl;
	
	return 1;
}
int Graph::isEdge(int label1, int label2)
{
	int v1 = index(label1);
	int v2 = index(label2);

	if (v1 == -1 || v2 == -1 || graph[v1][v2] == 0)
	{
		cout << "There's no such edge" << endl;
		return 0;
	}

	cout << "There's an edge from vertex " << label1 << " to vertex " << label2 << "." << endl << endl;
	return 1;
}
void Graph::findAllNeighbors(int label)
{
	int v = index(label);
	
	if (v == -1)
	{
		cout << "Vertex " << label << " is not in the graph." << endl;
		return;
	}

	cout << "Neighbors of vertex " << label << " are: " << endl;
	for (int r = 0; r < size; r++)
		if (graph[v][r] != 0)
			cout << "Vertex " << labels[r] << " (at index " << r << ") with weight " << graph[v][r] << endl;
	cout << endl;
}
void Graph::printGraph()
{
	cout << endl << "The current graph is: " << endl;
	
	for (int r = 0; r < size; r++)
	{
		cout << labels[r] << " : ";
		for (int c = 0; c < size; c++)
			cout << graph[r][c] << " ";
		cout << endl;
	}
	
	cout << endl;
}
int Graph::index(int label) // returns the index of the given label
{
	for (int i = 0; i < size; i++)
		if (labels[i] == label) return i;
	return -1;
}

int main()
{
	Graph g;
	g.addEdge(1, 2, 1);
	g.addEdge(2, 1, 5);
	g.addEdge(2, 3, 1);
	g.addEdge(3, 3, 7);
	g.addEdge(3, 4, 2);
	g.addEdge(4, 1, 3);
	g.printGraph();
	g.findAllNeighbors(2);
	g.remVertex(3);
	g.printGraph();
	g.remEdge(1, 2);
	g.printGraph();
			
	//system("pause");
	return 0;
} 