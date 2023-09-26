/**********************************************************************************
// Spike (Arquivo de Cabe�alho)
//
// Cria��o:     21 Abr 2012
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Plataformas do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_SPIKE_H_
#define _GRAVITYGUY_SPIKE_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos espec�ficos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites


enum SPIKETYPES { LARGESPIKE, MEDIUMSPIKE, SMALLSPIKE, LARGESPIKEL, MEDIUMSPIKEL, SMALLSPIKEL, LARGESPIKER, MEDIUMSPIKER, SMALLSPIKER};
// ---------------------------------------------------------------------------------

class Spike : public Object
{
private:
    Sprite* spike = nullptr;            // sprite da plataforma
    Color color;                            // cor da plataforma

public:
    Spike(float posX, float posY,
        uint spikeType,
        Color tint);                   // construtor    
    ~Spike();                            // destrutor

    void Update();                          // atualiza��o do objeto
    void Draw();                            // desenho do objeto
    void OnCollision(Object* obj);
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Spike::Draw()
{
    spike->Draw(x, y, z, 1.0f, 0.0f, color);
}

// ---------------------------------------------------------------------------------

#endif#pragma once
