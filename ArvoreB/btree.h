#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct btNo
{
	bool ehFolha;			// false se nao for uma folha, true se for uma folha.
	unsigned int numChaves; // Quantidade total de chaves no noh
	int *chaves;			// Ponteiro para uma lista com as chaves
	struct btNo **filhos;	// Ponteiro para uma lista de ponteiros dos nos filhos
} btNo;

typedef struct bTree
{
	btNo *raiz;			 // Ponteiro para o noh raiz
	unsigned char ordem; // Quantidade máxima de filhos
} bTree;

bTree btCriar(const unsigned char ordem);
void btDestruir(bTree t);
int btBuscar(bTree t, int chave);
void btInserir(bTree t, int key);
int btAltura(bTree t);
int btContaNos(bTree t);
int btContaChaves(bTree t);
void print(btNo *no);
#endif
