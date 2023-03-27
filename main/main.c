#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

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

//cria a tabela no banco de dados
int criarTabela()
{
	sqlite3 *db;
	int exit = 0;
	char *sql;
	char *messageError;

	//Abre o banco de dados
	exit = sqlite3_open("Banco de Dados/lista_clientes.db", &db);
	
	if(exit != SQLITE_OK){
		printf("Erro ao abrir banco de dados");
		sqlite3_close(db);
		return 1;	
	}
	
	//verifica se a tabela Cliente já foi criada
	exit = sqlite3_exec(db, "SELECT name FROM sqlite_master WHERE type='table' AND name='CLIENTE';", 0, 0, &messageError);

	//se não, cria ela
	if (exit != SQLITE_ROW)
	{
		sql = "CREATE  TABLE CLIENTE("
			  "ID INT PRIMARY KEY  NOT NULL, "
			  "NOME 	TEXT 	NOT NULL, "
			  "IDADE 	INT	NOT NULL, "
			  "ESTADO_CIVIL TEXT NOT NULL);";
			  
		//executa o comando de criação de tabela	
		exit = sqlite3_exec(db, sql, callback, 0, &messageError);
		
		//verifica se houve algum erro
		if (exit != SQLITE_OK)
		{
			printf("Erro: %s\n", messageError);
			sqlite3_free(messageError);
			sqlite3_close(db);
			return 1;
		}
	}
	sqlite3_close(db);
	return 0;
}

//função de manipulação do sqlite
int adicionarDados(char name[], char age[], char status[])
{
	sqlite3 *db;
	int exit = 0;
	int id = 0;
	char *messageError;
	char *sql;
	char *query = "SELECT * FROM CLIENTE";
	char *insert[50];
	char *count = "SELECT COUNT (*) FROM CLIENTE";

	//inicia o banco de dados
	exit = sqlite3_open("Banco de Dados/lista_clientes.db", &db);
	if (exit)
	{
		printf("Não foi possivel iniciar o db");
	}

	//conta quantos elementos tem na tabela
	exit = sqlite3_exec(db, count, contar, &id, NULL);

	if (exit != SQLITE_OK)
	{
		printf("SQLITE ERROR: %s\n", messageError);
	}

	//insere um elemento a tabela
	sprintf(insert, "INSERT INTO CLIENTE(ID, NOME, IDADE, ESTADO_CIVIL)"
					"VALUES('%d', '%s', '%s', '%s');",
			id, name, age, status);

	exit = sqlite3_exec(db, insert, callback, 0, &messageError);
	if (exit != SQLITE_OK)
	{
		printf("SQLITE ERROR: %s\n", messageError);
	}

	//escreve o banco de dados inteiro no terminal
	exit = sqlite3_exec(db, query, callback, NULL, NULL);
	if (exit != SQLITE_OK)
	{
		printf("SQLITE ERROR: %s\n", messageError);
	}

	sqlite3_close(db);
	return 0;
}


//Cria uma ficha de inscricao
int criarInscricao(void)
{	
	char nome[10], idade[3], estadoCivil[10];
	int estadoCivil_selecao, aux = 1;
	
	printf("\nPara começar, diga seu nome: ");
	scanf("%s", nome);

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

	adicionarDados(nome, idade, estadoCivil);
	
	return 0;
}

//funcao principal
int main(void)
{
	printf("Olá, bem vindo ao SII(Sistema integado de inscrições) \n\nVocê já tem uma conta?");

	int escolhaConta;
	printf("\nSIM[1]  NÃO[0]\n");
	scanf("%d", &escolhaConta);

	criarTabela();

	if (escolhaConta)
	{
		adicionarDados("Pedro", "58", "Solteiro");
		return 0;
	}
	else
	{
		criarInscricao();
	}

	return 0;
}

//id: 000000
//Nome: (nome)
//Idade: (idade)
//Estado Civil: (est civ)
