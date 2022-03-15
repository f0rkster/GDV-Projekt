#include "CPlayer.h"
#include "Data.h"
#include <math.h>
#include <iostream>

CPlayer::CPlayer()
    :CTriangle((float*)m_PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_Color)
    , m_ShootState(EPlayerShootState::READY)
{
    m_Speed = 0.1;
    m_Translation[1] = -3.5f;
}

CPlayer::~CPlayer()
{
    for (CBullet* b : m_Bullets)
    {
        delete b;
    }
}

void CPlayer::OnUpdate(SKeyState* _KeyState)
{
    if (_KeyState->m_isAdown) Move(EPlayerMoveState::LEFT);
    if (_KeyState->m_isDdown) Move(EPlayerMoveState::RIGHT);
    Shoot(_KeyState);

    for (CBullet* b : m_Bullets)
    {
        b->OnUpdate();
    }


    if (!m_Bullets.empty() && m_Bullets[0]->m_Translation[1] > TOP_BORDER)
    {
        m_Bullets.erase(m_Bullets.begin());
    }

    fillVertices();
}

void CPlayer::Move(EPlayerMoveState _State) {
    float* XPos = &m_Translation[0];
    float halfWidth = (fabsf((float)m_PointA[0]) + fabsf((float)m_PointB[0]))/2;

    if (_State == EPlayerMoveState::LEFT)  *XPos -= m_Speed;
    if (_State == EPlayerMoveState::RIGHT) *XPos += m_Speed;
    if (*XPos < LEFT_BORDER + halfWidth)   *XPos =  LEFT_BORDER  + halfWidth;
    if (*XPos > RIGHT_BORDER - halfWidth)  *XPos =  RIGHT_BORDER - halfWidth;
}

void CPlayer::Shoot(SKeyState* _KeyState) {
    switch (m_ShootState)
    {
    case EPlayerShootState::READY:
        if (_KeyState->m_isSPACEdown) m_ShootState = EPlayerShootState::SHOOT;
        break;
    case EPlayerShootState::SHOOT:
        if (m_Bullets.size() < m_MaxBullets)
            m_Bullets.push_back(new CBullet(m_Translation[0], m_Translation[1], EBulletState::UP));
        m_ShootState = EPlayerShootState::COOLDOWN;
        break;
    case EPlayerShootState::COOLDOWN:
        if (!_KeyState->m_isSPACEdown) m_ShootState = EPlayerShootState::READY;
        break;
    }
}