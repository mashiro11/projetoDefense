#include <stdio.h>

#include "../include/Game.h"
#include "../include/TitleState.h"
#ifndef GAME_WIDTH
    #define GAME_WIDTH 1024
    #define GAME_HEIGTH 600
#endif // GAME_WIDTH
int main(int argc, char** argv){
    Game novoJogo("Jogo teste", GAME_WIDTH, GAME_HEIGTH);
    //novoJogo.Push(new TitleState);
    novoJogo.Push(new StageState);
    novoJogo.Run();
    return 0;
}
