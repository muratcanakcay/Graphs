#include <iostream>
#include "vertex_graph.h"

using namespace std;

Vertex::Vertex()
{
	vector<int> neighbors; // neighbors of the vertex
	degree = 0; // degree of the vertex
	label = -1; // label of the vertex
}
int Vertex::addNeighbor(int v) // add vertex v as a neighbor
{
	if (find(neighbors.begin(), neighbors.end(), v) != neighbors.end())  // neighbors already contain v
	{
		if (DEBUG) cout << v << " is already in neighbor list of ";
		return 0;
	}

	// neighbors do not contain v
	if (DEBUG) cout << "Adding " << v << " as neighbor to ";
	degree++;
	neighbors.resize(degree);
	neighbors[degree - 1] = v;
	return v;
}
int Vertex::remNeighbor(int v) // remove vertex v from neighbors
{
	vector<int>::iterator it = find(neighbors.begin(), neighbors.end(), v);

	if (it != neighbors.end())  // neighbors contain v
	{
		if (DEBUG) cout << "Removing " << v << " from neighbor list of ";
		neighbors.erase(it, it + 1);
	}
	else // neighbors do not contain v
	{
		if (DEBUG) cout << v << " is not in the neighbor list of ";
		return 0;
	}

	degree--;
	return v;
}
int Vertex::doesExistNeighbor(int v) // ***CURRENTLY NOT USED*** 
							//checks if a vertex with label v exists in neighbors, 
							// if yes - returns "position" of vertex (position + 1) 
							// if no - returns (-1) * position of the first larger label in the neighbors 
							// returns 0 if no v exists in neighbors and all other labels are smaller than v. 
{
	for (int i = 0; i < degree; i++)
	{
		/* code snippet to use if I want to return the position of the neighbor at later time so that I can keep neighbor lise ordered

		if (neighbors[i] > v) // if a neighbor with larger label than v is found return -1*position of that neighbor
			return -(i + 1);
		if (neighbors[i] == v) // if neighbor with label v is found return position of that neighbor
			return i + 1;
		*/

		if (neighbors[i] == v) // if neighbor with label v is found return 1
			return 1;
	}

	return 0; // // if neighbor with label v is not found return 0 (if all neighbors of the vertex are smaller than v and v is not present in the neighbor list return 0)
}
void Vertex::printNeighbors()
{
	if (isEmpty())
	{
		if (DEBUG) cout << "The neighbor list is empty.";
		cout << endl;
		return;
	}

	if (DEBUG) cout << "The neighbors are: ";
	for (int i = 0; i < degree; i++)
	{
		int neighbor = neighbors[i];
		if (neighbor < 10) cout << ' ';
		cout << neighbor << ' ';
	}

	cout << endl;
	return;
}

Graph::Graph(int s = SIZE)
{
	cout << "Graph with " << s << " vertices created." << endl << endl;

	size = 0;
	vector<Vertex> graph;

	for (int v = 1; v < s + 1; v++)
		addVertex(v);
}
int Graph::addVertex(int v) // adds a vertex v to the graph if it does not exist, maintains the increasing order of vertices
{
	cout << "Adding " << v << " to the graph" << endl;

	int pos_v = position(v); // get position information for vertex v

	if (DEBUG) cout << "Position return from position() is " << pos_v << endl;

	if (pos_v > 0) // vertex v already exists in graph (at position pos_v-1)
	{
		cout << v << " is already in graph" << endl << endl;;
		return 0;
	}

	Vertex new_vertex;
	new_vertex.label = v;
	size++;

	if (pos_v == 0) // vertex v d.n.e. in graph and there's no vertex with larger label
	{
		if (DEBUG) cout << "Adding " << v << " to the end of the vertex list" << endl;
		graph.resize(size);
		graph[size - 1] = new_vertex; // insert vertex at the end
	}
	else // vertex v d.n.e. in graph but there's vertex with larger label
	{
		if (DEBUG) cout << "Adding " << v << " at position " << -pos_v << endl;
		graph.insert(graph.begin() - pos_v - 1, new_vertex); // insert vertex right before the vertex with larger label
	}

	cout << v << " added to graph." << endl << endl;
	return v;
}
int Graph::remVertex(int v) // removes vertex v from the graph if it exists
{
	cout << "Removing " << v << " from the graph" << endl;

	int pos_v = position(v);

	if (pos_v <= 0) // vertex does not exist
	{
		cout << v << " does not exist in graph" << endl << endl;
		return 0;
	}

	// vertex exists at position pos_v - 1

	graph.erase(graph.begin() + pos_v - 1);  // delete vertex (v) at position pos_v - 1
	size--;

	if (DEBUG) cout << "Removing " << v << " from neighbor lists" << endl;

	for (int i = 0; i < size; i++)
		if (graph[i].doesExistNeighbor(v))  // delete v from neighbor lists of all vertices
		{
			graph[i].remNeighbor(v);
			cout << graph[i].label << endl;
		}


	cout << v << " was removed from graph" << endl << endl;
	return v;
}
int Graph::addEdge(int v1, int v2)
{
	cout << "Adding edge between " << v1 << " and " << v2 << endl;

	int pos_v1 = position(v1);
	int pos_v2 = position(v2);

	if (pos_v1 == 0 || pos_v2 == 0)
	{
		if (!pos_v1) cout << v1 << " does not exist in the graph." << endl << endl;
		else cout << v2 << "does not exist in the graph." << endl << endl;
		return 0;
	}

	if (graph[pos_v1 - 1].addNeighbor(v2) == 0) // if addNeighbor returns 0 then there's already an edge
		cout << v1 << endl << "There's already an edge between " << v1 << " and " << v2 << endl << endl;
	else // there's no edge so add it to the other end too
	{
		if (DEBUG) cout << v1 << endl;
		graph[pos_v2 - 1].addNeighbor(v1);
		if (DEBUG) cout << v2 << endl << endl;
		cout << "An edge between " << v1 << " and " << v2 << " was added." << endl << endl;
	}

	return 1;
}
int Graph::remEdge(int v1, int v2)
{
	cout << "Removing edge between " << v1 << " and " << v2 << endl;

	int pos_v1 = position(v1);
	int pos_v2 = position(v2);

	if (pos_v1 <= 0 || pos_v2 <= 0)
	{
		if (!pos_v1) cout << v1 << " does not exist in the graph." << endl << endl;
		else cout << v2 << " does not exist in the graph." << endl << endl;
		return 0;
	}

	if (graph[pos_v1 - 1].remNeighbor(v2) == 0) // if remNeighbor returns 0 then there's no edge
		cout << v1 << endl << "There's no edge between " << v1 << " and " << v2 << endl << endl;
	else // there's an edge, so remove it from the other end too
	{
		if (DEBUG) cout << v1 << endl;
		graph[pos_v2 - 1].remNeighbor(v1);
		if (DEBUG) cout << v2 << endl;
		cout << "The edge between " << v1 << " and " << v2 << " is removed." << endl << endl;
	}

	return 1;
}
int Graph::position(int v) // checks if a vertex with label v exists in graph, 
							// if yes - returns "position" of vertex (position + 1) 
							// if no - returns (-1) * position of the first larger label in the graph 
							// returns 0 if no v exists in graph and all other labels are smaller than v. 
{
	for (int i = 0; i < size; i++)
	{
		if (graph[i].label > v) // if a vertex with larger label is found return -1*position of that vertex
			return -(i + 1);
		if (graph[i].label == v) // if vertex v is found return position of the vertex
			return i + 1;
	}

	return 0; // if all vertices in the graph are smaller than v and v is not present in the graph return 0
}
int Graph::index(int v) // returns index of a given label 
{
	for (int i = 0; i < size; i++)
		if (graph[i].label == v) return i;
	return -1;
}
int Graph::maxDeg(bool print_flag) // returns the max degree of the graph
{
	int max_degree = 0;
	for (int v = 0; v < size; v++)
	{
		int v_degree = graph[v].degree;
		if (v_degree > max_degree) max_degree = v_degree;
	}

	if (print_flag) cout << "Min. degree of the graph is: " << max_degree << endl << endl;

	return max_degree;
}
int Graph::minDeg(bool print_flag) // returns the min degree of the graph
{
	int min_degree = graph[0].degree;
	for (int v = 1; v < size; v++)
	{
		int v_degree = graph[v].degree;
		if (v_degree < min_degree)
			min_degree = v_degree;
	}

	if (print_flag) cout << "Min. degree of the graph is: " << min_degree << endl << endl;

	return min_degree;
}
bool Graph::isConnected(bool print_flag)
{
	bool flag = false;
	if (minDeg(0) >= (v_count(0) / 2) - 1) flag = true;

	if (print_flag)
	{
		cout << "The graph is ";
		if (!flag) cout << "not ";
		cout << "connected." << endl << endl;
	}

	return flag;
}
bool Graph::isEulerian(bool print_flag)
{
	bool flag = true;
	if (!isConnected(0)) flag = false;
	else
		for (int v = 0; v < size; v++)
			if (graph[v].degree % 2 != 0) flag = false;

	if (print_flag)
	{
		cout << "The graph is ";
		if (!flag) cout << "not ";
		cout << "Eulerian." << endl << endl;
	}

	return flag;
}
int Graph::v_count(bool print_flag) // returns number of vertices in the graph
{
	if (print_flag) cout << "The graph has " << size << " vertices." << endl << endl;
	return size;
}
int Graph::e_count(bool print_flag) // returns number of edges in the graph
{
	int tmp = 0;
	for (int v = 0; v < size; v++)
		tmp += graph[v].degree;

	if (print_flag) cout << "The graph has " << tmp / 2 << " edges." << endl << endl;
	return tmp / 2;
}
void Graph::printGraph() // prints the graph
{
	cout << "The graph is:" << endl;

	for (int v = 0; v < size; v++)
	{
		if (graph[v].label < 10) cout << ' ';
		cout << graph[v].label << "| ";
		graph[v].printNeighbors();
	}

	cout << endl;
}

int Graph::dfs_recursive(int label, int node,  vector<bool>* visited) // default value for visited is NULL
{
	if (DEBUG) cout << "Index return from index() is  " << index(node) << endl;

	if (index(node) == -1) // node d.n.e. in graph 
	{
		cout << "The root to start the dfs search does not exist in graph" << endl;
		return 0;
	}

	if (visited == NULL) // initialize list of the visited nodes 
	{
		visited = new vector<bool>;
		for (int i = 0; i < size; i++)
			visited->push_back(false);
	}

	if (!(*visited)[index(node)]) // if first visit to node
		(*visited)[index(node)] = true; // mark node as visited

	cout << "Visited: " << node << endl;

	if (DEBUG) cout << endl; // make output more readable

	if (node == label) // search item found
	{
		cout << "FOUND!" << endl << endl;
		return 1;
	}

	for (auto n : graph[index(node)].neighbors) // iterate through the neighbors of the node
	{
		if (!(*visited)[index(n)]) // if neighbor was not visited before
		{
			if (NEIGHBORS) cout << "Visiting neighbor of " << node << " : " << n << endl;
			if (dfs_recursive(label, n, visited) == 1) return 1; // run dfs using neighbor as root node
		}
	}
	
	return 0; // search item not found
}
int Graph::bfs_recursive(int label, int node, vector<bool>* visited, Queue* queue) // default value for visited and queue is NULL
{
	if (DEBUG) cout << "Index return from index() is  " << index(node) << endl;

	if (index(node) == -1) // node d.n.e. in graph 
	{
		cout << "The root to start the dfs search does not exist in graph" << endl;
		return 0;
	}

	if (visited == NULL) // if it's the first iteration
	{
		visited = new vector<bool>; // initialize list of visited nodes 
		for (int i = 0; i < size; i++)
			visited->push_back(false);

		queue = new Queue(); // initialize the queue
	}

	cout << "Visited: " << node << endl; // print the visited node 
	(*visited)[index(node)] = true; // mark node as visited
		
	if (node == label) // search item found
	{
		cout << "FOUND!" << endl << endl;
		return 1;
	}

	if (NEIGHBORS && graph[index(node)].degree == 1) // if the node has no neighbors other than parent
	{
		cout << node << " has no neighbors to enqueue." << endl;
		if (DEBUG) cout << queue->contents() << endl;
	}

	for (int n : graph[index(node)].neighbors) // iterate through the neighbors of the node
		if (!(*visited)[index(n)]) // if neighbor was not visited before 
		{
			queue->enqueue(n); // add neighbor to the queue
			(*visited)[index(n)] = true; // mark neighbor as visited
			if (NEIGHBORS) cout << "Enqueueing neighbor of " << node << " : " << n << endl;
			if (DEBUG) cout << queue->contents() << endl;
		}

	if (DEBUG) cout << endl; // make output more readable

	while (!queue->isEmpty()) // run dfs using next item in queue as root node until queue is empty
		bfs_recursive(label, queue->dequeue(), visited, queue);
		
	return 0; // search item not found
}