#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20  //Maximo de pontos, 20 devido ao tamanho do Banco de Dados
#define MAXPLAYERS 6
#define MAXPERFIS 17 //sujeito a mudança, atualmente existem 17 perfis no DB
#define TENTATIVAS 6

typedef struct _JOGADOR{
    int pontos = 0;
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
    while(player[0].pontos<MAX && player[1].pontos<MAX && player[2].pontos<MAX && player[3].pontos<MAX && player[4].pontos<MAX && player[5].pontos<MAX && ){
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

    for(i=0;i<jogadores;i++){
        if(jogador[i].pontos>=MAX){
            printf("Parabens jogador %d, voce ganhou o jogo!\n", (i+1));
        }
    }

    return 0;
}


void BancoDePerfis(PERFIL cartas[]) {
    int a = 0;

    strcpy(cartas[a].pergunta[0],"Dica 1: Navegador e explorador");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nasceu em Portugal");
    strcpy(cartas[a].pergunta[2],"Dica 3: Descobriu o Brasil");
    strcpy(cartas[a].pergunta[3],"Dica 4: Mesmo nome de um imperador do Brasil");
    strcpy(cartas[a].pergunta[4],"Dica 5: ");
    strcpy(cartas[a].resposta,"pedro alvares cabral");
    
    a++;

    strcpy(cartas[a].pergunta[0],"Dica 1: Pintor famoso");
    strcpy(cartas[a].pergunta[1],"Dica 2: Importante figura da Renascenca");
    strcpy(cartas[a].pergunta[2],"Dica 3: Nasceu na Italia");
    strcpy(cartas[a].pergunta[3],"Dica 4: Fez grandes contribuicoes em varias areas");
    strcpy(cartas[a].pergunta[4],"Dica 5: Pintou a Mona Lisa");
    strcpy(cartas[a].resposta,"leonardo da vinci");
    
    a++;

    strcpy(cartas[a].pergunta[0],"Dica 1: Fica no Banheiro");
    strcpy(cartas[a].pergunta[1],"Dica 2: Feito de plastico");
    strcpy(cartas[a].pergunta[2],"Dica 3: Usado junto com outro produto");
    strcpy(cartas[a].pergunta[3],"Dica 4: Tem cerdas");
    strcpy(cartas[a].pergunta[4],"Dica 5: Usado nos dentes");
    strcpy(cartas[a].resposta,"escova de dentes");
    
    a++;

    strcpy(cartas[a].pergunta[0],"Dica 1: Fisico da Suica");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nascido em 1879");
    strcpy(cartas[a].pergunta[2],"Dica 3: Ganhou o Premio Nobel");
    strcpy(cartas[a].pergunta[3],"Dica 4: Nascido na Alemanha");
    strcpy(cartas[a].pergunta[4],"Dica 5: Criou a Teoria da Relatividade");
    strcpy(cartas[a].resposta,"albert einstein");
    
    a++;

    strcpy(cartas[a].pergunta[0],"Dica 1: Fisico da Inglaterra");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nasceu em 1743");
    strcpy(cartas[a].pergunta[2],"Dica 3: Autodidata");
    strcpy(cartas[a].pergunta[3],"Dica 4: Criou a Mecanica Classica");
    strcpy(cartas[a].pergunta[4],"Dica 5: Uma maca caiu em sua cabeca");
    strcpy(cartas[a].resposta,"isaac newton");
    
    a++;

    strcpy(cartas[a].pergunta[0],"Dica 1: Presidente dos Estados Unidos");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nascido em 1961");
    strcpy(cartas[a].pergunta[2],"Dica 3: Aluno de Harvard Law School");
    strcpy(cartas[a].pergunta[3],"Dica 4: Ganhou o Nobel da Paz");
    strcpy(cartas[a].pergunta[4],"Dica 5: Primeiro presidente negro dos EUA");
    strcpy(cartas[a].resposta,"barack obama");
    
    a+;

    strcpy(cartas[a].pergunta[0],"Dica 1: Profeta do Islamismo");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nascido em Nazare");
    strcpy(cartas[a].pergunta[2],"Dica 3: Nasceu em uma mangedoura");
    strcpy(cartas[a].pergunta[3],"Dica 4: Transformou agua em vinho");
    strcpy(cartas[a].pergunta[4],"Dica 5: Foi crucificado");
    strcpy(cartas[a].resposta,"jesus");
    
    a++;

    strcpy(cartas[a].pergunta[0],"Dica 1: Navegador Italiano");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nascido em 1451");
    strcpy(cartas[a].pergunta[2],"Dica 3: 'descobriu' a America");
    strcpy(cartas[a].pergunta[3],"Dica 4: America do Sul tem um pais nomeado em sua homenagem");
    strcpy(cartas[a].pergunta[4],"Dica 5: Primeiro Europeu a chegar no continente americano");
    strcpy(cartas[a].resposta,"cristovao colombo");
    
    a++;
    
    strcpy(cartas[a].pergunta[0],"Dica 1: Matematico florentino");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nasceu em 1564");
    strcpy(cartas[a].pergunta[2],"Dica 3: Muito presente na Revolucao Cientifica");
    strcpy(cartas[a].pergunta[3],"Dica 4: Estudou Mecanica Classica");
    strcpy(cartas[a].pergunta[4],"Dica 5: Defendia o Heliocentrismo");
    strcpy(cartas[a].resposta,"galileu galilei");
    
    a++;
    
        
    strcpy(cartas[a].pergunta[0],"Dica 1: Profeta do Judaismo, Cristianismo e Islamismo");
    strcpy(cartas[a].pergunta[1],"Dica 2: Famoso por libertar os Hebreus do Egito");
    strcpy(cartas[a].pergunta[2],"Dica 3: Presente no livro de Exodo");
    strcpy(cartas[a].pergunta[3],"Dica 4: Abriu o Mar Vermelho");
    strcpy(cartas[a].pergunta[4],"Dica 5: Figura que detem a autoria da Tora");
    strcpy(cartas[a].resposta,"moises");
    
    a++;
    
        
    strcpy(cartas[a].pergunta[0],"Dica 1: Biologo britanico");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nasceu em 1809");
    strcpy(cartas[a].pergunta[2],"Dica 3: Publicou o livro A Origem das Especies");
    strcpy(cartas[a].pergunta[3],"Dica 4: Cientista Agnostico");
    strcpy(cartas[a].pergunta[4],"Dica 5: Criou a Teoria da Evolucao");
    strcpy(cartas[a].resposta,"charles darwin");
    
    a++;
    
        
    strcpy(cartas[a].pergunta[0],"Dica 1: Sociologo e Economista");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nasceu na Prussia, em 1818");
    strcpy(cartas[a].pergunta[2],"Dica 3: Grande critico do Capitalismo");
    strcpy(cartas[a].pergunta[3],"Dica 4: Atuou na Alemanha");
    strcpy(cartas[a].pergunta[4],"Dica 5: Criou o Socialismo");
    strcpy(cartas[a].resposta,"karl marx");
    
    a++;
        
        
    strcpy(cartas[a].pergunta[0],"Dica 1: Lider politico e militar frances");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nasceu em 1769");
    strcpy(cartas[a].pergunta[2],"Dica 3: Imperador dos Franceses");
    strcpy(cartas[a].pergunta[3],"Dica 4: Conquistou grande parte da Europa");
    strcpy(cartas[a].pergunta[4],"Dica 5: Perdeu contra a Russia, no inverno");
    strcpy(cartas[a].resposta,"napoleao bonaparte");
    
    a++;    
        
    strcpy(cartas[a].pergunta[0],"Dica 1: Grande inventor mecanico e cientista eletrotecnico");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nasceu em 1856");
    strcpy(cartas[a].pergunta[2],"Dica 3: revolucionou o campo do eletromagnetismo");
    strcpy(cartas[a].pergunta[3],"Dica 4: Criou um tipo de turbina que leva o seu nome");
    strcpy(cartas[a].pergunta[4],"Dica 5: 'ta in shockkk??'");
    strcpy(cartas[a].resposta,"nikola tesla");
    
    a++;    
        
    strcpy(cartas[a].pergunta[0],"Dica 1: Politico Alemao");
    strcpy(cartas[a].pergunta[1],"Dica 2: nasceu em 1889, na austria");
    strcpy(cartas[a].pergunta[2],"Dica 3: Queria ser artista");
    strcpy(cartas[a].pergunta[3],"Dica 4: principal instigador da Segunda Guerra Mundial");
    strcpy(cartas[a].pergunta[4],"Dica 5: Principal figura do Partido Nazista");
    strcpy(cartas[a].resposta,"adolf hitler");
    
    a++;    
        
    strcpy(cartas[a].pergunta[0],"Dica 1: Compositor Alemao");
    strcpy(cartas[a].pergunta[1],"Dica 2: Fez a transicao do classicismo para o romantismo");
    strcpy(cartas[a].pergunta[2],"Dica 3: Um dos mais importantes Compositores da musica ocidental");
    strcpy(cartas[a].pergunta[3],"Dica 4: Compos a musica do carro do gas");
    strcpy(cartas[a].pergunta[4],"Dica 5: Compos a famosa peca para piano 'Sonata ao Luar'");
    strcpy(cartas[a].resposta,"beethoven");
    
    a++;    
        
    strcpy(cartas[a].pergunta[0],"Dica 1: Alcunhado 'o Magnamico'");
    strcpy(cartas[a].pergunta[1],"Dica 2: Nascido em 1825");
    strcpy(cartas[a].pergunta[2],"Dica 3: Imperador do Brasil");
    strcpy(cartas[a].pergunta[3],"Dica 4: Recebeu um colegio como presente de aniversario");
    strcpy(cartas[a].pergunta[4],"Dica 5: Ultimo Imperador Brasileiro");
    strcpy(cartas[a].resposta,"pedro ii");
    
    a++;    
        
    strcpy(cartas[a].pergunta[0],"Dica 1: ");
    strcpy(cartas[a].pergunta[1],"Dica 2: ");
    strcpy(cartas[a].pergunta[2],"Dica 3: ");
    strcpy(cartas[a].pergunta[3],"Dica 4: ");
    strcpy(cartas[a].pergunta[4],"Dica 5: ");
    strcpy(cartas[a].resposta,"");
    
    a++;
    

    printf("%d", a);
    
    /*  Copia e Cola daqui
    
    strcpy(cartas[a].pergunta[0],"Dica 1: ");
    strcpy(cartas[a].pergunta[1],"Dica 2: ");
    strcpy(cartas[a].pergunta[2],"Dica 3: ");
    strcpy(cartas[a].pergunta[3],"Dica 4: ");
    strcpy(cartas[a].pergunta[4],"Dica 5: ");
    strcpy(cartas[a].resposta,"");
    
    a++;
    
    
    */
}
