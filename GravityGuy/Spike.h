/**********************************************************************************
// Spike (Arquivo de Cabeçalho)
//
// Criação:     21 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_SPIKE_H_
#define _GRAVITYGUY_SPIKE_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
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

    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
    void OnCollision(Object* obj);
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Spike::Draw()
{
    spike->Draw(x, y, z, 1.0f, 0.0f, color);
}

// ---------------------------------------------------------------------------------

#endif#pragma once
