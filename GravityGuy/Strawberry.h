#pragma once
/**********************************************************************************
// Strawberry (Arquivo de Cabeçalho)
//
// Criação:     20 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para o jogador
//
**********************************************************************************/

#ifndef _GRAVITYGUY_STRAWBERRY_H_
#define _GRAVITYGUY_STRAWBERRY_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites
#include "Player.h"                  

// ------------------------------------------------------------------------------


class Strawberry : public Object
{
private:
    TileSet* tileset;                // folha de sprites do personagem
    Animation* anim;                   // animação do personagem
    Player* player;
    int posX;
    int posY;
public:

    boolean following;

    Strawberry(int posX, int posY);
    ~Strawberry();                          // destrutor

    void OnCollision(Object* obj);     // resolução da colisão
    void Update();                      // atualização do objeto
    void Reset();                       
    void Draw();                        // desenho do objeto
};

inline void Strawberry::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif