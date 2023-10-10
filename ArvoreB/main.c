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

void testBase(int *i, int size, int ordem)
{
	bTree b = btCriar(ordem);
	for (int a = 0; a < size; a++)
	{
		printf("@@@ inserindo %i:\n", i[a]);
		btInserir(b, i[a]);
		print(b.raiz);
		printf("\n");
	}
	for (int a = 0; a < size; a++)
	{
		printf("@@@ buscando %i: ", i[a]);
		assert(btBuscar(b, i[a]) == 1);
		printf("OK\n", i[a]);
	}
	printf("@@@ altura: %i\n", btAltura(b));
	printf("@@@ Chaves: %i\n", btContaChaves(b));
	printf("@@@ Nos: %i\n", btContaNos(b));
	btDestruir(b);
}

int main(void)
{
	int test1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int test2[] = {57, 54, 52, 31, 51, 53, 60, 55, 46, 39, 35, 33, 45, 59, 50, 58, 49, 47, 36, 44, 37, 38, 56, 40, 43, 34, 32, 48, 42, 41};
	int test9[] = {60, 35, 23, 22, 34, 16, 30, 25, 26, 40, 38, 12, 41, 47, 44, 31, 3, 6, 21, 48, 5, 59, 19, 56, 51, 53, 52, 58, 55, 28, 43, 42, 2, 15, 33, 7, 10, 8, 14, 18, 54, 37, 29, 4, 17, 50, 20, 9, 57, 36, 39, 49, 1, 60, 13, 46, 45, 32, 27, 11, 24};
	int test10[] = {96, 76, 91, 62, 83, 78, 40, 93, 20, 39, 37, 44, 27, 97, 74, 51, 17, 38, 85, 9, 50, 58, 24, 90, 89, 72, 65, 11, 19, 21, 29, 98, 26, 10, 47, 42, 68, 84, 8, 5, 48, 35, 28, 100, 34, 52, 4, 32, 71, 22, 15, 99, 41, 55, 33, 60, 25, 2, 49, 3, 73, 94, 13, 80, 63, 53, 12, 45, 87, 64, 95, 23, 79, 75, 86, 77, 70, 67, 6, 31, 56, 30, 14, 57, 54, 81, 66, 59, 46, 69, 16, 1, 7, 82, 92, 18, 88, 61, 36, 43};

	testBase(test1, 10, 3);
	testBase(test2, 30, 4);
	testBase(test9, 60, 9);
	testBase(test10, 100, 3);
	return 0;
}