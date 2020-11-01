#include <stdio.h>
#include <stdlib.h>
#define MAX 120
#define TENTATIVAS 6

typedef struct _JOGADOR{
    char nome[42];
    int pontos;
    int usavel;
} JOGADOR;

typedef struct _PERFIL{
    char pergunta1[80];
    char pergunta2[80];
    char pergunta3[80];
    char pergunta4[80];
    char pergunta5[80];
    char resposta[20];
    int jaUsado = 0; /*tá indicando erro, verificar o que é. acredito que não dá pra definir a variável dentro da struct*/
    int pontuacao = 6; /*esse também tá dando erro*/
} PERFIL;

/*
   Primeiro a gente tem q criar um banco de dados com os perfis e as perguntas que a gente quer, depois fazer um sistema onde, na sua vez, cada jogador recebe um "perfil" aleatorio
do banco de dados. Ali ele tem a opçao de pedir uma dica (qnd o gets captar "dica") ou dar um palpite. se o palpite for igual ao "char resposta" do perfil analisado, ele ganha n pontos
(6-o numero de dicas usadas). Após isso, o próximo jogador recebe um outro perfil, com "jaUsado" = 0, e repete o mesmo procedimento. O primeiro jogador a conseguir 140 pontos vence, pois
cada ponto é equivalente ao numero de casas andadas.
*/

int main(){

    int jogadores, i, tamanhoMaxPerfil;
    JOGADOR players[6];
    PERFIL perfil[20];
    char resposta[20];

    printf("Insira a quantidade de jogadores (2-6)\n");
    scanf("%d", &jogadores);

    for(i=0;i<jogadores;i++){
        players[i].usavel=1;
    }

    


}
