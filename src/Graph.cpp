#include "Graph.hpp"

Edge::Edge(Vertex *a, Vertex *b)
{
	this->vertex_a = a;
	this->vertex_b = b;
}
Graph::Graph(string textFile,bool p_temPeso)
{
	this->temPeso=p_temPeso;

	ifstream file(textFile);
	cout << "lendo arquivo \n";
	if (file.is_open())
	{
		string line;
		istringstream lineStream;
		getline(file, line);
		auto numberOfVertices = stoi(line);

		for (int i = 0; i < numberOfVertices; i++)
		{
			Vertex *v = new Vertex();
			v->number = i;
			this->vertices.push_back(v);
		}
		while (getline(file, line))
		{
			if(this->temPeso==true){
				auto numbers = getNumbersFromLineV2(line);
				Edge *edge = new Edge(this->vertices[get<0>(numbers)- 1], this->vertices[get<1>(numbers)- 1]);
				edge->peso = get<2>(numbers);

				this->vertices[get<0>(numbers) - 1]->adjacents.push_back(this->vertices[get<1>(numbers) - 1]);
				this->vertices[get<1>(numbers) - 1]->adjacents.push_back(this->vertices[get<0>(numbers) - 1]);
				this->edges.push_back(edge);
			}
			else{
				auto numbers = getNumbersFromLine(line);
				Edge *edge = new Edge(this->vertices[numbers.first - 1], this->vertices[numbers.second - 1]);
				this->vertices[numbers.first - 1]->adjacents.push_back(this->vertices[numbers.second - 1]);
				this->vertices[numbers.second - 1]->adjacents.push_back(this->vertices[numbers.first - 1]);
				this->edges.push_back(edge);
			}
			
			
		}

		for (auto v : this->vertices)
		{
			BFSTable bfstable;
			this->BFS.push_back(bfstable);
		}
	}
}
void Graph::saveGraphInfoFile(string fileName)
{
	ofstream file(fileName);
	file << "Número de vértices: " << this->getNumberOfVertices() << "\n";
	file << "Número de arestas: " << this->getNumberOfEdges() << "\n";
	for (size_t i = 0; i < this->getNumberOfVertices(); i++)
		file << "Vértice: " << i << " Grau: " << this->vertices[i]->adjacents.size() << "\n";
}
void Graph::printGraphInfo()
{
	cout << "Número de vértices: " << this->getNumberOfVertices() << "\n";
	cout << "Número de arestas: " << this->getNumberOfEdges() << "\n";
	for (size_t i = 0; i < this->getNumberOfVertices(); i++)
		cout << "Vértice: " << i+1 << " Grau: " << this->vertices[i]->adjacents.size() << "\n";
}
void Graph::generateAdjacencyMatrix()
{
	cout << "Matrix de Adjacência\n";
	for (auto v : this->vertices)
	{
		int arr[this->getNumberOfVertices()];

		for (auto pa : v->adjacents)
		{
			arr[pa->number] = 1;
		}
		for (auto i : arr)
		{
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
		int arr[this->getNumberOfVertices()];

		for (auto pa : v->adjacents)
		{
			arr[pa->number] = 1;
		}
		for (auto i : arr)
		{
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
		for (auto a : v->adjacents)
		{
			cout << a->number << " ";
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
		for (auto a : v->adjacents)
		{
			file << a->number << " ";
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
			printf(" %d ", vertex->number);
		}
		cout << "}\n";
		counter++;
	}
}
void Graph::saveComponentsToFile(string fileName)
{
	ofstream file(fileName);
	int counter = 0;
	int tamanhoMaiorComponente = 0;
	int tamanhoMenorComponente = this->getNumberOfVertices();
	file << "Número de componentes: " << this->components.size() << "\n";

	for (auto component : this->components)
	{
		if (tamanhoMaiorComponente < component->vertices.size())
		{
			tamanhoMaiorComponente = component->vertices.size();
		}
		if (tamanhoMenorComponente > component->vertices.size())
		{
			tamanhoMenorComponente = component->vertices.size();
		}
		file << "Componente " << counter << ", Número de vertices: " << component->vertices.size() << "\n{";
		for (auto vertex : component->vertices)
		{
			file << " " << vertex->number << " ";
		}
		file << "}\n";
		counter++;
	}
	file << "Tamanho Maior Componente: " << tamanhoMaiorComponente << "\n";
	file << "Tamanho Menor Componente: " << tamanhoMenorComponente << "\n";
}
void Graph::breadthFirstSearch(int vertex)
{
	queue<Vertex *> queue;
	queue.push(this->vertices[vertex]);
	queue.front()->visitedbyBFF = true;
	for (auto v : this->vertices)
	{
		v->visitedbyBFF = false;
		this->BFS[v->number].distance = 0;
		this->BFS[v->number].root = 0;
	}
	while (!queue.empty())
	{
		for (auto s : queue.front()->adjacents)
		{
			if (s->visitedbyBFF == false)
			{
				this->BFS[s->number].distance = this->BFS[queue.front()->number].distance + 1;
				this->BFS[s->number].root = queue.front()->number;
				if ( this->BFS[s->number].distance > this->diameter){
					this->diameter = this->BFS[s->number].distance ;
				}
				s->visitedbyBFF = true;
				queue.push(s);
			}
		}
		queue.pop();
	}
}
void Graph::calculateDiameter()
{
	for (auto v : this->vertices)
	{
		breadthFirstSearch(v->number);
	}
	cout << "O DIÂMETRO DO GRAFO É: " << this->diameter << "\n";
}

void Graph::saveBFSToFile(string fileName)
{
	ofstream file(fileName);
	for (int i = 0; i < this->getNumberOfVertices(); i++)
	{
		file << "Vértice " << i << " Raiz " << this->BFS[i].root << " Nível " << this->BFS[i].distance << "\n";
	}
}

void Graph::printBFS()
{
	for (int i = 0; i < this->getNumberOfVertices(); i++)
	{
		cout << "Vértice " << i << " Raiz " << this->BFS[i].root << " Nível " << this->BFS[i].distance << "\n";
	}
}
void Graph::visitVerticesRecursive(Vertex *vertex, Graph *component)
{
	vertex->visitedbyComponentGenerator = true;
	component->vertices.push_back(vertex);
	for (auto v : vertex->adjacents)
	{
		if (!v->visitedbyComponentGenerator)
			visitVerticesRecursive(v, component);
	}
}
void Graph::graphDFS(int verticeInicial)
{
	int verticesVisitados[this->getNumberOfVertices()];
	No *n = new No();

	Vertex *v = this->vertices[verticeInicial];

	for (int i = 0; i < this->getNumberOfVertices(); ++i)
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
		if (verticesVisitados[v->number] == 0)
		{
			No *n = new No();

			n->noPai = noPai->num;
			n->nivel = noPai->nivel + 1;
			n->num = v->number;

			if (n->nivel > this->nivelMax)
			{
				this->nivelMax = n->nivel;
			}

			this->arvoreDeBusca.push_back(n);

			dfsr(v, verticesVisitados, n);
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

bool Graph::verificaPesos(){

	for(Edge* e : this->edges){
		if(e->peso < 0)
			return false;
	}

	return true;
}

void Graph::custoMinimoDijkstra(Vertex* s)
{	
	if(!this->verificaPesos()){
		cout << "O Grafo possui pesos negativos!";
		return;
	}
		

   int pa[getNumberOfVertices()]; //Vertice pai temporário
   float dist[getNumberOfVertices()]; //Custo mínimo	
   bool tree[getNumberOfVertices()];


   // inicialização:
	for(int i = 0;i<getNumberOfVertices();i++){
	  pa[i] = -1 ;
	  tree[i] = false;
	  dist[i] = INFINITY;
	}
	
	//Vértice inicial custo 0
	pa[s->number] = s->number;
	tree[s->number] = true; 
	dist[s->number] = 0.0;



	//Percorre as arestas procurando os vertices adjacentes ao s
	for(Edge* e : this->edges){

		if(e->vertex_a->number == s->number){
			pa[e->vertex_b->number] = s->number;
			dist[e->vertex_b->number] = e->peso;	
		}

		if(e->vertex_b->number == s->number){
			pa[e->vertex_a->number] = s->number;
			dist[e->vertex_a->number] = e->peso;	
		}	
	}
	
   Vertex* y = new Vertex();

   while (true) {

      // cálculo de y:
      float min = INFINITY;
      for (Vertex* z : this->vertices) {
		 //Vértice fechado 
         if (tree[z->number]) 
		 	continue;

		 //Vértice aberto	 
         if (dist[z->number] < min){		
            min = dist[z->number]; 
			y = z;
		}
      }



      if (min == INFINITY) 
	  	break;
      
	  tree[y->number] = true;

      // atualização de dist[] e pa[]:
	  for(Edge* e : this->edges)
	  {
		  if(e->vertex_a->number == y->number){
			  if(tree[e->vertex_b->number])
			  	continue;

			  if ((dist[y->number] + e->peso) < dist[e->vertex_b->number]){
				  dist[e->vertex_b->number] = dist[y->number] + e->peso;
				  pa[e->vertex_b->number] = y->number;
			  }
			 
		  }
		  
		  if(e->vertex_b->number == y->number){
			  if(tree[e->vertex_a->number])
			  	continue;

			  if ((dist[y->number] + e->peso) < dist[e->vertex_a->number]){
				  dist[e->vertex_a->number] = dist[y->number] + e->peso;
				  pa[e->vertex_a->number] = y->number;
			  }

		  }

	  }

}

   std::cout <<"\n";	

   	for(int i=0;i<getNumberOfVertices();i++){
	   
	   std::cout << "Custo para alcancar Vertice: "<< i+1 <<" "<< dist[i] << "\n";
   }

}

pair<int, int> Graph::getNumbersFromLine(string line)
{
	pair<int, int> numbers;
	istringstream buff(line);
	istream_iterator<string> buff_it(buff), end;
	vector<string> strings(buff_it, end);

	numbers.first = stoi(strings[0]);
	numbers.second = stoi(strings[1]);
	return numbers;
}

tuple<int,int,float> Graph:: getNumbersFromLineV2(string line){
	tuple<int,int,float> numbers;
	istringstream buff(line);
	istream_iterator<string> buff_it(buff), end;
	vector<string> strings(buff_it, end);

	numbers = make_tuple(stoi(strings[0]),stoi(strings[1]),stof(strings[2]));

	return numbers;
}

void Graph::testeArestas(){
	for (auto edge : this->edges){
		cout << "v1: " <<edge->vertex_a->number << " v2: " <<edge->vertex_b->number <<" Peso: " <<edge->peso <<"\n";

	}
}
