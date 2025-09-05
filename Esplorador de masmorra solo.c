#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>

// Cores ANSI
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[0;34m"
#define CYAN    "\033[0;36m"
#define MAGENTA "\033[0;35m"
#define RESET   "\033[0m"

// Fun��o de anima��o de carregamento com spinner
void animacaoCarregandoSpinner(int duracaoSegundos) {
    char frames[] = {'|', '/', '-', '\\'};
    printf("\n");

    for (int i = 0; i < duracaoSegundos * 4; i++) {
        printf(YELLOW "\rCarregando %c" RESET, frames[i % 4]);
        fflush(stdout);
        usleep(250000); // 0.25 segundos
    }

    printf(GREEN "\rCarregamento completo!   \n" RESET);
    sleep(1);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    char nome[30];
    int localAtual = 1;
    char comando[20];
    int jogando = 1;
    int tesouroEncontrado = 0;
    int jozzehAcariciado = 0;  // controle se o Joz'zeh j� foi acariciado

    printf(GREEN "\n==============================\n");
    printf(" Seja bem-vindo ao...\n");
    printf("   Solo Adventure Dungeon!\n");
    printf("==============================\n\n" RESET);

    printf(YELLOW "Informe seu nickname: " RESET);
    scanf("%29s", nome);

    // Anima��o antes de come�ar a aventura
    animacaoCarregandoSpinner(3);

    printf(GREEN "\nOl�, " YELLOW "%s" GREEN "! Sua aventura come�a agora.\n" RESET, nome);
    sleep(3);

    while (jogando) {
        // Limpa a tela
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Descri��o do local
        if (localAtual == 1) {
            printf(CYAN "\n?? Voc� est� na Entrada da Caverna.\n" RESET);
            printf("H� um caminho escuro � frente...\n");
            sleep(2);
        } else if (localAtual == 2) {
            printf(MAGENTA "\n?? Voc� est� no Caminho Escuro.\n" RESET);
            printf("Voc� ouve gotas de �gua e passos... ou seriam ecos?\n");
            printf("Uma luz fraca surge adiante.\n");
            sleep(2);
        } else if (localAtual == 3) {
            printf(YELLOW "\n?? Voc� entrou na C�mara do Tesouro!\n" RESET);
            if (!tesouroEncontrado) {
                printf("Riquezas infinitas brilham ao seu redor...\n");
                printf("E ali est� Joz'zeh, o Devorador, dormindo profundamente.\n");
                sleep(5)
            } else {
                printf(GREEN "A c�mara est� vazia, voc� j� pegou o tesouro.\n" RESET);
            }
            sleep(5);
        }

        printf(YELLOW "\nComandos dispon�veis: " CYAN "avancar" YELLOW ", " CYAN "voltar" YELLOW ", " CYAN "acariciar" YELLOW ", " CYAN "sair\n" RESET);
        printf("Digite um comando: ");
        scanf("%19s", comando);

        if (strcmp(comando, "avancar") == 0) {
            if (localAtual == 1) {
                localAtual = 2;
            } else if (localAtual == 2) {
                // Limpa a tela antes de entrar na sala do tesouro
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif

                localAtual = 3;
                if (!tesouroEncontrado) {
                    printf(RED "\n??  Voc� se depara com Joz'zeh, o Devorador!!!\n" RESET);
                    sleep(1);
                    printf(RED "Ele rosna... e ent�o...\n" RESET);
                    sleep(1);
                    printf(RED "Ele est�... dormindo? ??\n" RESET);
                    sleep(2);
                    printf(GREEN "Voc� passa sorrateiramente...\n" RESET);
                    sleep(1);
                    printf(BLUE "\n?? Voc� adentra a sala do tesouro...\n" RESET);
                    sleep(1);
                    printf(BLUE "Parab�ns, " YELLOW "%s" BLUE "! Voc� encontrou o pacote de whiskas dourado!\n" RESET, nome);
                    printf(GREEN "?? Voc� venceu o jogo!\n" RESET);
                    tesouroEncontrado = 1;
                    
                    sleep(5);
                }
            } else {
                printf(RED "?? Voc� j� est� na �ltima �rea.\n" RESET);
            }
        } else if (strcmp(comando, "voltar") == 0) {
            if (localAtual == 3) {
                localAtual = 2;
            } else if (localAtual == 2) {
                localAtual = 1;
            } else {
                printf(RED "?? Voc� j� est� na entrada.\n" RESET);
            }
        } else if (strcmp(comando, "acariciar") == 0) {
            if (localAtual == 3) {
                if (!jozzehAcariciado) {
                    printf(GREEN "\nVoc� cuidadosamente acaricia Joz'zeh...\n" RESET);
                    sleep(1);
                    printf(GREEN "Joz'zeh ronrona baixinho, parecendo gostar da aten��o.\n" RESET);
                    jozzehAcariciado = 1;
                } else {
                    printf(YELLOW "\nJoz'zeh j� est� satisfeito com suas car�cias.\n" RESET);
                }
            } else if (localAtual == 2) {
                printf(YELLOW "Voc� tenta acariciar algo, mas s� sente a brisa... \n" RESET);
            } else {
                printf(RED "N�o h� ningu�m para acariciar aqui.\n" RESET);
            }
        } else if (strcmp(comando, "sair") == 0) {
            printf(MAGENTA "Saindo do jogo... At� a pr�xima aventura!\n" RESET);
            jogando = 0;
        } else {
            printf(RED "Comando inv�lido. Tente novamente.\n" RESET);
        }

        sleep(1);
    }

    return 0;
}

