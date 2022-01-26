#include "CPlayer.h"

CPlayer::CPlayer()
{
	m_Speed = 0.1f;

	m_Translation[0] = 0.0f;
	m_Translation[1] = -9.0f;
	m_Translation[2] = 0.0f;
	
	m_Health = 3;

	m_State = CPlayer::Idle;
}


void CPlayer::OnUpdate(SKeyState _keyState)
{
    switch (m_State)
    {
    case CPlayer::Idle:
    {
        if (_keyState.m_IsLArrowDown) m_State = CPlayer::Left;
        if (_keyState.m_IsRArrowDown) m_State = CPlayer::Right;
        if (_keyState.m_IsSpaceDown)  m_State = CPlayer::Shoot;
    }
    break;

    case CPlayer::Left:
    {
        m_Translation[0] -= m_Speed;

        if (!_keyState.m_IsLArrowDown) m_State = CPlayer::Idle;
    }
    break;

    case CPlayer::Right:
    {
        m_Translation[0] += m_Speed;

        if (!_keyState.m_IsRArrowDown) m_State = CPlayer::Idle;
    }
    break;

    case CPlayer::Shoot:
    {
        if (!_keyState.m_IsSpaceDown) m_State = CPlayer::Idle;
    }
    break;
    }
}

CPlayer::~CPlayer()
{
}
