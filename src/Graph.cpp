#include "Graph.hpp"

Edge::Edge(Vertex *a, Vertex *b)
{
	this->vertex_a = a;
	this->vertex_b = b;
}
void Vertex::setAdjacentsAndDegree(std::vector<Edge*> edges)
{
	this->degree = 0;
	for (auto edge : edges)
	{
		if (edge->vertex_a == this)
		{
			this->adjacents.push_back(edge->vertex_b);
			this->degree++;
		}
		else if (edge->vertex_b == this)
		{
			this->adjacents.push_back(edge->vertex_a);
			this->degree++;
		}
		else if (edge->vertex_b == this && edge->vertex_a == this)
		{
			this->adjacents.push_back(edge->vertex_a);
			this->degree += 2;
		}
	}
}
Graph::Graph(std::string textFile)
{
	std::ifstream file(textFile);
	if (file.is_open())
	{
		std::string line;
		std::istringstream lineStream;
		getline(file, line);
		auto numberOfVertices = stoi(line);
		for (int i = 1; i <= numberOfVertices; i++)
		{
			Vertex *v = new Vertex();
			v->number = i;
			this->vertices[i] = v;
		}
		while (getline(file, line))
		{
			auto numbers = getNumbersFromLine(line);
			Edge* edge = new Edge(this->vertices[numbers.first], this->vertices[numbers.second]);
			this->edges.push_back(edge);
		}
		file.close();
		for (int i = 1; i <= numberOfVertices; i++)
			this->vertices[i]->setAdjacentsAndDegree(this->edges);
	}
}
void Graph::saveGraphInfoFile(std::string fileName)
{
	std::ofstream file(fileName, std::fstream::app);
	file << "Número de vértices: " << this->getNumberOfVertices() << "\n";
	file << "Número de arestas: " << this->getNumberOfEdges() << "\n";
	for (size_t i = 1; i <= this->getNumberOfVertices(); i++)
		file << "Vértice: " << i << " Grau: " << this->vertices[i]->degree << "\n";
}
void Graph::printGraphInfo()
{
	std::cout << "Número de vértices: " << this->getNumberOfVertices() << "\n";
	std::cout << "Número de arestas: " << this->getNumberOfEdges() << "\n";
	for (size_t i = 1; i <= this->getNumberOfVertices(); i++)
		std::cout << "Vértice: " << i << " Grau: " << this->vertices[i]->degree << "\n";
}
void Graph::generateAdjacencyMatrix()
{
	const auto SIZE = this->getNumberOfVertices();
	std::vector<std::vector<int>> adjacencyMatrix;
	for (auto i = 0; i < SIZE; i++)
	{
		std::vector<int> inner;
		for (auto j = 0; j < SIZE; j++)
			inner.push_back(0);
		adjacencyMatrix.push_back(inner);
	}
	auto i = 0;
	for(auto vertex: this->vertices){
		for(auto adjacent: vertex.second->adjacents){
			adjacencyMatrix[i][adjacent->number-1] = 1;
		}
		i++;
	}
	this->adjacencyMatrix = adjacencyMatrix;
}
void Graph::printAdjacencyMatrix(){
	const auto SIZE = this->getNumberOfVertices();
	std::cout << "Matriz de adjacência\n";
	for (auto i = 0; i < SIZE; i++){
		for (auto j = 0; j < SIZE; j++)
			std::cout << this->adjacencyMatrix[i][j] << " ";
		std::cout << "\n";
	}
}
void Graph::saveAdjacencyMatrixToFile(std::string fileName){
	std::ofstream file(fileName, std::fstream::app);
	file << "Matriz de adjacência\n";
	const auto SIZE = this->getNumberOfVertices();
	for (auto i = 0; i < SIZE; i++){
		for (auto j = 0; j < SIZE; j++)
			file << this->adjacencyMatrix[i][j] << " ";
		file << "\n";
	}

}
void Graph::generateAdjacencyList()
{
	std::vector<std::vector<int>> adjacencyList;
	for(auto vertex: this->vertices){
		std::vector<int> inner;
		for(auto adjacent: vertex.second->adjacents){
			inner.push_back(adjacent->number);
		}
		adjacencyList.push_back(inner);
	}
	this->adjacencyList = adjacencyList;
}
void Graph::printAdjacencyList(){
	std::cout << "Lista de adjacência\n";
	for (auto adjacents: this->adjacencyList){
		std::cout << "{ ";
		for (auto number: adjacents){
			std::cout << number << " ";
		}
		std::cout << "}\n";
	}
}
void Graph::saveAdjacencyListToFile(std::string fileName){
	std::ofstream file(fileName, std::fstream::app);
	file << "Lista de adjacência\n";
	for (auto adjacents: this->adjacencyList){
		file << "{ ";
		for (auto number: adjacents){
			file << number << " ";
		}
		file << "}\n";
	}
}
void Graph::generateComponents(){
	for (auto edge : this->edges){
		if (!edge->vertex_a->visited){
			Graph* component = new Graph();
			visitVerticesRecursive(edge->vertex_a, component);
			this->components.push_back(component);
		}	
	}
}
void Graph::printComponents(){
	int counter = 1;
	std::cout << "Número de componentes: " << this->components.size() << "\n";
	for (auto component : this->components){
		std::cout << "Componente " << counter << ", Número de vertices: " <<  component->vertices.size() <<"\n{";
		for (auto vertex: component->vertices){
			printf(" %d ", vertex.second->number);
		}
		std::cout << "}\n";
		counter++;
	}
}
void Graph::saveComponentsToFile(std::string fileName){
	std::ofstream file(fileName, std::fstream::app);
	int counter = 1;
	file << "Número de componentes: " << this->components.size() << "\n";
	for (auto component : this->components){
		file << "Componente " << counter << ", Número de vertices: " <<  component->vertices.size() <<"\n{";
		for (auto vertex: component->vertices){
			file <<" "<<vertex.second->number<<" ";
		}
		file << "}\n";
		counter++;
	}
}
void Graph::printAll(){
	this->printGraphInfo();
	this->printAdjacencyMatrix();
	this->printAdjacencyList();
	this->printComponents();
}
void Graph::saveAllToFile(std::string fileName){
	this->saveGraphInfoFile(fileName);
	this->saveAdjacencyMatrixToFile(fileName);
	this->saveAdjacencyListToFile(fileName);
	this->saveComponentsToFile(fileName);
}
void visitVerticesRecursive(Vertex* vertex, Graph* component){
	vertex->visited = true;
	component->vertices[component->vertices.size()+1] = vertex;
	for (auto v: vertex->adjacents){
		if(!v->visited)
			visitVerticesRecursive(v, component);
	}
}
std::pair<int, int> getNumbersFromLine(std::string line)
{
	std::pair<int, int> numbers;
	std::istringstream buff(line);
	std::istream_iterator<std::string> buff_it(buff), end;
	std::vector<std::string> strings(buff_it, end);
	numbers.first = std::stoi(strings[0]);
	numbers.second = std::stoi(strings[1]);
	return numbers;
}
