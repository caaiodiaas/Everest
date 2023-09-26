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
#include "Level1B.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
    scene = new Scene();
    backg = new TileSet("Resources/Home.png", 800, 800, 2, 4);
    //tileset = new TileSet("Resources/PressEnter.png", 72, 48, 1, 5);
    anim = new Animation(backg, 0.180f, true);
    
    tutorial = new TileSet("Resources/TutorialSheet.png",540,280,3,5);
    Tutorialanim = new Animation(tutorial, 0.100f, false);
    uint ativo[4] = { 0,1,2,3 };
    uint inativo[1] = { 4 };

    Tutorialanim->Add(ACTIVE, ativo, 4);
    Tutorialanim->Add(INACTIVE, inativo, 1);

    mouse = new Mouse();
    scene->Add(mouse, MOVING);

    menu[0] = new Item(100, 150, INICIAR, "Resources/MenuIniciar.png");
    menu[1] = new Item(100, 250, SAIR, "Resources/MenuSair.png");
    menu[2] = new Item(650, 75, TUTORIALKEY, "Resources/MenuTutorial.png");


    for (int i = 0; i < MaxItens; ++i)
        scene->Add(menu[i], STATIC);


    Everest::audio->Volume(MENU, 0.2f);
    Everest::audio->Play(MENU, true);

    startB = false;
    start = false;
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

    anim->NextFrame();
    scene->Update();


    for (int i = 0; i < MaxItens; ++i)
    {
        if (scene->Collision(mouse, menu[i]))
        {
            menu[i]->Select();
            if (menu[i]->Tutorial())
            {
                Tutorialanim->Select(ACTIVE);

            }
            else
                Tutorialanim->Restart();
         
            if (mouse->Clicked())
            {
                switch (menu[i]->Type())
                {
                case INICIAR:
                {
                    start = true;
                    break;
                }
                case SAIR:
                {
                    window->Close(); 
                    break;
                }
                case TUTORIALKEY:
                {
                    startB = true;
                    break;
                }
                }
            }
        }
        else
        {
            menu[i]->UnSelect();
            if (menu[i]->Tutorial()) {
                Tutorialanim->Select(INACTIVE);
            }
        }
        menu[i]->Update();
        Tutorialanim->NextFrame();
    }

    if (start) {
        Everest::audio->Stop(MENU);
        Everest::NextLevel<Level1>();
    }
    else {
        if (startB) {
            Everest::audio->Stop(MENU);
            Everest::NextLevel<Level1B>();
        }
    }


}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    //backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    anim->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    Tutorialanim->Draw(window->CenterX() + 115, window->CenterY() - 95, Layer::FRONT);
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