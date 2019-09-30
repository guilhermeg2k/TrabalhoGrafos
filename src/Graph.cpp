#include "Graph.hpp"

Graph::Graph(std::string textFile){
  std::ifstream file(textFile);
  if (file.is_open()){
    std::string line;
    std::istringstream lineStream;
    getline(file, line);
    auto numberOfVertices = stoi(line);
    for (size_t i = 1; i <= numberOfVertices; i++)
    {
      Vertex* v = new Vertex();
      this->vertices[i] = v;
    }
    while(getline(file,line))
    {
      auto numbers = getNumbersFromLine(line);
      Edge edge(this->vertices[numbers.first], this->vertices[numbers.second]);
      this->edges.push_back(edge);
    }
    file.close();
    for (size_t i = 1; i <= numberOfVertices; i++)
      this->vertices[i]->setAdjacentsAndDegree(&this->edges);
  }
}
Edge::Edge(Vertex* a, Vertex* b){
  this->vertex_a = a;
  this->vertex_b = b;
}

void Graph::generateGraphFile(std::string fileName){
  std::ofstream file(fileName);
  file << "Número de vértices: " << this->getNumberOfVertices() << "\n";
  file << "Número de arestas: " << this->getNumberOfEdges() << "\n";
  for (size_t i = 1; i <= this->getNumberOfVertices(); i++)
    file << "Vértice: " << i << " Grau: " << this->vertices[i]->degree << "\n";
}

void Vertex::setAdjacentsAndDegree(std::vector<Edge>* edges){
  this->degree = 0;
  for (auto edge: *edges){
    if (edge.vertex_a == this || edge.vertex_b == this){
      this->adjacents.push_back(edge.vertex_a);
      if (edge.vertex_b == this && edge.vertex_a == this){
        this->degree+=2;
      } else {
        this->degree++;
      }
    }
  }
}

std::pair<int, int> getNumbersFromLine(std::string line){
  std::pair<int, int> numbers;
  std::istringstream buff(line);
  std::istream_iterator<std::string> buff_it(buff), end;
  std::vector<std::string> strings(buff_it, end);
  numbers.first = std::stoi(strings[0]);
  numbers.second = std::stoi(strings[1]);
  return numbers;
}