#pragma once
/**********************************************************************************
// Level3 (Arquivo de Cabeçalho)
//
// Criação:     27 Set 2021
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Nível 2 do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_LEVEL3_H_
#define _GRAVITYGUY_LEVEL3_H_

// ------------------------------------------------------------------------------
// Inclusões

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

class Level3 : public Game
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