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
#include "Everest.h"
#include "Level1.h"
#include "Platform.h"

// ---------------------------------------------------------------------------------

Spike::Spike(float posX, float posY, uint spikeType, Color tint) : color(tint)
{
    switch (spikeType)
    {
    case LARGESPIKE:  spike = new Sprite("Resources/LongSpikeHorizontal.png"); type = LARGESPIKE; break;
    case MEDIUMSPIKE: spike = new Sprite("Resources/MediumSpikeHorizontal.png"); type = MEDIUMSPIKE; break;
    case SMALLSPIKE:  spike = new Sprite("Resources/SmallSpikeHorizontal.png"); type = SMALLSPIKE; break;
    case LARGESPIKEL:  spike = new Sprite("Resources/LongSpikeVerticalLeft.png"); type = LARGESPIKEL; break;
    case MEDIUMSPIKEL: spike = new Sprite("Resources/MediumSpikeVerticalLeft.png"); type = MEDIUMSPIKEL; break;
    case SMALLSPIKEL:  spike = new Sprite("Resources/SmallSpikeVerticalLeft.png"); type = SMALLSPIKEL; break;
    case LARGESPIKER:  spike = new Sprite("Resources/LongSpikeVerticalRight.png"); type = LARGESPIKER; break;
    case MEDIUMSPIKER: spike = new Sprite("Resources/MediumSpikeVerticalRight.png"); type = MEDIUMSPIKER; break;
    case SMALLSPIKER:  spike = new Sprite("Resources/SmallSpikeVerticalRight.png"); type = SMALLSPIKER; break;
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