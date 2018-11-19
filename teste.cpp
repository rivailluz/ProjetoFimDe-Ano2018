//System 1.0//


//BIBLIOTECAS//

#include <stdio.h> 		//biblioteca de padrão//
#include <stdlib.h> 	//biblioteca de funções auxiliares//
#include <windows.h> 	//biblioteca para função gráfica gotoxy//
#include <locale.h> 	//biblioteca para configuração de idiomas//
#include <string.h> 	//biblioteca para manipulação de strings//
#include <conio.h>  	//Biblioteca grafica

//DIRETIVAS DEFINE//

#define MAX 50			//definição do tamanho máximo das strings//
#define sleep 1000 		//definição do tempo de sleep/
#define LINHA_MINIMA 4
#define LINHA_MAXIMA 36
#define COLUNA_MINIMA 4
#define COLUNA_MAXIMA 76
#define ENTER 13
#define SETA_ESQUERDA 37
#define SETA_CIMA 38
#define SETA_DIREITA 39
#define SETA_BAIXO 40
#define ESC 27

//ESCOPO GLOBAL//

//structs//

//struct para definir destinos e local de partida//
struct destiny{
	char embark[MAX];
	char arrive[MAX];
};

//struct para configuração de disponibilidade//
struct set{
	int lug; 		//Variável que receberá o número de poltronas disponíveis para venda//
	int *array; 	//Array de poltronas em função da quantidade de poltronas disponibilizadas//
};

//struct para configuração de venda//
struct confirm{
	int quantity; 	 //Variável para armazenar a quantidade de poltronas para reserva//
	int *chair; 	 //Array em função da variável quantity//
	int option;		 //variavel condicional//
};

//struct para criação de conta//
struct create{
	char name[MAX]; 	//variável para cadastro de nome//
	int cpf; 			//código de pessoa física//
	int key; 			//senha do cadastro//
	int ver; 			//verificação//
	char email[MAX];	//email//
};

//Enumeração para o codigo das cores
enum DOS_COLORS {
        PRETO , AZUL , VERDE , CIANO , VERMELHO , MAGENTA , MARROM ,
        LIGHT_GRAY , DARK_GRAY , LIGHT_BLUE , LIGHT_GREEN , LIGHT_CYAN ,
        LIGHT_RED , LIGHT_MAGENTA , AMARELO , BRANCO 
} ;

//Variavel que contera as cores//     
DOS_COLORS CoresPrincipais [ 16 ] = { PRETO , AZUL , VERDE , CIANO , VERMELHO , MAGENTA , MARROM , LIGHT_GRAY , DARK_GRAY ,
                        LIGHT_BLUE , LIGHT_GREEN , LIGHT_CYAN , LIGHT_RED , LIGHT_MAGENTA ,AMARELO , BRANCO } ;
    
//Variaveis structs//
struct destiny d1; 		//declaração da variável da struct//
struct set s1; 			//variável do tipo set//
struct confirm c1;		//variável do tipo confirm para seleção de cadeiras//
struct create ac; 		//variável do tipo create para cadastro de contas//


//Funcões com retorno void//
void scan(struct destiny d1,struct create ac);		//protótipo da função de leitura dos locais de saida e chegada//
void check(struct destiny d1,int x , int y); 		// protótipo da função de check in//
void setup(struct set s1);							//protótipo da função de configuração de cadeiras disponíveis//
void chair(struct set s1); 							//Função de configuração administrativa (protótipo)//
void finish(void); 									//Função de exibição de mensagem de reserva//
void gotoxy(int x , int y); 						//função gráfica//
void ImprimeAviao (int x, int y); 					//parametro x e y = coordenada para o ponto superior esquerdo, onde a partir dai sera imprimido//
void moldura (int x1, int x2, int y1, int y2);		//funcao que imprime a moldura com as coordenadas dadas
void transicaoFim (int x1, int x2, int y1, int y2, int ax, int ay); 		//protótipo da transição//
void transicaoInicio (int x1, int x2, int y1, int y2, int ax, int ay); 		//protótipo de transição p2//
void push(void); 									//função para tela introdutória//
void title(void); 									//função título//
void account(struct create ac); 					//função de criação de conta//
void textcolor(DOS_COLORS iColor); 					//Função para mudar cor das letras
void backcolor (DOS_COLORS iColor);					//Função para mudar cor de fundo

//Funções com o retorno int//
int selec(struct confirm c1 ,struct set s1);		//Função destinada ao usuário (protótipo)//
int menu(struct confirm c1, int x , int y); 		//menu de confirmação//

//Função Principal//
int main (){ 
	//Definição do titulo da janela do DOS//
	SetConsoleTitle("Rivail Linhas Aereas");


	int x=7, y=5; //regulação do gotoxy//
	
	push(); //chamada da tela introdutória//
	
	getchar(); //função de exibição da transição//

	transicaoInicio(4, 76, 4, 36, 33, 33); //chamada da primeira função de transição//
	gotoxy(1,1);
	printf("12345678901234567890123456789012345678901234567890123456789012345678901234567890\n");
	printf("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n40\n41\n41\n42\n43\n43\n44\n45\n");

	gotoxy(30, 20); //Artifício gráfico para o título//
	
	title(); //chamada da função título//
	
	getchar(); //finalização da transição//
	
	transicaoFim(4, 76, 4, 36, 33, 33); //finalização da transição//
	
	fflush(stdin); //limpeza de buffer//
	
	moldura (4, 76, 4, 36);

	account(ac); //chamada da função de cadastro//
	
	moldura (4, 76, 4, 36);
	
	scan(d1,ac); //chamada da função de leitura//
	
	fflush(stdin); // limpeza de buffer (prevenção de bug)//
	
	
	moldura (4, 76, 4, 36);
	menu(c1,x,y); //chamada do menu de confirmação//
	
	while(menu(c1,x,y) == 1 || menu(c1,x,y)==0){ //laço de repetição para edição dos locais ou para Comando inválido//
		scan(d1,ac);//chamada da função de leitura//
	}
	
	transicaoInicio(4, 76, 4, 36, 33, 33); //transição da geração do boleto//
	
	moldura (4, 76, 4, 36);
	check(d1,x,y); //chamada do gerador de boleto de Check-in//
	
	transicaoFim(4, 76, 4, 36, 33, 33); //finalização da transição//
	
	moldura (4, 76, 4, 36);
	setup(s1); //função para leitura de cadeiras disponiveis/
	
	fflush(stdin); //prevenção de bugs//
	
	moldura (4, 76, 4, 36);
	chair(s1); //Chamada da função administrativa//
	
	fflush(stdin); //Limpeza de buffer//
	
	
	selec(c1,s1); //Chamada da função utilitária//
	
	while(selec(c1,s1)==1||selec(c1,s1)!= 1 && selec(c1,s1)!=0){
		selec(c1,s1);
	}
	
	
	return 0;	
}

void account(struct create ac){ //função de cadastro//
	int i;
	
	FILE *fptr;
	fptr=fopen("D://account.bin","wb+");
	
	
	gotoxy(25, 30);
	printf("De inicio, insira seu nome");
	gotoxy(25, 31);
	scanf("%50s" , ac.name);
	
	system("cls");
	moldura (4, 76, 4, 36);
	gotoxy(25, 30);
	printf("Insira seu email");
	gotoxy(25, 31);
	scanf("%50s" , ac.email);
	
	system("cls");
	moldura (4, 76, 4, 36);
	gotoxy(25, 30);
	printf("Por fim sua senha (apenas numeros)");
	gotoxy(25, 31);
	scanf("%d" , &ac.key);
	
	while(ac.key != ac.ver){
	
	gotoxy(25, 32);
	printf("Verifique sua senha");
	gotoxy(25, 31);
	scanf("%d" ,&ac.ver);
	
	printf("Robo VA-GA-BUN-DO!\a\a");
	
	Sleep(sleep);
	system("cls");
	moldura (4, 76, 4, 36);
	}

	printf("Conta verificada!(logo voce nao e um robo pssst...)\a\a");

	for(i=0 ; i <4;i++){
		fwrite(&ac,sizeof(struct create),1,fptr);
	}

		
	fclose(fptr);
	
	Sleep(sleep);
	system("cls");
}

void scan(struct destiny d1 , struct create ac){ //corpo da função de leitura//
	int i;

	printf("Bem vindo %50s" , ac.name);

	FILE *fptr; //uso de arquivos para gravação dos locais//
	fptr=fopen("D://destiny.bin","wb+");
	gotoxy(25, 15);
	
	printf("Insira o lugar de partida\n");
	gotoxy(25, 16);
	scanf("%50s" , d1.embark);
	gotoxy(25, 17);
	printf("Insira o destino\n");
	gotoxy(25, 18);
	scanf("%50s" , d1.arrive);
	
	for(i = 0;i <2;i++){
		fwrite(&d1,sizeof(struct destiny) , 1 , fptr); //gravação no arquivo//
	}
	
	
	fclose(fptr); //fechamento do arquivo//
	
}

int menu(struct confirm c1,int x,int y){ //Corpo da função de menu de confirmação//
	char t;
	int i;
	system("cls"); //Limpeza de tela//
	
//variável de controle para retorno de opção//
	 i = 1;
	do{
		moldura (4, 76, 4, 36);
		gotoxy(25, 15);
		printf("CONFIRMAÇÃO");
		gotoxy(25, 16);
		printf("  Editar local de partida e chegada");
		gotoxy(25, 17);
		printf("  Confirmar e gerar boleto de Check in");
		gotoxy(25, 15 + i);
		printf (">");
		gotoxy(25, 15 + i);
		t = getchar();
		if (t == 72) i = 1;
		if (t == 80) i = 2;
		
		system("ClS");
	}while (t != 13); 
	
 
	return i; //retorno da variável de controle//
	
	
	system("cls");

}

void gotoxy(int x , int y){ //corpo da função gráfica gotoxy//
	
	COORD graph;
	graph.X=x;
	graph.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),graph); //função da windows.h//
	
}

void textcolor( DOS_COLORS iColor ){
        HANDLE hl = GetStdHandle ( STD_OUTPUT_HANDLE ) ;
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo ;
        BOOL b = GetConsoleScreenBufferInfo ( hl , & bufferInfo ) ;
        bufferInfo. wAttributes &= 0x00F0 ;
        SetConsoleTextAttribute ( hl , bufferInfo. wAttributes |= iColor ) ;
}

void backcolor( DOS_COLORS iColor ){
        HANDLE hl = GetStdHandle ( STD_OUTPUT_HANDLE ) ;
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo ;
        BOOL b = GetConsoleScreenBufferInfo ( hl , & bufferInfo ) ;
        bufferInfo. wAttributes &= 0x000F ;
        SetConsoleTextAttribute ( hl , bufferInfo. wAttributes |= ( iColor << 4 ) ) ;
}

void check(struct destiny d1,int x , int y){ //Função para geração do boleto de Check-in//
	
	char check[3]; //variável para confirmação de Check-in//
	int i;
	
	system("cls");
	
	FILE *fptr; //criação do ponteiro para arquivo//
	fptr=fopen("D://destiny.bin" ,"rb+"); //abertura do arquivo//
	
	gotoxy(x,y);
	printf("Boleto de Check-in\n");
	
	printf("Locais\n");
	
	for( i=0; i <1;i++){
		fread(&d1,sizeof(struct destiny), 1 , fptr); //acesso ao arquivo//
		printf("%s\n" , d1.embark);
		printf("%s\n" , d1.arrive);
		fseek(fptr, sizeof(struct destiny), SEEK_END); //busca no arquivo//
	}
	
	
	while(strcmp(check,"Ok")!=0||strcmp(check,"ok")!=0){ //Função strcmp para conexão condicional//
		
		printf("Realizar Check-in?(press Ok)\n"); //confirmação final de Check-in//
		scanf("%2s" , check);
		
		 /*Caso o comando não seja referente aos disponíveis, retornará ao início*/
			printf("Comando Inválido\n");
			Sleep(sleep);
			system("cls");
		
	}
	 
		system("cls");
		printf("Check-in realizado\a\a\n\n");
	
	
	system("pause");
	system("cls");
	
}

//Admin Setup de cadeiras//

void setup(struct set s1){
	printf("Insira o numero de cadeiras para a venda\n");
	scanf("%d" , &s1.lug);
}


void chair(struct set s1){
	int i;
	
	printf("Insira o código das cadeiras\n");
	
	for(i = 0; i<s1.lug;i++){
		scanf("%d" , &s1.array[i]);
	}
	
	system("cls"); //limpeza de tela//
	
	//Tela do usuário//
	
	printf("Poltronas disponíveis\n");
	
	for(i = 0; i < s1.lug;i++){
		printf("%d " , s1.array[i]);
	}
	
}


//Usuario funcional//

int selec(struct confirm c1,struct set s1){
	int i;
	int option; //variável condicional//
	int rtn=0; // Variável para retorno de valor//
	
	
		
		//uso da variável quant para relacionar venda e disponibilidade//

	while(c1.quantity > s1.lug){
	
	printf("\nInsira a quantidade de poltronas a ser reservadas (quantidade < %d)\n" , s1.lug);
	scanf("%d" ,&c1.quantity);
	
	if(c1.quantity > s1.lug){
		printf("Quantidade indisponível\n");
		Sleep(sleep); //Parada de 1000 segundos na exibição da mensagem//
		system("cls"); //limpeza de tela//
	}
	
}

 //Fora do loop//


	printf("Selecione suas poltronas\n");
	
	for(i = 0 ; i < c1.quantity; i++){
		scanf("%d" , &c1.chair[i]);
	}
	
	for(i = 0 ; i < s1.lug; i++){
		if(c1.chair[i]==s1.array[i]){
			s1.array[i]=0;
		}
	}
	
	printf("Poltronas disponíveis\n");
	
	for(i = 0 ;i < s1.lug;i++){
		printf("%d " , s1.array[i]);
	}
	
	//opção de saída//
	
	printf("\nPress 1 para reservar novamente ou 0 para sair\n");
	scanf("%d" , &option);
	
	switch(option){
		
		case 1:
		rtn = option;
		break;
		
		case 0:
			rtn = option;
			break;
			
		default:
			printf("Opção inválida\n");
			Sleep(sleep);
			system("cls");
	}
	
	
	return rtn;
	
}

void finish(void){
	
	printf("Passagem reservada\n\a\a");
	system("pause");
}

void ImprimeAviao (int x, int y){ 
    x=21  ; 
    
	
	gotoxy(x,y);
	printf("                  /\\");
	y++;
	gotoxy(x,y);
	printf("                 |^^|");
	y++;
	gotoxy(x,y);
	printf("                 |{}|");
	y++;
	gotoxy(x,y);
	printf("  _______________/~~\\________________");
	y++;
	gotoxy(x,y);
	printf(" /               |  |                \\");
	y++;
	gotoxy(x,y);
	printf("`========--------.  .---------========'");
	y++;
	gotoxy(x,y);
	printf("                 ||||");
	y++;
	gotoxy(x,y);
	printf("                  ||");
	y++;
	gotoxy(x,y);
	printf("                  ||");
	y++;
	gotoxy(x,y);
	printf("                  ||");
	y++;
	gotoxy(x,y);
	printf("                  ||");
	y++;
	gotoxy(x,y);
	printf("              ,---||---,");
	y++;
	gotoxy(x,y);
	printf("              '---<>---'");
}

void moldura ( int x1, int x2, int y1, int y2){
	int i;
	
	//Linhas
	for(i = COLUNA_MINIMA+1;i < COLUNA_MAXIMA;i++){
		gotoxy(i,LINHA_MINIMA);
		printf("\xCD");
		gotoxy(i,LINHA_MAXIMA);
		printf("\xCD");
	}
	
	//Desenho das Colunas
	for(i = LINHA_MINIMA + 1;i <LINHA_MAXIMA;i++){
		gotoxy(COLUNA_MINIMA,i);
		printf("\xBA");
		gotoxy(COLUNA_MAXIMA,i);
		printf("\xBA");
	}
	
	//Desenhos dos cantos
	gotoxy (COLUNA_MINIMA,LINHA_MINIMA);
	printf ("\xC9");
	gotoxy (COLUNA_MINIMA,LINHA_MAXIMA);
	printf ("\xC8");
	gotoxy (COLUNA_MAXIMA,LINHA_MINIMA);
	printf ("\xBB");
	gotoxy (COLUNA_MAXIMA,LINHA_MAXIMA);
	printf ("\xbc");
	
}

void transicaoFim (int x1, int x2, int y1, int y2, int ax, int ay){
	int a = ay, c = y2;
	do{
		moldura(x1, x2, y1, c);
		ImprimeAviao(ax, a);
		a-=3;
		c-=3;
		Sleep(1);
		system("CLS");
	}while (c >= 0);
}

void transicaoInicio (int x1, int x2, int y1, int y2, int ax, int ay){
	int a = ay, c = y2;
	do{
		moldura(x1, x2, c, y2);
		ImprimeAviao(ax, a);
	
		a-=3;
		if (c - 3 >= y1){
			c-=3;
		}else
			if (c - 3 >= y1)
				c--;
			
		Sleep(100);
		system("CLS");
	}while (a > 0);
	c-=2;
	moldura(x1, x2, c, y2);
}

void push(void){ //tela introdutória//
	
	system("MODE 80, 41"); //medidas da tela para transição//

	system("color 9f"); //colorização gráfica//
	gotoxy(25, 20);
	printf("Pressione qualquer tecla...\n");
}

void title(void){ //função título//
	printf ("RIVAIL LINHAS AEREAS\a\a\a"); //titulo//
}
void titulo(int coluna,int linha){
	int i;
	i = linha;
	
	gotoxy(i,coluna);
	printf("######### \n");
	i++;
	gotoxy(i,coluna);
	printf("#      ##    #                              #   #\n");
	i++;
	gotoxy(i,coluna);
	printf("#     ##                                        #\n");
	i++;
	gotoxy(i,coluna);
	printf("#   ###      #   ##         ##     ###      #   #\n");
	i++;
	gotoxy(i,coluna);
	printf("# ###        #    ##       ##     ## ##     #   #\n");
	i++;
	gotoxy(i,coluna);
	printf("#   ##       #     ##     ##     ##   ##    #   #\n");
	i++;
	gotoxy(i,coluna);
	printf("#    ###     #      ### ###     ## ### ##   #   #\n");
	i++;
	gotoxy(i,coluna);
	printf("#      ###   #        ###       ##     ##   #   #\n");
	i++;
	gotoxy(i,coluna);
	printf("\n");
	i++;
	gotoxy(i,coluna);
	printf("###\n"); 
	i++;
	gotoxy(i,coluna);   
	printf("###         #\n"); 
	i++;
	gotoxy(i,coluna);
	printf("###\n");
	i++;
	gotoxy(i,coluna);
	printf("###         #   #####      ##   ###    ###      ###     ######\n"); 
	i++;
	gotoxy(i,coluna);
	printf("###         #   ##  ###    ##   ###    ###     ## ##    ##\n");   
	i++;
	gotoxy(i,coluna);
	printf("###         #   ##   ###   ##   ### ## ###    ##   ##     ####\n"); 
	i++;
	gotoxy(i,coluna);
	printf("#########   #   ##    ###  ##   ###    ###   ## ### ##       ##\n");
	i++;
	gotoxy(i,coluna);
	printf("#########   #   ##      ####    ###    ###   ##     ##   ####\n");
	i++;
	gotoxy(i,coluna);
	printf("\n");
	i++;
	gotoxy(i,coluna);                                                                                      
	printf("  #####\n");  
	i++;
	gotoxy(i,coluna);                                                                
	printf(" ##    ##\n");    
	i++;
	gotoxy(i,coluna);                                                                       
	printf("##      ##\n");  
	i++;
	gotoxy(i,coluna);                                                       
	printf("## #### ##   ######   ########   ######     ###     ######\n");      
	i++;
	gotoxy(i,coluna);                                                   
	printf("## #### ##   #        #    ##    #         ## ##    ##\n");      
	i++;
	gotoxy(i,coluna);                              
	printf("##      ##   ####     #####      ####     ##   ##     ####\n");  
	i++;
	gotoxy(i,coluna);                                              
	printf("##      ##   #        #   ##     #       ## ### ##       ##\n");  
	i++;
	gotoxy(i,coluna);                                                                                                                                       
	printf("##      ##   ######   #     ##   ######  ##     ##   ####\n");                                                       
}


