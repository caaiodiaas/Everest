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


        if ((player->X() + 10 <= x + platform->Width() / 2) || (player->X() - 10 >= x - platform->Width() / 2)) {
            if (player->Y() + 20 < y - platform->Height() / 2) {
                player->MoveTo(player->X(), player->Y() - 1, Layer::MIDDLE);

                if (player->X() + 10 > x - platform->Width() / 2 && player->X() + 10 < x + platform->Width() / 2 || player->X() - 10 < x + platform->Width() / 2 && player->X() - 10 > x - platform->Width() / 2)
                {
                    if (!player->dashing) {
                        player->hasDash = true;
                    }
                    player->hasSideJump = true;
                }

                if (player->dashing && player->dashSide == 7 || player->dashSide == 5)
                {
                    if (window->KeyDown(VK_SPACE))
                        player->hasDash = true;
                        player->waveDashing = true;

                }else if (window->KeyPress(VK_UP)) {
                    if (player->X() + 10 > x - platform->Width() / 2 && player->X() + 10 < x + platform->Width() / 2 || player->X() - 10 < x + platform->Width() / 2 && player->X() - 10 > x - platform->Width() / 2)
                    {
                        player->jumping = true;
                        player->jumpTimer->Start();
                    }

                }
            }
            if (player->Y() - 20 >= y + platform->Height() / 2) {
                player->MoveTo(player->X(), player->Y() + 1, Layer::MIDDLE);
                player->jumping = false;
            }
        }

        if ((player->Y() + 10 <= y + platform->Height() / 2) || (player->Y() -10 >= y - platform->Height() / 2)) {


            if (player->X() + 10 < x - platform->Width() / 2) {
                player->MoveTo(player->X() - 2, player->Y(), Layer::MIDDLE);
                if (player->dashing)
                {
                    player->velX = 0;
                }
                if (window->KeyDown(VK_RIGHT))
                {
                    player->jumping = false;
                    player->sideJumping = false;
                    player->MoveTo(player->X(), player->Y()-1.5f, Layer::MIDDLE);
                    if (window->KeyPress(VK_UP) && window->KeyDown(VK_RIGHT) && player->hasSideJump) {

                        player->sideJumping = true;
                        player->sideJumpSide = 1;
                        player->sideJumpTimer->Start();
                        player->hasSideJump = false;
                    }
                }


            }

            if (player->X() - 10 > x + platform->Width() / 2) {
                player->MoveTo(player->X() + 2, player->Y(), Layer::MIDDLE);
                if (player->dashing)
                {
                    player->velX = 0;
                }
                if (window->KeyDown(VK_LEFT))
                {
                    player->jumping = false;
                    player->sideJumping = false;
                    player->MoveTo(player->X(), player->Y() - 1.5f, Layer::MIDDLE);
                    if (window->KeyPress(VK_UP) && player->hasSideJump) {
                        player->sideJumping = true;
                        player->sideJumpSide = 0;
                        player->sideJumpTimer->Start();
                        player->hasSideJump = false;
                    }
                }

            }
        }


}