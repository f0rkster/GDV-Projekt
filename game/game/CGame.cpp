#include "CGame.h"
#include "Data.h"
#include "CUtility.h"

#include <iostream>
#include <cstdlib>
#include <random>

CGame::CGame(gfx::BHandle* _ppPlayerMesh, gfx::BHandle* _ppShieldMesh, gfx::BHandle* _ppEnemyMesh, gfx::BHandle* _ppBulletMesh)
    : m_State(EGameState::START)
    , m_ppPlayerMesh(_ppPlayerMesh)
    , m_ppShieldMesh(_ppShieldMesh)
    , m_ppEnemyMesh(_ppEnemyMesh)
    , m_ppBulletMesh(_ppBulletMesh)
{
    do {
        std::system("CLS");
        std::cout << "Welcome to Matthias Gabel's GDV project." << std::endl;
        std::cout << std::endl;
        std::cout << "Instructions:" << std::endl;
        std::cout << "The blue shields protect you from some enemy missiles. \nBut be careful, you can also damage your shields." << std::endl;
        std::cout << std::endl;
        std::cout << "Move with 'A' and 'D' or with the arrow keys. \nFire projectiles with 'SPACE'." << std::endl;
        std::cout << std::endl;
        std::cout << "You only have one life so take good care of it." << std::endl;
        std::cout << std::endl;
        std::cout << "The goal of the game is to survive as long as possible." << std::endl;
        std::cout << std::endl;
        std::cout << "The game is over when the enemies reach the baseline or you get hit." << std::endl;
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
    m_pPlayer = new CPlayer();
    m_pPlayer->m_Bullets.push_back(new CBullet(m_pPlayer->m_Translation[0], m_pPlayer->m_Translation[1], EBulletState::UP));

    float shieldYPos = -2.0f;
    m_pShields.push_back(new CShield(-WIDTH/3, shieldYPos));
    m_pShields.push_back(new CShield(0       , shieldYPos));
    m_pShields.push_back(new CShield( WIDTH/3, shieldYPos));

    float padding = 0.5f;
    int numberOfEnemiesInRow = 23;
    int numberOfRows = 3;
    int numberOfEnemies = numberOfEnemiesInRow * numberOfRows;

    for (int i = 0; i < numberOfEnemies; i++)
    {
        for (CEnemy* e : m_pEnemies)
        {
            e->OnUpdate();
        }
        m_pEnemies.push_back(new CEnemy(LEFT_BORDER + padding, TOP_BORDER - padding));
    }

}

void CGame::RunGame(SKeyState* _KeyState)
{
    m_pPlayer->OnUpdate(_KeyState);
    
    EnemyActions();

    CollisionControll();
    
    if (!m_pEnemies.empty() && m_pEnemies.front()->m_Translation[1] <= -1.5f)
    {
        m_State = EGameState::GAMEOVER;
    }
    if (!m_pPlayer->m_IsPlayerAlive)
    {
        m_State = EGameState::GAMEOVER;
    }
}

void CGame::FinalizedGame()
{
    do {
        std::system("CLS");
        std::cout << "Congratulation your Score is " << m_Score << "!";
        std::cout << std::endl;
        //std::cout << '\n' << "Press the Enter key to restart game.";
    } while (std::cin.get() != '\n');
    //m_State = EGameState::START;
    //RestartGame();
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

    for (CBullet* b : m_EnemieBullets)
    {
        delete b;
    }

    InitGame();
}

void CGame::CreateEnemy() {
    float padding = 0.5f;
    m_pEnemies.push_back(new CEnemy(LEFT_BORDER + padding, TOP_BORDER - padding));
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

bool CGame::BulletIsInShield(CShield* _s, CBullet* _b)
{
    // https://www.geeksforgeeks.org/find-two-rectangles-overlap/

    float l1x = _s->CRectangle::m_PointD[0] + _s->m_Translation[0];
    float l1y = _s->CRectangle::m_PointD[1] + _s->m_Translation[1];
    float r1x = _s->CRectangle::m_PointB[0] + _s->m_Translation[0];
    float r1y = _s->CRectangle::m_PointB[1] + _s->m_Translation[1];
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

bool CGame::BulletIsInPlayer(CPlayer* _p, CBullet* _b)
{
    // https://www.geeksforgeeks.org/find-two-rectangles-overlap/

    float l1x = _p->CTriangle::m_PointA[0] + _p->m_Translation[0];
    float l1y = _p->CTriangle::m_PointC[1] + _p->m_Translation[1];
    float r1x = _p->CTriangle::m_PointB[0] + _p->m_Translation[0];
    float r1y = _p->CTriangle::m_PointB[1] + _p->m_Translation[1];
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

void CGame::EnemyActions()
{
    m_Ticks++;
    if (m_Ticks == m_MaxTicks)
    {
        for (CEnemy* e : m_pEnemies)
        {
            e->OnUpdate();
        }

        RandomEnemyShoot();
        CreateEnemy();
        HandleEnemySpeed();
        m_Score += 1;
        m_Ticks = 0;
    }
    for (CBullet* b : m_EnemieBullets)
    {
        b->OnUpdate();
    }
}

void CGame::CollisionControll()
{
    for (CEnemy* e : m_pEnemies)
    {
        for (CBullet* b : m_pPlayer->m_Bullets)
        {
            if (BulletIsInEnemy(e, b))
            {
                m_Score += 100;
                m_pPlayer->m_Bullets.erase(m_pPlayer->m_Bullets.begin() + CUtility::getVectorIndex(m_pPlayer->m_Bullets, b));
                m_pEnemies.erase(m_pEnemies.begin() + CUtility::getVectorIndex(m_pEnemies, e));
            }
        }
    }

    for (CShield* s : m_pShields)
    {
        for (CBullet* b : m_pPlayer->m_Bullets)
        {
            if (BulletIsInShield(s, b))
            {
                m_pPlayer->m_Bullets.erase(m_pPlayer->m_Bullets.begin() + CUtility::getVectorIndex(m_pPlayer->m_Bullets, b));
                s->Strike();
                if (s->m_CurrentHealth <= 0)
                {
                    m_pShields.erase(m_pShields.begin() + CUtility::getVectorIndex(m_pShields, s));
                }
            }
        }
    }

    for (CBullet* b : m_EnemieBullets)
    {
        for (CShield* s : m_pShields)
        {
            if (BulletIsInShield(s, b))
            {
                m_EnemieBullets.erase(m_EnemieBullets.begin() + CUtility::getVectorIndex(m_EnemieBullets, b));
                s->Strike();
                if (s->m_CurrentHealth <= 0)
                {
                    m_pShields.erase(m_pShields.begin() + CUtility::getVectorIndex(m_pShields, s));
                }
            }
        }
        if (BulletIsInPlayer(m_pPlayer, b)) m_pPlayer->m_IsPlayerAlive = false;
    }
}

void CGame::RandomEnemyShoot()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    float XPos = m_pEnemies[gen() % m_pEnemies.size()]->m_Translation[0];
    float YPos = m_pEnemies[gen() % m_pEnemies.size()]->m_Translation[1];
    m_EnemieBullets.push_back(new CBullet(XPos, YPos, EBulletState::DOWN));
}
