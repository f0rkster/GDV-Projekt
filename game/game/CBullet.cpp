#include "CBullet.h"

CBullet::CBullet(float _X, float _Y)
    :CRectangle((float*)m_PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_PointD, (float*)m_Color)
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
    m_Translation[1] += m_Speed;
    fillVertices();
}
