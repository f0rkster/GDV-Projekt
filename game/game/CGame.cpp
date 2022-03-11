#include "CGame.h"
#include "Data.h"

CGame::CGame(gfx::BHandle* _ppPlayerMesh, gfx::BHandle* _ppShieldMesh, gfx::BHandle* _ppEnemyMesh, gfx::BHandle* _ppBulletMesh)
    : m_State(EGameState::START)
    , m_ppPlayerMesh(_ppPlayerMesh)
    , m_ppShieldMesh(_ppShieldMesh)
    , m_ppEnemyMesh(_ppEnemyMesh)
    , m_ppBulletMesh(_ppBulletMesh)
{
    this->initGame();
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

void CGame::initGame()
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

void CGame::runGame(SKeyState* _KeyState)
{
    this->m_pPlayer->OnUpdate(_KeyState);
    
    m_Ticks++;
    if (m_Ticks == m_MaxTicks)
    {
        for (CEnemy* e : m_pEnemies)
        {
            e->OnUpdate();
        }
        float padding = 0.5f;
        this->m_pEnemies.push_back(new CEnemy(LEFT_BORDER + padding, TOP_BORDER - padding));

        m_SpeedUpInterval++;
        if (m_SpeedUpInterval >= m_MaxSpeedUpInterval)
        {
            if (m_MaxTicks > 10) m_MaxTicks -= 5;
            m_SpeedUpInterval = 0;
        }
        m_Ticks = 0;
    }
}

void CGame::finalizedGame()
{
}

