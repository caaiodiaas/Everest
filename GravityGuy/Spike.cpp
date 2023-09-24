/**********************************************************************************
// Platform (Código Fonte)
//
// Criação:     21 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#include "Spike.h"
#include "Player.h"
#include "GravityGuy.h"
#include "Level1.h"
#include "Platform.h"

// ---------------------------------------------------------------------------------

Spike::Spike(float posX, float posY, uint spikeType, Color tint) : color(tint)
{
    switch (spikeType)
    {
    case SMALL:  spike = new Sprite("Resources/Finish.png"); type = SMALL; break;
    case MEDIUM: spike = new Sprite("Resources/Finish.png"); type = MEDIUM; break;
    case LARGE:  spike = new Sprite("Resources/Finish.png"); type = LARGE; break;
    case FINISH: spike = new Sprite("Resources/Finish.png"); type = FINISH; break;
    }


    BBox(new Rect(-spike->Width() / 2.0f,
        -spike->Height() / 2.0f,
        spike->Width() / 2.0f,
        spike->Height() / 2.0f));


    MoveTo(posX, posY, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Spike::~Spike()
{
    delete spike;
}

// -------------------------------------------------------------------------------

void Spike::Update()
{

}

// -------------------------------------------------------------------------------

void Spike::OnCollision(Object* obj)
{
    if (obj->Type() == 0)
    {
        Player* player = (Player*)obj;
        player->isDead = true;
    }
}