#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 120
#define MAXPLAYERS 6
#define MAXPERFIS 2 //sujeito a mudança, numero aleatorio
#define TENTATIVAS 6

typedef struct _JOGADOR{
    int pontos;
    int usavel;
} JOGADOR;

typedef struct _PERFIL{
    char pergunta[5][60];
    char resposta[30];
} PERFIL;

void BancoDePerfis(PERFIL cartas[]);

/*
   Primeiro a gente tem q criar um banco de dados com os perfis e as perguntas que a gente quer, depois fazer um sistema onde, na sua vez, cada jogador recebe um "perfil" aleatorio
do banco de dados. Ali ele tem a opçao de pedir uma dica (qnd o gets captar "dica") ou dar um palpite. se o palpite for igual ao "char resposta" do perfil analisado, ele ganha n pontos
(6-o numero de dicas usadas). Após isso, o próximo jogador recebe um outro perfil, com "jaUsado" = 0, e repete o mesmo procedimento. O primeiro jogador a conseguir 140 pontos vence, pois
cada ponto é equivalente ao numero de casas andadas.
*/

int main(){

    printf("Bem vindo ao jogo PERFIL!\n");

    int i, j = 0, k, tamanhoMaxPerfil;
    unsigned int jogadores, descontaVezes = 0, vez = 0, cartasUsadas = 0, controle = 1, pergunta=0;
    JOGADOR player[MAXPLAYERS];
    PERFIL cartas[MAXPERFIS];
    PERFIL temp;
    char resposta[50];  //acredito, atualmente, que 50 seja suficiente 

    BancoDePerfis(cartas);

    //CAPTANDO A QUANTIDADE DE JOGADORES
    while(jogadores<2 || jogadores>6) {
        printf("Insira a quantidade de jogadores (2-6): ");
        scanf("%d", &jogadores);
        if(jogadores<2){
            printf("Voce nao pode jogar com menos de duas pessoas!\n");
        }
        else if(jogadores>6){
            printf("Opa, pessoas demais!\n");
        }
    }

    //ATRIBUINDO A QUANTIDADE DE JOGADORES AO PROGRAMA
    for(i=0;i<jogadores;i++){
        player[i].pontos=0;
        player[i].usavel=1;
    }

    //CRIANDO O SISTEMA DE CADA "ROUND", ATE O FINAL DO JOGO 
    while(player[j].pontos<MAX){
        printf("Jogador %d, responda:\n", j+1);
        i = rand() % (MAXPERFIS-cartasUsadas); /*ALEATORIZA A CARTA*/
        //CRIANDO SISTEMA DE PERGUNTAS (eu deveria fazer um maximo de tentativas, ou o jogador fica respondendo até acertar?)
        while(controle){
            puts(cartas[i].pergunta[pergunta]);
            fflush(stdin);
            gets(resposta);
            fflush(stdin);

            /*Checa que pediu dica*/
            if(strcmp(resposta, "dica") == 0){
                if(descontaVezes==4){
                    printf("Voce ja atingiu o maximo de dicas!\n");
                }
                else{ 
                    pergunta++;
                    descontaVezes++;
                }
            }
            //Se ele acertar: printa (acertou), atribui os pontos ao jogador, corrige o vetor de PERFIS, retorna o controle pra 0 para mudar de round, o que mais?
            else if(strcmp(resposta, cartas[i].resposta) == 0){
                printf("Parabens, voce acertou!\n\n");
                player[j].pontos += (5 - descontaVezes);

                //corrigindo o vetor de cartas para o perfil "i" sair deste

                cartasUsadas++;
                for(k=i;k<(MAXPERFIS-cartasUsadas); k++){
                    temp = cartas[k];
                    cartas[k]=cartas[k+1];
                    cartas[k+1]=temp;
                }
                controle=0;
            }
        }

        /*MOSTRAR PONTUAÇÃO*/
        printf("J1: %d pontos | J2: %d pontos", player[0].pontos, player[1].pontos);
        if (player[2].usavel == 1){
            printf(" | J3: %d pontos", player[2].pontos);
            if (player[3].usavel == 1){
                printf(" | J4: %d pontos", player[3].pontos);
                if (player[4].usavel == 1){
                    printf(" | J5: %d pontos", player[4].pontos);
                    if (player[5].usavel == 1){
                        printf(" | J6: %d pontos\n", player[5].pontos);
                    }
                }
            }
        }
        printf("\n\n");
        
        controle=1;
        vez++;
        j = vez % jogadores;
    }

    return 0;
}

void BancoDePerfis(PERFIL cartas[]) {
    strcpy(cartas[0].pergunta[0],"Dica 1: Navegador e explorador");
    strcpy(cartas[0].pergunta[1],"Dica 2: Nasceu em Portugal");
    strcpy(cartas[0].pergunta[2],"Dica 3: Descobriu o Brasil");
    strcpy(cartas[0].pergunta[3],"Dica 4: ");
    strcpy(cartas[0].pergunta[4],"Dica 5: ");
    strcpy(cartas[0].resposta,"pedro alvares cabral");

    strcpy(cartas[1].pergunta[0],"Dica 1: Pintor famoso");
    strcpy(cartas[1].pergunta[1],"Dica 2: Importante figura da Renascenca");
    strcpy(cartas[1].pergunta[2],"Dica 3: Nasceu na Italia");
    strcpy(cartas[1].pergunta[3],"Dica 4: Fez grandes contribuicoes em varias areas");
    strcpy(cartas[1].pergunta[4],"Dica 5: Pintou a Mona Lisa");
    strcpy(cartas[1].resposta,"leonardo da vinci");

    strcpy(cartas[2].pergunta[0],"");
    strcpy(cartas[2].pergunta[1],"");
    strcpy(cartas[2].pergunta[2],"");
    strcpy(cartas[2].pergunta[3],"");
    strcpy(cartas[2].pergunta[4],"");
    strcpy(cartas[2].resposta,"");

}