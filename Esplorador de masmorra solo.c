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

// Função de animação de carregamento com spinner
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
    int jozzehAcariciado = 0;  // controle se o Joz'zeh já foi acariciado

    printf(GREEN "\n==============================\n");
    printf(" Seja bem-vindo ao...\n");
    printf("   Solo Adventure Dungeon!\n");
    printf("==============================\n\n" RESET);

    printf(YELLOW "Informe seu nickname: " RESET);
    scanf("%29s", nome);

    // Animação antes de começar a aventura
    animacaoCarregandoSpinner(3);

    printf(GREEN "\nOlá, " YELLOW "%s" GREEN "! Sua aventura começa agora.\n" RESET, nome);
    sleep(3);

    while (jogando) {
        // Limpa a tela
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Descrição do local
        if (localAtual == 1) {
            printf(CYAN "\n?? Você está na Entrada da Caverna.\n" RESET);
            printf("Há um caminho escuro à frente...\n");
            sleep(2);
        } else if (localAtual == 2) {
            printf(MAGENTA "\n?? Você está no Caminho Escuro.\n" RESET);
            printf("Você ouve gotas de água e passos... ou seriam ecos?\n");
            printf("Uma luz fraca surge adiante.\n");
            sleep(2);
        } else if (localAtual == 3) {
            printf(YELLOW "\n?? Você entrou na Câmara do Tesouro!\n" RESET);
            if (!tesouroEncontrado) {
                printf("Riquezas infinitas brilham ao seu redor...\n");
                printf("E ali está Joz'zeh, o Devorador, dormindo profundamente.\n");
                sleep(5);
            } else {
                printf(GREEN "A câmara está vazia, você já pegou o tesouro.\n" RESET);
            }
            sleep(5);
        }

        printf(YELLOW "\nComandos disponíveis: " CYAN "avancar" YELLOW ", " CYAN "voltar" YELLOW ", " CYAN "acariciar" YELLOW ", " CYAN "sair\n" RESET);
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
                    printf(RED "\n??  Você se depara com Joz'zeh, o Devorador!!!\n" RESET);
                    sleep(1);
                    printf(RED "Ele rosna... e então...\n" RESET);
                    sleep(1);
                    printf(RED "Ele está... dormindo? ??\n" RESET);
                    sleep(2);
                    printf(GREEN "Você passa sorrateiramente...\n" RESET);
                    sleep(1);
                    printf(BLUE "\n?? Você adentra a sala do tesouro...\n" RESET);
                    sleep(1);
                    printf(BLUE "Parabéns, " YELLOW "%s" BLUE "! Você encontrou o pacote de whiskas dourado!\n" RESET, nome);
                    printf(GREEN "?? Você venceu o jogo!\n" RESET);
                    tesouroEncontrado = 1;
                    
                    sleep(5);
                }
            } else {
                printf(RED "?? Você já está na última área.\n" RESET);
            }
        } else if (strcmp(comando, "voltar") == 0) {
            if (localAtual == 3) {
                localAtual = 2;
            } else if (localAtual == 2) {
                localAtual = 1;
            } else {
                printf(RED "?? Você já está na entrada.\n" RESET);
            }
        } else if (strcmp(comando, "acariciar") == 0) {
            if (localAtual == 3) {
                if (!jozzehAcariciado) {
                    printf(GREEN "\nVocê cuidadosamente acaricia Joz'zeh...\n" RESET);
                    sleep(1);
                    printf(GREEN "Joz'zeh ronrona baixinho, parecendo gostar da atenção.\n" RESET);
                    jozzehAcariciado = 1;
                } else {
                    printf(YELLOW "\nJoz'zeh já está satisfeito com suas carícias.\n" RESET);
                }
            } else if (localAtual == 2) {
                printf(YELLOW "Você tenta acariciar algo, mas só sente a brisa... \n" RESET);
            } else {
                printf(RED "Não há ninguém para acariciar aqui.\n" RESET);
            }
        } else if (strcmp(comando, "sair") == 0) {
            printf(MAGENTA "Saindo do jogo... Até a próxima aventura!\n" RESET);
            jogando = 0;
        } else {
            printf(RED "Comando inválido. Tente novamente.\n" RESET);
        }

        sleep(1);
    }

    return 0;
}

