# Pokemon_Battle-C
CCP230/CC2632 T.010.610 / Projeto 2 
## Participantes do Grupo

- Nome: João Guilherme Faber
  - RA: 24.124.060-7

- Nome: Murilo Passarelli 
  - RA: 24.124.041-5

- Nome: Gabriel Furlani 
  - RA: 24.124.062-1


## Objetivo do Projeto

O objetivo desse projet é aprimorar as habilidades com a linguagem C de uma forma animada e interativa com o grupo, juntando os interesses em comum nós iremos criar uma batalha pokemon entre o usuario e a máquina, com o usuário podendo escolher uma variedade de 3 pokemons que são os inicias da quarta geração, e entrando em uma batalha contra o oponente que é o computador podendo escolher entre 3 habilidades.
O Projeto tem as seguintes regras:
- seu projeto deve armazenar dados em arquivos binários e texto simples (não precisam armazenar a mesma informação e cada tipo de arquivo pode ser usado para coisas diferentes)
- seu projeto deve usar arrays, structs e ponteiros para armazenar e gerenciar informações do seu programa
- so do GitHub Workflow e branches para cada funcionalidade do projeto
- README.md contendo descrição do projeto, como compilar e executar
## Compilação e Execução

Para compilar e executar o projeto, siga os seguintes passos:

1. Certifique-se de que você tem um compilador C instalado.
2. Clone o repositório para o seu computador:

    ```sh
    git clone <URL_DO_REPOSITÓRIO>
    ```
   
3. Navegue até o diretório do projeto:

    ```sh
    cd <NOME_DO_DIRETÓRIO>
    ```

4. Compile o código:

    ```sh
    gcc -o batalha_pokemon main.c batalha.c pokemon.c
    ```
5. De o Comit no código:

   ```sh
   git commit -m "Primeiro commit na branch master"
   ```
7. De o Push no código:

    ```sh
    git push -u origin master
    ```

## Forma de Uso

Após compilar e executar o programa, siga as instruções exibidas na tela para iniciar uma batalha Pokémon. O Programa começará se apresentando e logo após isso irá pedir que coloque seu nome. O programa permitirá que você escolha seus Pokémon, ataques e estratégias para vencer a batalha. Cada jogador alternará turnos para escolher suas ações, e o jogo continuará até que um dos jogadores seja declarado vencedor. (o outro jogador é a própria máquina)
