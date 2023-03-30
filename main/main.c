#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "header/function.c"

//funcao principal
int main(void)
{
	printf("Olá, bem vindo ao SII(Sistema integado de inscrições) \n\nVocê já tem uma conta?");

	criarTabela();

	int escolhaConta;
	int aux = 1;
	int id_login;
	char senha[8];
	//fica em loop até o usuário escolher uma opção válida
	while (aux)
	{
		printf("\nSIM[1]  NÃO[0]\n");
		scanf("%d", &escolhaConta);

		if (escolhaConta == 1 || escolhaConta == 0)
		{
			aux = 0;
		}
	}

	if (!escolhaConta)
	{
		criarInscricao();
	}
	else
	{
		printf("Insira seu Id: ");
		scanf("%d", &id_login);

		printf("Digite sua senha: ");
		scanf("%s", &senha);

		buscarFicha(id_login, senha);
	}

	return 0;
}
