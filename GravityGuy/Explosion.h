#pragma once
/**********************************************************************************
// Explosion (Arquivo de Cabeçalho)
//
// Criação:     20 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para o jogador
//
**********************************************************************************/

#ifndef _GRAVITYGUY_EXPLOSION_H_
#define _GRAVITYGUY_EXPLOSION_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites
#include "Player.h"                  
#include "Scene.h"

// ------------------------------------------------------------------------------


class Explosion : public Object
{
private:
    TileSet* tileset;                // folha de sprites do personagem
    Animation* anim;                   // animação do personagem
    Scene* scene;
    int posX;
    int posY;
public:

    boolean following;

    Explosion(int posX, int posY, Scene * scene);
    ~Explosion();                          // destrutor

    void Update();                      // atualização do objeto
    void Reset();
    void Draw();                        // desenho do objeto
};

inline void Explosion::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif