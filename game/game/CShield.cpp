#include "CShield.h"

CShield::CShield(float _X, float _Y)
    :CRectangle((float*)m_PointA, (float*)m_PointB, (float*)m_PointC, (float*)m_PointD, (float*)m_Color)
    , m_CurrentHealth(5)
{
    m_Translation[0] = _X;
    m_Translation[1] = _Y;
}

CShield::~CShield()
{
}

void CShield::Strike()
{
    m_CurrentHealth--;
    switch (m_CurrentHealth)
    {
    case 5:
        CRectangle::m_Color[0] = 0.0f;
        CRectangle::m_Color[1] = 0.5f;
        CRectangle::m_Color[2] = 1.0f;
        CRectangle::m_Color[3] = 1.0f;
        break;
    case 4:
        CRectangle::m_Color[0] = 0.0f;
        CRectangle::m_Color[1] = 1.0f;
        CRectangle::m_Color[2] = 0.0f;
        CRectangle::m_Color[3] = 1.0f;
        break;
    case 3:
        CRectangle::m_Color[0] = 1.0f;
        CRectangle::m_Color[1] = 1.0f;
        CRectangle::m_Color[2] = 0.0f;
        CRectangle::m_Color[3] = 1.0f;
        break;
    case 2:
        CRectangle::m_Color[0] = 1.0f;
        CRectangle::m_Color[1] = 0.5f;
        CRectangle::m_Color[2] = 0.0f;
        CRectangle::m_Color[3] = 1.0f;
        break;
    case 1:
        CRectangle::m_Color[0] = 1.0f;
        CRectangle::m_Color[1] = 0.0f;
        CRectangle::m_Color[2] = 0.0f;
        CRectangle::m_Color[3] = 1.0f;
        break;
    case 0:
        CRectangle::m_Color[0] = 0.0f;
        CRectangle::m_Color[1] = 0.0f;
        CRectangle::m_Color[2] = 0.0f;
        CRectangle::m_Color[3] = 1.0f;
        break;
    default:
        break;
    }
    fillColors();
}
