#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define max_vida 150
typedef enum {FOGO, AGUA, PLANTA} Tipo;

// Definicões de cores para o terminal (USE SEMPRE O RESETAR DEPOIS )
#define Resetar "\033[0m"
#define Vermelho "\033[31m"
#define Verde "\033[32m"
#define Azul "\033[34m"
#define Amarelo "\033[33m"
#define Roxo "\033[35m"
#define Ciano "\033[36m"
#define Cinza "\033[30m"
#define Negrito "\033[1m"

// Struct com todos os dados do jogador e de seu pokemon
typedef struct{
    char nome[50];
    int vida;
    int ataque;
    int ataque_especial;
    int qtd_especial;
    int cura;
    int qtd_cura;
    Tipo tipo;
}Pokemon;

// Pokemons disponiveis
Pokemon pokemons[3] = {
    {"Chimchar", max_vida, 20, 28, 3, 25, 4, FOGO},
    {"Turtwig", max_vida, 15, 35, 3, 25, 4, PLANTA},
    {"Piplup", max_vida, 18, 32, 3, 25, 4, AGUA}
};

// Estrutura para armazenar o jogador e seu pokemon escolhido
typedef struct{
    char nome[50];
    char jogador_pokemon[50];
}Jogador;

void linhaDeCarregamento(){
    printf(Ciano "Carregando" Resetar);
    for (int i = 0; i < 3; i++) {
        printf(Ciano "." Resetar);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}

const char *cor_pokemon(Pokemon pokemon){
    switch (pokemon.tipo){
    case FOGO:
        return Negrito Vermelho;
    case PLANTA:
        return Negrito Verde;
    case AGUA:
        return Negrito Azul;
    default:
        return Resetar;
    }
}

// Verifica se o jogador ja jogou antes
int verificarJogadorExistente(Jogador *jogador){
    Jogador jogadorExistente;
    FILE *arquivo = fopen("jogador.bin", "rb");
    if(arquivo == NULL){
        return 0;
    }

    while(fread(&jogadorExistente, sizeof(Jogador), 1, arquivo)){
        if(strcmp(jogadorExistente.nome, jogador->nome) == 0){
            strcpy(jogador->jogador_pokemon, jogadorExistente.jogador_pokemon);
            fclose(arquivo);

            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

// Função para mostrar o menu de boas vindas e perguntar o nome
void boasVindas(Jogador *jogador){
    printf(Negrito Azul "Bem-vindo ao mundo de Pokemon!" Resetar "\n");
    printf(Negrito Azul "Vamos comecar. Primeiro, voce precisa falar com uma pessoa, so um momento.\n");
    linhaDeCarregamento();
    printf(Roxo "...\n" Resetar);
    printf(Roxo "Ola, sou o professor %sRowan%s, parece que voce acabou de chegar em Sinnoh." Resetar "\n", Resetar, Roxo);
    printf(Roxo "Para comecar, por favor, me diga o seu nome: " Resetar);
    fgets(jogador->nome, 50, stdin);
    jogador->nome[strcspn(jogador->nome, "\n")] = 0;
}

// Função para escolher o pokemon inicial
void escolherPokemon(Jogador *jogador){
    int escolha = 0;
    char cor_j[20];

    do{
        printf(Roxo "\nOtimo, %s%s!%s Prazer em conhece-lo!\n" Resetar, Resetar, jogador->nome, Roxo);
        printf(Roxo "\n%s%s%s, agora escolha seu Pokemon inicial. Lembre-se, ele sera seu companheiro para uma longa jornada cheia de aventuras!\n", Resetar, jogador->nome, Roxo);
        printf(Negrito Vermelho "1. Chimchar\n" Resetar);
        printf(Negrito Verde "2. Turtwig\n" Resetar);
        printf(Negrito Azul "3. Piplup\n" Resetar);
        printf(Negrito "Escolha um companheiro (1-3): " Resetar);
        scanf("%d", &escolha);
        getchar();

        switch (escolha) {
            case 1:
                strcpy(jogador->jogador_pokemon, "Chimchar");
                strcpy(cor_j, Negrito Vermelho "");
                break;
            case 2:
                strcpy(jogador->jogador_pokemon, "Turtwig");
                strcpy(cor_j, Negrito Verde "");
                break;
            case 3:
                strcpy(jogador->jogador_pokemon, "Piplup");
                strcpy(cor_j, Negrito Azul "");
                break;
            default:
                printf(Vermelho "Escolha invalida! Por favor, escolha novamente.\n" Resetar);
                escolha = 0;
        }
    }while(escolha == 0);

    printf(Roxo "\nParabens, %s%s!%s Voce escolheu %s%s%s como seu primeiro Pokemon, excelente escolha!" Resetar, Resetar, jogador->nome, Roxo, cor_j, jogador->jogador_pokemon, Resetar Roxo);
}

// Função para salvar os dados do jogador em um arquivo binario
void salvarJogador(Jogador *jogador){
    FILE *arquivo = fopen("jogador.bin", "ab");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    fwrite(jogador, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);
}

// Função que escolhe aleatoriamente o pokemon do oponente dentre os diferentes do que o jogador escolheu
Pokemon escolher_oponente_pokemon(Pokemon jogador_pokemon){
    Pokemon oponente_pokemon;
    do{
        oponente_pokemon = pokemons[rand() % 3];
    }while(strcmp(oponente_pokemon.nome, jogador_pokemon.nome) == 0);

    printf(Roxo "\nSeu rival e amigo de infancia %sBarry%s escolheu %s%s%s como seu parceiro!" Resetar, Negrito Cinza, Resetar Roxo, cor_pokemon(oponente_pokemon), oponente_pokemon.nome, Resetar Roxo);

    return oponente_pokemon;
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


// Função para iniciar a batalha entre o jogador e o oponente
int batalha_total(Pokemon jogador_pokemon, Pokemon oponente_pokemon){
    const char *cor_j = cor_pokemon(jogador_pokemon);
    const char *cor_o = cor_pokemon(oponente_pokemon);
    int jogador_max_vida = jogador_pokemon.vida;
    int oponente_max_vida = oponente_pokemon.vida;

    const char* cor_vida_jogador;
    const char* cor_vida_oponente;

    printf(Negrito Cinza"\n\nBarry%s te desafia para uma batalha pokemon! Vamos Lutar!\n" Resetar, Resetar);
    linhaDeCarregamento();
    printf("\nRival %sBarry%s manda %s%s%s para batalhar!" Resetar, Negrito Cinza, Resetar, cor_o, oponente_pokemon.nome, Resetar);
    printf("\nVoce manda %s%s%s!\n" Resetar, cor_j, jogador_pokemon.nome, Resetar);
    //Incompleto
}

int main() {
    srand(time(NULL));

    Jogador jogador;
    Pokemon jogador_pokemon;

    boasVindas(&jogador);     

    if(verificarJogadorExistente(&jogador)){
        jogador_pokemon = link_jogador_pokemon(&jogador);
        printf(Roxo "\nBem-vindo de volta, %s%s!%s Seu Pokemon %s%s%s estava esperando por voce!" Resetar, Resetar, jogador.nome, Roxo, cor_pokemon(jogador_pokemon),jogador.jogador_pokemon, Resetar Roxo);
    } else {
        escolherPokemon(&jogador); 
        salvarJogador(&jogador);   
        jogador_pokemon = link_jogador_pokemon(&jogador); 
    }    

    if(strlen(jogador_pokemon.nome) == 0) {
        printf("Erro: Pokemon do jogador nao encontrado.\n");
        return 1;
    }

    Pokemon oponente_pokemon = escolher_oponente_pokemon(jogador_pokemon);

    batalha_total(jogador_pokemon, oponente_pokemon); // Batalha e seus resultados

    printf(Roxo "\nParabens %s%s!%s Esse foi somente o inicio da incrivel jornada que te aguarda! Esperamos que tenha gostado." Resetar, Resetar, jogador.nome, Roxo);

    return 0;
}