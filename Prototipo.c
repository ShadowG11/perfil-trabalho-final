#include <stdio.h>
#include <random.h>
#define MAX 120
#define MAXPLAYERS 6
#define MAXPERFIS 169 //sujeito a mudança, numero aleatorio
#define TENTATIVAS 6

typedef struct _JOGADOR{
    char[42] nome;
    int pontos;
    int usavel;
    
} JOGADOR;

typedef struct _PERFIL{
    char pergunta1[];
    char pergunta2[];
    char pergunta3[];
    char pergunta4[];
    char pergunta5[];
    char resposta;
} PERFIL;

/*
   Primeiro a gente tem q criar um banco de dados com os perfis e as perguntas que a gente quer, depois fazer um sistema onde, na sua vez, cada jogador recebe um "perfil" aleatorio
do banco de dados. Ali ele tem a opçao de pedir uma dica (qnd o gets captar "dica") ou dar um palpite. se o palpite for igual ao "char resposta" do perfil analisado, ele ganha n pontos
(6-o numero de dicas usadas). Após isso, o próximo jogador recebe um outro perfil, com "jaUsado" = 0, e repete o mesmo procedimento. O primeiro jogador a conseguir 140 pontos vence, pois
cada ponto é equivalente ao numero de casas andadas.
*/

int main(){

    printf("Bem vindo ao jogo PERFIL!");

    int i, j = 0, k, tamanhoMaxPerfil, *pergunta;
    unsigned int jogadores, descontaVezes, vez = 0, cartasUsadas = 0, controle = 1;
    JOGADOR players[MAXPLAYERS];
    PERFIL cartas[MAXPERFIS];
    PERFIL temp;
    char resposta[50];  //acredito, atuamente, que 50 seja suficiente 

    //CAPTANDO A QUANTIDADE DE JOGADORES
    for(i=0;i<1;i++){
        printf("Insira a quantidade de jogadores (2-6)\n");
        scanf("%d", &jogadores);
        if(jogadores<2){
            printf("Voce não pode jogar com menos de duas pessoas!\n");
            i=0;
        }
        else if(jogadores>6){
            printf("Opa, pessoas demais!\n");
            i=0
        }
    }

    //ATRIBUINDO A QUANTIDADE DE JOGADORES AO PROGRAMA
    for(i=0;i<jogadores;i++){

        players[i].usavel=1;
    }

    //CRIANDO O SISTEMA DE CADA "ROUND", ATE O FINAL DO JOGO 
    while(player[j].pontos<MAX){

        //CRIANDO SISTEMA DE PERGUNTAS (eu deveria fazer um maximo de tentativas, ou o jgoador fica respondendo até acertar?)
        while(controle){
            i = randomInteger(0, (MAXPERFIS-cartasUsadas));
            pergunta = &cartas[i].pergunta1
            puts(*pergunta);
            gets(resposta);
            if(resposta=="dica"){
                if(descontaVezes=5){
                    printf("voce ja atingiu o maximo de dicas!\n");
                    break;
                }
                else{ 
                    pergunta++;
                    descontaVezes++;
                }
            }
            //Se ele acertar: printa (acertou), atribui os pontos ao jogador, corrige o vetor de PERFIS, retorna o controle pra 0 para mudar de round, o que mais?
            else if(resposta==cartas[i].resposta){
                printf("Parabens, voce acertou!\n");
                player[j].pontos = (TENTATIVAS - descontaVezes);

                //corrigindo o vetor de cartas para o perfil "i" sair deste

                cartasUsadas++;
                for(k=i;k<(MAXPERFIS-cartasUsadas); k++){
                    temp = cartas[i];
                    cartas[i]=cartas[i+1];
                    cartas[i+1]=temp;
                }
                controle=0;
            }
        }  

        controle=1;
        vez++;
        j= vez % jogadores;
    }

    return 0;
}
