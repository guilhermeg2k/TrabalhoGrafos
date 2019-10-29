#include "Graph.hpp"
#include <map>
using namespace std;
int main()
{
	std::string archive;
	
	// variável de controle das opções que podem ser selecionadas
	int op = 0;
	int vbl = 0;
	//controle de operações já realizadas
	int matrix_r = 0;
	int list_r = 0;
	int comp_r = 0;
	int info_r = 0;
	
	// controla quem pode aparecer
	char proc = 'i';
	
	cout << "Digite o nome do arquivo que desja abrir:\nEx.: as_graph.txt :\n";
	cin >> archive;
	Graph graph(archive);
	cout << "Arquivo de nome '" << archive << "' carregado com sucesso\n\n";
	cout << "============================ BEM VINDO ============================\n\n";

	while (proc == 'i')
	{
		cout << "====================================================================\n\n";
		cout << "[1]EXIBE INFORMACOES DO GRAFO\n";
		if (matrix_r == 0)
			cout << "[2]GERAR MATRIZ DE ADJACÊNCIA\n";
		else
			cout << "[-]MATRIZ DE ADJACENCIA JA GERADA EM ARQUIVO EXTERNO\n";
		
		if (list_r == 0)
			cout << "[3]GERAR LISTA DE ADJACÊNCIA\n";
		else
			cout << "[-]LISTA DE ADJACENCIA JÁ GERADA EM ARQUIVO EXTERNO\n";
		if (comp_r == 0)
			cout << "[4]GERAR COMPONENTES CONEXOS\n";
		else
			cout << "[-]COMPONENTES CONEXOS JÁ GERADO EM ARQUIVO EXTERNO\n";
		//
		cout << "[5]REALIZAR BUSCA EM LARGURA\n";
		cout << "[6]REALIZAR BUSCA EM PROFUNDIDADE\n";
		cout << "[7]CALCULAR DIÂMETRO DO GRAFO\n";
		cout << "[8]SAIR DO PROGRAMA\n";
		cin >> op;
		
		switch (op)
		{

		case 1:
		{
			graph.printGraphInfo();	
			int gi = 0;
			if(info_r == 0 ){
				cout <<"\nDESEJA SALVAR AS INFORMAÇÕES DO GRAFO EM UM ARQUIVO EXTERNO?\n[1]SIM\n[2]NAO\n";
				cin >> gi;
					if (gi ==1){
						graph.saveGraphInfoFile("out/info.txt");
						cout << "ARQUIVO DE SAIDA GERADO COM NOME 'out/info.txt'";
						info_r = 1;
					}
			}
			break;
		}
		case 2:
		{
			system("clear");
			cout << "====================================================================\n\n";
			cout << "DESEJA PRINTAR OU SALVAR EM UM ARQUIVO EXTERNO?\n[1]PRINTAR\n[2]SALVAR EM ARQUIVO\n";
			int gm = 0;
			cin >> gm;
			if (gm == 2)
			{
				matrix_r = 1;
				graph.saveAdjacencyMatrixToFile("out/matrix.txt");
				cout << "\nARQUIVO DE SAIDA GERADO, NOME: 'out/matrix.txt'\n";
			} else if (gm == 1 ){
				graph.generateAdjacencyMatrix();
			}
			break;
		}
		case 3:
		{
			system("clear");
			int gl = 0;
			cout << "====================================================================\n\n";
			cout << "DESEJA PRINTAR OU SALVAR EM UM ARQUIVO EXTERNO?\n[1]PRINTAR\n[2]SALVAR EM ARQUIVO\n";
			cin >> gl;
			if (gl == 2)
			{
				list_r = 1;
				system("clear");
				graph.saveAdjacencyListToFile("out/list.txt");
				cout << "\nARQUIVO DE SAIDA GERADO, NOME: 'out/list.txt'\n";
			} else if (gl == 1){
				system("clear");
				graph.generateAdjacencyList();
			}
			break;
		}
		case 4:
		{
			system("clear");
			graph.generateComponents();
			
			int gc = 0;
			cout << "====================================================================\n\n";
			cout << "DESEJA PRINTAR OU SALVAR EM UM ARQUIVO EXTERNO?\n[1]PRINTAR\n[2]SALVAR EM ARQUIVO\n";
			cin >> gc;
			if (gc == 2)
			{
				comp_r = 1;
				graph.saveComponentsToFile("out/components.txt");
				cout << "\nARQUIVO DE SAIDA GERADO, NOME: 'out/componentes.txt'\n";
			} else if(gc == 1){
				system("clear");
				graph.printComponents();
			}
			break;
		}
		case 5:
		{
			int vbl;
			int salva_bfs = 0;
			cout << "====================================================================\n\n";
			cout << "DIGITE O NUMERO DO VERTICE QUE DESEJA REALIZAR A BUSCA: \n";
			cin >> vbl;
			graph.breadthFirstSearch(vbl);
			cout << "====================================================================\n\n";
			cout <<"DESEJA SALVAR OS DADOS DA BUSCA EM LARGURA (BREADTH FIRST SEARCH) EM UM ARQUIVO EXTERNO?\n[1]SIM\n[2]NAO\n";
			cin >> salva_bfs;
			if(salva_bfs == 1){
				string newFileName = "out/BFS_"+to_string(vbl)+".txt";
				graph.saveBFSToFile(newFileName);
				cout << "\nARQUIVO DE SAIDA GERADO, NOME: '"+newFileName+"'\n";
			}
			break;
		}
		case 6:
		{
			int teste;
			int vbp;
			int salva_dfs = 0;
			cout << "====================================================================\n\n";
			cout << "DIGITE O NUMERO DO VERTICE QUE DESEJA REALIZAR A BUSCA: \n";
			cin >> vbp;
			graph.graphDFS(vbp);
			cout <<"DESEJA SALVAR OS DADOS DA BUSCA EM PROFUNDIDADE (DEPTH-FIRST SEARCH) EM UM ARQUIVO EXTERNO?\n[1]SIM\n[2]NAO\n";
			cin >> salva_dfs; 
			if(salva_dfs == 1){
				string newFileName = "out/DFS_"+to_string(vbp)+".txt";
				graph.geraArquivoArvore(newFileName);
				cout << "\nARQUIVO DE SAIDA GERADO, NOME: '"+newFileName+"'\n";
			}
			break;
		}
		
		case 7:
		{
			graph.calculateDiameter();
			break;
		}
		case 8: {
			proc = 's';
			break;
		}
		default:
			break;
		}
	}
	system("clear");
	cout << "====================================================================\n\n";
	cout << "============================== OBRIGADO ============================\n";
	cout << "OBS.: TODOS OS ARQUIVOS DE SAIDA FORAM ARMAZENADOS NA PASTA 'OUT'\n";

}
