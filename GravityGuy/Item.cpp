/**********************************************************************************
// Item (C�digo Fonte)
//
// Cria��o:     14 Mai 2012
// Atualiza��o: 31 Ago 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define um item de menu
//
**********************************************************************************/

#include "Item.h"

// ---------------------------------------------------------------------------------

Item::Item(float posX, float posY, uint menuId, string imgFile)
{
    // cria tileset e anima��o
    tileset = new TileSet(imgFile, 179, 99, 2, 4);
    animation = new Animation(tileset, 0.100f, false);

    // define sequ�ncias de anima��o
    uint selected[3] = { 1,2,3 };
    uint notselected[1] = { 0 };

    // adiciona sequ�ncias de anima��o
    animation->Add(SELECTED, selected, 3);
    animation->Add(NOTSELECTED, notselected, 1);

    // cria bounding box
    BBox(new Rect(-1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));

    // ajusta posi��o do item
    MoveTo(posX, posY, Layer::FRONT);

    // define o identificador do item
    type = menuId;
}

// ---------------------------------------------------------------------------------

Item::~Item()
{
    delete animation;
    delete tileset;
}

// -------------------------------------------------------------------------------

void Item::Select()
{
    animation->Select(SELECTED);
}

// -------------------------------------------------------------------------------

void Item::UnSelect()
{
    animation->Select(NOTSELECTED);
}

// -------------------------------------------------------------------------------

void Item::Update()
{
    animation->NextFrame();
}

// -------------------------------------------------------------------------------

void Item::Draw()
{
    animation->Draw(x, y, z);
}

// -------------------------------------------------------------------------------