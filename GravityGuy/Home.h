/**********************************************************************************
// Home (Arquivo de Cabe�alho)
//
// Cria��o:     14 Fev 2013
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Tela de abertura do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_HOME_H_
#define _GRAVITYGUY_HOME_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Mouse.h"
#include "Item.h"
#include "Scene.h"

// ------------------------------------------------------------------------------

enum MenuID { INICIAR, SAIR, TUTORIALKEY};

enum TutorialStatus {ACTIVE, INACTIVE};

// ------------------------------------------------------------------------------
class Home : public Game
{
private:
    static const int MaxItens = 3;
    Scene* scene = nullptr;
    TileSet* backg = nullptr;       // pano de fundo
    TileSet* tileset = nullptr;    // tileset da anima��o
    Animation* anim = nullptr;     // anima��o do menu
    Mouse* mouse = nullptr;
    bool start;
    bool startB;
    bool exists;
    TileSet* tutorial = nullptr;
    Animation* Tutorialanim = nullptr;

    Item* menu[MaxItens] = { 0 };

public:
    void Init();                    // inicia n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza n�vel
};

// -----------------------------------------------------------------------------

#endif