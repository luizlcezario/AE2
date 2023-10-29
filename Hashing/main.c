#include "hash.h"
#include <stdio.h>
int main()
{
	tipoHash hash = criar(encadeamento, 11);
	// 	INSERIR cor azul
	inserir(hash, "cor", "azul");
	// INSERIR cidade campinas
	inserir(hash, "cidade", "campinas");
	// INSERIR nome fernando
	inserir(hash, "nome", "fernado");
	// INSERIR universidade ufabc
	inserir(hash, "universidade", "ufabc");
	// INSERIR curso computacao
	inserir(hash, "curso", "computacao");
	// QUANTIDADE
	printf("%i\n", quantidade(hash));
	// BUSCAR nome
	printf("%s\n", buscar(hash, "nome"));
	// BUSCAR cor
	printf("%s\n", buscar(hash, "cor"));
	// BUSCAR universidade
	printf("%s\n", buscar(hash, "universidade"));
	// BUSCAR cidade
	printf("%s\n", buscar(hash, "cidade"));
	// BUSCAR curso
	printf("%s\n", buscar(hash, "curso"));
	// BUSCAR azul
	if (buscar(hash, "azul") == NULL)
		printf("%s\n", "(NULL)");
	// INSERIR avenida estado
	inserir(hash, "avenida", "estado");
	// INSERIR estrela sol
	inserir(hash, "estrela", "sol");
	// INSERIR disciplina aed2
	inserir(hash, "disciplina", "aed2");
	// INSERIR centro CMCC
	inserir(hash, "centro", "CMCC");
	// QUANTIDADE
	printf("%i\n", quantidade(hash));
	// APAGAR cor
	apagar(hash, "cor");
	if (buscar(hash, "azul") == NULL)
		printf("%s\n", "(NULL)");

	destruir(hash);
}
