#include "CGame.h"
#include "Data.h"
#include "CUtility.h"

#include <iostream>

CGame::CGame(gfx::BHandle* _ppPlayerMesh, gfx::BHandle* _ppShieldMesh, gfx::BHandle* _ppEnemyMesh, gfx::BHandle* _ppBulletMesh)
    : m_State(EGameState::START)
    , m_ppPlayerMesh(_ppPlayerMesh)
    , m_ppShieldMesh(_ppShieldMesh)
    , m_ppEnemyMesh(_ppEnemyMesh)
    , m_ppBulletMesh(_ppBulletMesh)
{
    do {
        std::cout << '\n' << "Press the Enter key to continue.";
    } while (std::cin.get() != '\n');
    m_State = EGameState::RUN;
    InitGame();
}

CGame::~CGame()
{
    delete m_pPlayer;

    for (CShield* s : m_pShields)
    {
        delete s;
    }

    for (CBullet* b : m_pPlayer->m_Bullets)
    {
        delete b;
    }    
    
    for (CEnemy* e : m_pEnemies)
    {
        delete e;
    }
}

void CGame::InitGame()
{
    this->m_pPlayer = new CPlayer();
    m_pPlayer->m_Bullets.push_back(new CBullet(m_pPlayer->m_Translation[0], m_pPlayer->m_Translation[1]));

    float shieldYPos = -2.0f;
    this->m_pShields.push_back(new CShield(-WIDTH/3, shieldYPos));
    this->m_pShields.push_back(new CShield(0       , shieldYPos));
    this->m_pShields.push_back(new CShield( WIDTH/3, shieldYPos));

    float padding = 0.5f;
    this->m_pEnemies.push_back(new CEnemy(LEFT_BORDER + padding, TOP_BORDER - padding));
}

void CGame::RunGame(SKeyState* _KeyState)
{
    this->m_pPlayer->OnUpdate(_KeyState);
    
    m_Ticks++;
    if (m_Ticks == m_MaxTicks)
    {
        for (CEnemy* e : m_pEnemies)
        {
            e->OnUpdate();
        }

        CreateEnemy();
        HandleEnemySpeed();

        m_Ticks = 0;
    }

    for (CEnemy* e : m_pEnemies)
    {
        for (CBullet* b : m_pPlayer->m_Bullets)
        {
            if (BulletIsInEnemy(e, b))
            {
                
                m_pPlayer->m_Bullets.erase(m_pPlayer->m_Bullets.begin() + CUtility::getVectorIndex(m_pPlayer->m_Bullets, b));
                m_pEnemies.erase(m_pEnemies.begin() + CUtility::getVectorIndex(m_pEnemies, e));
            }
        }
    }

    if (m_pEnemies.front()->m_Translation[1] <= -1.5f)
    {
        m_State = EGameState::GAMEOVER;
    }
}

void CGame::FinalizedGame()
{
    do {
        std::cout << '\n' << "Press the Enter key to restart game.";
    } while (std::cin.get() != '\n');
    m_State = EGameState::START;
    RestartGame();
}

void CGame::RestartGame() {
    delete m_pPlayer;

    for (CShield* s : m_pShields)
    {
        delete s;
    }

    for (CBullet* b : m_pPlayer->m_Bullets)
    {
        delete b;
    }

    for (CEnemy* e : m_pEnemies)
    {
        delete e;
    }

    InitGame();
}

void CGame::CreateEnemy() {
    float padding = 0.5f;
    this->m_pEnemies.push_back(new CEnemy(LEFT_BORDER + padding, TOP_BORDER - padding));
}

void CGame::HandleEnemySpeed() {
    m_SpeedUpInterval++;
    if (m_SpeedUpInterval >= m_MaxSpeedUpInterval)
    {
        if (m_MaxTicks > 10) m_MaxTicks -= 5;
        m_SpeedUpInterval = 0;
    }
}

bool CGame::BulletIsInEnemy(CEnemy* _e, CBullet* _b)
{
    // https://www.geeksforgeeks.org/find-two-rectangles-overlap/

    float l1x = _e->CRectangle::m_PointD[0] + _e->m_Translation[0];
    float l1y = _e->CRectangle::m_PointD[1] + _e->m_Translation[1];
    float r1x = _e->CRectangle::m_PointB[0] + _e->m_Translation[0];
    float r1y = _e->CRectangle::m_PointB[1] + _e->m_Translation[1];
    float l2x = _b->CRectangle::m_PointD[0] + _b->m_Translation[0];
    float l2y = _b->CRectangle::m_PointD[1] + _b->m_Translation[1];
    float r2x = _b->CRectangle::m_PointB[0] + _b->m_Translation[0];
    float r2y = _b->CRectangle::m_PointB[1] + _b->m_Translation[1];

    // To check if either rectangle is actually a line
    // For example :  l1 ={-1,0}  r1={1,1}  l2={0,-1}
    // r2={0,1}

    // If one rectangle is on left side of other
    if (r1x < l2x || l1x > r2x)
        return false;

    // If one rectangle is above other
    if (l1y < r2y || r1y > l2y)
        return false;

    return true;
}
