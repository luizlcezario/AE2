#include "trie.h"
#include <stdio.h>
#include <assert.h>

int main(void)
{
	no *raiz;
	char *lst[] = {"pa",
				   "patricia",
				   "pato",
				   "pateta",
				   "pano",
				   "pulo"};

	raiz = criarNo();
	for (int i = 0; i < 6; i++)
	{
		adicionarPalavra(lst[i], raiz);
	}
	for (int i = 0; i < 6; i++)
	{
		printf("test if %s is in the tree: ", lst[i]);
		assert(buscaPalavra(lst[i], raiz) == 1);
		printf("OK\n");
		if (i % 2 == 0)
		{
			removerPalavra(lst[i], raiz);
			printf("test if %s is not anymore in the tree: ", lst[i]);
			assert(buscaPalavra(lst[i], raiz) == 0);
			printf("OK\n");
		}
	}
	apagarArvore(raiz);
	return 0;
}