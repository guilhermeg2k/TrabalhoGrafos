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
	// system pause
	
	// controla quem pode aparecer
	char proc = 'i';
	
	cout << "Digite o nome do arquivo que desja abrir:\nEx.: as_graph :\n";
	cin >> archive;
	archive = archive + ".txt";
	Graph graph(archive);
	cout << "Arquivo de nome '" << archive << "' carregado com sucesso\n\n";
	system("PAUSE");
	cout << "============================ BEM VINDO ============================\n\n";

	while (proc == 'i')
	{
		cout << "====================================================================\n\n";
		cout << "[1]EXIBE INFORMACOES DO GRAFO\n";
		if (matrix_r == 0)
			cout << "[2]GERAR MATRIZ DE ADJACÊNCIA\n";
		else
			cout << "[-]MATRIZ DE ADJACENCIA JA GERADA\n";
		
		if (list_r == 0)
			cout << "[3]GERAR LISTA DE ADJACÊNCIA\n";
		else
			cout << "[-]LISTA DE ADJACENCIA JA GERADA\n";
		if (comp_r == 0)
			cout << "[4]GERAR COMPONENTES CONEXOS\n";
		else
			cout << "[-]COMPONENTES CONEXOS JA GERADOS\n";
		//
		cout << "[5]REALIZAR BUSCA EM LARGURA\n";
		cout << "[6]REALIZAR BUSCA EM PROFUNDIDADE\n";
		cout << "[7]SAIR DO PROGRAMA\n";
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
						graph.saveGraphInfoFile("out_info.txt");
						cout << "ARQUIVO DE SAIDA GERADO COM NOME 'out_info.txt'";
						info_r = 1;
					}
			}
			break;
		}
		case 2:
		{
			system("clear");
			graph.generateAdjacencyMatrix();
			int gm = 0;
			cout << "====================================================================\n\n";
			cout << "DESEJA SALVAR A MATRIX DE ADJACÊNCIA GERADA EM UM ARQUIVO EXTERNO ?\n[1]SIM\n[2]NAO\n";
			cin >> gm;
			if (gm == 1)
			{
				matrix_r = 1;
				graph.saveAdjacencyMatrixToFile("out_matrix.txt");
				cout << "\nARQUIVO DE SAIDA GERADO, NOME: 'out_matrix.txt'\n";
			}
			break;
		}
		case 3:
		{
			system("clear");
			graph.generateAdjacencyList();
			int gl = 0;
			cout << "====================================================================\n\n";
			cout << "DESEJA SALVAR A LISTA DE ADJACÊNCIA GERADA EM UM ARQUIVO EXTERNO ?\n[1]SIM\n[2]NAO\n";
			cin >> gl;
			if (gl == 1)
			{
				list_r = 1;
				graph.saveAdjacencyListToFile("out_list.txt");
				cout << "\nARQUIVO DE SAIDA GERADO, NOME: 'out_list.txt'\n";
			}
			break;
		}
		case 4:
		{
			system("clear");
			graph.generateComponents();
			graph.printComponents();
			int gc = 0;
			cout << "====================================================================\n\n";
			cout << "DESEJA SALVAR OS COMPONENTES COEXOS GERADOS EM UM ARQUIVO EXTERNO ?\n[1]SIM\n[2]NAO\n";
			cin >> gc;
			if (gc == 1)
			{
				comp_r = 1;
				graph.saveComponentsToFile("out_components.txt");
				cout << "\nARQUIVO DE SAIDA GERADO, NOME: 'out_componentes.txt'\n";
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
				graph.saveBFSToFile("out_bfs.TXT");
				cout << "\nARQUIVO DE SAIDA GERADO, NOME: 'BFS.txt'\n";
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
				graph.geraArquivoArvore();
				cout << "\nARQUIVO DE SAIDA GERADO, NOME: 'Arvore.txt'\n";
			}
			break;
		}
		
		case 7:
		{
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
