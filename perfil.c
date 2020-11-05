#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXPONTOS 20  /*Maximo de pontos, 20 devido ao tamanho do Banco de Dados*/
#define MAXPLAYERS 6
#define MAXPERFIS 17 /*sujeito a mudança, atualmente existem 17 perfis no DB*/

typedef struct _JOGADOR{
    int pontos;
    int usavel;
} JOGADOR;

typedef struct _PERFIL{
    char pergunta[5][70];
    char resposta[30];
} PERFIL;

void BancoDePerfis(PERFIL cartas[]);

/*
   Primeiro a gente tem q criar um banco de dados com os perfis e as perguntas que a gente quer, depois fazer um sistema onde, na sua vez, cada jogador recebe um "perfil" aleatorio
do banco de dados. Ali ele tem a opçao de pedir uma dica (qnd o gets captar "dica") ou dar um palpite. se o palpite for igual ao "char resposta" do perfil analisado, ele ganha n pontos
(5-o numero de dicas usadas). Após isso, o próximo jogador recebe um outro perfil, com "jaUsado" = 0, e repete o mesmo procedimento. O primeiro jogador a conseguir 20 pontos vence, pois
cada ponto é equivalente ao numero de casas andadas.
*/

int main(){
    int i;
    int j = 0;
    int k;
    unsigned int jogadores, descontaVezes = 0, vez = 0, cartasUsadas = 0, controle = 1, pergunta=0;
    JOGADOR player[MAXPLAYERS];
    PERFIL cartas[MAXPERFIS];
    PERFIL temp;
    char resposta[30];  /*acredito, atualmente, que 50 seja suficiente*/
    srand(time(0));

    BancoDePerfis(cartas);

    printf("Bem vindo ao jogo PERFIL!\n");

    /*CAPTANDO A QUANTIDADE DE JOGADORES*/
    while(jogadores<2 || jogadores>6) {
        printf("Insira a quantidade de jogadores (2-6): ");
        scanf("%ud", &jogadores);
        fflush(stdin);
        if(jogadores<2){
            printf("Voce nao pode jogar com menos de duas pessoas!\n");
        }
        else if(jogadores>6){
            printf("Opa, pessoas demais!\n");
        }
    }

    /*ATRIBUINDO A QUANTIDADE DE JOGADORES AO PROGRAMA*/
    for(i=0;i<jogadores;i++){
        player[i].pontos=0;
        player[i].usavel=1;
    }

    /*CRIANDO O SISTEMA DE CADA "ROUND", ATE O FINAL DO JOGO*/
    while(player[j].pontos<MAXPONTOS){
        printf("Jogador %d, responda:\n", j+1);
        i = rand() % (MAXPERFIS-cartasUsadas); /*ALEATORIZA A CARTA*/

        /*SISTEMA DE PERGUNTAS*/
        while(controle){
            puts(cartas[i].pergunta[pergunta]);
            gets(resposta);

            /*Checa se pediu dica*/
            if(strcmp(resposta, "dica") == 0){
                if(descontaVezes==4){
                    printf("Voce ja atingiu o maximo de dicas!\n");
                }
                else{ 
                    pergunta++;
                    descontaVezes++;
                }
            }

            /*Checa se pulou*/
            else if(strcmp(resposta, "pular") == 0){
                printf("Resposta pulada!\n");
                controle = 0;
            }

            /*Se ele acertar: printa (acertou), atribui os pontos ao jogador, corrige o vetor de PERFIS, retorna o controle pra 0 para mudar de round*/
            else if(strcmp(resposta, cartas[i].resposta) == 0){
                printf("Parabens, voce acertou!\n\n");
                player[j].pontos += (5 - descontaVezes);

                /*corrigindo o vetor de cartas para o perfil "i" sair deste*/
                cartasUsadas++;
                for(k=i;k<(MAXPERFIS-cartasUsadas); k++){
                    temp = cartas[k];
                    cartas[k]=cartas[k+1];
                    cartas[k+1]=temp;
                }
                controle=0;
            }

            else{
                printf("Resposta errada!\n");
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
                        printf(" | J6: %d pontos", player[5].pontos);
                    }
                }
            }
        }
        printf("\n\n");
        
        /*CONFERE SE ACABOU O JOGO*/
        if(player[j].pontos>=MAXPONTOS){
            break;
        }

        controle=1;
        vez++;
        j = vez % jogadores;
        descontaVezes = 0;
        pergunta = 0;

        if(j>jogadores){
            j=0;
        }

    }

    printf("Parabens jogador %d, voce ganhou o jogo!\n", (j+1));

    return 0;
}


void BancoDePerfis(PERFIL cartas[]) {
    strcpy(cartas[0].pergunta[0],"Dica 1: Navegador e explorador");
    strcpy(cartas[0].pergunta[1],"Dica 2: Nasceu em Portugal");
    strcpy(cartas[0].pergunta[2],"Dica 3: Descobriu o Brasil");
    strcpy(cartas[0].pergunta[3],"Dica 4: Mesmo primeiro nome de um imperador do Brasil");
    strcpy(cartas[0].pergunta[4],"Dica 5: ");
    strcpy(cartas[0].resposta,"pedro alvares cabral");


    strcpy(cartas[1].pergunta[0],"Dica 1: Pintor famoso");
    strcpy(cartas[1].pergunta[1],"Dica 2: Importante figura da Renascenca");
    strcpy(cartas[1].pergunta[2],"Dica 3: Nasceu na Italia");
    strcpy(cartas[1].pergunta[3],"Dica 4: Fez grandes contribuicoes em varias areas");
    strcpy(cartas[1].pergunta[4],"Dica 5: Pintou a Mona Lisa");
    strcpy(cartas[1].resposta,"leonardo da vinci");


    strcpy(cartas[2].pergunta[0],"Dica 1: Fica no Banheiro");
    strcpy(cartas[2].pergunta[1],"Dica 2: Feito de plastico");
    strcpy(cartas[2].pergunta[2],"Dica 3: Usado junto com outro produto");
    strcpy(cartas[2].pergunta[3],"Dica 4: Tem cerdas");
    strcpy(cartas[2].pergunta[4],"Dica 5: Usado nos dentes");
    strcpy(cartas[2].resposta,"escova de dentes");


    strcpy(cartas[3].pergunta[0],"Dica 1: Fisico da Suica");
    strcpy(cartas[3].pergunta[1],"Dica 2: Nascido em 1879");
    strcpy(cartas[3].pergunta[2],"Dica 3: Ganhou o Premio Nobel");
    strcpy(cartas[3].pergunta[3],"Dica 4: Nascido na Alemanha");
    strcpy(cartas[3].pergunta[4],"Dica 5: Criou a Teoria da Relatividade");
    strcpy(cartas[3].resposta,"albert einstein");


    strcpy(cartas[4].pergunta[0],"Dica 1: Fisico da Inglaterra");
    strcpy(cartas[4].pergunta[1],"Dica 2: Nasceu em 1743");
    strcpy(cartas[4].pergunta[2],"Dica 3: Autodidata");
    strcpy(cartas[4].pergunta[3],"Dica 4: Criou a Mecanica Classica");
    strcpy(cartas[4].pergunta[4],"Dica 5: Uma maca caiu em sua cabeca");
    strcpy(cartas[4].resposta,"isaac newton");


    strcpy(cartas[5].pergunta[0],"Dica 1: Presidente dos Estados Unidos");
    strcpy(cartas[5].pergunta[1],"Dica 2: Nascido em 1961");
    strcpy(cartas[5].pergunta[2],"Dica 3: Aluno de Harvard Law School");
    strcpy(cartas[5].pergunta[3],"Dica 4: Ganhou o Nobel da Paz");
    strcpy(cartas[5].pergunta[4],"Dica 5: Primeiro presidente negro dos EUA");
    strcpy(cartas[5].resposta,"barack obama");


    strcpy(cartas[6].pergunta[0],"Dica 1: Profeta do Islamismo");
    strcpy(cartas[6].pergunta[1],"Dica 2: Nascido em Nazare");
    strcpy(cartas[6].pergunta[2],"Dica 3: Nasceu em uma mangedoura");
    strcpy(cartas[6].pergunta[3],"Dica 4: Transformou agua em vinho");
    strcpy(cartas[6].pergunta[4],"Dica 5: Foi crucificado");
    strcpy(cartas[6].resposta,"jesus");


    strcpy(cartas[7].pergunta[0],"Dica 1: Navegador Italiano");
    strcpy(cartas[7].pergunta[1],"Dica 2: Nascido em 1451");
    strcpy(cartas[7].pergunta[2],"Dica 3: 'descobriu' a America");
    strcpy(cartas[7].pergunta[3],"Dica 4: America do Sul tem um pais nomeado em sua homenagem");
    strcpy(cartas[7].pergunta[4],"Dica 5: Primeiro Europeu a chegar no continente americano");
    strcpy(cartas[7].resposta,"cristovao colombo");

    
    strcpy(cartas[8].pergunta[0],"Dica 1: Matematico florentino");
    strcpy(cartas[8].pergunta[1],"Dica 2: Nasceu em 1564");
    strcpy(cartas[8].pergunta[2],"Dica 3: Muito presente na Revolucao Cientifica");
    strcpy(cartas[8].pergunta[3],"Dica 4: Estudou Mecanica Classica");
    strcpy(cartas[8].pergunta[4],"Dica 5: Defendia o Heliocentrismo");
    strcpy(cartas[8].resposta,"galileu galilei");

    
        
    strcpy(cartas[9].pergunta[0],"Dica 1: Profeta do Judaismo, Cristianismo e Islamismo");
    strcpy(cartas[9].pergunta[1],"Dica 2: Famoso por libertar os Hebreus do Egito");
    strcpy(cartas[9].pergunta[2],"Dica 3: Presente no livro de Exodo");
    strcpy(cartas[9].pergunta[3],"Dica 4: Abriu o Mar Vermelho");
    strcpy(cartas[9].pergunta[4],"Dica 5: Figura que detem a autoria da Tora");
    strcpy(cartas[9].resposta,"moises");

    
        
    strcpy(cartas[10].pergunta[0],"Dica 1: Biologo britanico");
    strcpy(cartas[10].pergunta[1],"Dica 2: Nasceu em 1809");
    strcpy(cartas[10].pergunta[2],"Dica 3: Publicou o livro A Origem das Especies");
    strcpy(cartas[10].pergunta[3],"Dica 4: Cientista Agnostico");
    strcpy(cartas[10].pergunta[4],"Dica 5: Criou a Teoria da Evolucao");
    strcpy(cartas[10].resposta,"charles darwin");

    
        
    strcpy(cartas[11].pergunta[0],"Dica 1: Sociologo e Economista");
    strcpy(cartas[11].pergunta[1],"Dica 2: Nasceu na Prussia, em 1818");
    strcpy(cartas[11].pergunta[2],"Dica 3: Grande critico do Capitalismo");
    strcpy(cartas[11].pergunta[3],"Dica 4: Atuou na Alemanha");
    strcpy(cartas[11].pergunta[4],"Dica 5: Criou o Socialismo");
    strcpy(cartas[11].resposta,"karl marx");

        
        
    strcpy(cartas[12].pergunta[0],"Dica 1: Lider politico e militar frances");
    strcpy(cartas[12].pergunta[1],"Dica 2: Nasceu em 1769");
    strcpy(cartas[12].pergunta[2],"Dica 3: Imperador dos Franceses");
    strcpy(cartas[12].pergunta[3],"Dica 4: Conquistou grande parte da Europa");
    strcpy(cartas[12].pergunta[4],"Dica 5: Perdeu contra a Russia, no inverno");
    strcpy(cartas[12].resposta,"napoleao bonaparte");
  
        
    strcpy(cartas[13].pergunta[0],"Dica 1: Grande inventor mecanico e cientista eletrotecnico");
    strcpy(cartas[13].pergunta[1],"Dica 2: Nasceu em 1856");
    strcpy(cartas[13].pergunta[2],"Dica 3: revolucionou o campo do eletromagnetismo");
    strcpy(cartas[13].pergunta[3],"Dica 4: Criou um tipo de turbina que leva o seu nome");
    strcpy(cartas[13].pergunta[4],"Dica 5: 'ta in shockkk?'");
    strcpy(cartas[13].resposta,"nikola tesla");
   
        
    strcpy(cartas[14].pergunta[0],"Dica 1: Politico Alemao");
    strcpy(cartas[14].pergunta[1],"Dica 2: nasceu em 1889, na austria");
    strcpy(cartas[14].pergunta[2],"Dica 3: Queria ser artista");
    strcpy(cartas[14].pergunta[3],"Dica 4: principal instigador da Segunda Guerra Mundial");
    strcpy(cartas[14].pergunta[4],"Dica 5: Principal figura do Partido Nazista");
    strcpy(cartas[14].resposta,"adolf hitler");
   
        
    strcpy(cartas[15].pergunta[0],"Dica 1: Compositor Alemao");
    strcpy(cartas[15].pergunta[1],"Dica 2: Fez a transicao do classicismo para o romantismo");
    strcpy(cartas[15].pergunta[2],"Dica 3: Um dos mais importantes Compositores da musica ocidental");
    strcpy(cartas[15].pergunta[3],"Dica 4: Compos a musica do carro do gas");
    strcpy(cartas[15].pergunta[4],"Dica 5: Compos a famosa peca para piano 'Sonata ao Luar'");
    strcpy(cartas[15].resposta,"beethoven");
  
        
    strcpy(cartas[16].pergunta[0],"Dica 1: Alcunhado 'o Magnamico'");
    strcpy(cartas[16].pergunta[1],"Dica 2: Nascido em 1825");
    strcpy(cartas[16].pergunta[2],"Dica 3: Imperador do Brasil");
    strcpy(cartas[16].pergunta[3],"Dica 4: Recebeu um colegio como presente de aniversario");
    strcpy(cartas[16].pergunta[4],"Dica 5: Ultimo Imperador Brasileiro");
    strcpy(cartas[16].resposta,"pedro ii");
      
}
