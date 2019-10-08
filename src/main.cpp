#include "Graph.hpp"
using namespace std;
int main(){
  Graph graph("teste.txt");
  graph.generateGraphFile("saida.txt");
  graph.generateAdjacencyMatrix();
  graph.generateAdjacencyList();
}