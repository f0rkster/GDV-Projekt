#pragma once

#include "yoshix_fix_function.h"
#include <vector>

#include "CPlayer.h"
#include "CShield.h"
#include "SKeyState.h"

enum EGameState {START, RUN, PAUSED, GAMEOVER};
class CGame {
public:
    CGame(gfx::BHandle* _ppPlayerMesh, gfx::BHandle* _ppShieldMesh, gfx::BHandle* _ppEnemyMesh, gfx::BHandle* _ppBulletMesh);
    ~CGame();

    void initGame();
    void runGame(SKeyState* _KeyState);
    void finalizedGame();


public: 
    EGameState m_State;

    gfx::BHandle* m_ppPlayerMesh;
    gfx::BHandle* m_ppShieldMesh;
    gfx::BHandle* m_ppEnemyMesh;
    gfx::BHandle* m_ppBulletMesh;

    CPlayer* m_pPlayer;
    std::vector<CShield*> m_pShields;

};
