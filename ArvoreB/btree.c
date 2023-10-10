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
	return no;
}

btNo *cpNo(btNo *x, int ordem)
{
	btNo *cpy = btNoCriar(ordem);
	for (int i = 0; i < ordem + 1; i++)
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

	b.ordem = ordem;
	b.raiz = btNoCriar(ordem);
	return b;
}

void btNoDestruir(btNo *no)
{
	int a;

	if (no)
	{
		for (a = 0; a < no->numChaves; a++)
		{
			btNoDestruir(no->filhos[a]);
		}
		btNoDestruir(no->filhos[a]);
		free(no->chaves);
		free(no->filhos);
	}
}

void btDestruir(bTree b)
{
	// IMPLEMENTAR!
	btNoDestruir(b.raiz);
	free(b.raiz);
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
	int t = ordem / 2;
	btNo *z = btNoCriar(ordem);
	btNo *y = x->filhos[child];
	z->ehFolha = y->ehFolha;
	z->numChaves = t;
	for (int j = 0; j < t; j++)
		z->chaves[j] = y->chaves[j + t + 1];
	if (!y->ehFolha)
	{
		for (int j = 0; j < t + 1; j++)
			z->filhos[j] = y->filhos[j + t + 1];
	}
	y->numChaves = t;
	for (int j = x->numChaves; j > child + 1; j--)
		x->filhos[j + 1] = y->filhos[j];
	x->filhos[child + 1] = z;
	for (int j = x->numChaves; j > child; j--)
	{
		x->filhos[j + 1] = x->filhos[j];
	}
	x->chaves[child] = y->chaves[t];
	x->numChaves++;
}

void insertNonFullNo(btNo *x, int chave, int ordem)
{
	int i = x->numChaves;

	int pos = buscarChave(i, x->chaves, chave);
	if (pos < i && x->chaves[pos] == chave)
		return;
	if (x->ehFolha)
	{
		for (int j = pos; j < x->numChaves; j++)
			x->chaves[j + 1] = x->chaves[j];
		x->chaves[pos] = chave;
		x->numChaves++;
	}
	else
	{
		insertNonFullNo(x->filhos[i], chave, ordem);
		if (x->filhos[i]->numChaves == ordem)
			splitChild(x, i, ordem);;
	}
}

void btInserir(bTree b, int chave)
{
	btNo *r = b.raiz;

	insertNonFullNo(r, chave, b.ordem);
	if (r->numChaves == b.ordem)
	{

		btNo *s = cpNo(r, b.ordem);
		r->numChaves = 0;
		r->filhos[0] = s;
		s->ehFolha = r->ehFolha;
		r->ehFolha = false;
		splitChild(r, 0, b.ordem);
	}
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
