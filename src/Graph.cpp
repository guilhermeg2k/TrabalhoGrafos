#include "Graph.hpp"
Edge::Edge(Vertex *a, Vertex *b)
{
	this->vertex_a = a;
	this->vertex_b = b;
}
void Vertex::setAdjacentsAndDegree(vector<Edge *> edges)
{
	this->degree = 0;
	for (auto edge : edges)
	{
		if (edge->vertex_a == this)
		{
			this->adjacents[edge->vertex_b->number] = (edge->vertex_b);
			this->degree++;
		}
		else if (edge->vertex_b == this)
		{
			this->adjacents[edge->vertex_a->number] = (edge->vertex_a);
			this->degree++;
		}
		else if (edge->vertex_b == this && edge->vertex_a == this)
		{
			this->adjacents[edge->vertex_a->number] = (edge->vertex_a);
			this->degree += 2;
		}
	}
}
Graph::Graph(string textFile)
{
	ifstream file(textFile);
	if (file.is_open())
	{
		string line;
		istringstream lineStream;
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
			Edge *edge = new Edge(this->vertices[numbers.first], this->vertices[numbers.second]);
			this->edges.push_back(edge);
		}
		file.close();
		for (int i = 1; i <= numberOfVertices; i++)
			this->vertices[i]->setAdjacentsAndDegree(this->edges);
	}
}
void Graph::saveGraphInfoFile(string fileName)
{
	ofstream file(fileName);
	file << "Número de vértices: " << this->getNumberOfVertices() << "\n";
	file << "Número de arestas: " << this->getNumberOfEdges() << "\n";
	for (size_t i = 1; i <= this->getNumberOfVertices(); i++)
		file << "Vértice: " << i << " Grau: " << this->vertices[i]->degree << "\n";
}
void Graph::printGraphInfo()
{
	cout << "Número de vértices: " << this->getNumberOfVertices() << "\n";
	cout << "Número de arestas: " << this->getNumberOfEdges() << "\n";
	for (size_t i = 1; i <= this->getNumberOfVertices(); i++)
		cout << "Vértice: " << i << " Grau: " << this->vertices[i]->degree << "\n";
}
void Graph::generateAdjacencyMatrix()
{
	cout << "Matrix de Adjacência\n";
	for (auto v : this->vertices)
	{
		int arr[this->getNumberOfVertices()] = {};
		for (auto pa : v.second->adjacents)
		{
			arr[pa.second->number] = 1;	
		}
		for (auto i: arr){
			cout << i;
		}
		cout << "\n";
	}
}
void Graph::saveAdjacencyMatrixToFile(string fileName)
{
	ofstream file(fileName);
	file << "Matrix de Adjacência\n";
	for (auto v : this->vertices)
	{
		int arr[this->getNumberOfVertices()] = {};
		for (auto pa : v.second->adjacents)
		{
			arr[pa.second->number] = 1;	
		}
		for (auto i: arr){
			file << i;
		}
		file << "\n";
	}
}
void Graph::generateAdjacencyList()
{
	cout << "Lista de Adjacência\n";
	for (auto v : this->vertices)
	{
		cout << "{ ";
		for (auto a : v.second->adjacents)
		{
			cout << a.second->number << " ";
		}
		cout << "}\n";
	}
	cout << "\n";
}
void Graph::saveAdjacencyListToFile(string fileName)
{
	ofstream file(fileName);
	file << "Lista de Adjacência\n";
	for (auto v : this->vertices)
	{
		file << "{ ";
		for (auto a : v.second->adjacents)
		{
			file << a.second->number << " ";
		}
		file << "}\n";
	}
	file << "\n";
}
void Graph::generateComponents()
{
	for (auto edge : this->edges)
	{
		if (!edge->vertex_a->visitedbyComponentGenerator)
		{
			Graph *component = new Graph();
			visitVerticesRecursive(edge->vertex_a, component);
			this->components.push_back(component);
		}
	}
}
void Graph::printComponents()
{
	int counter = 1;
	cout << "Número de componentes: " << this->components.size() << "\n";
	for (auto component : this->components)
	{
		cout << "Componente " << counter << ", Número de vertices: " << component->vertices.size() << "\n{";
		for (auto vertex : component->vertices)
		{
			printf(" %d ", vertex.second->number);
		}
		cout << "}\n";
		counter++;
	}
}
void Graph::saveComponentsToFile(string fileName)
{
	ofstream file(fileName);
	int counter = 1;
	int tamanhoMaiorComponente = 0;
	int tamanhoMenorComponente = this->getNumberOfVertices();
	file << "Número de componentes: " << this->components.size() << "\n";

	for (auto component : this->components)
	{
		file << "Componente " << counter << ", Número de vertices: " << component->vertices.size() << "\n{";
		for (auto vertex : component->vertices)
		{
			file << " " << vertex.second->number << " ";
		}
		file << "}\n";
		counter++;
	}
	file << "Tamanho Maior Componente: " << tamanhoMaiorComponente << "\n";
	file << "Tamanho Menor Componente: " << tamanhoMenorComponente << "\n";
}
void Graph::breadthFirstSearch(int vertex)
{
	int distance = 1;
	queue<Vertex *> queue;
	for (auto v : this->vertices)
	{
		BFSTable *bfstable = new BFSTable;
		this->BFS[v.first] = bfstable;
	}
	queue.push(this->vertices[vertex]);
	queue.front()->visitedbyBFF = true;
	while (!queue.empty())
	{
		for (auto s : queue.front()->adjacents)
		{
			if (s.second->visitedbyBFF == false)
			{
				this->BFS[s.second->number]->distance = distance;
				this->BFS[s.second->number]->root = queue.front()->number;
				s.second->visitedbyBFF = true;
				queue.push(s.second);
			}
		}
		distance++;
		queue.pop();
	}
}
void Graph::printBFS()
{
	cout << "VERTEX   ";
	for (auto v : this->vertices)
	{
		cout << v.first << " ";
	}
	cout << "\n";
	cout << "ROOT     ";
	for (int i = 1; i <= this->getNumberOfVertices(); i++)
	{
		cout << this->BFS[i]->root << " ";
	}
	cout << "\nDISTANCE ";
	for (int i = 1; i <= this->getNumberOfVertices(); i++)
	{
		cout << this->BFS[i]->distance << " ";
	}
	cout << "\n";
}
void Graph::saveBFSToFile(string fileName)
{
	ofstream file(fileName);
	file << "V|  ";
	for (auto v : this->vertices)
	{
		file << v.first << " ";
	}
	file << "\nR|  ";
	for (int i = 1; i <= this->getNumberOfVertices(); i++)
	{
		file << this->BFS[i]->root << " ";
	}
	file << "\nD|  ";
	for (int i = 1; i <= this->getNumberOfVertices(); i++)
	{
		file << this->BFS[i]->distance << " ";
	}
	file << "\n";
}
void Graph::visitVerticesRecursive(Vertex *vertex, Graph *component)
{
	vertex->visitedbyComponentGenerator = true;
	component->vertices[component->vertices.size() + 1] = vertex;
	for (auto v : vertex->adjacents)
	{
		if (!v.second->visitedbyComponentGenerator)
			visitVerticesRecursive(v.second, component);
	}
}
void Graph::graphDFS(int verticeInicial)
{
	int verticesVisitados[this->getNumberOfVertices()];
	No *n = new No();

	Vertex *v = this->vertices[verticeInicial];

	for (int i = 1; i <= this->getNumberOfVertices(); ++i)
	{
		verticesVisitados[i] = 0;
	}

	//***raiz***
	n->nivel = 0;
	n->noPai = verticeInicial;
	n->num = verticeInicial;

	this->arvoreDeBusca.push_back(n);

	for (int i = v->number; i <= this->getNumberOfVertices(); ++i)
	{
		if (verticesVisitados[i] == 0)
			dfsr(v, verticesVisitados, n);
	}
}

void Graph::dfsr(Vertex *vPai, int *verticesVisitados, No *noPai)
{
	verticesVisitados[vPai->number] = 1;

	for (auto v : vPai->adjacents)
	{
		if (verticesVisitados[v.second->number] == 0)
		{
			No *n = new No();

			n->noPai = noPai->num;
			n->nivel = noPai->nivel + 1;
			n->num = v.second->number;

			if (n->nivel > this->nivelMax)
			{
				this->nivelMax = n->nivel;
			}

			this->arvoreDeBusca.push_back(n);

			dfsr(v.second, verticesVisitados, n);
		}
	}
}
void Graph::geraArquivoArvore(string fileName)
{
	ofstream file(fileName);

	for (int i = 0; i <= this->nivelMax; i++)
	{
		for (auto no : this->arvoreDeBusca)
		{
			if (no->nivel == i)
				file << "Nível: " << no->nivel << "  Vértice: " << no->num << "  Vértice Pai: " << no->noPai << "\n";
		}
	}

	cout << "Arquivo de arvore gerado";
}
pair<int, int> getNumbersFromLine(string line)
{
	pair<int, int> numbers;
	istringstream buff(line);
	istream_iterator<string> buff_it(buff), end;
	vector<string> strings(buff_it, end);
	numbers.first = stoi(strings[0]);
	numbers.second = stoi(strings[1]);
	return numbers;
}
