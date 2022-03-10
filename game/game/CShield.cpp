#include "CShield.h"

CShield::CShield(float _X, float _Y)
    :CRectangle((float*)this->m_PointA, (float*)this->m_PointB, (float*)this->m_PointC, (float*)this->m_PointD, (float*)this->m_Color)
{
    m_Translation[0] = _X;
    m_Translation[1] = _Y;
}

CShield::~CShield()
{
}