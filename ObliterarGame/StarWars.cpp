#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <SDL2/SDL_image.h>
//#include <SDL_ttf.h>

#define WINDOWSIZE_X 800
#define WINDOWSIZE_Y 600

#define COLUNAS 15
#define LINHAS 10
#define LADO 1
#define tamanho 30

using namespace std;

typedef struct{
    char aux[3];
    int ponto;
}ficha;

int main(int argc, char *argv[]){

    ficha novo, compara;
    char letra;
    int qtd;

    char *ranking = "Ranking.txt";

    fstream arquivo("Ranking.txt");
    if( arquivo == 0){//erro
        // erro no processo
        cout << "O arquivo nao pode ser aberto!";
		return 1;
	}

    // tela para programação
    SDL_Window* window = NULL;

    // tela do jogo
    SDL_Renderer *screenRenderer = NULL;

    SDL_Surface
    *surMenu,
    *surTutorial,
    *surCreditos,
    *surintro,
    *background,
    *block,
    *vetAnim[6],
    *vetMotion[6],
    *vetShoot[8],
    *vetVidaP1[4],
    *vetVidaP2[4],
    *person2,
    *person1,
    *shoot;

    SDL_Texture
    *texMenu,
    *texTutorial,
    *texCreditos,
    *texintro,
    *textureBackground,
    *textureVidaP1[4],
    *textureVidaP2[4],
    *textureAnim[6],
    *textureMotion[6],
    *textureShoot[8],
    *texture_Block,
    *texture_person1,
    *texture_person2,
    *texture_shoot1,
    *texture_shoot2;

    //Comandos e interações
    SDL_Event evento;
    SDL_Event menuJogo;

    int
    fechaJogo = 0,
    menu = 1,
    sub = 0,
    cont = 0,
    anim = 0,
    motion = 0,
    animVida = 0,
    animVida1 = 0,
    animVida2 = 0,
    animaTiro = 0,
    i = 0,
    j = 0,
    estado = 0,
    stop = 0,
    stop2 = 0,
    JogoAtivo = 1,
    teclapressionada1 = 0,
    teclapressionada2 = 0,
    lancamento = 0,
    lancamento2 = 0;

    char
    id[] = {'0', '1', '2', '3', '4', '5', '6', '7'},
    path[50] = {"img/char/Jedi-Idle/Jedi-Idle10000.png"},
    srcProjetil [50] = {"img/tiro/projetil/Projetil0010.png"},
    src[50] = {"img/char/Jedi-Idle/2Jedi-Idle0000.png"},
    srcVida[50] = {"img/texture/3.png"};

    // parabola
    float
    forca = 0,
    dir = 0,
    angulo,
    angulo2,
    v,
    v2,
    tempo1= 0,
    tempo2= 0;

    // iniciando a SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout <<"Nao foi possivel inicializar a SDL! "<<" SDL_Error: "<<SDL_GetError() << endl;
            return 1;
    }

    // criando a janela
    window = SDL_CreateWindow("O B L I T E R A R ! ! !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWSIZE_X, WINDOWSIZE_Y, SDL_WINDOW_SHOWN);
    if( window == NULL ){
        cout <<"Janela nao pode ser criada! " <<" SDL_Error: "<< SDL_GetError() << endl;
        SDL_Quit();
        return 2;
    }

    //Criar um renderizador
    screenRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if(screenRenderer == NULL)
        cout<<"Nao foi possivel inicializar a Renderizacao. \n"<<SDL_GetError();
    else{
        cout<<"Rendirizacao completa com sucesso!\n";
        //Inicializa a cor do renderizador
        //SDL_SetRenderDrawColor( screenRenderer, 0x0, 0x0, 0x0, 0x0 );

        //limpa a tela
        SDL_RenderClear(screenRenderer);

        //Carregamento de imagens
        IMG_Init(IMG_INIT_PNG);
        block = IMG_Load("img/texture/Brick_Block.png");
        texture_Block = SDL_CreateTextureFromSurface(screenRenderer, block);
        SDL_FreeSurface(block);

        person1 = IMG_Load("img/char/char.png");
        texture_person1 = SDL_CreateTextureFromSurface(screenRenderer, person1);
        SDL_FreeSurface(person1);

        person2 = IMG_Load("img/char/char2.png");
        texture_person2 = SDL_CreateTextureFromSurface(screenRenderer, person2);
        SDL_FreeSurface(person2);

        shoot = IMG_Load("img/tiro/tiro.png");
        texture_shoot1 = SDL_CreateTextureFromSurface(screenRenderer, shoot);
        SDL_FreeSurface(shoot);

        background = IMG_Load("img/texture/fundo.png");
        textureBackground = SDL_CreateTextureFromSurface(screenRenderer, background);
        SDL_FreeSurface(background);

        IMG_Init(IMG_INIT_JPG);
        surMenu = IMG_Load("img/menu/menu.jpg");
        texMenu = SDL_CreateTextureFromSurface(screenRenderer, surMenu);
        SDL_FreeSurface(surMenu);

        surCreditos = IMG_Load("img/menu/creditos.jpg");
        texCreditos = SDL_CreateTextureFromSurface(screenRenderer, surCreditos);
        SDL_FreeSurface(surMenu);

        surintro = IMG_Load("img/menu/intro.jpg");
        texintro = SDL_CreateTextureFromSurface(screenRenderer, surintro);
        SDL_FreeSurface(surintro);

        surTutorial = IMG_Load("img/menu/tutorial.jpg");
        texTutorial = SDL_CreateTextureFromSurface(screenRenderer, surTutorial);
        SDL_FreeSurface(surTutorial);

    }

     //=====================Carrega sprites em memória PLAYER1===========================================
        for(int anim = 0; anim < 7; anim++){
            IMG_Init(IMG_INIT_PNG);
            vetAnim[anim] = IMG_Load(path);

            for(int con = 0; path[con+1]!='\0'; con++)
                cont = con;

            path[cont-3] = id[sub];
            sub++;
        }

        for(int anima = 0; anima < 7; anima++){
            textureAnim[anima] = SDL_CreateTextureFromSurface(screenRenderer, vetAnim[anima]);
            SDL_FreeSurface(vetAnim[anima]);
        }
        //====================================================================================
        //=====================Carrega sprites em memória PLAYER2===========================================
        sub = 0;
        for(int motion = 0; motion < 6; motion++){
            IMG_Init(IMG_INIT_PNG);
            vetMotion[motion] = IMG_Load(src);

            for(int con = 0; src[con+1]!='\0'; con++)
                cont = con;

            src[cont-3] = id[sub];
            sub++;
        }

        for(int animaP2 = 0; animaP2 < 6; animaP2++){
            textureMotion[animaP2] = SDL_CreateTextureFromSurface(screenRenderer, vetMotion[animaP2]);
            SDL_FreeSurface(vetMotion[animaP2]);
        }
        //====================================================================================
        //=====================Carrega sprites em memória Projetil============================
        sub = 0;
        for(int animaTiro = 0; animaTiro < 7; animaTiro++){
            IMG_Init(IMG_INIT_PNG);
            vetShoot[animaTiro] = IMG_Load(srcProjetil);

            for(int con = 0; srcProjetil[con+1]!='\0'; con++)
                cont = con;

            srcProjetil[cont-3] = id[sub];
            sub++;
        }

        for(int animaTiro = 0; animaTiro < 7; animaTiro++){
            textureShoot[animaTiro] = SDL_CreateTextureFromSurface(screenRenderer, vetShoot[animaTiro]);
            SDL_FreeSurface(vetShoot[animaTiro]);
        }
        //====================================================================================
        //=====================Carrega sprites em memória VIDA============================
        sub = 0;
        for(animVida = 0; animVida < 3; animVida++){
            IMG_Init(IMG_INIT_PNG);
            vetVidaP1[animVida] = IMG_Load(srcVida);

            for(int con = 0; srcVida[con+1]!='\0'; con++)
                cont = con;

            srcVida[cont-3] = id[sub];
            sub++;
        }

        for(int vida = 0; vida < 3; vida++){
            textureVidaP1[vida] = SDL_CreateTextureFromSurface(screenRenderer, vetVidaP1[vida]);
            SDL_FreeSurface(vetVidaP1[vida]);
        }
        //====================================================================================


    anim = 0;
    motion = 0;
    animaTiro = 0;
    animVida1 = 4;
    animVida2 = 4;

    //Menu (TELA INICIAL)==================================
    SDL_Rect r2 = {0, 0, 800, 600}; //menu
    SDL_RenderDrawRect(screenRenderer, &r2);

    SDL_Rect r3 = {0, 0, 800, 600}; //tutorial
    SDL_RenderDrawRect(screenRenderer, &r3);

    SDL_Rect r5 = {0, 0, 800, 600}; //creditos
    SDL_RenderDrawRect(screenRenderer, &r5);

    SDL_Rect r6 = {0, 0, 800, 600}; //introducao
    SDL_RenderDrawRect(screenRenderer, &r6);

    // Objetos & Personagens================================
    SDL_Rect matriz [LINHAS][COLUNAS];

    SDL_Rect fundo = {0, 0, WINDOWSIZE_X, WINDOWSIZE_Y};
    SDL_RenderDrawRect(screenRenderer, &fundo);

    SDL_Rect object = {100, 100, 200, 200};
    SDL_RenderDrawRect(screenRenderer, &object);

    SDL_Rect tiro1 = {30, 550, 10, 10};
    SDL_RenderDrawRect(screenRenderer,&tiro1);

    SDL_Rect tiro2 = {720, 550, 10, 10};
    SDL_RenderDrawRect(screenRenderer, &tiro2);

    SDL_Rect player1 = {10, 520, 75, 60};
    SDL_RenderDrawRect(screenRenderer, &player1);

    SDL_Rect player2 = {750, 520, 75, 60};
    SDL_RenderDrawRect(screenRenderer, &player2);

    SDL_Rect vidaP1 = {player1.x, player1.y, 20, 20};
    SDL_RenderDrawRect(screenRenderer, &vidaP1);

    SDL_Rect vidaP2 = {player2.x, player2.y, 40, 40};
    SDL_RenderDrawRect(screenRenderer, &vidaP2);

    //Matriz ================================================================
    //posiçao inical da matriz
    int pos_ini_y = 150;
    int pos_ini_x = 250;
    //pos = tamanho
    int pos = 30;

    for(i = 0; i < LINHAS; i++){
            for(j = 0; j < COLUNAS; j++){
                matriz[i][j].x =  (i*pos)+pos_ini_x;
                matriz[i][j].y =  (j*pos)+pos_ini_y;
                matriz[i][j].w = pos;
                matriz[i][j].h = pos;
            }
    }
//INICIO DO MENU
    SDL_RenderClear(screenRenderer);//desenha na tela a IMG da intro, primeira coisa q acontece quando rodamos o programa
    SDL_RenderCopy(screenRenderer, texintro, NULL, &r6);
    SDL_RenderPresent(screenRenderer);//atualiza para essa IMG aparecer
    cout<<"intro\n";//cout pra ter ctz a entrou a intro, aparece na tena de prompt
    SDL_Delay(1000);//delay pra janela da intro na pasar direto

    while(!fechaJogo){

        SDL_RenderClear(screenRenderer);
        SDL_RenderCopy(screenRenderer, texMenu, NULL, &r2);//desenha na tela a IMG do menu dps da intro
        SDL_RenderPresent(screenRenderer);//atualiza para essa IMG aparecer
        cout<<"menu\n";//cout pra ter ctz a entrou a intro, aparece na tena de prompt

        while( menu == 1 ){//REPETICAO DO MENU
           while(SDL_PollEvent(&menuJogo)){//ligando evento do menu

                if(menuJogo.type == SDL_KEYDOWN){//se for um evento de tecla pressionada
                    if(menuJogo.key.keysym.sym == SDLK_ESCAPE){//e se essa tecla for o ESC, o menu fecha e sai do jogo.
                        fechaJogo = 1;
                        menu = 0;//condicao pra sair do menu (!= 1)
                        lancamento = 0;
                        lancamento2 = 0;
                        JogoAtivo = 0;//condicao pra sair do jogo ativo (!= 1)
                    }//FECHA A CONDICAO DE FECHAR O JOGO COM O ESC DENTRO DA REPETICAO DO MENU
                }

                if(menuJogo.type == SDL_KEYDOWN)
                if(menuJogo.key.keysym.sym == SDLK_KP_ENTER || menuJogo.key.keysym.sym == SDLK_RETURN){//IR PARA O JOGO
                    cout<<"entrou no jogo\n";
                    menu += 1;
                    JogoAtivo = 1;
                }//FECHA A CONDICAO DE IR PARA O JOGO

                if(menuJogo.type == SDL_KEYDOWN)
                if(menuJogo.key.keysym.sym == SDLK_KP_1 || menuJogo.key.keysym.sym == SDLK_1){//IR PARA TUTORIAL
                    cout<<"tutorial\n";
                    SDL_RenderClear(screenRenderer);
                    SDL_RenderCopy(screenRenderer, texTutorial, NULL, &r3);
                    SDL_RenderPresent(screenRenderer);
                }//FECHA O IR PARA TUTORIAL

                if(menuJogo.type == SDL_KEYDOWN)
                if(menuJogo.key.keysym.sym == SDLK_2 || menuJogo.key.keysym.sym == SDLK_KP_2){//VOLTAR PARA O MENU
                    cout<<"voltou para o menu\n";
                    SDL_RenderClear(screenRenderer);
                    SDL_RenderCopy(screenRenderer, texMenu, NULL, &r2);
                    SDL_RenderPresent(screenRenderer);
                    menu += 0;
                }//FECHA VOLTAR PARA MENU

                if(menuJogo.type == SDL_KEYDOWN)
                if(menuJogo.key.keysym.sym == SDLK_3 || menuJogo.key.keysym.sym == SDLK_KP_3){//IR PARA O CREDITOS
                    cout<<"creditos\n";
                    SDL_RenderClear(screenRenderer);
                    SDL_RenderCopy(screenRenderer, texCreditos, NULL, &r5);
                    SDL_RenderPresent(screenRenderer);
                }//FECHA IR PARA O CREDITOS
          }
        }

        //INICIO DO GAME
        while ( JogoAtivo ){

            while (SDL_PollEvent(&evento) ){
                if( evento.type == SDL_QUIT)
                        JogoAtivo = 0;

                if(evento.type == SDL_KEYDOWN){
                    if(evento.key.keysym.sym == SDLK_ESCAPE)
                        JogoAtivo = 0; menu = 1;lancamento = 0; lancamento2 = 0;
                }

                switch (estado){
                    //MOVIMENTO PLAYER1-----------------------------------------------
                    //seta para esquerda   ( 1 )
                    case(0)://Movimento livre
                        if ( evento.type == SDL_KEYDOWN) {
                            if ( evento.key.keysym.sym == SDLK_a)
                                teclapressionada1 = 1;
                        }
                            if (evento.type == SDL_KEYUP)
                                teclapressionada1 = 0;

                            // SETA PARA direita ( 2 )
                            if ( evento.type == SDL_KEYDOWN) {
                                if ( evento.key.keysym.sym == SDLK_d)
                                    teclapressionada1 = 2;
                            }
                            if ( evento.type == SDL_KEYUP)
                                teclapressionada1 = 0;

                            if ( evento.type == SDL_KEYDOWN){
                                if ( evento.key.keysym.sym == SDLK_RETURN){
                                    cout<<"Player1, mantenha ESPACO pressionado para adicionar velocidade\n";
                                    estado+=1;
                                }
                            }

                        break;

                    case(1)://Adição de velocidade player1
                        if ( evento.type == SDL_KEYDOWN){
                            if ( evento.key.keysym.sym == SDLK_SPACE && !lancamento){
                            forca+=10;

                            if(forca == 200)
                                forca = 0;

                            cout<<"Forca: "<<forca<<endl;
                            }
                        }

                         if (evento.type == SDL_KEYUP&&!lancamento ){
                            if ( evento.key.keysym.sym == SDLK_SPACE && !lancamento)
                                v = forca;
                         }

                         if ( evento.type == SDL_KEYDOWN){
                            if ( evento.key.keysym.sym == SDLK_RETURN){
                                cout<<"Player1, selecione o angulo\n";
                                forca = 0;
                                estado+=1;
                            }
                         }
                        break;

                    case(2)://Set Angulo & Lançamento player1
                        if(evento.type == SDL_KEYDOWN){
                            if(evento.key.keysym.sym == SDLK_w  && dir < 90){
                                dir+=1;
                                cout<<"Angulo: "<<dir<<endl;
                            }
                            else if(evento.key.keysym.sym == SDLK_s  && dir > 0){
                                dir-=1;
                                cout<<"Angulo: "<<dir<<endl;
                            }
                        }

                        if(dir >= 90)
                            dir = 0;

                        if ( evento.type == SDL_KEYDOWN){
                            if ( evento.key.keysym.sym == SDLK_RETURN){
                                cout<<"Lancar!!\n";
                                angulo = dir;
                                lancamento = 1;
                                dir = 0;
                                estado+=1;
                            }
                        }
                        break;
                    //------------------------------------------------------------
                    //MOVIMENTO PLAYER2-----------------------------------------------
                    case (3):
                        // SETA PARA direita ( 1 )
                        if ( evento.type == SDL_KEYDOWN) {
                            if ( evento.key.keysym.sym == SDLK_RIGHT)
                                teclapressionada2 = 1;
                        }
                            if (evento.type == SDL_KEYUP)
                                teclapressionada2 = 0;

                            // SETA PARA Esquerda ( 2 )
                            if ( evento.type == SDL_KEYDOWN) {
                                if ( evento.key.keysym.sym == SDLK_LEFT)
                                    teclapressionada2 = 2;
                            }
                            if ( evento.type == SDL_KEYUP) {
                                teclapressionada2 = 0;
                            }

                           if ( evento.type == SDL_KEYDOWN){
                                if ( evento.key.keysym.sym == SDLK_RETURN){
                                    cout<<"Playe2, mantenha ESPACO pressionado para adicionar velocidade\n";
                                    estado+=1;
                                }
                            }
                            break;

                    case (4): // Adição de velocidade player2
                        if ( evento.type == SDL_KEYDOWN){
                            if ( evento.key.keysym.sym == SDLK_SPACE && !lancamento2){
                            forca+=10;

                            if(forca == 200)
                                forca = 0;

                            cout<<"Forca: "<<forca<<endl;
                            }
                        }

                         if (evento.type == SDL_KEYUP&&!lancamento2 ){
                            if ( evento.key.keysym.sym == SDLK_SPACE && !lancamento2)
                                v2 = forca;
                         }

                         if ( evento.type == SDL_KEYDOWN){
                            if ( evento.key.keysym.sym == SDLK_RETURN){
                                cout<<"Player2, selecione o angulo\n";
                                forca = 0;
                                estado+=1;
                            }
                         }
                        break;

                    case(5)://Set Angulo & Lançamento player2
                        if(evento.type == SDL_KEYDOWN){
                            if(evento.key.keysym.sym == SDLK_SPACE  && dir < 90){
                                dir+=1;
                                cout<<"Angulo: "<<dir<<endl;
                            }
                        }

                        if(dir >= 90)
                            dir = 0;

                        if ( evento.type == SDL_KEYDOWN){
                            if ( evento.key.keysym.sym == SDLK_RETURN){
                                cout<<"Lancar!!\n";
                                angulo2 = dir;
                                lancamento2 = 1;
                                dir = 0;
                                estado = 0;
                                cout<<"Player1!\n"<<"Ache uma posicao para o desparo\n";
                            }
                        }
                        break;

                    case(6):
                        SDL_RenderClear(screenRenderer);
                        SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                        SDL_RenderPresent(screenRenderer);
                        cout <<"-----------------------------------------------------------------\n";
                        cout <<"|             R A N K I N G   D E   V I T O R I A S             |\n";
                        cout <<"-----------------------------------------------------------------\n\n";

                        // lendo o arquivo por tipos
                        cout << "NICK ATE 3 LETRAS: \n";

                        cout <<"Insira o nick name do Player 1: ";
                        cin >> novo.aux;

                        cout <<"Pontos: ";
                        cin >> novo.ponto;
                        cout<<endl;

                        cout <<"Insira o nick name do Player 2: ";
                        cin >> compara.aux;

                        cout <<"Pontos: ";
                        cin >> compara.ponto;
                        cout<<endl;

                        if (compara.ponto == novo.ponto){
                            arquivo << "Player 1 e Player 2 empataram!" <<endl;
                            arquivo.close();
                        }

                        if (compara.ponto > novo.ponto){
                            arquivo << "Nick Name: " << compara.aux <<" - Pontos "<< compara.ponto<< '\0' <<endl;
                            arquivo.close();
                        }
                        else{
                            arquivo << "Nick Name: " << novo.aux <<" - Pontos "<< novo.ponto<< '\0' <<endl;
                            arquivo.close();
                        }

                        ifstream in (ranking);

                        if( !in ){
                            // erro no processo
                            cout << "O arquivo nao pode ser aberto!\n";
                            return 1; //erro
                        }//a funзгo good checa se o estado da stream estah bom  para operacao de E/S

                        if (novo.ponto < compara.ponto){
                            compara.ponto = novo.ponto;
                            //compara.aux = novo.aux;
                        }

                        while( in.good() ){
                            // in serб zero quando eof (fim do arquivo) for encontrado
                            letra = in.get();
                            cout << letra;
                        }
                        // fecha o arquivo
                        in.close();

                        break;
                    }
                }
                //------------------------------------------------------------



        // REALIZAR OS CALCULOS (IA, MOVIMENTOS, COLISÃO)

        //CONTROLE PLAYER1---------------------------------------------------------
            //Movimento ESQUERDA-----------------------------------------------
            if ( teclapressionada1 == 2 && !stop && player1.x + player1.w < WINDOWSIZE_X){
                player1.x+=10;
                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }
            //Colisão------------------------------------------------------------
            if( teclapressionada1 == 2 && !stop && player1.x + player1.w >= WINDOWSIZE_X){
                player1.x-=10;
                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }

            //Movimento DIREITA-----------------------------------------------
            if( teclapressionada1 == 1 && !stop && player1.x + player1.w < WINDOWSIZE_X){
                player1.x-=10;
                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }
            //Colisao----------------------------------------------------------
            if(player1.x <= 0 && !stop){
                player1.x+=10;
                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }
            //COLISAO DO PLAYER1 COM MATRIZ--------------------------------------
            for(i = 0; i < LINHAS; i++){
                for(j = 0; j < COLUNAS; j++){
                     if( matriz[i][j].y+matriz[i][j].h > player1.y
                        && player1.y+player1.h > matriz[i][j].y
                        && matriz[i][j].x+matriz[i][j].w > player1.x
                        && player1.x+player1.w > matriz[i][j].x){
                        player1.x-=10;
                    }
                }
            }
            //Lançamento Oblicuo------------------------------------------------
            if ( !lancamento ){
                stop = 0;
                tiro1.y = player1.y + 5;
                tiro1.x = player1.x + 65;
                tempo1 = 0;
                angulo = 0;

                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }

            if ( lancamento ){
                SDL_Delay(5);
                stop = 1;

                float radianos = (angulo * M_PI)/180;
                float c = cos(radianos);
                float s = sin(radianos);

                float Vx= v* c*tempo1;
                float Vy= v* s*tempo1 - (9.81*(tempo1*tempo1))/2.0;

                tiro1.x = player1.x + 65 + (int)Vx;
                tiro1.y = player1.y + 5 - (int)Vy;
                cout << "X: " << tiro1.x << " Y: " << tiro1.y <<endl;

                tempo1 += 0.1;

                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }

            //colisao tiro1-----------------------------------------
            //COM O SOLO
            if(0 >= -1*(tiro1.y+tiro1.h) >= 590 || 0 >= tiro1.x+tiro1.w >= 770 )
                lancamento = 0; //cout<<"Player2!\n"<<"Ache uma posicao para o desparo\n";

                //COM O PLAYER2
            if( player2.y+player2.h > tiro1.y
                && tiro1.y+tiro1.h > player2.y
                && player2.x+player2.w > tiro1.x
                && tiro1.x+tiro1.w > player2.x){
                animVida2-=1;
                cout<<"Colidiu!\n"<<"Player2!\n"<<"Ache uma posicao para o desparo\n";


                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
                lancamento = 0;
                estado = 0;
                }
                //===COM MATRIZ=======================
                for(i = 0; i < LINHAS; i++){
                    for(j = 0; j < COLUNAS; j++){
                        if( matriz[i][j].y+matriz[i][j].h > tiro1.y
                            && tiro1.y+tiro2.h > matriz[i][j].y
                            && matriz[i][j].x+matriz[i][j].w > tiro1.x
                            && tiro1.x+tiro1.w > matriz[i][j].x){
                            cout<<"colidiu!\n"<<"Player2!\n"<<"Ache uma posicao para o desparo\n";;
                            matriz[i][j].x = -200;
                            lancamento = 0;
                        }
                    }
                }
            //=================================

        //CONTROLE PLAYER2---------------------------------------------------------
            //Movimento ESQUERDA-----------------------------------------------
            if ( teclapressionada2 == 2 && !stop2 && player2.x + player2.w < WINDOWSIZE_X){
                player2.x-=10;
                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }
            //Colisão------------------------------------------------------------
            if(player2.x <= 0 && !stop2){
                player2.x+=15;
                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }
            //Movimento DIREITA-----------------------------------------------
            if( teclapressionada2 == 1 && !stop2 && player2.x + player2.w < WINDOWSIZE_X){
                player2.x+=10;
                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }
            //Colisao----------------------------------------------------------
            if( teclapressionada2 == 2 && !stop2 && player2.x + player2.w >= WINDOWSIZE_X){
                player2.x-=15;
                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }
            //COLISAO DO PLAYER2 COM MATRIZ--------------------------------------
            for(i = 0; i < LINHAS; i++){
                for(j = 0; j < COLUNAS; j++){
                     if( matriz[i][j].y+matriz[i][j].h > player2.y
                        && player2.y+player2.h > matriz[i][j].y
                        && matriz[i][j].x+matriz[i][j].w > player2.x
                        && player2.x+player2.w > matriz[i][j].x){
                        player2.x+=10;
                    }
                }
            }
            //Lançamento Oblicuo------------------------------------------------
            if ( !lancamento2 ){
                stop2 = 0;
                tiro2.y = player2.y + 8;
                tiro2.x = player2.x - 8;
                tempo2 = 0;
                angulo2 = 0;

                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }

            if ( lancamento2 ){

                float radianos = (angulo2 * M_PI)/180;
                float c = cos(radianos);
                float s = sin(radianos);

                float Vx= v2* c*tempo2;
                float Vy= v2* s*tempo2 - (9.81*(tempo2*tempo2))/2.0;

                tiro2.x = player2.x - 8 - (int)Vx;
                tiro2.y = player2.y + 8 - (int)Vy;
                cout << "X: " << tiro2.x << " Y: " << tiro2.y <<endl;

                tempo2 += 0.1;

                SDL_RenderClear(screenRenderer);
                SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro1);
                SDL_RenderCopy(screenRenderer, textureShoot[animaTiro], NULL, &tiro2);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida1], NULL, &vidaP1);
                SDL_RenderCopy(screenRenderer, textureVidaP1[animVida2], NULL, &vidaP2);
                SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[LINHAS][COLUNAS]);
                SDL_RenderCopy(screenRenderer, textureAnim[anim], NULL, &player1);
                SDL_RenderCopy(screenRenderer, textureMotion[motion], NULL, &player2);
                SDL_RenderPresent(screenRenderer);
            }

            //colisao tiro2-----------------------------------------
            //COM O SOLO
            if( (tiro2.y)* -1 >= 590 || tiro2.x < 0)
                lancamento2 = 0;
            //COM O PLAYER1
            if( player1.y+player1.h > tiro2.y
               && tiro2.y+tiro2.h > player1.y
               && player1.x+player1.w > tiro2.x
               && tiro2.x+tiro2.w > player1.x){

                animVida1-=1;
                cout<<"Colidiu!\n"<<"Player2!\n"<<"Ache uma posicao para o desparo\n";
                cout<<"Colidiu!\n";
                lancamento2 = 0;
            }
            //===COM MATRIZ=======================
            for(i = 0; i < LINHAS; i++){
                for(j = 0; j < COLUNAS; j++){
                    if( matriz[i][j].y+matriz[i][j].h > tiro2.y
                        && tiro2.y+tiro2.h > matriz[i][j].y
                        && matriz[i][j].x+matriz[i][j].w > tiro2.x
                        && tiro2.x+tiro1.w > matriz[i][j].x){
                        cout<<"colidiu!\n";
                        matriz[i][j].x = -200;
                        lancamento2 = 0;
                    }
                }
            }
            //=================================

        // atualiza a janela para aparecer
            for(i = 0; i < LINHAS; i++){
                for(j = 0; j < COLUNAS; j++){
                    SDL_RenderCopy(screenRenderer, texture_Block, NULL, &matriz[i][j]);
                }
            }

            //SDL_RenderCopy(screenRenderer, textureBackground, NULL, &fundo);

            if(anim >=5)
                anim = 0;
            else
                anim+=1;

            if(motion >=5)
                motion = 0;
            else
                motion+=1;

            if(animVida1 <= 0)
                estado = 6;

            /*
            if(animaTiro >= 7)
                animaTiro = 0;
            else
                animaTiro+=1;//*/

            SDL_RenderPresent(screenRenderer);
            SDL_Delay(50);

        }
    }

    // encerra a sdl
    SDL_DestroyTexture(texture_person1);
    SDL_DestroyTexture(texture_Block);
    SDL_DestroyTexture(texture_shoot1);

    SDL_FreeSurface(block);
    SDL_FreeSurface(person1);
    SDL_FreeSurface(shoot);

    SDL_DestroyRenderer(screenRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
