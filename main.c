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

#define max_vida 150
typedef enum { FOGO, AGUA, PLANTA } Tipo;

// Status dos pokemons
typedef struct {
    char nome[50];
    int vida;
    int ataque;
    int ataque_especial; 
    int quant_ataque_especial; 
    int cura;
    int quant_cura;
    Tipo tipo;  
} Pokemon;

// Pokemons disponiveis
Pokemon pokemons[3] = {
    {"Chimchar", max_vida, 20, 35, 3, 10, 3, FOGO},
    {"Turtwig", max_vida, 15, 30, 3, 10, 3, PLANTA},
    {"Piplup", max_vida, 18, 32, 3, 10, 3, AGUA}
};

// Estrutura para armazenar o jogador e seu Pokemon escolhido
typedef struct {
    char nome[50];
    char jogador_pokemon[20];
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
                strcpy(jogador->jogador_pokemon, "Chimchar");
                break;
            case 2:
                strcpy(jogador->jogador_pokemon, "Turtwig");
                break;
            case 3:
                strcpy(jogador->jogador_pokemon, "Piplup");
                break;
            default:
                printf(Vermelho "Escolha invalida! Por favor, escolha novamente.\n" Resetar);
                escolha = 0;  
        }
    } while (escolha == 0);

    printf(Roxo "\nParabens, %s! Voce escolheu %s como seu primeiro Pokemon, excelente escolha!\n" Resetar, jogador->nome, jogador->jogador_pokemon);
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

// Correlaciona os dados do tipo Jogador com o tipo Pokemon
Pokemon link_jogador_pokemon(Jogador *jogador){
    Pokemon jogador_pokemon;

    for(int i = 0; i < sizeof(pokemons) / sizeof(pokemons[0]); i++){
        if (strcmp(jogador->jogador_pokemon, pokemons[i].nome) == 0){
        jogador_pokemon = pokemons[i];
        return jogador_pokemon;
        }
    }

    Pokemon vazio = {"", 0, 0, 0, 0, 0, 0, FOGO};
    return vazio;
}

// Funçao para escolher o pokemon do oponente
Pokemon escolher_oponente_pokemon(Pokemon jogador_pokemon){
    Pokemon oponente_pokemon;
    do{
        oponente_pokemon = pokemons[rand() % 3];
    }while(strcmp(oponente_pokemon.nome, jogador_pokemon.nome) == 0);
    return oponente_pokemon;
}

// Funcao principal
int main() {
    srand(time(NULL));
    Jogador jogador;
    Pokemon jogador_pokemon;

    boasVindas(&jogador);        
    escolherPokemon(&jogador);   
    salvarJogador(&jogador);  

    jogador_pokemon = link_jogador_pokemon(&jogador);
    Pokemon oponente_pokemon = escolher_oponente_pokemon(jogador_pokemon);

    // Teste das funcoes
    printf("\nPokemon do jogador: %s", jogador_pokemon.nome);
    printf("\nPokemon do oponente: %s", oponente_pokemon.nome);   

    return 0;
}