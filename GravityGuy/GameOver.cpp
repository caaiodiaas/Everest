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
#include "Everest.h"
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

    Everest::audio->Volume(ENDING, 0.2f);
    Everest::audio->Play(ENDING,1);
    Everest::audio->Play(WIND, 1);
}

// ----------------------------------------------------------------------

void GameOver::Update()
{

    deathCount.str("");
    deathCount << "x" << Everest::player->deathCount;
    font->Draw(window->CenterX()+ 100, 95, deathCount.str(), { 0, 0, 0, 1 }, Layer::FRONT, 2);

    strawberryCount.str("");
    strawberryCount << "x" << Everest::player->strawberryCount << "/3";
    font->Draw(window->CenterX() - 45, 95, strawberryCount.str(), { 1, 0, 0, 1 }, Layer::FRONT, 2);


    font->Draw(window->CenterX() - 30, 700, "PRESS ENTER", { 1, 0, 0, 1 }, Layer::FRONT, 2);

    if (window->KeyPress(VK_ESCAPE) || window->KeyPress(VK_RETURN)) {
        Everest::player->ResetAll();
        Everest::audio->Stop(ENDING);
        Everest::audio->Stop(WIND);
        Everest::NextLevel<Home>();
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

