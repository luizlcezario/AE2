#include "btree.h"
#include <stdio.h>
#include <assert.h>

void print(btNo *no)
{
	int i;

	printf("[ ");
	for (i = 0; i < no->numChaves || no->filhos[i] != NULL; i++)
	{
		if (no->filhos[i] != NULL)
			print(no->filhos[i]);
		if (i < no->numChaves)
			printf("%i ", no->chaves[i]);
	}
	printf("] ");
}

void testInserir()
{
	int i[] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	bTree b = btCriar(3);
	for (int a = 0; a < 10; a++)
	{
		btInserir(b, i[a]);
		print(b.raiz);
		printf("\n@@@\n");
	}
	btDestruir(b);
}

int main(void)
{
	testInserir();
	return 0;
}