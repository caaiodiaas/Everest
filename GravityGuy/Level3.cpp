/**********************************************************************************
// Level3 (Código Fonte)
//
// Criação:     14 Fev 2013
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Nível 1 do jogo
//
**********************************************************************************/

#include "Everest.h"
#include "Home.h"
#include "Level3.h"
#include "Level3.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"

#include <string>
#include <fstream>
#include "Spike.h"
#include "Strawberry.h"
#include "Level3.h"
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros estáticos da classe

Scene* Level3::scene = nullptr;
Font* Level3::font = nullptr;            // fonte para texto

// ------------------------------------------------------------------------------

void Level3::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background(Color{ 1,0.6,0.6,1 });
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(Everest::player, MOVING);

    // adiciona jogador na cena
    strawberry = new Strawberry(650, 80);
    scene->Add(strawberry, MOVING);


    // ----------------------
    // plataformas
    // ----------------------

    Platform* plat;
    Spike* spike;
    float posX, posY;
    uint  platType;
    Color white{ 1,0.9,0.9,1 };

    // cria fontes para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");

    //PARTE ESQUERDA

    spike = new Spike(118, 257, LARGESPIKE, white);
    scene->Add(spike, STATIC);

    spike = new Spike(325, 257, MEDIUMSPIKE, white);
    scene->Add(spike, STATIC);

    spike = new Spike(56, 395, MEDIUMSPIKEL, white);
    scene->Add(spike, STATIC);

    spike = new Spike(86, 745, SMALLSPIKE, white);
    scene->Add(spike, STATIC);

    spike = new Spike(208, 703, SMALLSPIKER, white);
    scene->Add(spike, STATIC);

    spike = new Spike(278, 735, SMALLSPIKEL, white);
    scene->Add(spike, STATIC);


    plat = new Platform(71, 151, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(419, 180, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(224, 292, LARGE, white);
    scene->Add(plat, STATIC);

    plat = new Platform(20, 536, LARGEV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(224, 780, LARGE, white);
    scene->Add(plat, STATIC);
   
    plat = new Platform(243, 703, SMALLV, white);
    scene->Add(plat, STATIC);


    //PARTE CENTRAL

    spike = new Spike(219, 0, SMALLSPIKER, white);
    scene->Add(spike, STATIC);

    spike = new Spike(585, 185, SMALLSPIKE, white);
    scene->Add(spike, STATIC);

    spike = new Spike(501, 618, SMALLSPIKE, white);
    scene->Add(spike, STATIC);

    spike = new Spike(375, 573, SMALLSPIKER, white);
    scene->Add(spike, STATIC);

    spike = new Spike(341, 461, SMALLSPIKE, white);
    scene->Add(spike, STATIC);

    spike = new Spike(203, 461, SMALLSPIKE, white);
    scene->Add(spike, STATIC);


    plat = new Platform(254, -93, LARGEV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(585, 40, SMALLV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(701, 82, MEDIUMV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(498, 20, LARGE, white);
    scene->Add(plat, STATIC);

    plat = new Platform(591, 449, LARGEV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(760, 221, LARGE, white);
    scene->Add(plat, STATIC);

    plat = new Platform(501, 653, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(410, 555, MEDIUMV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(272, 494, MEDIUM, white);
    scene->Add(plat, STATIC);

    plat = new Platform(272, 452, SMALLV, white);
    scene->Add(plat, STATIC);


    //PARTE DIREITA

    spike = new Spike(800, 340, SMALLSPIKE, white);
    scene->Add(spike, STATIC);


    plat = new Platform(780, 576, LARGEV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(772, 780, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(772, 653, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(632, 551, SMALLV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(753, 375, SMALL, white);
    scene->Add(plat, STATIC);
    // ----------------------

    // inicia com música

    Everest::audio->Volume(MUSIC3, 0.1f);
    Everest::audio->Play(MUSIC3, 1);
    Everest::audio->Play(WIND, 1);
    Everest::player->MoveTo(70, 100, Layer::FRONT);
}

// ------------------------------------------------------------------------------

void Level3::Update()
{
    if (Everest::player->playing == false)
    {
        font->Draw(70 + 55, 100 + 10, "PRESSIONE", { 1,1,1,1 }, Layer::UPPER, 2);
        font->Draw(70 + 75, 100 + 35, "ESPAÇO", { 1,1,1,1 }, Layer::UPPER, 2);
    }

    if (Everest::player->isDead)
    {
        Everest::audio->Play(DEATH);
        if (Everest::player->Y() < window->Height())
        {

            explosion = new Explosion(Everest::player->X(), Everest::player->Y(), scene);
        }
        else {
            explosion = new Explosion(Everest::player->X(), window->Height() - 20, scene);
        }

        scene->Add(explosion, STATIC);
        strawberry->Reset();
        Everest::player->deathCount++;
        Everest::player->Dead();
        Everest::player->MoveTo(70, 100, Layer::FRONT);
        Everest::player->isDead = false;
        Everest::player->playing = false;
        Everest::player->anim->Select(FALLINGRIGHT);

    }

    Color deathColor{ 0.65f, 0.65f, 0.65f, 1.0f };
    deathCount.str("");
    deathCount << "x" << Everest::player->deathCount;
    font->Draw(window->CenterX() - 300, 40, deathCount.str(), deathColor, Layer::FRONT, 1.5f);

    Color strawberryColor{ 1.0f, 0.5f, 0.5f, 1.0f };
    strawberryCount.str("");
    strawberryCount << "x" << Everest::player->strawberryCount << "/3";
    font->Draw(window->CenterX() - 300, 60, strawberryCount.str(), strawberryColor, Layer::FRONT, 1.5f);

    if (window->KeyPress(VK_ESCAPE))
    {
        Everest::audio->Stop(MUSIC3);
        Everest::audio->Stop(WIND);
        Everest::NextLevel<Home>();
        Everest::player->Reset();
    }
    else if (Everest::player->Y() - 20 > window->Height())
    {
        Everest::player->isDead = true;
    }
    else if (Everest::player->Right() > window->Width() || window->KeyPress('N'))
    {
        Everest::player->MoveTo(70, 100, Layer::FRONT);
        Everest::player->Reset();
        if (strawberry->following)
        {
            Everest::player->strawberryCount++;
            strawberry->Reset();
        }
        Everest::audio->Stop(WIND);
        Everest::audio->Stop(MUSIC3);
        Everest::NextLevel<GameOver>();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }


}

// ------------------------------------------------------------------------------

void Level3::Draw()
{
    backg->Draw();
    scene->Draw();

    if (Everest::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level3::Finalize()
{
    scene->Remove(Everest::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
