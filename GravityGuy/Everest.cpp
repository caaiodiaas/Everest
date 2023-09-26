/**********************************************************************************
// Everest (Código Fonte)
// 
// Criação:     05 Out 2011
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Jogo estilo plataforma usando a engine do curso
//
**********************************************************************************/

#include "Engine.h"
#include "Everest.h"
#include "Home.h"
#include "GameOver.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

// inicializa membros estáticos da classe
Game*   Everest::level = nullptr;
Player* Everest::player = nullptr;
Audio*  Everest::audio = nullptr;
bool    Everest::viewBBox = false;

// ------------------------------------------------------------------------------

void Everest::Init() 
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(MENU, "Resources/Menu.wav");
    audio->Add(MUSIC1, "Resources/music1.wav");
    audio->Add(MUSIC2, "Resources/music2.wav");
    audio->Add(MUSIC3, "Resources/music3.wav");
    audio->Add(ENDING, "Resources/ending.wav");
    audio->Add(WIND, "Resources/wind.wav");
    audio->Volume(WIND, 2.5f);
    audio->Add(WALK, "Resources/walk_sound.wav", 5);
    audio->Volume(WALK, 1.2f);
    audio->Add(JUMP, "Resources/jump_sound.wav");
    audio->Volume(JUMP, 2);
    audio->Add(DASH, "Resources/dash_sound.wav");
    audio->Volume(DASH,1.5f);
    audio->Add(STRAWBERRY, "Resources/strawberry_sound.wav");
    audio->Add(DEATH, "Resources/death_sound.wav");
    audio->Add(GRAB, "Resources/grab_sound.wav");
    audio->Volume(GRAB,1.5f);

    // bounding box não visível
    viewBBox = false;

    // cria jogador
    player = new Player();

    // inicializa nível de abertura do jogo
    level = new Home();
    level->Init();
}

// ------------------------------------------------------------------------------

void Everest::Update()
{
    // habilita/desabilita visualização da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;    

    // atualiza nível
    level->Update();
} 

// ------------------------------------------------------------------------------

void Everest::Draw()
{
    // desenha nível
    level->Draw();
} 

// ------------------------------------------------------------------------------

void Everest::Finalize()
{
    level->Finalize();

    delete player;
    delete audio;
    delete level;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura o motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 800);
    engine->window->Color(30, 50, 80);
    engine->window->Title("Everest");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Everest());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

