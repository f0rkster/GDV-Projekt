#include "CBullet.h"

CBullet::CBullet(float _X, float _Y, EBulletState _State)
    :CRectangle((float*)m_PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_PointD, (float*)m_Color)
    , m_State(_State)
{
    m_Translation[0] = _X;
    m_Translation[1] = _Y;
    m_Speed = 0.1f;
}

CBullet::~CBullet()
{
}

void CBullet::OnUpdate()
{
    switch (m_State)
    {
    case EBulletState::DOWN:
        m_Translation[1] -= m_Speed;
        break;
    case EBulletState::UP:
        m_Translation[1] += m_Speed;
        break;
    default:
        break;
    }
    fillVertices();
}
