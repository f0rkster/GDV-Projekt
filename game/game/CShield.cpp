#include "CShield.h"

CShield::CShield()
    :CRectangle((float*)this->m_PointA, (float*)this->m_PointB, (float*)this->m_PointC, (float*)this->m_PointD, (float*)this->m_Color)
{
}

CShield::~CShield()
{
}