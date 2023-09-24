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

#include "Platform.h"
#include "Player.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType, Color tint) : color(tint)
{
    switch (platType)
    {
    case SMALL:  platform = new Sprite("Resources/SmallGray.png"); type = SMALL; break;
    case MEDIUM: platform = new Sprite("Resources/MediumGray.png"); type = MEDIUM; break;
    case LARGE:  platform = new Sprite("Resources/LongGray.png"); type = LARGE; break;
    case FINISH: platform = new Sprite("Resources/LongGrayV.png"); type = FINISH; break;
    }


        BBox(new Rect(-platform->Width() / 2.0f,
            -platform->Height() / 2.0f,
            platform->Width() / 2.0f,
            platform->Height() / 2.0f));


    MoveTo(posX, posY, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
    delete platform;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{

}

// -------------------------------------------------------------------------------

void Platform::OnCollision(Object* obj)
{
    Player* player = (Player*)obj;

    // Colisões eixo X

    //Plataforma na esquerda
    if (player->X() + 5 < x - platform->Width() / 2) {
        player->MoveTo(x - platform->Width() / 2 - 15, player->Y(), Layer::MIDDLE);
        if (player->dashing)
        {
            player->velX = 0;
        }
        if (window->KeyDown(VK_RIGHT) && player->hasSideJump && !player->jumping)
        {
            player->Translate(0, -150 * gameTime);
            player->sideJumping = false;
            if (window->KeyPress(VK_UP) && !player->dashing) {
                player->jumping = false;
                player->MoveTo(x - platform->Width() / 2 - 25, player->Y(), Layer::MIDDLE);
                player->sideJumping = true;
                player->sideJumpSide = 1;
                player->sideJumpTimer->Start();
                player->hasSideJump = false;
            }
        }


    }
    else

        //Plataforma na direita
        if (player->X() - 5 > x + platform->Width() / 2) {
            player->MoveTo(x + platform->Width() / 2 + 15, player->Y(), Layer::MIDDLE);
            if (player->dashing)
            {
                player->velX = 0;
            }
            if (window->KeyDown(VK_LEFT) && player->hasSideJump && !player->jumping)
            {
                player->Translate(0,-150*gameTime);
                player->sideJumping = false;
                if (window->KeyPress(VK_UP) && !player->dashing) {
                    player->jumping = false;
                    player->MoveTo(x + platform->Width() / 2 + 25, player->Y(), Layer::MIDDLE);
                    player->sideJumping = true;
                    player->sideJumpSide = 0;
                    player->sideJumpTimer->Start();
                    player->hasSideJump = false;
                }
            }

        }else
        // Colisões eixo Y
            //Plataforma abaixo
            if (player->Y() < y - platform->Height() / 2) {
                player->MoveTo(player->X(), y - platform->Height() / 2 - 20, Layer::MIDDLE);

                if (player->X()  > x - platform->Width() / 2 && player->X() < x + platform->Width() / 2 || player->X()  < x + platform->Width() / 2 && player->X()  > x - platform->Width() / 2)
                {
                    if (!player->dashing) {
                        player->hasDash = true;
                    }
                    player->hasSideJump = true;
                }

                if (player->dashing && player->dashSide == 7 || player->dashSide == 5)
                {
                    if (window->KeyDown(VK_SPACE)) {
                        player->MoveTo(player->X(), y - platform->Height() / 2 - 25, Layer::MIDDLE);
                        player->hasDash = true;
                        player->waveDashing = true;
                    }
                       

                }else if (window->KeyPress(VK_UP)) {
                    if (player->X() > x - platform->Width() / 2 && player->X() < x + platform->Width() / 2 || player->X() < x + platform->Width() / 2 && player->X() > x - platform->Width() / 2)
                    {
                        player->MoveTo(player->X(), y - platform->Height() / 2 - 25, Layer::MIDDLE);
                        player->jumping = true;
                        player->jumpTimer->Start();
                    }

                }
            }else
            //Plataforma acima
            if (player->Y() > y + platform->Height() / 2) {
                player->MoveTo(player->X(), y + platform->Height() / 2 + 25, Layer::MIDDLE);
                player->jumping = false;
            }
        


        


}