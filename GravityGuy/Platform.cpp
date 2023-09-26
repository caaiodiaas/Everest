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
#include "Everest.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType, Color tint) : color(tint)
{
    switch (platType)
    {
    case LARGE:  platform = new Sprite("Resources/LongHorizontal.png"); type = LARGE; break;
    case MEDIUM: platform = new Sprite("Resources/MediumHorizontal.png"); type = MEDIUM; break;
    case SMALL:  platform = new Sprite("Resources/SmallHorizontal.png"); type = SMALL; break;
    case LARGEV:  platform = new Sprite("Resources/LongVertical.png"); type = LARGEV; break;
    case MEDIUMV: platform = new Sprite("Resources/MediumVertical.png"); type = MEDIUMV; break;
    case SMALLV:  platform = new Sprite("Resources/LongVertical.png"); type = SMALLV; break;
    }


        BBox(new Rect(( - platform->Width()-10) / 2.0f,
            (- platform->Height()) / 2.0f,
            (platform->Width()+10) / 2.0f,
            (platform->Height()) / 2.0f));


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
    if (obj->Type() == 0)
    {
        Player* player = (Player*)obj;

        // Colisões eixo X

        //Plataforma na direita
        if (player->X() < x - platform->Width() / 2) {
            if (player->Y() + 15 < y - platform->Height() / 2 && !window->KeyDown(VK_DOWN))
            {
                player->MoveTo(x - platform->Width() / 2 - 5, player->Y(), Layer::MIDDLE);
            }
            else {

                if(window->KeyDown(VK_RIGHT) && !player->waveDashing)
                player->MoveTo(x - platform->Width() / 2 - 15, player->Y(), Layer::MIDDLE);
            }

            if (player->dashing && (player->dashSide == 0 || player->dashSide == 1 || player->dashSide == 7) && player->Y() > y - platform->Height() / 2)
            {
                player->velX = 0;
            }
            if (window->KeyDown(VK_RIGHT) && player->hasSideJump && !player->jumping && !player->waveDashing)
            {
                player->stopped = true;
                if (player->hasDash)
                {
                    player->anim->Select(GRABINGRIGHT);
                }
                else {
                    player->anim->Select(GRABINGRIGHTB);
                }
                player->Translate(0, -150 * gameTime);
                player->sideJumping = false;
                if (window->KeyPress(VK_UP) && !player->dashing) {
                    Everest::audio->Play(JUMP);
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

            //Plataforma na esquerda
            if (player->X() > x + platform->Width() / 2) {
                if ((player->Y() + 15 < y - platform->Height() / 2) && !window->KeyDown(VK_DOWN))
                {
                    player->MoveTo(x + platform->Width() / 2 + 5, player->Y(), Layer::MIDDLE);
                }
                else {
                    if (window->KeyDown(VK_LEFT) && !player->waveDashing)
                    player->MoveTo(x + platform->Width() / 2 + 15, player->Y(), Layer::MIDDLE);
                }

                if (player->dashing && (player->dashSide == 3 || player->dashSide == 4 || player->dashSide == 5) && player->Y() > y - platform->Height() / 2)
                {
                    player->velX = 0;
                }
                if (window->KeyDown(VK_LEFT) && player->hasSideJump && !player->jumping && !player->waveDashing)
                {
                    player->stopped = true;
                    if (player->hasDash)
                    {
                        player->anim->Select(GRABINGLEFT);
                    }
                    else {
                        player->anim->Select(GRABINGLEFTB);
                    }
                    player->Translate(0, -150 * gameTime);
                    player->sideJumping = false;
                    if (window->KeyPress(VK_UP) && !player->dashing) {
                        Everest::audio->Play(JUMP);
                        player->jumping = false;
                        player->MoveTo(x + platform->Width() / 2 + 25, player->Y(), Layer::MIDDLE);
                        player->sideJumping = true;
                        player->sideJumpSide = 0;
                        player->sideJumpTimer->Start();
                        player->hasSideJump = false;
                    }
                }

            }
            else
                // Colisões eixo Y
                    //Plataforma abaixo
                if (player->Y() < y - platform->Height() / 2) {
                    player->MoveTo(player->X(), y - platform->Height() / 2 - 25, Layer::MIDDLE);

                    if (player->X() > x - platform->Width() / 2 && player->X() < x + platform->Width() / 2 || player->X() < x + platform->Width() / 2 && player->X() > x - platform->Width() / 2)
                    {
                        if (!player->dashing) {
                            player->hasDash = true;
                        }
                        player->hasSideJump = true;
                        player->onFloor = true;
                    }

                    if (player->dashSide == 7 || player->dashSide == 5)
                    {
                        if (window->KeyDown(VK_SPACE)) {
                            player->velX = 200;
                            Everest::audio->Play(JUMP);
                            player->MoveTo(player->X(), y - platform->Height() / 2 - 35, Layer::MIDDLE);
                            player->waveDashing = true;
                        }
                    }
                    else if (window->KeyPress(VK_UP)) {
                        if (player->X() > x - platform->Width() / 2 && player->X() < x + platform->Width() / 2 || player->X() < x + platform->Width() / 2 && player->X() > x - platform->Width() / 2)
                        {
                            Everest::audio->Play(JUMP);
                            player->MoveTo(player->X(), y - platform->Height() / 2 - 25, Layer::MIDDLE);
                            player->jumping = true;
                            player->jumpTimer->Start();
                        }

                    }
                }
                else
                    //Plataforma acima
                    if (player->Y() > y + platform->Height() / 2) {
                        player->MoveTo(player->X(), y + platform->Height() / 2 + 25, Layer::MIDDLE);
                        player->jumping = false;
                    }

    }

        


}