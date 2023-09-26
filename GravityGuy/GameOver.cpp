/**********************************************************************************
// GameOver (Arquivo de Cabeçalho)
// 
// Criação:     14 Fev 2013
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Fim do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "GameOver.h"
#include "GravityGuy.h"
#include "Home.h"
#include "Font.h"

// ----------------------------------------------------------------------
Font* GameOver::font = nullptr;            // fonte para texto

void GameOver::Init()
{
    title = new Sprite("Resources/GameOver.png");

    // cria fontes para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");

    GravityGuy::audio->Volume(ENDING, 0.2f);
    GravityGuy::audio->Play(ENDING);
}

// ----------------------------------------------------------------------

void GameOver::Update()
{


    deathCount.str("");
    deathCount << "x" << GravityGuy::player->deathCount;
    font->Draw(window->CenterX()+ 100, 95, deathCount.str(), { 0, 0, 0, 1 }, Layer::FRONT, 2);

    strawberryCount.str("");
    strawberryCount << "x" << GravityGuy::player->strawberryCount << "/3";
    font->Draw(window->CenterX() - 45, 95, strawberryCount.str(), { 1, 0, 0, 1 }, Layer::FRONT, 2);

    if (window->KeyPress(VK_ESCAPE) || window->KeyPress(VK_RETURN)) {
        GravityGuy::player->ResetAll();
        GravityGuy::NextLevel<Home>();
    }
}

// ----------------------------------------------------------------------

void GameOver::Draw()
{
    title->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

// ----------------------------------------------------------------------

void GameOver::Finalize()
{
    delete title;
    delete font;
}

// ----------------------------------------------------------------------

