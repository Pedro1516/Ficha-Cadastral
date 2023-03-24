#include <stdio.h>
#include <string.h>

struct clientes
{
	char nome[30];
	char idade[3];
	char estadoCivil[10];
};


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
		
		return 0;
}

//Adiciona os dados numa struct
int adicionarDados(){
	
}




int main(void)
{
	printf("Olá, bem vindo ao SII(Sistema integado de inscrições \n\nVocê já tem uma conta?");
	
	int escolhaConta;
	printf("\nSIM[1]  NAO[0]\n");
	scanf("%d", &escolhaConta);
	
	if(escolhaConta)
	{
		return 0;
	}
	else
	{
		criarInscricao();
	}
	
	//	printf("\n\nNome: %s\nIdade: %s\nEstado Civil: %s", nome, idade, estadoCivil);
		
	
	
	
	
	return 0;
}


//id: 000000
//Nome: (nome)
//Idade: (idade)
//Estado Civil: (est civ)
