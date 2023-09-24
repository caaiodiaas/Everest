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
    tileset = new TileSet("Resources/GravityGuy.png", 32, 48, 5, 10);
    anim = new Animation(tileset, 0.120f, true);

    // sequências de animação do player
    uint still[1] = { 0};
    uint invert[4] = {6,7,8,9};
    uint normal[4] = {1,2,3,4};

    anim->Add(INVERTED, invert, 4);
    anim->Add(NORMAL, normal, 4);
    anim->Add(STILL, still, 1);

    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));
    
    // inicializa estado do player
    gravity = NORMAL;  
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
    // volta ao estado inicial
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
    gravity = NORMAL;
    level = 0;
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{


}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    gravity = 200;
    // ação da gravidade sobre o personagem  
    Translate(0, gravity * gameTime);

    if (window->KeyDown(VK_RIGHT))
        Translate(velX * gameTime, 0);
    if (window->KeyDown(VK_LEFT))
        Translate(-velX * gameTime, 0);

    if (hasDash && !dashing && window->KeyPress(VK_SPACE))
    {
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
        anim->Select(NORMAL);
        if (!window->KeyDown(VK_DOWN) && !window->KeyDown(VK_RIGHT) && !window->KeyDown(VK_LEFT) && !window->KeyDown(VK_DOWN)) {
            anim->Select(STILL);
        }
    }
    else {
        anim->Select(INVERTED);
    }
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------