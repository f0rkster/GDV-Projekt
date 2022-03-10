#include "CPlayer.h"
#include "Data.h"
#include <math.h>

CPlayer::CPlayer()
    :CTriangle((float*)this->m_PointA, (float*)this->m_PointB, (float*)this->m_PointC, (float*)this->m_Color)
    , m_ShootState(EPlayerShootState::READY)
{
    this->m_Speed = 0.1;
    this->m_Translation[1] = -3.5f;
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

    for (CBullet* b : this->m_Bullets)
    {
        b->OnUpdate();
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
        this->m_Bullets.push_back(new CBullet(this->m_Translation[0], this->m_Translation[1]));
        m_ShootState = EPlayerShootState::COOLDOWN;
        break;
    case EPlayerShootState::COOLDOWN:
        if (!_KeyState->m_isSPACEdown) m_ShootState = EPlayerShootState::READY;
        break;
    }
}