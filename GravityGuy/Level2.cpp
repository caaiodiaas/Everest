/**********************************************************************************
// Level2 (Código Fonte)
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
#include "Level2.h"
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

Scene* Level2::scene = nullptr;
Font* Level2::font = nullptr;            // fonte para texto

// ------------------------------------------------------------------------------

void Level2::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background(Color{ 0.8f,1,0.8f,1 });
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(Everest::player, MOVING);

    // adiciona jogador na cena
    strawberry = new Strawberry(window->CenterX() + 300, window->Height() - 100);
    scene->Add(strawberry, MOVING);

    // ----------------------
    // plataformas
    // ----------------------

    Platform* plat;
    Spike* spike;
    float posX, posY;
    uint  platType;
    Color white{ 1,1,1,1 };

    // cria fontes para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");

    plat = new Platform(window->CenterX() - 550, window->Height() - 20, 2, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->CenterX() + 600, window->Height() - 20, 2, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->CenterX() - 400, 0, 2, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->CenterX() + 400, 0, 2, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->CenterX(), window->Height() + 280, 3, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->CenterX() + 200, window->Height() - 180, 2, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->Width() - 20, window->CenterY() + 420, 3, white);
    scene->Add(plat, STATIC);

    plat = new Platform(20, window->CenterY(), 3, white);
    scene->Add(plat, STATIC);

    spike = new Spike(window->CenterX() + 100, window->CenterY() + 100, 3, white);
    scene->Add(spike, STATIC);
    // ----------------------

    // inicia com música
    Everest::audio->Volume(MUSIC2, 0.1f);
    Everest::audio->Play(MUSIC2);
    Everest::audio->Play(WIND);

    Everest::player->MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
}

// ------------------------------------------------------------------------------

void Level2::Update()
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
        Everest::player->MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
        Everest::player->Reset();

    }

    Color deathColor{ 0.65f, 0.65f, 0.65f, 1.0f };
    deathCount.str("");
    deathCount << "x" << Everest::player->deathCount;
    font->Draw(window->CenterX() - 300, 80, deathCount.str(), deathColor, Layer::FRONT, 1.5f);

    Color strawberryColor{ 1.0f, 0.5f, 0.5f, 1.0f };
    strawberryCount.str("");
    strawberryCount << "x" << Everest::player->strawberryCount << "/3";
    font->Draw(window->CenterX() - 300, 100, strawberryCount.str(), strawberryColor, Layer::FRONT, 1.5f);

    if (window->KeyPress(VK_ESCAPE))
    {
        Everest::audio->Stop(WIND);
        Everest::audio->Stop(MUSIC2);
        Everest::NextLevel<Home>();
        Everest::player->Reset();
    }
    else if (Everest::player->Y() - 20 > window->Height())
    {
        Everest::player->isDead = true;
    }
    else if (Everest::player->Right() > window->Width() || window->KeyPress('N'))
    {
        Everest::player->MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
        Everest::player->Reset();
        if (strawberry->following)
        {
            Everest::player->strawberryCount++;
            strawberry->Reset();
        }
        Everest::audio->Stop(WIND);
        Everest::audio->Stop(MUSIC2);
        Everest::NextLevel<Level3>();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }


}

// ------------------------------------------------------------------------------

void Level2::Draw()
{
    backg->Draw();
    scene->Draw();

    if (Everest::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level2::Finalize()
{
    scene->Remove(Everest::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
