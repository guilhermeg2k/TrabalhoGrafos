#include "Graph.hpp"

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
			this->vertices[i] = v;
		}
		while (getline(file, line))
		{
			auto numbers = getNumbersFromLine(line);
			Edge edge(this->vertices[numbers.first], this->vertices[numbers.second]);
			this->edges.push_back(edge);
		}
		file.close();
		for (int i = 1; i <= numberOfVertices; i++)
			this->vertices[i]->setAdjacentsAndDegree(&this->edges);
	}
}
Edge::Edge(Vertex *a, Vertex *b)
{
	this->vertex_a = a;
	this->vertex_b = b;
}

void Graph::generateGraphFile(std::string fileName)
{
	std::ofstream file(fileName);
	file << "Número de vértices: " << this->getNumberOfVertices() << "\n";
	file << "Número de arestas: " << this->getNumberOfEdges() << "\n";
	for (size_t i = 1; i <= this->getNumberOfVertices(); i++)
		file << "Vértice: " << i << " Grau: " << this->vertices[i]->degree << "\n";
}

void Vertex::setAdjacentsAndDegree(std::vector<Edge> *edges)
{
	this->degree = 0;
	for (auto edge : *edges)
	{
		if (edge.vertex_a == this)
		{
			this->adjacents.push_back(edge.vertex_b);
			this->degree++;
		}
		else if (edge.vertex_b == this)
		{
			this->adjacents.push_back(edge.vertex_a);
			this->degree++;
		}
		else if (edge.vertex_b == this && edge.vertex_a == this)
		{
			this->adjacents.push_back(edge.vertex_a);
			this->degree += 2;
		}
	}
}
void Graph::generateAdjacencyMatrix()
{
	std::cout << "Matrix de Adjacência\n";
	for (unsigned int i = 1; i <= this->getNumberOfVertices(); i++)
	{
		for (size_t j = 1; j <= this->getNumberOfVertices(); j++)
		{
			auto finded = std::find(this->vertices[i]->adjacents.begin(),
									this->vertices[i]->adjacents.end(),
									this->vertices[j]);
			if (finded != this->vertices[i]->adjacents.end())
				std::cout << "1 ";
			else
				std::cout << "0 ";
		}
		std::cout << "\n";
	}
}
void Graph::generateAdjacencyList()
{
	std::cout << "Lista de Adjacência\n";
	for (unsigned int i = 1; i <= this->getNumberOfVertices(); i++)
	{
		std::cout << "{ ";
		for (size_t j = 1; j <= this->getNumberOfVertices(); j++)
		{
			auto finded = std::find(this->vertices[i]->adjacents.begin(),
									this->vertices[i]->adjacents.end(),
									this->vertices[j]);
			if (finded != this->vertices[i]->adjacents.end())
				std::cout << j << " ";
		}
		if (i == this->getNumberOfVertices())
			std::cout << "}";
		else
			std::cout << "}, ";
	}
	std::cout << "\n";
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
