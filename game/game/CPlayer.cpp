#include "CPlayer.h"

CPlayer::CPlayer()
    :CTriangle((float*)this->m_PointA, (float*)this->m_PointB, (float*)this->m_PointC, (float*)this->m_Color)
{
}

CPlayer::~CPlayer(){}
