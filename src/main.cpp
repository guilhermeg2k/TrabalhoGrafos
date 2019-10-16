#include "Graph.hpp"
using namespace std;
int main(){
  Graph graph("teste.txt");
  graph.generateAdjacencyList();
  graph.generateAdjacencyMatrix();
  graph.generateComponents();
  graph.printAll();
  graph.saveAllToFile("out/Graph.txt");
}