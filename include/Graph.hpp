#ifndef GRAPHS_HPP
#define GRAPHS_HPP
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
class Edge;
class Vertex;
class Graph;
class Vertex
{
public:
	unsigned int number;
	unsigned int degree;
	std::vector<Vertex *> adjacents;
	void setAdjacentsAndDegree(std::vector<Edge*> edges);
	bool visited = false;
};
class Edge
{
public:
	Edge();
	Edge(Vertex *a, Vertex *b);
	Vertex *vertex_a;
	Vertex *vertex_b;
};
class Graph
{
public:
	Graph(){};
	Graph(std::string textFile);
	std::vector<Edge*> edges;
	std::map<int, Vertex *> vertices;
	std::vector<Graph*> components;
	void generateGraphFile(std::string fileName);
	unsigned int getNumberOfVertices(){
		return this->vertices.size();
	};
	unsigned int getNumberOfEdges(){
		return this->edges.size();
	};
	void generateAdjacencyMatrix();
	void generateAdjacencyList();
	void generateComponents();
	void printComponents();
};
std::pair<int, int> getNumbersFromLine(std::string line);
void visitVerticesRecursive(Vertex* vertex, Graph* component);
#endif
