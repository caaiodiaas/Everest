/**********************************************************************************
// Level2B (Código Fonte)
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
#include "Level2B.h"
#include "Level2B.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"

#include <string>
#include <fstream>
#include "Spike.h"
#include "Strawberry.h"
#include "Level3.h"
#include "Level3B.h"
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros estáticos da classe

Scene* Level2B::scene = nullptr;
Font* Level2B::font = nullptr;            // fonte para texto

// ------------------------------------------------------------------------------

void Level2B::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background(Color{ 1,1,0.6,1 });
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(Everest::player, MOVING);

    // adiciona jogador na cena
    strawberry = new Strawberry(680, 280);
    scene->Add(strawberry, MOVING);


    // ----------------------
    // plataformas
    // ----------------------

    Platform* plat;
    Spike* spike;
    float posX, posY;
    uint  platType;
    Color white{ 1,1,0.9f,1 };

    // cria fontes para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");

    //PARTE ESQUERDA



    spike = new Spike(221, 170, SMALLSPIKE, white);
    scene->Add(spike, STATIC);

    plat = new Platform(118, 780, MEDIUM, white);
    scene->Add(plat, STATIC);

    plat = new Platform(71, 654, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(20, 410, LARGEV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(26, 166, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(156, -38, LARGEV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(214, 206, MEDIUM, white);
    scene->Add(plat, STATIC);

    plat = new Platform(400, 20, LARGE, white);
    scene->Add(plat, STATIC);


    // PARTE CENTRAL

    spike = new Spike(221, 170, SMALLSPIKE, white);
    scene->Add(spike, STATIC);

    spike = new Spike(345, 679, LARGESPIKER, white);
    scene->Add(spike, STATIC);

    spike = new Spike(408, 501, SMALLSPIKE, white);
    scene->Add(spike, STATIC);

    plat = new Platform(212, 490, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(212, 413, SMALLV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(262, 340, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(383, 780, LARGEV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(423, 780, LARGEV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(434, 536, SMALL, white);
    scene->Add(plat, STATIC);

    //PARTE DIREITA

    spike = new Spike(745, 63, SMALLSPIKER, white);
    scene->Add(spike, STATIC);

    spike = new Spike(745, 330, LARGESPIKER, white);
    scene->Add(spike, STATIC);

    plat = new Platform(523, 297, SMALLV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(604, 212, SMALLV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(554, 250, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(642, 135, MEDIUM, white);
    scene->Add(plat, STATIC);

    plat = new Platform(780, 224, LARGEV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(682, 468, MEDIUM, white);
    scene->Add(plat, STATIC);


    //ESPINHO DE FUNDO
    spike = new Spike(55, 620, SMALLSPIKEL, white);
    scene->Add(spike, STATIC);



    // ----------------------

    // inicia com música

    Everest::audio->Volume(MUSIC2, 0.1f);
    Everest::audio->Frequency(MUSIC2, 1.1f);
    Everest::audio->Play(MUSIC2, 1);
    Everest::audio->Play(WIND, 1);
    Everest::player->MoveTo(55, 720, Layer::FRONT);
}

// ------------------------------------------------------------------------------

void Level2B::Update()
{
    if (Everest::player->playing == false)
    {
        font->Draw(55 + 55, 720 + 10, "PRESSIONE", { 1,1,1,1 }, Layer::UPPER, 2);
        font->Draw(55 + 75, 720 + 35, "ESPAÇO", { 1,1,1,1 }, Layer::UPPER, 2);
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
        Everest::player->MoveTo(55, 720, Layer::FRONT);
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
        Everest::audio->Stop(MUSIC2);
        Everest::audio->Stop(WIND);
        Everest::NextLevel<Home>();
        Everest::player->Reset();
    }
    else if (Everest::player->Y() - 20 > window->Height())
    {
        Everest::player->isDead = true;
    }
    else if (Everest::player->Y() < 0 || window->KeyPress('N'))
    {
        Everest::player->MoveTo(55, 720, Layer::FRONT);
        Everest::player->Reset();
        if (strawberry->following)
        {
            Everest::player->strawberryCount++;
            strawberry->Reset();
        }
        Everest::audio->Stop(WIND);
        Everest::audio->Stop(MUSIC2);
        Everest::NextLevel<Level3B>();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }


}

// ------------------------------------------------------------------------------

void Level2B::Draw()
{
    backg->Draw();
    scene->Draw();

    if (Everest::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level2B::Finalize()
{
    scene->Remove(Everest::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
