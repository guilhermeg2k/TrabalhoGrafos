#include "Graph.hpp"
#include <map>
using namespace std;
int main(){
	Graph graph("teste.txt");
	graph.generateAdjacencyMatrix();
	graph.saveAdjacencyMatrixToFile("out/MATRIX.TXT");
	graph.generateAdjacencyList();
	graph.saveAdjacencyListToFile("out/LIST.TXT");
	/* 1 DEPENDE DA 2 */
	/* 1 */graph.generateComponents();
	/* 2 */ graph.saveComponentsToFile("out/components.txt");
	/* 2 */ graph.printComponents();
	/* 1 */graph.breadthFirstSearch(2);
	/* 2 */graph.saveBFSToFile("out/BFS.TXT");
	/* 1 */graph.graphDFS(5);
  	/* 2 */graph.geraArquivoArvore();
}
