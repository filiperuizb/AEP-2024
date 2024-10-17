#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100


//Criação das funções ---> 
void tiraCursor();
void criptografia(char *senha);
void gotoxy(int x, int y);
void setColor(int color);
void desenharMoldura();
bool verificaSenha(const char *senha);
void inserirUsuario();
void verLista();
void removerUsuario();
void efeitoDigitacao(const char *texto);
void exibirInformacoes();
void exibirMenu();

// PRINCIPAL ------>
int main() {
    setlocale(LC_ALL, "Portuguese");
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
-> Criptografia | Foi usado ponteiro pra apontar direto pro primeiro caracter sem precisar declarar diferente do array */

void criptografia(char *senha) {
    while (*senha) {
        *senha += 7; 
        senha++;
    }
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
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Faz a moldura em volta do Menu */

void desenharMoldura() {
    int i;

    setColor(12); 

   // Aep-2024
    for (i = 16; i <= 64; i++) {
        gotoxy(i, 2); printf("_");
    }
    gotoxy(35, 2); printf("AEP - 2024");

    // Retas
    for (i = 16; i <= 64; i++) {
        gotoxy(i, 3); printf("_");
        gotoxy(i, 18); printf("_");
    }

    // Verticais
    for (i = 4; i < 18; i++) {
        gotoxy(15, i); printf("|");
        gotoxy(65, i); printf("|");
    }

	//Cantos
    gotoxy(15, 3); printf("|");
    gotoxy(65, 3); printf("|");
    gotoxy(15, 18); printf("|");
    gotoxy(65, 18); printf("|");

    setColor(15);
}
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Checa a senha */

bool verificaSenha(const char *senha) {
    bool v1,v2,v3,v4,v5;
	v1=v2=v3=v4=v5 = false;
    int tamanho = 0;

    tamanho = strlen(senha);

    // Verifica o tamanho
    if (tamanho >= 8 && tamanho <= 12) v1 = true;

    // Faz todas as verificações duma vez
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

    // Valida se tudo se estiver verdadeiro
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
    gotoxy(28, 5);
    setColor(9);
    printf("-> MENU INSERIR <-");

    setColor(15);
	gotoxy(18, 7);
    printf("Digite o usuário: ");
    scanf("%s", usuario);

   
    while (true) {
    	setColor(15);
        gotoxy(18, 8);
        printf("Digite a senha: ");
        scanf("%s", senha);

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
            
            //Printf vazio pra limpar as linhas que mostrava as informações da senha
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

	//Faz a criptografia do usuario e senha inserido
    criptografia(usuario);
    criptografia(senha);

    // Abre o arquivo txt
    arquivo = fopen("usuarios.txt", "a");
    if (arquivo == NULL) {
        gotoxy(18, 14);
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Insere o usuario e senha (CRIPTOGRAFADOS) no arquivo
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
    gotoxy(28, 5);
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

    gotoxy(18, 7);
    printf("Usuários criptografados:\n");
    int linha_y = 8; 
    while (fgets(linha, MAX, arquivo) != NULL) {
        gotoxy(18, linha_y++);
        printf("%s", linha);
    }

    fclose(arquivo);
    setColor(12);
    gotoxy(18, linha_y + 2);
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
    gotoxy(28, 5);
    printf("-> MENU REMOVER <-");

	setColor(15);
    gotoxy(18, 7);
    printf("Digite o usuário a ser removido: ");
    scanf("%s", usuario);
    criptografia(usuario);

    // Abrindo arquivo usuarios 
    arquivo = fopen("usuarios.txt", "r");
    temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        gotoxy(18, 9);
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    while (fgets(linha, MAX, arquivo) != NULL) {
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

//Efeito pra parecer que o computador está digitando
void efeitoDigitacao(const char *texto) {
    while (*texto) {
        printf("%c", *texto);
        Sleep(50); 
        texto++;
    }
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Menu de informações */

void exibirInformacoes() {
    system("cls");
    desenharMoldura();
    
  
    setColor(12);
    gotoxy(18, 5);
    efeitoDigitacao("Feito por:");
    Sleep(500);
    
    setColor(9);
    gotoxy(18, 6);
    efeitoDigitacao("-> Filipe Ruiz Boligon");
    Sleep(500);
    
    gotoxy(18, 7);
    efeitoDigitacao("-> Joao Miguel Bonfim");
    Sleep(500);
    
    gotoxy(18, 8);
    efeitoDigitacao("-> Gabriel Henrik Da Maia");
    Sleep(500);

	setColor(12);
    gotoxy(18, 10);
    efeitoDigitacao("------------ Bibliotecas usadas ------------ ");
    Sleep(500);
    
    setColor(9);
	gotoxy(18,11);
	efeitoDigitacao("stdio.h, stdlib.h, windows.h");
	    
    gotoxy(18, 12);
    efeitoDigitacao("conio.h, locale.h, stdbool.h, string.h.");
    Sleep(500);
    
    setColor(12);
    gotoxy(18,13);
    efeitoDigitacao("---------------------------------------------");
    
    setColor(7);
    gotoxy(18, 14);
    efeitoDigitacao("Obrigado por chegar até aqui e ate uma próxima");
    Sleep(500);
    

    setColor(14);
    gotoxy(18, 15);
    efeitoDigitacao("BOM DIA!!!");

    setColor(15);
    gotoxy(18, 17);
    printf("Para voltar, pressione qualquer tecla.");
    
    setColor(15); 
    getch(); 
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-> Menu */

void exibirMenu() {
    int opcao = 0;
    int tecla;
    bool sair = false;
   
	
	do {
        system("cls"); 
        desenharMoldura(); 
        setColor(9);
        gotoxy(30, 5);
        printf("-> MENU PRINCIPAL <- ");
        
        setColor(15);
        
        for(int i = 0; i < 5; i++) {
            gotoxy(22, 8 + i);
            if(opcao == i) {
                setColor(769);
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
        
        // Seta pra cima = 72 | Seta pra baixo = 80 | Enter = 13
        tecla = getch();
        if (tecla == 224) {
            tecla = getch();
            if (tecla == 72) { 
                opcao--;
                if (opcao < 0) opcao = 4;
            } else if (tecla == 80) { 
                opcao++;
                if (opcao > 4) opcao = 0;
            }
        } else if (tecla == 13) { 
            switch (opcao) {
                case 0:
                    inserirUsuario();
                    break;
                case 1:
                    removerUsuario();
                    break;
                case 2:
                    verLista();
                    break;
                case 3:
                    exibirInformacoes();
                    break;
                case 4:
                    sair = true;
                    break;;
            }
        }
    } while (!sair);
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
fim; */
