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
    tileset = new TileSet("Resources/player.png", 51, 57, 9, 18);
    anim = new Animation(tileset, 0.120f, true);

    // sequências de animação do player
    uint stillRight[1] = { 0};
    uint stillLeft[1] = { 17 };
    uint walkingRight[8] = {1,2,3,4,5,6,7,8};
    uint walkingLeft[8] = { 9,10,11,12,13,14,15,16 };

    anim->Add(WALKINGRIGHT, walkingRight, 8);
    anim->Add(WALKINGLEFT, walkingLeft, 8);
    anim->Add(STILLRIGHT, stillRight, 1);
    anim->Add(STILLLEFT, stillLeft, 1);

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
    gravity = 250;

    deathCount = 0;
    isDead = false;

    strawberryCount = 0;

    type = 0;

    lastSide = 0;
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
    gravity = 250;
    velX = 200;
    velY = 200;
    isDead = false;
}

void Player::ResetAll()
{
    gravity = 250;
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

    if (window->KeyDown(VK_RIGHT)) {
        lastSide = 0;
        Translate(velX * gameTime, 0);
        anim->Select(WALKINGRIGHT);
    }

    if (window->KeyDown(VK_LEFT)) {
        lastSide = 1;
        Translate(-velX * gameTime, 0);
        anim->Select(WALKINGLEFT);
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
            case 0: Translate(velX*4 * gameTime, -velY * gameTime, 0); break; //RIGHT
            case 1: Translate(velX*3 * gameTime, -velY*3 * gameTime, 0); break;//UP RIGHT
            case 2: Translate(0, -velY*4 * gameTime, 0); break;//UP
            case 3: Translate(-velX*3 * gameTime, -velY*3 * gameTime, 0); break;//UP LEFT
            case 4: Translate(-velX*4 * gameTime, -velY * gameTime, 0); break;//LEFT
            case 5: Translate(-velX*3 * gameTime, velY*2 * gameTime, 0); break;//DOWN LEFT
            case 6: Translate(0, velY*3 * gameTime, 0); break;//DOWN
            case 7: Translate(velX*3 * gameTime, velY*2 * gameTime, 0); break;//DOWN RIGHT
            default: Translate(0, -velY*4 * gameTime, 0); break;//DEFAULT UP
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
        if (jumpTimer->Elapsed() < 0.25f) {
            Translate(0, -velY*2.5f * gameTime);
        }
        else {
            jumpTimer->Stop();
            jumpTimer->Reset();
            jumping = false;
        }
    }

    if (waveDashing)
    {
        if (waveDashTimer->Elapsed() < 0.25f) {
            if(dashSide == 7)
                Translate(velX*3 * gameTime, -velY*4* gameTime);
            if (dashSide == 5)
                Translate(-velX * 3 * gameTime, -velY*4 * gameTime);
        }
        else {
            waveDashTimer->Stop();
            waveDashTimer->Reset();
            waveDashing = false;
        }
    }

    if (sideJumping)
    {
        if (sideJumpTimer->Elapsed() < 0.25f) {
            if (sideJumpSide == 0)
                Translate(velX*1.5f * gameTime, -velY * 2.5f * gameTime);
            if (sideJumpSide == 1)
                Translate(-velX*1.5f * gameTime, -velY * 2.5f * gameTime);
        }
        else {
            sideJumpTimer->Stop();
            sideJumpTimer->Reset();
            sideJumping = false;
        }
    }

    // atualiza animação
    
    if (hasDash) {
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

    anim->NextFrame();
}

// ---------------------------------------------------------------------------------