/**********************************************************************************
// Mouse (Arquivo de Cabeçalho)
//
// Criação:     14 Mai 2012
// Atualização: 31 Ago 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Gerencia mouse na tela
//
**********************************************************************************/

#ifndef _MOUSE_H_
#define _MOUSE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"        
#include "Types.h"        

// ---------------------------------------------------------------------------------

class Mouse : public Object
{
public:
    Mouse();            // construtor
    ~Mouse();           // destrutor

    bool Clicked();     // click do mouse
    void Update();      // atualização do objeto
    void Draw();        // desenho do objeto 
};

// ---------------------------------------------------------------------------------

#endif