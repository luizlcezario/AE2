#include "btree.h"
#include <stdio.h>
#include <assert.h>

void print(btNo *no)
{
	int i;

	if (no)
	{
		printf("[ ");
		for (i = 0; i < no->numChaves; i++)
		{
			print(no->filhos[i]);
			printf("%d ", no->chaves[i]);
		}
		print(no->filhos[i]);
		printf("] ");
	}
}

void testInserir()
{
	int i[] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	bTree b = btCriar(3);
	for (int a = 0; a < 10; a++)
	{
		printf("\n@@@ inserindo %i\n", i[a]);
		btInserir(b, i[a]);
		print(b.raiz);
		printf("\n");
	}
	btDestruir(b);
}

int main(void)
{
	testInserir();
	return 0;
}