#include "CGame.h"

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
}

void CGame::initGame()
{
    this->m_pPlayer = new CPlayer();
}

void CGame::runGame()
{
}

void CGame::finalizedGame()
{
}

