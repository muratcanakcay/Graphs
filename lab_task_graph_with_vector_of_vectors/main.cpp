#pragma once
#include <iostream>
#include "vertex_graph.h"

using namespace std;

int main()
{
	if (0)
	{
		Graph g(4);
		g.printGraph();
		g.addVertex(2);
		g.printGraph();
		g.remVertex(7);

		g.remVertex(2);
		g.printGraph();

		g.addVertex(7);
		g.printGraph();
		g.addVertex(2);
		g.addVertex(19);
		g.addVertex(13);
		g.remVertex(21);
		g.remVertex(3);
		g.printGraph();

		g.addEdge(13, 19);
		g.addEdge(13, 19);
		g.addEdge(2, 7);
		g.addEdge(13, 7);
		g.addEdge(7, 19);
		g.printGraph();

		g.remEdge(2, 4);
		g.remEdge(13, 19);
		g.printGraph();

		g.isConnected(0);
		g.isEulerian(0);

		g.isConnected(1);
		g.isEulerian(1);

		g.minDeg(1);
		g.maxDeg(1);
		g.v_count(1);
		g.e_count(1);

		g.addEdge(1, 4);
		g.addEdge(2, 1);
		g.addEdge(4, 7);
		g.addEdge(13, 19);

		g.printGraph();

		g.remVertex(7);

		g.printGraph();

		g.isConnected(1);
		g.isEulerian(1);

		g.minDeg(1);
		g.maxDeg(1);
		g.v_count(1);
		g.e_count(1);

		g.addEdge(13, 2);
		g.dfs_recursive(0, 1);
	} 
	if (0)
	{
		Graph h(7);
		h.addEdge(1, 2);
		h.addEdge(2, 3);
		h.addEdge(3, 4);
		h.addEdge(3, 5);
		h.addEdge(5, 6);
		h.addEdge(1, 7);

		cout << "**** DFS ****" << endl;
		h.dfs_recursive(0, 1);
		cout << endl;
		cout << "**** BFS ****" << endl;
		h.bfs_recursive(0, 1);
	}

	if (1)
	{
		Graph m(18);
		m.addEdge(1, 2);
		m.addEdge(1, 3);
		m.addEdge(2, 4);
		m.addEdge(2, 5);
		m.addEdge(4, 8);
		m.addEdge(4, 9);
		m.addEdge(8, 13);
		m.addEdge(8, 14);
		m.addEdge(9, 15);
		m.addEdge(3, 6);
		m.addEdge(3, 7);
		m.addEdge(6, 10);
		m.addEdge(7, 11);
		m.addEdge(7, 12);
		m.addEdge(11, 16);
		m.addEdge(12, 17);
		m.addEdge(12, 18);
		//m.addEdge(1, 9);
		//m.remVertex(8); 

		m.printGraph();

		//cout << "**** DFS ****" << endl;
		//m.dfs_recursive(0, 1);
		//cout << endl;
		//cout << "**** BFS ****" << endl;
		//m.bfs_recursive(0, 1);
		//cout << endl;
		//cout << "**** BFS ****" << endl;

		m.dfs(14, 1);
	}





	//system("pause");

	return 1;
}