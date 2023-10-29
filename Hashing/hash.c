#include "hash.h"

// Funcao hash. Retorna o indice de uma chave na tabela. Nao alterar!
int hash(char chave[STR_SIZE], int tamanho, int tentativa)
{
	int h = chave[0];
	for (int i = 1; chave[i] != '\0'; i++)
		h = (h * 251 * chave[i]) % tamanho;
	return (h + tentativa) % tamanho;
}

tipoHash criar(modoHash m, int t)
{
	tipoHash h;
	h.tamanho = t;
	switch (h.modo = m)
	{
	case semColisao:
		h.tabela.aberto = (hashAberto *)malloc(sizeof(hashAberto) * t);
		for (int i = 0; i < t; i++)
			h.tabela.aberto[i].chave[0] = h.tabela.aberto[i].valor[0] = '\0';
		break;

	case encadeamento:
		h.tabela.encadeada = (hashEncadeada *)malloc(sizeof(hashEncadeada) * t);
		for (int i = 0; i < t; i++)
			h.tabela.encadeada[i].primeiro = NULL;
		break;

	case aberto:
		h.tabela.aberto = (hashAberto *)malloc(sizeof(hashAberto) * t);
		for (int i = 0; i < t; i++)
		{
			h.tabela.aberto[i].excluido = false;
			h.tabela.aberto[i].chave[0] = h.tabela.aberto[i].valor[0] = '\0';
		}
		break;
	}
	return h;
}

void destruir(tipoHash h)
{
	listaEncadeada *tmp = NULL;
	listaEncadeada *tmp2 = NULL;
	switch (h.modo)
	{
	case aberto:
	case semColisao:
		free(h.tabela.aberto);
		h.tabela.aberto = NULL;
		break;

	case encadeamento:
		for (int i = 0; i < h.tamanho; i++)
		{
			for (tmp = h.tabela.encadeada[i].primeiro; tmp != NULL; tmp = tmp2)
			{
				tmp2 = tmp->proximo;
				free(tmp);
			}
		}
		free(h.tabela.encadeada);
		h.tabela.encadeada = NULL;
		break;
	}
}

void inserir(tipoHash h, char c[STR_SIZE], char v[STR_SIZE])
{
	int idx = hash(c, h.tamanho, 0);
	listaEncadeada *tmp;
	switch (h.modo)
	{
	case semColisao:
		strcpy(h.tabela.aberto[idx].chave, c);
		strcpy(h.tabela.aberto[idx].valor, v);
		break;

	case encadeamento:

		if (h.tabela.encadeada[idx].primeiro == NULL)
		{
			h.tabela.encadeada[idx].primeiro = (listaEncadeada *)malloc(sizeof(listaEncadeada) * 1);
			strcpy(h.tabela.encadeada[idx].primeiro->chave, c);
			strcpy(h.tabela.encadeada[idx].primeiro->valor, v);
			h.tabela.encadeada[idx].primeiro->proximo = NULL;
		}
		else
		{
			tmp = h.tabela.encadeada[idx].primeiro;
			while (tmp->proximo != NULL)
				tmp = tmp->proximo;
			tmp->proximo = (listaEncadeada *)malloc(sizeof(listaEncadeada) * 1);
			strcpy(tmp->proximo->chave, c);
			strcpy(tmp->proximo->valor, v);
			tmp->proximo->proximo = NULL;
		}
		break;
	case aberto:
		// IMPLEMENTAR!!!
		// DICA: Eh utilizado encadeamento aberto linear. Utilize as tentativas conforme mostrado abaixo.
		for (int tentativa = 0; tentativa < h.tamanho; tentativa++)
		{
			idx = hash(c, h.tamanho, tentativa);
			if (h.tabela.aberto[idx].chave[0] == 0)
			{
				strcpy(h.tabela.aberto[idx].chave, c);
				strcpy(h.tabela.aberto[idx].valor, v);
				break;
			}
		}
		break;
	}
}

char *buscar(tipoHash h, char c[STR_SIZE])
{
	int idx = hash(c, h.tamanho, 0);
	listaEncadeada *tmp = NULL;
	switch (h.modo)
	{
	case semColisao:
		return strcmp(h.tabela.aberto[idx].chave, c) == 0 ? h.tabela.aberto[idx].valor : NULL;

	case encadeamento:
		tmp = h.tabela.encadeada[idx].primeiro;
		while (tmp != NULL)
		{
			if (strcmp(tmp->chave, c) == 0)
				return tmp->valor;
			tmp = tmp->proximo;
		}
		return NULL;
	case aberto:
		if (strcmp(h.tabela.aberto[idx].chave, c) == 0)
			return h.tabela.aberto[idx].valor;
		for (int tentativa = 0; tentativa < h.tamanho; tentativa++)
		{
			idx = hash(c, h.tamanho, tentativa);
			if (strcmp(h.tabela.aberto[idx].chave, c) == 0)
				return h.tabela.aberto[idx].valor;
		}
		return NULL;
	}
	return NULL;
}

void apagar(tipoHash h, char c[STR_SIZE])
{
	int idx = hash(c, h.tamanho, 0);
	listaEncadeada *tmp = NULL;
	listaEncadeada *tmp2 = NULL;
	switch (h.modo)
	{
	case semColisao:
		if (strcmp(h.tabela.aberto[idx].chave, c) == 0)
			h.tabela.aberto[idx].chave[0] = h.tabela.aberto[idx].valor[0] = '\0';
		break;

	case encadeamento:
		tmp = h.tabela.encadeada[idx].primeiro;
		tmp2;
		while (tmp != NULL)
		{
			if (strcmp(tmp->chave, c) == 0)
			{
				if (tmp2 == NULL)
					h.tabela.encadeada[idx].primeiro = tmp->proximo;
				else
					tmp2->proximo = tmp->proximo;
				free(tmp);
				break;
			}
			tmp2 = tmp;
			tmp = tmp->proximo;
		}
		break;
	case aberto:
		if (strcmp(h.tabela.aberto[idx].chave, c) == 0)
			h.tabela.aberto[idx].chave[0] = h.tabela.aberto[idx].valor[0] = '\0';
		for (int tentativa = 0; tentativa < h.tamanho; tentativa++)
		{
			idx = hash(c, h.tamanho, tentativa);
			if (strcmp(h.tabela.aberto[idx].chave, c) == 0)
			{
				h.tabela.aberto[idx].chave[0] = h.tabela.aberto[idx].valor[0] = '\0';
				break;
			}
		}
		break;
	}
}

int quantidade(tipoHash h)
{
	int qtd = 0;
	listaEncadeada *tmp = NULL;
	switch (h.modo)
	{
	case semColisao:
	case aberto: // Igual ao semColisao, portanto, jah implementado!!!
		for (int i = 0; i < h.tamanho; i++)
			if (h.tabela.aberto[i].chave[0] != '\0')
				qtd++;
		break;

	case encadeamento:
		for (int i = 0; i < h.tamanho; i++)
		{
			for (tmp = h.tabela.encadeada[i].primeiro; tmp != NULL; tmp = tmp->proximo)
				qtd++;
		}
		break;
	}
	return qtd;
}
