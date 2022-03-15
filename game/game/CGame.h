#pragma once

#include "yoshix_fix_function.h"
#include <vector>

#include "CBullet.h"
#include "CPlayer.h"
#include "CShield.h"
#include "CEnemy.h"
#include "SKeyState.h"

enum class EGameState {START, RUN, PAUSED, GAMEOVER};
class CGame {
public:
    CGame(gfx::BHandle* _ppPlayerMesh, gfx::BHandle* _ppShieldMesh, gfx::BHandle* _ppEnemyMesh, gfx::BHandle* _ppBulletMesh);
    ~CGame();

    void InitGame();
    void RunGame(SKeyState* _KeyState);
    void FinalizedGame();

private:
    void RestartGame();
    void CreateEnemy();
    void HandleEnemySpeed();
    bool BulletIsInEnemy(CEnemy* _e, CBullet* _b);
    bool BulletIsInShield(CShield* _s, CBullet* _b);
    void EnemyActions();
    void CollisionControll();
    void RandomEnemyShoot();

private:
    int m_Ticks = 0;
    int m_MaxTicks = 80;
    int m_SpeedUpInterval = 0;
    int m_MaxSpeedUpInterval = 10;


public: 
    EGameState m_State;

    gfx::BHandle* m_ppPlayerMesh;
    gfx::BHandle* m_ppShieldMesh;
    gfx::BHandle* m_ppEnemyMesh;
    gfx::BHandle* m_ppBulletMesh;

    CPlayer* m_pPlayer;
    std::vector<CShield*> m_pShields;
    std::vector<CEnemy*> m_pEnemies;
    std::vector<CBullet*> m_EnemieBullets;

};
