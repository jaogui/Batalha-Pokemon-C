#include <stdio.h>
#include <string.h>
#include <unistd.h> // Para usar sleep()

// Definicoes de cores para o terminal (USE SEMPRE O RESETAR DEPOIS)
#define Resetar "\033[0m"
#define Vermelho "\033[31m"
#define Verde "\033[32m"
#define Azul "\033[34m"
#define Roxo "\033[35m"
#define Negrito "\033[1m"

// Estrutura para armazenar o jogador e seu Pokemon escolhido
typedef struct {
    char nome[50];
    char pokemonEscolhido[20];
} Jogador;

// Funcao para mostrar uma linha de carregamento
void linhaDeCarregamento() {
    printf(Verde "Carregando" Resetar);
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}

// Funcao para mostrar o menu de boas-vindas e perguntar o nome
void boasVindas(Jogador *jogador) {
    printf(Negrito Azul "Bem-vindo ao mundo de Pokemon!" Resetar "\n");
    printf("Vamos comecar. Primeiro, voce precisa falar com uma pessoa, so um momento.\n");
    linhaDeCarregamento();
    printf(Roxo "...\n...\n...\n" Resetar);
    printf(Roxo "Ola, sou o professor Rowan, parece que voce acabou de chegar em Sinnoh." Resetar "\n");
    printf(Roxo "Para comecar, por favor, me diga o seu nome: "Resetar);
    fgets(jogador->nome, 50, stdin);
    jogador->nome[strcspn(jogador->nome, "\n")] = 0; 
    printf(Verde "\nOtimo, %s! Prazer em conhece-lo!\n" Resetar, jogador->nome);
}

// Funcao para escolher o Pokemon inicial
void escolherPokemon(Jogador *jogador) {
    int escolha = 0;

    do {
        printf("\n%s, agora escolha seu Pokemon inicial. Lembre-se, ele sera seu companheiro para uma longa jornada cheia de aventuras!\n", jogador->nome);
        printf(Negrito Vermelho "1. Chimchar\n" Resetar);
        printf(Negrito Verde "2. Turtwig\n" Resetar);
        printf(Negrito Azul "3. Piplup\n" Resetar);
        printf(Negrito "Escolha um companheiro (1-3): " Resetar);
        scanf("%d", &escolha);
        getchar();  

        switch (escolha) {
            case 1:
                strcpy(jogador->pokemonEscolhido, "Chimchar");
                break;
            case 2:
                strcpy(jogador->pokemonEscolhido, "Turtwig");
                break;
            case 3:
                strcpy(jogador->pokemonEscolhido, "Piplup");
                break;
            default:
                printf(Vermelho "Escolha invalida! Por favor, escolha novamente.\n" Resetar);
                escolha = 0;  
        }
    } while (escolha == 0);

    printf(Roxo "\nParabens, %s! Voce escolheu %s como seu primeiro Pokemon, excelente escolha!\n" Resetar, jogador->nome, jogador->pokemonEscolhido);
}

// Funcao para salvar os dados do jogador em um arquivo binario
void salvarJogador(Jogador *jogador) {
    FILE *arquivo = fopen("jogador.bin", "wb"); 
    if (arquivo == NULL) {
        printf(Vermelho "Erro ao abrir o arquivo para salvar os dados.\n" Resetar);
        return;
    }

    fwrite(jogador, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);

    printf(Verde "\nDados salvos com sucesso!\n" Resetar);
}

// Funcao principal
int main() {
    Jogador jogador;

    boasVindas(&jogador);        
    escolherPokemon(&jogador);   
    salvarJogador(&jogador);     

    return 0;
}