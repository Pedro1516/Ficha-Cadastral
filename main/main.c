#include <stdio.h>
#include <string.h>

typedef  struct clientes
{
	char id[10];
	char nome[30];
	char idade[3];
	char estadoCivil[10];
}add;

//Adiciona os dados numa struct
add adicionarDados(char name[], char age[], char status[]){
	struct clientes novoCliente;
	strcpy(novoCliente.nome, name);
	strcpy(novoCliente.idade, age);
	strcpy(novoCliente.estadoCivil, status);
	
	return novoCliente;
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
		
	while(aux){
			printf("\nQual seu estado civil? \nSolteiro[0] Casado[1] Viuvo[2] Divorciado[3] Separado[4]\n");
			scanf("%d", &estadoCivil_selecao);
			
			switch(estadoCivil_selecao){
				case 0:
					strcpy(estadoCivil, "Solteiro");
					break;
				case 1:
					strcpy(estadoCivil, "Casado");
				 	break;
				case 2:
					strcpy(estadoCivil,  "Viuvo");
				 	break;
				 case 3:
				 	strcpy(estadoCivil, "Divorciado");
				 	break;
				 case 4:
				 	strcpy(estadoCivil, "Separado");
				 	break;
			}
			if(estadoCivil_selecao >= 0 && estadoCivil_selecao < 5){aux = 0;}
		}
		
		add teste =  adicionarDados(nome, idade, estadoCivil);
	  	printf("\n\nNome: %s\nIdade: %s\nEstado Civil: %s", teste.nome, teste.idade, teste.estadoCivil);
				
		return 0;
}



//funcao principal
int main(void)
{
	printf("Olá, bem vindo ao SII(Sistema integado de inscrições) \n\nVocê já tem uma conta?");
	
	int escolhaConta;
	printf("\nSIM[1]  NÃO[0]\n");
	scanf("%d", &escolhaConta);
	
	if(escolhaConta)
	{
		return 0;
	}
	else
	{
	criarInscricao();
	}
	
		
	return 0;
}
