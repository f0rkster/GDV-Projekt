#include "CBullet.h"

CBullet::CBullet() {
    m_Speed = 0.1f;
    m_State = CBullet::Up;
    m_Translation[0] = 0.0f;
    m_Translation[1] = 0.0f;
    m_Translation[2] = 0.0f;
}

void CBullet::OnUpdate()
{
    switch (m_State)
    {
    case CBullet::Up:
    {
        m_Translation[1] += m_Speed;
    }
    break;
    case CBullet::Down:
    {
        m_Translation[1] -= m_Speed;
    }
    break;
    }
}

CBullet::~CBullet(){}