/**********************************************************************************
// Player (Arquivo de Cabe�alho)
// 
// Cria��o:     20 Abr 2012
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para o jogador 
//
**********************************************************************************/

#ifndef _GRAVITYGUY_PLAYER_H_
#define _GRAVITYGUY_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites

// ------------------------------------------------------------------------------

enum Animations {WALKINGRIGHT, WALKINGLEFT, STILLRIGHT, STILLLEFT, DASHINGRIGHT, DASHINGLEFT, GRABINGRIGHT, GRABINGLEFT, GRABINGRIGHTB, GRABINGLEFTB, JUMPINGRIGHT, JUMPINGLEFT, JUMPINGRIGHTB, JUMPINGLEFTB, FALLINGRIGHT, FALLINGLEFT, FALLINGRIGHTB,FALLINGLEFTB};         // tipo da gravidade

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet   * tileset;                // folha de sprites do personagem
    int         level;                  // n�vel finalizado
    int lastSide;

    
public:
    Animation* anim;                   // anima��o do personagem
    uint deathCount;
    uint strawberryCount;    

    boolean onFloor;

    boolean isDead;

    uint        gravity;                // gravidade atuando sobre o jogador
    int velX;
    int velY;
    boolean       jumping;              // jogador pulando
    Timer* jumpTimer;
    boolean dashing;
    boolean hasDash;
    int dashSide;
    Timer* dashTimer;
    boolean waveDashing;
    Timer* waveDashTimer;

    boolean grabbing;

    boolean hasSideJump;
    boolean sideJumping;
    Timer* sideJumpTimer;
    int sideJumpSide;

    Timer* walkTimer;
    boolean walkTimerOn;

    Player();                           // construtor
    ~Player();                          // destrutor

    void Reset();                       // volta ao estado inicial
    void ResetAll();                       // volta ao estado inicial
    void Dead();
    int Level();                        // �ltimo n�vel finalizado
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo
    float Right();                     // coordenadas da base
    float Left();                        // coordenadas do topo

    void OnCollision(Object * obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline int Player::Level()
{ return level; }

inline float Player::Bottom()
{ return y + tileset->Height()/2; }

inline float Player::Top()
{ return y - tileset->Height()/2; }

inline float Player::Right()
{
    return x;
}

inline float Player::Left()
{
    return x ;
}

inline void Player::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif