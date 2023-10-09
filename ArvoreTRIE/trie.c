#include "trie.h"

// DICA: Estude o arquivo trie.h antes de iniciar a sua implementacao!

no *criarNo(void)
{
	int i;
	no *novo = (no *)malloc(sizeof(no));
	if (novo != NULL)
	{
		novo->tipo = 'I';
		for (i = 0; i < TAMANHO_ALFABETO; i++)
			novo->filho[i] = NULL;
	}
	else
	{
		return NULL;
	}
	return novo;
}

void apagarArvore(no *raiz)
{
	if (raiz == NULL)
		return;
	for (int i = 0; i < TAMANHO_ALFABETO; i++)
	{
		apagarArvore(raiz->filho[i]);
	}
	free(raiz);
}

void adicionarPalavra(char *palavra, no *raiz)
{
	// IMPLEMENTAR !!!
	int nivel = 0, indice;
	no *tmp = raiz;

	for (nivel = 0; nivel < strlen(palavra); nivel++)
	{
		indice = CHAR_TO_INDEX(palavra[nivel]);
		if (tmp->filho[indice] == NULL)
		{
			tmp->filho[indice] = criarNo();
		}
		tmp = tmp->filho[indice];
	}
	tmp->tipo = 'P';
}

int buscaPalavra(char *palavra, no *raiz)
{
	int i, indice;
	no *tmp = raiz;

	for (i = 0; i < strlen(palavra); i++)
	{
		indice = CHAR_TO_INDEX(palavra[i]);
		if (tmp->filho[indice] != NULL)
			tmp = tmp->filho[indice];
		else
			break;
	}
	if (palavra[i] == '\0' && tmp->tipo == 'P')
		return 1;
	else
		return 0;
}

int numeroDeNos(no *r)
{
	// IMPLEMENTAR !!!
	// Dica: A funcao pode ser muito simples se utilizar recursao
	int final = 1;
	if (r == NULL)
		return 0;
	for (int i = 0; i < TAMANHO_ALFABETO; i++)
	{
		if (r->filho[i] != NULL)
		{
			final += numeroDeNos(r->filho[i]);
		}
	}
	return final;
}

int numeroDePalavras(no *r)
{
	// IMPLEMENTAR !!!
	// Dica: Similar a funcao numeroDeNos, mas contabilize apenas os tipos 'P', que representa as palavras
	int final = 0;
	if (r == NULL)
		return 0;
	if (r->tipo == 'P')
		final++;
	for (int i = 0; i < TAMANHO_ALFABETO; i++)
	{
		if (r->filho[i] != NULL)
		{
			final += numeroDePalavras(r->filho[i]);
		}
	}
	return final;
}

int altura(no *r)
{
	// IMPLEMENTAR !!!
	int final = 1;
	int tmp = 0;
	if (r == NULL)
		return 0;
	for (int i = 0; i < TAMANHO_ALFABETO; i++)
	{
		if (r->filho[i] != NULL)
		{
			tmp += altura(r->filho[i]);
		}
		if (final < tmp)
		{
			final = tmp;
		}
	}
	return final;
}

void removerPalavra(char *palavra, no *raiz)
{
	// IMPLEMENTAR !!!
	int i, indice;
	no *tmp = raiz;
	no *pai;
	int len = strlen(palavra);
	if (buscaPalavra(palavra, raiz) == 0)
		return;
	for (i = 0; i < len - 1; i++)
	{
		indice = CHAR_TO_INDEX(palavra[i]);
		if (tmp->filho[indice] != NULL)
			tmp = tmp->filho[indice];
	}
	pai = tmp->filho[CHAR_TO_INDEX(palavra[i])];
	pai->tipo = 'I';
	for (i = 0; i < TAMANHO_ALFABETO; i++)
	{
		if (pai->filho[i] != NULL)
		{
			break;
		}
	}
	if (i == TAMANHO_ALFABETO)
	{
		tmp->filho[CHAR_TO_INDEX(palavra[len - 1])] = NULL;
		free(pai);
	}

}