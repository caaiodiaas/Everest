/**********************************************************************************
// Strawberry (Código Fonte)
//
// Criação:     20 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para o jogador
//
**********************************************************************************/

#include "Strawberry.h"
#include "GravityGuy.h"
#include "Platform.h"

// ---------------------------------------------------------------------------------

Strawberry::Strawberry(int posXnew, int posYnew)
{
    tileset = new TileSet("Resources/strawberry.png", 32, 45, 12, 12);
    anim = new Animation(tileset, 0.120f, true);


    uint normal[12] = { 0,1,2,3,4,5,6,7,8,9,10,11};

    anim->Add(0, normal, 12);

    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));

    posX = posXnew;
    posY = posYnew;
    // posição inicial
    MoveTo(posX, posY, Layer::FRONT);

    type = 1;
}

// ---------------------------------------------------------------------------------

Strawberry::~Strawberry()
{
    delete anim;
    delete tileset;
}

// ---------------------------------------------------------------------------------

void Strawberry::Reset()
{
    MoveTo(posX, posY, Layer::FRONT);
    following = false;
}


// ---------------------------------------------------------------------------------

void Strawberry::OnCollision(Object* obj)
{
    if (obj->Type() == 0) {
        if (!following)
        {
            GravityGuy::audio->Play(STRAWBERRY);
        }
        player = (Player*)obj;
        following = true;
    }
}

// ---------------------------------------------------------------------------------

void Strawberry::Update()
{
    if (following)
    {
        Translate((player->X()-25 - x) * 2*gameTime,(player->Y()-10 - y)  * 2*gameTime);
    }

    anim->Select(0);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------