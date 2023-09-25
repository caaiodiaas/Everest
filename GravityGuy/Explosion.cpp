/**********************************************************************************
// Explosion (Código Fonte)
//
// Criação:     20 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para o jogador
//
**********************************************************************************/

#include "Explosion.h"
#include "GravityGuy.h"
#include "Platform.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(int posXnew, int posYnew, Scene * s)
{
    tileset = new TileSet("Resources/GravityGuy.png", 32, 48, 5, 10);
    anim = new Animation(tileset, 0.12f, false);

    uint normal[4] = { 1,2,3,4 };

    anim->Add(0, normal, 4);


    posX = posXnew;
    posY = posYnew;
    // posição inicial
    MoveTo(posX, posY, Layer::FRONT);

    scene = s;

}

// ---------------------------------------------------------------------------------

Explosion::~Explosion()
{
    delete anim;
    delete tileset;
}

// ---------------------------------------------------------------------------------

void Explosion::Reset()
{
    MoveTo(posX, posY, Layer::FRONT);
}


// ---------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------

void Explosion::Update()
{
    anim->NextFrame();
    if (anim->Inactive())
        scene->Delete();
}

// ---------------------------------------------------------------------------------