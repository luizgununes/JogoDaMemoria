/*

* Programa: Jogo da Memória
* Data de Criação: 01/07/2017
* Criado por: Luiz Gustavo Nunes

*/	

// Bibliotecas:
#include <stdio.h> // Biblioteca para o printf e scanf.
#include <stdlib.h> // Biblioteca para o rand() e system cls.
#include <time.h> // Biblioteca para o srand() e clock.
#include <locale.h> // Biblioteca para a regionalização.
#include <windows.h> // Biblioteca para o sleep.

//Tabuleiro:
#define N 5 // Largura do Tabuleiro (Linhas).
#define M 8 // Comprimento do Tabuleiro (Colunas).
#define P 20 // Quantidade de Cartas Diferentes (Metade do Total).

// Váriáveis Globais:
char GAB[N][M]; // Tabuleiro Gabarito.
char TAB[N][M]; // Tabuleiro Apresentado.
char CAR[P] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'}; // Cartas.
int COL[M]; // Número de Colunas.
int score=0; // Pontuação.
int acao=0; // Ações.     
clock_t inicio,fim; // Contador.          
	           
// Função p/ Exibir o Menu:
void menu() {
	printf("\t****************************************************************\n"); 
	printf("\t****************************************************************\n");
    printf("\t**                    = Jogo da Memória =                     **\n");
    printf("\t** Objetivo: Escolher as cartas e formar seus pares.          **\n");
    printf("\t** O jogador vence quando encontrar todos os pares.           **\n");
    printf("\t** ---------------------------------------------------------- **\n");
    printf("\t** Para jogar, digite 1 e pressione ENTER.                    **\n");
    printf("\t** Para sair, digite qualquer tecla.                          **\n");
	printf("\t****************************************************************\n"); 
    printf("\t****************************************************************\n");
	scanf("%d", &acao); // Lê a decisão do jogador.
	system("cls"); // Limpa a tela após uma ação.
}

// Função p/ Saída do Programa:
void saida() {	
	float c;
	fim=clock();
		c=fim-inicio/(CLOCKS_PER_SEC);
		c=c/1000;
	system ("cls");
		if (score==0)
		printf ("\n\n\tJogo encerrado.\n\n");
		else {
			if (score==20)
				printf ("\n\tPARABÉNS, VOCÊ GANHOU!"); 
		printf ("\n\n\t Fim de Jogo.\n\t Score Final: %.2f\n\n", (score/c));
	}
}

// Função p/ Esconder as Cartas:
void esconder() {
	int i, j;
	for (i=0; i<N; i++) 
		for (j=0; j<M; j++)
			TAB[i][j]='*';
}

// Função p/ Inicializar o Tabuleiro:
void inicializacao() {
	int i, j, k=0;
	for (i=0; i<N; i++)
		for (j=0; j<M; j++){
			GAB[i][j]=CAR[k];
			if (k<P-1)
				k++;
				else 
					k=0;
		}
	esconder();
}

// Função p/ Embaralhar Cartas:
void embaralhar () {
	int i, j, x, y;
	char aux;
	srand(time(NULL)); // Gerador de Números Aleatórios.
	for (i=0; i<N; i++)
		for (j=0; j<M; j++){
			x=rand()%N; // Gera Valores Aleatórios de 0 até N.
			y=rand()%M; // Gera Valores Aleatórios de 0 até M.
			aux=GAB[i][j];
			GAB[i][j]=GAB[x][y];
			GAB[x][y]=aux;
		}	
}

// Função p/ Mostrar Tela de Jogo:
void telajogo (int acao) {
	int i, j;
	if (acao==1){
		printf ("\n Para Sair, digite: -1, -1 \n\n\tScore: %d \n\n", score);
		printf ("\t ");
		for (i=0; i<M; i++){
			COL[i]=i;
			printf (" %d\t", COL[i]);
		}
		printf ("\n");
		for (i=0; i<N; i++) {
			printf ("\t%d", i);
			for (j=0; j<M; j++)
				printf ("[%c]\t", TAB[i][j]);
		printf ("\n\n");
		}
	}
}

// Função p/ Atualizar a Tela:
void atualizartela(int acao) {
	Sleep (1000); // Para o Programa por 1 Segundo (1000ms).
	system ("cls");
	telajogo(acao);
}

// Função p/ Execução do Jogo:
void jogar (int acao) {
	int i, j, x, y, virar=0, checar=1;
	while (score<20 && acao==1){ 
		do {   			
			printf ("\n> Informe as Coordenadas (Linha Coluna) da 1ª Carta: ");
			scanf ("%d %d", &i, &j);
			if (i<0 || j<0){
				acao=-1;
				break;
			}
			if (i>=N || j>=M){
				printf ("Coordenada Inválida!");
				checar=0;
				atualizartela(acao);
			}
				else 
					checar=1;	
			if (TAB[i][j]=='*' && checar==1){
				TAB[i][j]=GAB[i][j];
				system ("cls");
				telajogo(acao);
				virar++;
			}
				else if (checar==1){
						printf ("Esta carta já foi escolhida!");
						atualizartela(acao);
					}
		} while (virar<1);
		if (acao<0)
			break;
		do {
			printf ("\n> Informe as Coordenadas (Linha Coluna) da 2ª Carta: ");
			scanf ("%d %d", &x, &y);	
			if (x<0 || y<0){
				acao=-1;
				break;
			}
			if (x>=N || y>=M){
				printf ("Coordenada Inválida!");
				checar=0;
				atualizartela(acao);
			}
				else 
					checar=1;
			if (TAB[x][y]=='*' && checar==1){
				TAB[x][y]=GAB[x][y];
				system ("cls");
				telajogo(acao);
				virar++;
			}
				else 
					if (checar==1){
						printf ("Esta carta já foi escolhida!");
						atualizartela(acao);	
	 				}
		} while (virar<2);	
		if (acao<0)
			break;
		if (TAB[i][j]==TAB[x][y]){
			virar=0; 
			score++;
			printf ("\n\t\t\t\t  É Par!");
			Sleep (500); // Para o Programa por Meio Segundo (500ms).
		}
			else { 
				TAB[i][j]='*';
				TAB[x][y]='*';
				virar=0;
				printf ("\n\t\t\t\t  ERROU!");
				Sleep (300); // Para o Programa por 0.3 Segundos (300ms).
			}
		atualizartela(acao);
 	}
}

// Função Principal:
int main() {
	// Comando de Regionalização:
	setlocale(LC_ALL, "Portuguese");
	// Título do Programa:
	SetConsoleTitle("Jogo da Memoria 1.0");
	// Ordem de Execução:
	inicializacao();
	embaralhar();
	menu();
	telajogo(acao);
	jogar(acao);
	saida();
return 0;
}

/* Para testar o fim do jogo rapidamente, trocar as matrizes define para 2x2 e o score para 2. */
