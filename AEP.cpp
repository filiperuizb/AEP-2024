#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX 100



void tiraCursor();
void inverterSenha(char senha[20]);
void converteVogal(char senha[20]);
void criptografia(char senha[20]);
void reverteVogal(char senha[20]);
void descriptografia(char senha[20]);
void gotoxy(int x, int y);
void setColor(int color);
int efeitoRainbow(int cor);
void desenharMoldura();
bool verificaSenha(char senha[20]);
void inserirUsuario();
void verLista();
void removerUsuario();
void efeitoDigitacao(const char texto[100]); 
void efeitoDigitacaoSEMCOR(const char texto[100]);
void exibirInformacoes();
void exibirMenu();

// PRINCIPAL ------>
int main() {
    setlocale(LC_CTYPE, "Portuguese");
    srand(time(NULL));
		tiraCursor();
    exibirMenu();
    return 0;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Função pra tirar o cursor que aparece lá em baixo pra digitar no menu principal */

void tiraCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo); 
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(hConsole, &cursorInfo); 
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Criptografia */
void inverterSenha(char senha[20]) {
  int comeco = 0;
  int tamanho = strlen(senha) - 1;
	
  while(comeco < tamanho) {
    char temp = senha[comeco];
    senha[comeco] = senha[tamanho];
    senha[tamanho] = temp;
    comeco++;
    tamanho--;
  }
}

void converteVogal(char senha[20]) {
	inverterSenha(senha);
	srand(time(0));  
	int tamanho = strlen(senha);
	int i;
	for(i = 0; i < tamanho; i++) {
		if(senha[i] == 'a' || senha[i] == 'e' || senha[i] == 'i' || senha[i] == 'o' || senha[i] == 'u' ||
		   senha[i] == 'A' || senha[i] == 'E' || senha[i] == 'I' || senha[i] == 'O' || senha[i] == 'U') {
			int incrementoVogal = 2;
			senha[i] += incrementoVogal;	
			incrementoVogal++;
		}
	}
}

void criptografia(char senha[20]) {
    converteVogal(senha);
    int i = 0;
    while (senha[i]) {
        int incremento = 5;
        senha[i] += incremento; 
        i++;
        incremento++;
    }
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Descriptografia*/

void reverteVogal(char senha[20]) {
	int tamanho = strlen(senha);
	int i;
	int decrementoVogal = 2;
	
	for(i = 0; i < tamanho; i++) {
		if(senha[i] == 'c' || senha[i] == 'g' || senha[i] == 'k' || senha[i] == 'q' || senha[i] == 'w' ||
		   senha[i] == 'C' || senha[i] == 'G' || senha[i] == 'K' || senha[i] == 'Q' || senha[i] == 'W') {
			senha[i] -= decrementoVogal;
			decrementoVogal++;
		}
	}
	inverterSenha(senha);
}

void descriptografia(char senha[20]) {
    int i = 0;
    int decremento = 5;

    while (senha[i]) {
        senha[i] -= decremento;
        i++;
        decremento++;
    }
  
    reverteVogal(senha);
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Coordenadas da tela*/

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Mudar a cor dos textos */

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    
    /* 
	CORES:
	0	Preto
	1	Azul
	2	Verde
	3	Azul claro
	4	Vermelho
	5	Roxo
	6	Amarelo
	7	Branco claro
	8	Cinza
	9	Azul claro  
	10	Verde claro
	11	Azul piscina
	12	Vermelho claro
	13	Rosa
	14	Amarelo claro
	15	Branco
	*/
}
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Efeito rainbow */

int efeitoRainbow(int cor) {
	cor = (cor % 15) + 1;
	return cor;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Faz a moldura em volta do Menu */

void desenharMoldura() {
	int infinito = 0;
	int cor = 1;
	
		
		int i;
		setColor(9);  
	
	    // AEP-2024
	    for (i = 16; i <= 64; i++) {
	        gotoxy(i, 2); 
	        printf("_");
	    }
	    gotoxy(35, 2); 
	    printf("AEP - 2024");
	
	    // Retas
	    for (i = 16; i <= 64; i++) {
	        gotoxy(i, 3); 
	        printf("_");
	        gotoxy(i, 18); 
	        printf("_");
	    }
	
	    // Lateral
	    for (i = 4; i < 18; i++) {
	        gotoxy(15, i); 
	        printf("|");
	        gotoxy(65, i); 
	        printf("|");
	    }
	
	    // Cantos
	    gotoxy(15, 3); 
	    printf("|"); 
	    gotoxy(65, 3); 
	    printf("|");  
	    gotoxy(15, 18); 
	    printf("|"); 
	    gotoxy(65, 18); 
	    printf("|");  
	
	    setColor(15);  
			
	
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Checa a senha */

bool verificaSenha(char senha[20]) {
    bool v1,v2,v3,v4,v5;
	v1=v2=v3=v4=v5 = false;
    int tamanho = 0;

    tamanho = strlen(senha);

    
    if (tamanho >= 8 && tamanho <= 12) v1 = true;

    
    for (int i = 0; i < tamanho; i++) {
        if (senha[i] >= 'a' && senha[i] <= 'z') v2 = true;
        if (senha[i] >= 'A' && senha[i] <= 'Z') v3 = true;
        if (senha[i] >= '0' && senha[i] <= '9') v5 = true;
        if ((senha[i] >= 32 && senha[i] <= 47) || 
            (senha[i] >= 58 && senha[i] <= 64) ||
            (senha[i] >= 91 && senha[i] <= 96) || 
            (senha[i] >= 123 && senha[i] <= 126)) {
            v4 = true; 
        }
    }

    
    return v1 && v2 && v3 && v4 && v5;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Menu - Inserir usuário */

void inserirUsuario() {
    char usuario[MAX], senha[MAX];
    FILE *arquivo;

    system("cls");
    desenharMoldura(); 
    gotoxy(30, 5);
    setColor(9);
    printf("-> MENU INSERIR <-");

    setColor(15);
	gotoxy(18, 7);
    printf("Digite o usuário: ");
    gets(usuario);

   
    while (true) {
    	setColor(15);
        gotoxy(18, 8);
        printf("Digite a senha: ");
        gets(senha);

        if (verificaSenha(senha)) {
            break; 
        } else {
            gotoxy(18, 10);
            printf("Senha inválida!\n");
            gotoxy(18, 11);
            printf("-> 8 a 12 caracteres\n");
            gotoxy(18, 12);
            printf("-> Deve ter maiúscula, minúscula\n");
            gotoxy(18, 13);
            printf("-> Deve ter número\n");
            gotoxy(18, 14);
            printf("-> Deve ter caractere especial\n");
            gotoxy(18, 15);
            printf("-> Para tentar novamente, aperte Enter!");

            getch(); 
                        
            // Limpar informações
            gotoxy(18,8);
            printf("                                              ");
            gotoxy(18, 10);
            printf("                                               "); 
            gotoxy(18, 11);
            printf("                                               ");
            gotoxy(18, 12);
            printf("                                               ");
            gotoxy(18, 13);
            printf("                                               ");
            gotoxy(18, 14);
            printf("                                               ");
            gotoxy(18, 15);
            printf("                                               ");
        }
    }


    criptografia(usuario);
    criptografia(senha);


    arquivo = fopen("usuarios.txt", "a");
    if (arquivo == NULL) {
        gotoxy(18, 14);
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "Usuário: %s | Senha: %s\n", usuario, senha);
    fclose(arquivo);
    setColor(10);
    gotoxy(18, 14);
    printf("Usuário inserido!\n");

    gotoxy(18, 16);
    printf("Para voltar, pressione qualquer tecla");
    getch(); 
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Menu - lista de usuários criptografados */

void verLista() {
    char linha[MAX];
    FILE *arquivo;

    system("cls");
    desenharMoldura(); 
    setColor(9);
    gotoxy(30, 5);
    printf("-> LISTA DE USUÁRIOS <-");
    
    
	setColor(15);
    arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
    	setColor(12);
        gotoxy(18, 7);
        printf("Nenhum usuário encontrado!\n");
        getch();
        return;
    }

    gotoxy(29, 7);
    printf("Usuários criptografados:\n");
    setColor(12);
	gotoxy(27,8);
    printf("____________________________");
    setColor(15);
    int linhaY = 9; 
    while (fgets(linha, MAX, arquivo) != NULL) {
        gotoxy(24, linhaY++);
        printf("%s", linha);
    }

    fclose(arquivo);
    setColor(12);
    gotoxy(22, 19);
    printf("Para voltar, pressione qualquer tecla");
    getch(); 
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Menu - Remover Usuario */

void removerUsuario() {
    char usuario[MAX], linha[MAX];
    FILE *arquivo, *temp;
    int encontrado = 0;

    system("cls");
    desenharMoldura();
    setColor(9);
    gotoxy(30, 5);
    printf("-> MENU REMOVER <-");

    setColor(15);
    gotoxy(18, 7);
    printf("Digite o usuário a ser removido: ");
    scanf("%s", usuario);
 		criptografia(usuario);
 		
    arquivo = fopen("usuarios.txt", "r");
    temp = fopen("temp.txt", "w");

    if (arquivo == NULL || temp == NULL) {
        gotoxy(18, 9);
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    while (fgets(linha, MAX, arquivo) != NULL) {
        // Comparar com o usuário, sem criptografá-lo novamente
        if (strstr(linha, usuario) == NULL) {
            fputs(linha, temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");

    gotoxy(18, 9);
    if (encontrado) {
        setColor(10);
        printf("Usuário removido!\n");
    } else {
        setColor(12);
        printf("Usuário não encontrado!\n");
    }

    gotoxy(18, 11);
    printf("Para voltar, pressione qualquer tecla");
    getch();
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 
 -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 -> Efeito pra parecer que o computador está digitando */
void efeitoDigitacao(const char texto[100]) {
    int i = 0;
    int cor = 1;
    while (texto[i] != '\0') {
        setColor(cor);
		printf("%c", texto[i]);
        Sleep(30); 
        i++;
        cor = efeitoRainbow(cor);
        
    }
}
void efeitoDigitacaoSEMCOR(const char texto[100]) {
    int i = 0;
    while (texto[i] != '\0') {
        
		printf("%c", texto[i]);
        Sleep(30); 
        i++;
        
        
    }
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Menu de informações */

void exibirInformacoes() {
    system("cls");
    desenharMoldura();
    int cor = 12;
    int tecla; 
    int teclaEnter = 13;
    int setaBaixo = 80;
    int setaCima = 72;
  
    setColor(9);
    gotoxy(18, 5);
    efeitoDigitacaoSEMCOR("Feito por:");
    Sleep(500);
    
    
	gotoxy(20, 6);
	setColor(9);
	efeitoDigitacao("-> Filipe Ruiz Boligon");
	Sleep(500);
	gotoxy(20, 7);
	efeitoDigitacao("-> Joao Miguel Bonfim");
	Sleep(500);
	gotoxy(20, 8);
	efeitoDigitacao("-> Gabriel Henrik Da Maia");	
	Sleep(500);

	setColor(9);
    gotoxy(18, 10);
    efeitoDigitacaoSEMCOR("------------ Bibliotecas usadas ------------ ");
    Sleep(500);
    
    setColor(9);
	gotoxy(18,11);
	efeitoDigitacao("stdio.h, stdlib.h, windows.h");
	    
    gotoxy(18, 12);
    efeitoDigitacao("conio.h, time.h, locale.h, stdbool.h, string.h.");
    Sleep(500);
    
    setColor(9);
    gotoxy(18,13);
    efeitoDigitacaoSEMCOR("---------------------------------------------");
    
	gotoxy(18, 14);
	setColor(14);
	efeitoDigitacaoSEMCOR("Obrigado por chegar até aqui e ate uma próxima");
		
	for(;;) {
	    setColor(cor);
	    gotoxy(18, 15);
	    efeitoDigitacaoSEMCOR("BOM DIA!!!");
	
		cor = efeitoRainbow(cor);
	    if(cor == 7 || cor == 15) {
	    	cor = efeitoRainbow(cor);
		}	
	    setColor(15);
	    gotoxy(18, 17);
	    printf("Para voltar, pressione qualquer tecla.");
	    
	    if(kbhit()) {
	    	if (tecla = getch()) {
	    		if(tecla == teclaEnter) {
	    			break;
				}
			}
		}
		    
	}
	setColor(15);  	
}
	
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Menu */

void exibirMenu() {
    int opcao = 0;
    int tecla;
    bool sair = false;
    int cor = 1; 
    int teclaEnter = 13;
    int setaBaixo = 80;
    int setaCima = 72;

    system("cls"); 
    

    while (!sair) {
        
        desenharMoldura(); 
        setColor(efeitoRainbow(cor));
        gotoxy(30, 5);
        printf("-> MENU PRINCIPAL <- ");
        
        setColor(9);
        gotoxy(25,6);
        printf("______________________________");
        
        
        

        cor = efeitoRainbow(cor); 
        Sleep(80); 

        setColor(15); 
        for(int i = 0; i < 5; i++) {
            gotoxy(25, 8 + i); 
            if(opcao == i) {
                setColor(efeitoRainbow(cor));
                printf(">");
            } else {
                setColor(15);
                printf(" ");
            }
            switch (i) {
                case 0:
                    printf(" Inserir");
                    break;
                case 1:
                    printf(" Remover");
                    break;
                case 2:
                    printf(" Ver lista");
                    break;
                case 3:
                    printf(" Informações");
                    break;
                case 4:
                    printf(" Sair");
                    break;
            }
        }
		
		setColor(9);
		gotoxy(25,14);
        printf("______________________________");
        
        if (kbhit()) { 
            tecla = getch();
            if (tecla == 224) {
                tecla = getch();
                if (tecla == setaCima) { 
                    opcao--;
                    if (opcao < 0) opcao = 4;
                } else if (tecla == setaBaixo) { 
                    opcao++;
                    if (opcao > 4) opcao = 0;
                }
            } else if (tecla == teclaEnter) { 
                switch (opcao) {
                    case 0:
                        inserirUsuario();
                        system("cls");
                        desenharMoldura();
                        break;
                    case 1:
                        removerUsuario();
                        system("cls");
                        desenharMoldura();
                        break;
                    case 2:
                        verLista();
                        system("cls");
                        desenharMoldura();
                        break;
                    case 3:
                        exibirInformacoes();
                        system("cls");
                        desenharMoldura();
                        break;
                    case 4:
                        sair = true;
                        break;
                }
            }
        }
    }
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
fim; */
