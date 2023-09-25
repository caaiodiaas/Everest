/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     20 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para o jogador 
//
**********************************************************************************/

#include "Player.h"
#include "GravityGuy.h"
#include "Platform.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    tileset = new TileSet("Resources/player.png", 51, 57, 9, 63);
    anim = new Animation(tileset, 0.090f, true);

    // sequências de animação do player
    uint stillRight[1] = { 0};
    uint stillLeft[1] = { 17 };
    uint walkingRight[8] = {1,2,3,4,5,6,7,8};
    uint walkingLeft[8] = {16,15,14,13,12,11,10,9 };
    uint dashingRight[5] = {49,48,47,46,45};
    uint dashingLeft[5] = { 54,55,56,57,58};
    uint jumpingRight[4] = { 18,19,20,21 };
    uint jumpingLeft[4] = {30,29,28,27 };
    uint jumpingRightB[4] = { 22,23,24,25 };
    uint jumpingLeftB[4] = { 34,33,32,31 };
    uint grabingRight[1] = { 36 };
    uint grabingLeft[1] = { 37 };
    uint grabingRightB[1] = { 38 };
    uint grabingLeftB[1] = { 39 };
    uint fallingRight[1] = { 21 };
    uint fallingLeft[1] = { 27 };
    uint fallingRightB[1] = { 25 };
    uint fallingLeftB[1] = { 31 };

    anim->Add(WALKINGRIGHT, walkingRight, 8);
    anim->Add(WALKINGLEFT, walkingLeft, 8);
    anim->Add(STILLRIGHT, stillRight, 1);
    anim->Add(STILLLEFT, stillLeft, 1);
    anim->Add(DASHINGLEFT, dashingLeft, 5);
    anim->Add(DASHINGRIGHT, dashingRight, 5);
    anim->Add(JUMPINGLEFT, jumpingLeft, 4);
    anim->Add(JUMPINGRIGHT, jumpingRight, 4);
    anim->Add(JUMPINGLEFTB, jumpingLeftB, 4);
    anim->Add(JUMPINGRIGHTB, jumpingRightB, 4);
    anim->Add(GRABINGRIGHT, grabingRight, 1);
    anim->Add(GRABINGLEFT, grabingLeft, 1);
    anim->Add(GRABINGRIGHTB, grabingRightB, 1);
    anim->Add(GRABINGLEFTB, grabingLeftB, 1);
    anim->Add(FALLINGRIGHT, fallingRight, 1);
    anim->Add(FALLINGLEFT, fallingLeft, 1);
    anim->Add(FALLINGRIGHTB, fallingRightB, 1);
    anim->Add(FALLINGLEFTB, fallingLeftB, 1);


    // cria bounding box
    BBox(new Rect(
        -1.0f * (tileset->TileWidth()-19) / 2.0f,
        -1.0f * (tileset->TileHeight()-9) / 2.0f,
        (tileset->TileWidth() - 19) / 2.0f,
        (tileset->TileHeight() - 9) / 2.0f));
    
    level = 0;

    // posição inicial
    MoveTo(window->CenterX(), window->Height() - 300, Layer::FRONT);

    jumping = false;
    jumpTimer = new Timer();

    hasDash = true;
    dashing = false;
    dashTimer = new Timer();

    waveDashing = false;
    waveDashTimer = new Timer();

    hasSideJump = true;
    sideJumping = false;
    sideJumpTimer = new Timer();

    velX = 200;
    velY = 200;
    gravity = 200;

    deathCount = 0;
    isDead = false;

    strawberryCount = 0;

    type = 0;

    lastSide = 0;

    onFloor = false;
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;    
}

// ---------------------------------------------------------------------------------

void Player::Reset()
{
    gravity = 200;
    velX = 200;
    velY = 200;
    isDead = false;
}

void Player::ResetAll()
{
    gravity = 200;
    velX = 200;
    velY = 200;
    isDead = false;
    deathCount = 0;
    strawberryCount = 0;
}


void Player::Dead()
{
    gravity = 0;
    velX = 0;
    velY = 0;
    hasDash = false;
    hasSideJump = false;
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{


}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    // ação da gravidade sobre o personagem  
    Translate(0, gravity * gameTime);


    // atualiza animação

    if (!jumping && !dashing && !waveDashing) {
        if (hasDash)
        {
            if (onFloor)
            {
                if (!window->KeyDown(VK_DOWN) && !window->KeyDown(VK_RIGHT) && !window->KeyDown(VK_LEFT) && !window->KeyDown(VK_DOWN)) {
                    if (lastSide == 0)
                    {
                        anim->Select(STILLRIGHT);

                    }
                    else {
                        anim->Select(STILLLEFT);
                    }

                }
            }
            else {
                if (lastSide == 0)
                {
                    anim->Select(FALLINGRIGHT);

                }
                else {
                    anim->Select(FALLINGLEFT);
                }
            }
        }
        else {
{
                if (lastSide == 0)
                {
                    anim->Select(FALLINGRIGHTB);  //trocar para no dash

                }
                else {
                    anim->Select(FALLINGLEFTB);  //trocar para no dash
                }
            }
        }
    }

    if (window->KeyDown(VK_RIGHT)) {
        lastSide = 0;
        Translate(velX * gameTime, 0);
        if (onFloor && !jumping)
        {
            anim->Select(WALKINGRIGHT);
        }
        else {
            if (hasDash)
            {
                anim->Select(FALLINGRIGHT);
            }else{
                anim->Select(FALLINGRIGHTB);
            }

        }

    }

    if (window->KeyDown(VK_LEFT)) {
        lastSide = 1;
        Translate(-velX * gameTime, 0);
        if (onFloor && !jumping)
        {
            anim->Select(WALKINGLEFT);
        }
        else {
            if (hasDash)
            {
                anim->Select(FALLINGLEFT);
            }
            else {
                anim->Select(FALLINGLEFTB);
            }

        }
    }


    if (hasDash && !dashing && window->KeyPress(VK_SPACE) && !waveDashing)
    {
        MoveTo(x, y - 5, Layer::MIDDLE);
        jumping = false;
        sideJumping = false;
        dashing = true;
        hasDash = false;
        dashTimer->Start();
        if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_UP))
        {
            dashSide = 3;
        }
        else if (window->KeyDown(VK_LEFT) && !window->KeyDown(VK_DOWN))
        {
            dashSide = 4;
        }else if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_UP))
        {
            dashSide = 1;
        }
        else if (window->KeyDown(VK_RIGHT) && !window->KeyDown(VK_DOWN))
        {
            dashSide = 0;
        }else if (window->KeyDown(VK_UP) && !window->KeyDown(VK_RIGHT) && !window->KeyDown(VK_LEFT))
        {
            dashSide = 2;
        }
        else if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_DOWN)) {
            dashSide = 7;
        }
        else if (window->KeyDown(VK_DOWN) && !window->KeyDown(VK_RIGHT) && !window->KeyDown(VK_LEFT)) {
            dashSide = 6;
        }
        else if (window->KeyDown(VK_LEFT) && window->KeyDown(VK_DOWN)) {
            dashSide = 5;
        }
        
    }

    if (dashing) {

        if (dashTimer->Elapsed() < 0.15f) {
            switch (dashSide) {
            case 0: Translate(velX*4 * (1 - dashTimer->Elapsed()) * gameTime, -velY * (1 - dashTimer->Elapsed()) * gameTime, 0); anim->Select(DASHINGRIGHT); break; //RIGHT
            case 1: Translate(velX*3 * (1 - dashTimer->Elapsed()) * gameTime, -velY*3 * (1 - dashTimer->Elapsed()) * gameTime, 0); anim->Select(DASHINGRIGHT); break;//UP RIGHT
            case 2: Translate(0, -velY*4 * (1 - dashTimer->Elapsed()) * gameTime, 0);
                if (lastSide == 0)
            {
                anim->Select(DASHINGRIGHT);
            }
                  else {
                anim->Select(DASHINGLEFT);
            } break;//UP
            case 3: Translate(-velX*3 * (1 - dashTimer->Elapsed()) * gameTime, -velY*3 * (1 - dashTimer->Elapsed()) * gameTime, 0); anim->Select(DASHINGLEFT); break;//UP LEFT
            case 4: Translate(-velX*4 * (1 - dashTimer->Elapsed()) * gameTime, -velY * (1 - dashTimer->Elapsed()) * gameTime, 0); anim->Select(DASHINGLEFT); break;//LEFT
            case 5: Translate(-velX*3 * (1 - dashTimer->Elapsed()) * gameTime, velY*2 * (1 - dashTimer->Elapsed()) * gameTime, 0); anim->Select(DASHINGLEFT); break;//DOWN LEFT
            case 6: Translate(0, velY*3 * (1 - dashTimer->Elapsed()) * gameTime, 0);
                if (lastSide == 0)
                {
                    anim->Select(DASHINGRIGHT);
                }
                else {
                    anim->Select(DASHINGLEFT);
                }
                break;//DOWN
            case 7: Translate(velX*3 * (1 - dashTimer->Elapsed()) * gameTime, velY*2 * (1 - dashTimer->Elapsed()) * gameTime, 0); anim->Select(DASHINGRIGHT); break;//DOWN RIGHT
            default: Translate(0, -velY*4 * (1 - dashTimer->Elapsed()) * gameTime, 0); break;//DEFAULT UP
            }

        }
        else {
            dashing = false;
            dashSide = -1;
            dashTimer->Stop();
            dashTimer->Reset();
            velX = 200;
        }
    }

    if (jumping)
    {
        if (lastSide == 0)
        {
            anim->Select(JUMPINGRIGHT);

        }
        else {
            anim->Select(JUMPINGLEFT);
        }
        if (jumpTimer->Elapsed() < 0.3f) {

            Translate(0, -velY * 6*(0.5f-jumpTimer->Elapsed()) * gameTime);
        }
        else {
            if (lastSide == 0)
            {
                anim->Select(FALLINGRIGHT);
            }
            else {
                anim->Select(FALLINGLEFT);
            }

            jumpTimer->Stop();
            jumpTimer->Reset();
            jumping = false;
        }
    }

    if (waveDashing)
    {
        if (waveDashTimer->Elapsed() < 0.3f) {
            if (dashSide == 7) {
                anim->Select(DASHINGRIGHT);
                Translate(velX * 4 * (0.5f - waveDashTimer->Elapsed()) * gameTime, -velY * 10 * (0.5f - waveDashTimer->Elapsed()) * gameTime);
            }

            if (dashSide == 5) {
                anim->Select(DASHINGLEFT);
                Translate(-velX * 4 * (0.5f - waveDashTimer->Elapsed()) * gameTime, -velY * 10 * (0.5f - waveDashTimer->Elapsed()) * gameTime);
            }
                
        }
        else {
            waveDashTimer->Stop();
            waveDashTimer->Reset();
            waveDashing = false;
        }
    }

    if (sideJumping)
    {
        if (lastSide == 1)
        {
            if (hasDash)
            {
                anim->Select(JUMPINGLEFT);
            }
            else {
                anim->Select(JUMPINGLEFTB);
            }
        }
        else {
            if (hasDash)
            {
                anim->Select(JUMPINGRIGHT);
            }
            else {
                anim->Select(JUMPINGRIGHTB);
            }
        }
        if (sideJumpTimer->Elapsed() < 0.25f) {
            if (sideJumpSide == 0) {
                lastSide = 0;
                Translate(velX * 4 * (0.5f - sideJumpTimer->Elapsed()) * gameTime, -velY * 6 * (0.5f - sideJumpTimer->Elapsed())* gameTime);
            }

            if (sideJumpSide == 1) {
                lastSide = 1;
                Translate(-velX * 4 * (0.5f - sideJumpTimer->Elapsed()) * gameTime, -velY * 6 * (0.5f - sideJumpTimer->Elapsed()) * gameTime);
            }

        }
        else {
            sideJumpTimer->Stop();
            sideJumpTimer->Reset();
            sideJumping = false;
        }
    }

    onFloor = false;

    anim->NextFrame();
}

// ---------------------------------------------------------------------------------