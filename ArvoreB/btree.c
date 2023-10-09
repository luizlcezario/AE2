#include <stdlib.h>
#include "btree.h"

btNo *btNoCriar(int ordem)
{
	btNo *no = (btNo *)malloc(sizeof(btNo));
	no->ehFolha = true;
	no->numChaves = 0;
	no->chaves = (int *)malloc(sizeof(int) * ordem + 1);
	no->chaves[ordem] = 0;
	no->filhos = (btNo **)calloc(ordem + 1, sizeof(btNo *));
}

btNo *cpNo(btNo *x, int ordem)
{
	btNo *cpy = btNoCriar(ordem);
	for (int i = 0; i < ordem; i++)
	{
		cpy->chaves[i] = x->chaves[i];
		x->chaves[i] = 0;
		cpy->filhos[i] = x->filhos[i];
		x->filhos[i] == NULL;
	}
	cpy->numChaves = x->numChaves;
	return cpy;
}
bTree btCriar(const unsigned char ordem)
{
	bTree b;
	// IMPLEMENTAR!
	b.ordem = ordem;
	b.raiz = btNoCriar(ordem);
	// DICA 1: Crie uma funcao auxiliar
	// DICA 2: Alem do no, nao esqueca de alocar a lista de chaves e filhos, de acordo com a ordem:
	//           A lista de chaves tem o tamanho da ordem (um a mais, utilizado como auxiliar)
	//           A lista de filhos tem o tamanho da ordem + 1 (um a mais, utilizado como auxiliar)
	// DICA 3: Nao esqueca de inicializar todos atributos (ver btree.h)
	return b;
}

void btNoDestruir(btNo *no)
{
	for (int a = 0; no->filhos[a] != NULL; a++)
	{
		btNoDestruir(no->filhos[a]);
	}
	free(no->chaves);
	free(no->filhos);
}

void btDestruir(bTree b)
{
	// IMPLEMENTAR!
	btNoDestruir(b.raiz);
	free(b.raiz);
	// DICA 1: Destrua primeiro os filhos
	// DICA 2: Nao esqueca de desalocar a lista de chaves e filhos de cada noh
}

int buscarChave(int n, const int *a, int chave)
{
	int lo;
	int hi;
	int mid;

	lo = -1;
	hi = n;
	while (lo + 1 < hi)
	{
		mid = (lo + hi) / 2;
		if (a[mid] == chave)
		{
			return mid;
		}
		else if (a[mid] < chave)
		{
			lo = mid;
		}
		else
		{
			hi = mid;
		}
	}
	return hi;
}

void splitChild(btNo *x, int child, int ordem)
{
	int t = ordem / 2 + ordem % 2;

	btNo *z = btNoCriar(ordem);
	btNo *y = x->filhos[child];
	z->ehFolha = y->ehFolha;
	z->numChaves = t - 1;
	for (int j = 0; j < t - 1; j++)
	{
		z->chaves[j] = y->chaves[j + 1];
	}
	if (!y->ehFolha)
	{
		for (int j = 0; j < t; j++)
		{
			z->filhos[j] = y->filhos[j + t];
		}
	}
	y->numChaves = t - 1;
	for (int j = x->numChaves + 1; j > child + 1; j--)
	{
		x->filhos[j + 1] = y->filhos[j];
	}
	x->filhos[child + 1] = z;
	for (int j = x->numChaves; j > child; j--)
	{
		x->filhos[j + 1] = x->filhos[j];
	}
	// x->chaves[child] = y->chaves[child];
	// x->numChaves = x->numChaves + 1;
}

void insertNonFullNo(btNo *x, int chave, int ordem)
{
	int i = x->numChaves;

	if (x->ehFolha)
	{
		while (i >= 0 && chave < x->chaves[i - 1])
		{
			x->chaves[i] = x->chaves[i - 1];
			i = i - 1;
		}
		x->chaves[i] = chave;
		x->numChaves = x->numChaves + 1;
	}
	else
	{
		while (i >= 0 && chave < x->chaves[i])
		{
			i = i - 1;
		}
		if (x->filhos[i]->numChaves == ordem / 2 - 1)
		{
			splitChild(x, i, ordem);
			if (chave > x->chaves[i])
			{
				i = i + 1;
			}
		}
		insertNonFullNo(x->filhos[i], chave, ordem);
	}
}

void btInserir(bTree b, int chave)
{
	btNo *r = b.raiz;

	if (r->numChaves == b.ordem - 1)
	{
		btNo *s = cpNo(r, b.ordem);
		r->numChaves = 0;
		r->filhos[0] = s;
		r->ehFolha = false;
		splitChild(r, 0, b.ordem);
		insertNonFullNo(r, chave, b.ordem);
	}
	else
		insertNonFullNo(b.raiz, chave, b.ordem);
}

int buscar(btNo *no, int chave)
{
	int pos = buscarChave(no->numChaves, no->chaves, chave);
	if (pos < no->numChaves && no->chaves[pos] == chave)
	{
		return 1;
	}
	else
	{
		return (!no->ehFolha && buscar(no->filhos[pos], chave));
	}
}

int btBuscar(bTree b, int chave)
{
	// IMPLEMENTAR!
	// Retornar true se a chave nao existe false se a chave nao existe
	int pos;
	if (b.raiz->numChaves == 0)
	{
		return 0;
	}
	return (buscar(b.raiz, chave));
}

int btAltura(bTree b)
{
	btNo *tmp;
	int count = 1;

	tmp = b.raiz;
	while (tmp->filhos[0] != NULL)
	{
		tmp = tmp->filhos[0];
		count++;
	}
	return count;
}

int teste(btNo *no)
{
	int a = 1;

	for (int a = 0; no->filhos[a] != NULL; a++)
	{
		a += teste(no->filhos[a]);
	}
	return a;
}

int btContaNos(bTree b)
{
	return teste(b.raiz);
}

int contaChaves(btNo *no)
{
	int a = 0;

	for (int a = 0; no->filhos[a] != NULL; a++)
	{
		a += contaChaves(no->filhos[a]);
	}
	return a + no->numChaves;
}

int btContaChaves(bTree t)
{
	return contaChaves(t.raiz);
}
