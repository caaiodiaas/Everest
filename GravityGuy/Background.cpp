/**********************************************************************************
// Background (Código Fonte)
// 
// Criação:     21 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Plano de fundo do jogo
//
**********************************************************************************/

#include "Background.h"

// ---------------------------------------------------------------------------------

Background::Background(Color tint) : color(tint)
{
    MoveTo(window->CenterX(), window->CenterY(), Layer::BACK);
    yF = yB = y;

    // carrega imagens
    imgF = new Image("Resources/BackgFront.png");
    imgB = new Image("Resources/BackgBack.png");

    // cria sprites do plano de fundo
    sky     = new Sprite("Resources/Sky.png");    
    backgF1 = new Sprite(imgF);
    backgF2 = new Sprite(imgF);
    backgB1 = new Sprite(imgB);
    backgB2 = new Sprite(imgB);

    strawberryIcon = new Sprite("Resources/StrawCounter.png");
    deathIcon = new Sprite("Resources/DeathCounter.png");
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    delete deathIcon;
    delete strawberryIcon;
    delete imgF;
    delete imgB;    
    delete backgF1;
    delete backgF2;
    delete backgB1;
    delete backgB2;
    delete sky;
}

// -------------------------------------------------------------------------------

void Background::Update()
{
    // move sprites com velocidades diferentes
    yF -= -50 * gameTime;
    yB -= -30 * gameTime;
}

// -------------------------------------------------------------------------------

void Background::Draw()
{
    // desenha pano de fundo
    sky->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 1.0f, 0.0f, color);

    // desenha prédios mais distantes
    backgB1->Draw(x, yB, Layer::LOWER, 1.0f, 0.0f, color);
    backgB2->Draw(x, yB - imgB->Height(), Layer::LOWER, 1.0f, 0.0f, color);
    
    // traz pano de fundo de volta para dentro da tela
    if (yB - imgB->Height()/2.0f > window->Height())
        yB -= imgB->Height();

    // desenha prédios mais próximos
    backgF1->Draw(x, yF, Layer::MIDDLE, 1.0f, 0.0f, color);
    backgF2->Draw(window->Width() / 2.0f, yF - imgF->Height(), Layer::MIDDLE, 1.0f, 0.0f, color);

    // traz pano de fundo de volta para dentro da tela
    if (yF - imgF->Height()/2.0f > window->Height())
        yF -= imgF->Height();

    strawberryIcon->Draw(60, 48, Layer::FRONT, 1);
    deathIcon->Draw(60, 28, Layer::FRONT, 1);
}

// -------------------------------------------------------------------------------
