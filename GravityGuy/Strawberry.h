#pragma once
/**********************************************************************************
// Strawberry (Arquivo de Cabe�alho)
//
// Cria��o:     20 Abr 2012
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para o jogador
//
**********************************************************************************/

#ifndef _GRAVITYGUY_STRAWBERRY_H_
#define _GRAVITYGUY_STRAWBERRY_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites
#include "Player.h"                  

// ------------------------------------------------------------------------------


class Strawberry : public Object
{
private:
    TileSet* tileset;                // folha de sprites do personagem
    Animation* anim;                   // anima��o do personagem
    Player* player;
    int posX;
    int posY;
public:

    boolean following;

    Strawberry(int posX, int posY);
    ~Strawberry();                          // destrutor

    void OnCollision(Object* obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o do objeto
    void Reset();                       
    void Draw();                        // desenho do objeto
};

inline void Strawberry::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif