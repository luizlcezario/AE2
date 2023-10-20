#include "uf.h"

grafo *criarGrafo(int V, int E)
{
	grafo *g = (grafo *)malloc(sizeof(grafo));
	g->V = V;
	g->E = E;
	g->VetorDeArestas = (aresta *)malloc(g->E * sizeof(aresta));
	return g;
}

void destruirGrafo(grafo *g)
{
	free(g->VetorDeArestas);
	free(g);
}

subset *Make_Subset(int tamanho)
{
	subset *subconjuntos = (subset *)malloc(tamanho * sizeof(subset));
	for (int i = 0; i < tamanho; i++)
	{
		Make_Set(subconjuntos, i);
	}
	return subconjuntos;
}

void Destroy_Subset(subset *s)
{
	free(s);
}

void Make_Set(subset subconjuntos[], int i)
{
	subconjuntos[i].pai = i;
	subconjuntos[i].rank = 0;
}

// Funcao que procura o representante (pai) do elemento i com compressao de caminho.
int Find_Set(subset subconjuntos[], int i)
{
	if (subconjuntos[i].pai != i)
		subconjuntos[i].pai = Find_Set(subconjuntos, subconjuntos[i].pai);
	return subconjuntos[i].pai;
}

// Funcao que junta os conjuntos de x e y com uniao ponderada.
void Union(subset subconjuntos[], int x, int y)
{
	x = Find_Set(subconjuntos, x);
	y = Find_Set(subconjuntos, y);
	if (subconjuntos[x].rank > subconjuntos[y].rank)
		subconjuntos[y].pai = x;
	else
	{
		subconjuntos[x].pai = y;
		if (subconjuntos[x].rank == subconjuntos[y].rank)
			subconjuntos[y].rank++;
	}

	// DICA: Pseudo-codigo disponivel no Slide. Nao esquecer da uniao ponderada.
}

// Funcao utilizada para verificar se o grafo tem ou nao ciclo
bool TemCiclo(grafo *g)
{
	// IMPLEMENTAR !!!
	// IMPLEMENTAR !!!
	// IMPLEMENTAR !!!
	// DICA: Faca um laco de 0 ate g->E unindo os vertices.
	//       Caso os verticies ja pertencerem ao memso componente conexo (usar Find_Set),
	//       significa que o grafo tem um ciclo.
	bool tem_ciclo = false;
	subset *s = Make_Subset(g->V);
	for (int i = 0; i < g->E; i++)
	{
		if (Find_Set(s, g->VetorDeArestas[i].origem) == Find_Set(s, g->VetorDeArestas[i].destino))
			tem_ciclo = true;
		Union(s, g->VetorDeArestas[i].origem, g->VetorDeArestas[i].destino);
	}
	Destroy_Subset(s);
	return tem_ciclo;
}

int QuantidadeComponentesConexas(grafo *g)
{
	// IMPLEMENTAR !!!
	// IMPLEMENTAR !!!
	// IMPLEMENTAR !!!
	subset *s = Make_Subset(g->V);
	for (int i = 0; i < g->E; i++)
	{
		int rx = Find_Set(s, g->VetorDeArestas[i].origem);
		int ry = Find_Set(s, g->VetorDeArestas[i].destino);
		if (rx != ry)
			Union(s, rx, ry);
	}
	int nc = 0;
	for (int i = 0; i < g->V; i++)
	{
		if (i == Find_Set(s, i))
		{
			nc++;
		}
	}
	Destroy_Subset(s);
	return nc;
}

int MaiorComponenteConexa(grafo *g)
{
	// IMPLEMENTAR !!!
	// IMPLEMENTAR !!!
	// IMPLEMENTAR !!!
	// DICA: Inicio similar a funcao anterior, mas eh preciso contar quantos vertices tem cada
	//       componente conexo para descobrir qual eh de maior quantidade.
	//       Tente criar um vetor auxiliar (tamanho g->V), percorrer todos os vertices e
	//       incrementar o no representante (pai) para cada vertice. Assim, basta buscar a maior contagem.
	if (g->V < 1)
		return 0;
	subset *s = Make_Subset(g->V);
	for (int i = 0; i < g->E; i++)
	{
		int rx = Find_Set(s, g->VetorDeArestas[i].origem);
		int ry = Find_Set(s, g->VetorDeArestas[i].destino);
		if (rx != ry)
			Union(s, rx, ry);
	}
	int nc = 0;
	int *vetor = calloc(sizeof(int), g->V);
	for (int i = 0; i < g->V; i++)
	{
		int a = Find_Set(s, i);
		vetor[a]++;
	}
	for (int i = 0; i < g->V; i++)
	{
		if (nc < vetor[i])
			nc = vetor[i];
	}
	Destroy_Subset(s);
	free(vetor);
	return nc;
}

int compara(const void *i, const void *a)
{
	aresta *x = (aresta *)i;
	aresta *y = (aresta *)a;

	return (x->peso > y->peso);
}

int SomaPesoArestasDaArvoreGeradoraMinima(grafo *g)
{
	int *vetor = (int *)calloc(sizeof(int), g->V);
	qsort(g->VetorDeArestas, g->E, sizeof(g->VetorDeArestas[0]), &compara);
	subset *s = Make_Subset(g->V);
	int x = 0, y = 0;
	while (x < g->V - 1 && y < g->E)
	{
		aresta prox = g->VetorDeArestas[y++];
		int a = Find_Set(s, prox.origem);
		int b = Find_Set(s, prox.destino);

		if (a != b)
		{
			resultante[x++] = prox;
			Union(s, a, b);
		}
	}
	int count = 0;
	for (int i = 0; i < x; ++i)
	{
		count += resultante[i].peso;
	}
	Destroy_Subset(s);
	return count;
}

int main()
{
}