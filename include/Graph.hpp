#ifndef GRAPHS_HPP
#define GRAPHS_HPP
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>
class Edge;
class Vertex;
class Graph;
class Edge{
  public:
    Edge();
    Edge(Vertex* a, Vertex* b);
    Vertex* vertex_a;
    Vertex* vertex_b;
};
class Vertex{
  public:
    unsigned int degree;
    std::vector<Vertex*> adjacents;
    void setAdjacentsAndDegree(std::vector<Edge>* edges);
};
class Graph{
  public:
    Graph();
    Graph(std::string textFile);
    std::vector<Edge> edges;
    std::map<int, Vertex*> vertices;
    void generateGraphFile(std::string fileName);
    unsigned int getNumberOfVertices(){
      return this->vertices.size();
    };
    unsigned int getNumberOfEdges(){
      return this->edges.size();
    };
};
std::pair<int, int> getNumbersFromLine(std::string line);
#endif
