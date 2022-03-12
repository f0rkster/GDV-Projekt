#include "CEnemy.h"
#include "Data.h"

CEnemy::CEnemy(float _X, float _Y)
    : CRectangle((float*)this->m_PointA, (float*)this->m_PointB, (float*)this->m_PointC, (float*)this->m_PointD, (float*)this->m_Color)
    , m_MoveState(EMoveState::RIGHT)
{
    this->m_Translation[0] = _X;
    this->m_Translation[1] = _Y;
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
            move(m_MoveState);
            m_MoveState = EMoveState::RIGHT;
        }
        else
        {
            move(m_MoveState);
        }
        break;
    case EMoveState::RIGHT:
        if (m_Translation[0] >= RIGHT_BORDER - padding)
        {
            m_MoveState = EMoveState::DOWN;
            move(m_MoveState);
            m_MoveState = EMoveState::LEFT;
        }
        else
        {
            move(m_MoveState);
        }
        break;
    default:
        break;
    }
}

void CEnemy::move(EMoveState _State)
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
