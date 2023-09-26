/**********************************************************************************
// Level1 (Código Fonte) 
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
#include "Level1.h"
#include "Level2.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"

#include <string>
#include <fstream>
#include "Spike.h"
#include "Strawberry.h"
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros estáticos da classe

Scene * Level1::scene = nullptr;
Font* Level1::font = nullptr;            // fonte para texto

// ------------------------------------------------------------------------------

void Level1::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background(Color{ 1,1,1,1 });
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(Everest::player, MOVING);

    // adiciona jogador na cena
    strawberry = new Strawberry(90, 520);
    scene->Add(strawberry, MOVING);


    // ----------------------
    // plataformas
    // ----------------------

    Platform * plat;
    Spike * spike;
    float posX, posY;
    uint  platType;
    Color white { 1,1,1,1 };

    // cria fontes para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");

    plat = new Platform(20, -99, LARGEV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(71, 145, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(20, 388, LARGEV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(223, 630, LARGE, white);
    scene->Add(plat, STATIC);

    plat = new Platform(110, 590, SMALL, white);
    scene->Add(plat, STATIC);

    plat = new Platform(300, 190, MEDIUM, white);
    scene->Add(plat, STATIC);

    plat = new Platform(200, 328, MEDIUMV, white);
    scene->Add(plat, STATIC);

    plat = new Platform(338, 428, MEDIUM, white);
    scene->Add(plat, STATIC);

    spike = new Spike(338, 160, MEDIUMSPIKE, white);
    scene->Add(spike, STATIC);

    spike = new Spike(165, 290, LARGESPIKER, white);
    scene->Add(spike, STATIC);



    // ----------------------

    // inicia com música

    Everest::audio->Volume(MUSIC1, 0.1f);
    Everest::audio->Play(MUSIC1,1);
    Everest::audio->Play(WIND, 1);
    Everest::player->MoveTo(70, 80, Layer::FRONT);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{


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
        Everest::player->MoveTo(70, 80, Layer::FRONT);
        Everest::player->Reset();

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
        Everest::audio->Stop(MUSIC1);
        Everest::audio->Stop(WIND);
        Everest::NextLevel<Home>();
        Everest::player->Reset();
    }
    else if (Everest::player->Y() -20 > window->Height())
    {
        Everest::player->isDead = true;
    }
    else if (Everest::player->Right() > window->Width() || window->KeyPress('N'))
    {
        Everest::player->MoveTo(70, 80, Layer::FRONT);
        Everest::player->Reset();
        if (strawberry->following)
        {
            Everest::player->strawberryCount++;
            strawberry->Reset();
        }
        Everest::audio->Stop(WIND);
        Everest::audio->Stop(MUSIC1);
        Everest::NextLevel<Level2>();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }    


}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    backg->Draw();
    scene->Draw();

    if (Everest::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    scene->Remove(Everest::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
