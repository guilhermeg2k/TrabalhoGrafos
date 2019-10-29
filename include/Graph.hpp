#ifndef GRAPHS_HPP
#define GRAPHS_HPP
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
class Edge;
class Vertex;
class Graph;
class No;
class No
{
public:
	int noPai;
	int nivel;
	int num;
};
class Vertex
{
public:
	unsigned int number;
	unsigned int degree;
	vector<Vertex *> adjacents;
	void setAdjacentsAndDegree(vector<Edge*> edges);
	bool visitedbyComponentGenerator = false;
	bool visitedbyBFF = false;
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
struct BFSTable;
public:
	Graph(){};
	Graph(string textFile);
	vector<Edge*> edges;
	vector<Vertex *> vertices;
	vector<Graph*> components;
	//vector<vector<int>> adjacencyMatrix;
	//vector<vector<int>> adjacencyList;
	vector<BFSTable*> BFS;
	std::vector<No*> arvoreDeBusca;
	int nivelMax = 0;
	void printGraphInfo();
	void saveGraphInfoFile(string fileName);
	void generateAdjacencyMatrix();
	void saveAdjacencyMatrixToFile(string fileName);
	void generateAdjacencyList();
	void saveAdjacencyListToFile(string fileName);
	void generateComponents();
	void printComponents();
	void saveComponentsToFile(string fileName);
	void breadthFirstSearch(int vertex);
	void saveBFSToFile(string fileName);
	void printBFS();
	void graphDFS(int verticeInicial); 
	void dfsr(Vertex* vPai,int* pre,No* noPai);
	void printArvore();
	void geraArquivoArvore(string fileName);
	unsigned int getNumberOfVertices(){
		return this->vertices.size();
	};
	unsigned int getNumberOfEdges(){
		return this->edges.size();
	};
private:
	struct BFSTable{
		int distance = 0;
		int root = 0;
	};
	void visitVerticesRecursive(Vertex* vertex, Graph* component);
};
pair<int, int> getNumbersFromLine(string line);
#endif
