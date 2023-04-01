#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include "header.h"

//funcao callback, ela alinha os itens da tabela
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

//função callback que serve para pegar o valor de count no sql
int contar(void *data, int argc, char **argv, char **azColName)
{
	int *result = (int *)data;
	*result = atoi(argv[0]);
	return 0;
}

//funcao que extrai senha do usuario do banco de dados
int extSenha(void *data, int argc, char **argv, char **azColName)
{
	char *result = (char *)data;
	strcpy(result, argv[0]);
	return 0;
}

//cria a tabela no banco de dados
int criarTabela()
{
	sqlite3 *db;
	int exit = 0;
	char *sql = NULL;
	char *messageError = NULL;

	//Abre o banco de dados
	exit = sqlite3_open("Banco de Dados/lista_clientes.db", &db);

	if (exit != SQLITE_OK)
	{
		printf("Erro ao abrir banco de dados");
		sqlite3_close(db);
		return 1;
	}
	//comando em sql para criação de tabela(A tabela só será criada se ela ainda não existir )
	sql = "CREATE  TABLE IF NOT EXISTS CLIENTE("
		  "ID INT PRIMARY KEY  NOT NULL, "
		  "NOME 	TEXT 	NOT NULL, "
		  "IDADE 	INT	NOT NULL, "
		  "ESTADO_CIVIL TEXT NOT NULL, "
		  "SENHA TEXT NOT NULL);";

	//executa o comando de criação de tabela
	exit = sqlite3_exec(db, sql, callback, 0, &messageError);

	//verifica se houve algum erro
	if (exit != SQLITE_OK)
	{
		//printf("%s", exit);
		printf("Erro (ao criar tabela): %s\n", messageError);
		sqlite3_free(messageError);
		sqlite3_close(db);
		return 1;
	}

	sqlite3_close(db);
	return 0;
}

//função de manipulação do sqlite
int adicionarDados(char name[], char age[], char status[], char senha[])
{
	sqlite3 *db;
	int exit = 0;
	int id = 0;
	char *messageError = NULL;
	char *query = NULL;	
	char *insert = NULL;
	int size = strlen(name) + strlen(age) + strlen(status) + strlen(senha) + 100; 
	insert = (char *)malloc(size * sizeof(char));
	char *count = "SELECT COUNT (*) FROM CLIENTE";

	//inicia o banco de dados
	exit = sqlite3_open("Banco de Dados/lista_clientes.db", &db);
	if (exit)
	{
		printf("Não foi possivel iniciar o db\n");
	}

	//conta quantos elementos tem na tabela e adiciona o valor a variavel id
	exit = sqlite3_exec(db, count, contar, &id, NULL);

	if (exit != SQLITE_OK)
	{
		printf("SQLITE ERROR: %s\n", messageError);
	}

	//insere um elemento a tabela
	sprintf(insert, "INSERT INTO CLIENTE(ID, NOME, IDADE, ESTADO_CIVIL, SENHA)"
					"VALUES('%d', '%s', '%s', '%s', '%s');",
			id, name, age, status, senha);

	exit = sqlite3_exec(db, insert, callback, 0, &messageError);
	if (exit != SQLITE_OK)
	{
		printf("SQLITE ERROR (erro ao inserir dado): %s\n", messageError);
	}

	query = sqlite3_mprintf("SELECT * FROM CLIENTE WHERE ID = %d ", id);
		exit = sqlite3_exec(db, query, callback, 0, &messageError);

		//se ocorrer algum erro a execução da função para e é printado o erro
		if (exit != SQLITE_OK)
		{
			printf("ERRO AO MOSTRAR DADOS \nErro: %s", messageError);
			sqlite3_free(messageError);
			sqlite3_close(db);
			return 1;
		}
	
	free(insert);
	insert = NULL;
	sqlite3_close(db);
	return 0;
}

//Cria uma ficha de inscricao
int criarInscricao(void)
{
	char nome[50], idade[4], estadoCivil[11], senha[9];
	int estadoCivil_selecao, aux = 1;

	printf("\nPara começar, diga seu nome: ");
	getchar();
	fgets(nome, sizeof(nome), stdin);

	//Retira a quebra de linha(\n) da variável nome
	if (nome[strlen(nome) - 1] == '\n')
	{
		nome[strlen(nome) - 1] = '\0';
	}

	printf("\nAgora diga sua idade: ");
	scanf("%s", idade);

	while (aux)
	{
		printf("\nQual seu estado civil? \nSolteiro[0] Casado[1] Viuvo[2] Divorciado[3] Separado[4]\n");
		scanf("%d", &estadoCivil_selecao);

		switch (estadoCivil_selecao)
		{
		case 0:
			strcpy(estadoCivil, "Solteiro");
			break;
		case 1:
			strcpy(estadoCivil, "Casado");
			break;
		case 2:
			strcpy(estadoCivil, "Viuvo");
			break;
		case 3:
			strcpy(estadoCivil, "Divorciado");
			break;
		case 4:
			strcpy(estadoCivil, "Separado");
			break;
		}
		if (estadoCivil_selecao >= 0 && estadoCivil_selecao < 5)
		{
			aux = 0;
		}
	}

	//define a senha do usuário
	printf("Defina sua senha [deve conter no máximo 8 caracteres]: ");

	getchar();
	fgets(senha, sizeof(senha), stdin);

	
	//retira o \n no final de senha
	if (senha[strlen(senha) - 1] == '\n')
	{
		
		senha[strlen(senha) - 1] = '\0';
	}

	adicionarDados(nome, idade, estadoCivil, senha);

	return 0;
}

int buscarFicha(int id, char senha[])
{
	sqlite3 *db;
	char *sql;
	char *messageError = NULL;
	int exit = 0;
	char senha_do_usuario[9];

	//abre o banco de dados
	exit = sqlite3_open("Banco de Dados/lista_clientes.db", &db);
	//verifica se houve algum erro
	if (exit)
	{
		printf("Não foi possivel abrir o banco de dados");
		sqlite3_free(messageError);
		sqlite3_close(db);
		return 1;
	}

	//passa o comando sql de recuperação de dado
	sql = sqlite3_mprintf("SELECT SENHA FROM CLIENTE WHERE ID = %d", id);

	//recupera a senha do banco de dados de acordo com o id
	exit = sqlite3_exec(db, sql, extSenha, &senha_do_usuario, &messageError);
	
	if (messageError != SQLITE_OK)
	{
		printf("Não foi possivel recuperar a senha do usuário\n Error: %s", &messageError);
		sqlite3_free(messageError);
		sqlite3_close(db);
		return 1;
	}

	//verifica se a senha está correta(senha padrão)
	if (strcmp(senha, senha_do_usuario))
	{
		printf("SENHA INCORRETA!");
		return 0;
	}
	else
	{
		//seleciona da tablea cliente o elemento que possui id 1
		sql = sqlite3_mprintf("SELECT * FROM CLIENTE WHERE ID = %d ", id);
		exit = sqlite3_exec(db, sql, callback, 0, &messageError);

		//se ocorrer algum erro a execução da função para e é printado o erro
		if (exit != SQLITE_OK)
		{
			printf("ERRO AO MOSTRAR DADOS \nErro: %s", messageError);
			sqlite3_free(messageError);
			sqlite3_close(db);
			return 1;
		}
	}

	sqlite3_close(db);
	return 0;
}