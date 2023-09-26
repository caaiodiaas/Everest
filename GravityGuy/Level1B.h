#pragma once
/**********************************************************************************
// Level1B (Arquivo de Cabeçalho)
//
// Criação:     14 Fev 2013
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Nível 1 do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_LEVEL1B_H_
#define _GRAVITYGUY_LEVEL1B_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Strawberry.h"
#include "Background.h"
#include "Font.h"
#include <sstream>
#include "Explosion.h"
using std::stringstream;

// ------------------------------------------------------------------------------

class Level1B : public Game
{
private:
    Background* backg = nullptr;   // pano de fundo animado
    stringstream deathCount;              // texto temporário
    stringstream strawberryCount;              // texto temporário
    Strawberry* strawberry = nullptr;
    Explosion* explosion = nullptr;

public:
    static Scene* scene;           // cena do nível
    static Font* font;            // fonte para texto

    void Init();                    // inicialização do nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finalização do nível
};

// -----------------------------------------------------------------------------

#endif