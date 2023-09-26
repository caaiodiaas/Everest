/**********************************************************************************
// Home (Código Fonte)
//
// Criação:     14 Fev 2013
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Tela de abertura do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "Everest.h"
#include "Home.h"
#include "Level1.h"
#include "Item.h"
#include "Mouse.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
    bool start = false;
    scene = new Scene();
    backg = new TileSet("Resources/Home.png", 800, 800, 2, 4);
    //tileset = new TileSet("Resources/PressEnter.png", 72, 48, 1, 5);
    anim = new Animation(backg, 0.180f, true);

    mouse = new Mouse();
    scene->Add(mouse, MOVING);

    menu[0] = new Item(150, 150, INICIAR, "Resources/MenuIniciar.png");
    menu[1] = new Item(150, 250, SAIR, "Resources/MenuSair.png");

    for (int i = 0; i < MaxItens; ++i)
        scene->Add(menu[i], STATIC);


    Everest::audio->Volume(MENU, 0.2f);
    Everest::audio->Play(MENU, true);
}

// ------------------------------------------------------------------------------

void Home::Update()
{

    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    mouse->Update();

    // se a tecla ENTER for pressionada
    if (window->KeyPress(VK_RETURN))
    {
        start = true;
    }
    else
    {
        anim->NextFrame();
        scene->Update();
    }


    for (int i = 0; i < MaxItens; ++i)
    {
        if (scene->Collision(mouse, menu[i]))
        {
            menu[i]->Select();

            if (mouse->Clicked())
            {
                switch (menu[i]->Type())
                {
                case INICIAR:
                {
                    start = true;
                    break;
                }
                case SAIR: window->Close(); break;
                }
            }
        }
        else
        {
            menu[i]->UnSelect();
        }

        menu[i]->Update();
        

    }

    if (start) {
        Everest::audio->Stop(MENU);
        Everest::NextLevel<Level1>();
    }
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    //backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    anim->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    scene->Draw();
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete backg;
    delete anim;
    delete scene;
}

// ------------------------------------------------------------------------------