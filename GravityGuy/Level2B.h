#pragma once
/**********************************************************************************
// Level2B (Arquivo de Cabe�alho)
//
// Cria��o:     27 Set 2021
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   N�vel 2 do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_LEVEL2B_H_
#define _GRAVITYGUY_LEVEL2B_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Strawberry.h"
#include "Background.h"
#include "Font.h"
#include "Explosion.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

class Level2B : public Game
{
private:
    Background* backg = nullptr;   // pano de fundo animado
    stringstream deathCount;              // texto tempor�rio
    stringstream strawberryCount;              // texto tempor�rio
    Strawberry* strawberry = nullptr;
    Explosion* explosion = nullptr;
public:
    static Scene* scene;           // cena do n�vel
    static Font* font;            // fonte para texto

    void Init();                    // inicializa��o do n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza��o do n�vel
};

// -----------------------------------------------------------------------------

#endif