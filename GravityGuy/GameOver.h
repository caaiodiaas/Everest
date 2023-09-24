/**********************************************************************************
// GameOver (Arquivo de Cabe�alho)
// 
// Cria��o:     14 Fev 2013
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Fim do jogo
//              
**********************************************************************************/

#ifndef _GRAVITYGUY_GAMEOVER_H_
#define _GRAVITYGUY_GAMEOVER_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"
#include "Font.h"
#include <sstream>
using std::stringstream;
// ------------------------------------------------------------------------------

class GameOver : public Game
{
private:
    Sprite * title = nullptr;       // tela de fim
    stringstream deathCount;              // texto tempor�rio
    stringstream strawberryCount;              // texto tempor�rio

public:
    static Font* font;            // fonte para texto
    void Init();                    // inicializa��o do n�vel
    void Update();                  // l�gica da tela de fim
    void Draw();                    // desenho da tela
    void Finalize();                // finaliza��o do n�vel
};

// ------------------------------------------------------------------------------

#endif