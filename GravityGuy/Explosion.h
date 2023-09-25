#pragma once
/**********************************************************************************
// Explosion (Arquivo de Cabe�alho)
//
// Cria��o:     20 Abr 2012
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para o jogador
//
**********************************************************************************/

#ifndef _GRAVITYGUY_EXPLOSION_H_
#define _GRAVITYGUY_EXPLOSION_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites
#include "Player.h"                  
#include "Scene.h"

// ------------------------------------------------------------------------------


class Explosion : public Object
{
private:
    TileSet* tileset;                // folha de sprites do personagem
    Animation* anim;                   // anima��o do personagem
    Scene* scene;
    int posX;
    int posY;
public:

    boolean following;

    Explosion(int posX, int posY, Scene * scene);
    ~Explosion();                          // destrutor

    void Update();                      // atualiza��o do objeto
    void Reset();
    void Draw();                        // desenho do objeto
};

inline void Explosion::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif