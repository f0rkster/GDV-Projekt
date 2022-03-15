#include "CEnemy.h"
#include "Data.h"

CEnemy::CEnemy(float _X, float _Y)
    : CRectangle((float*)m_PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_PointD, (float*)m_Color)
    , m_MoveState(EMoveState::RIGHT)
{
    m_Translation[0] = _X;
    m_Translation[1] = _Y;
}

CEnemy::~CEnemy()
{
}

void CEnemy::OnUpdate()
{
    float padding = 0.5f;
    switch (m_MoveState)
    {
    case EMoveState::LEFT:
        if (m_Translation[0] <= LEFT_BORDER + padding)
        {
            m_MoveState = EMoveState::DOWN;
            Move(m_MoveState);
            m_MoveState = EMoveState::RIGHT;
        }
        else
        {
            Move(m_MoveState);
        }
        break;
    case EMoveState::RIGHT:
        if (m_Translation[0] >= RIGHT_BORDER - padding)
        {
            m_MoveState = EMoveState::DOWN;
            Move(m_MoveState);
            m_MoveState = EMoveState::LEFT;
        }
        else
        {
            Move(m_MoveState);
        }
        break;
    default:
        break;
    }
}

void CEnemy::Move(EMoveState _State)
{
    switch (_State)
    {
    case EMoveState::LEFT:
        m_Translation[0] -= 0.5f;
        break;
    case EMoveState::RIGHT:
        m_Translation[0] += 0.5f;
        break;
    case EMoveState::DOWN:
        m_Translation[1] -= 0.5f;
     default:
        break;
    }
}