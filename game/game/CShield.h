#pragma once
#include "CRectangle.h"

class CShield : public CRectangle
{
private:
    static constexpr float m_PointA[3] = { -1.0f, -0.25f, 0.0f };
    static constexpr float m_PointB[3] = {  1.0f, -0.25f, 0.0f };
    static constexpr float m_PointC[3] = {  1.0f,  0.25f, 0.0f };
    static constexpr float m_PointD[3] = { -1.0f,  0.25f, 0.0f };
    static constexpr float m_Color[4] =  {  0.0f,  0.5f, 1.0f, 1.0f };

public:
    CShield(float _X, float _Y);
    ~CShield();
    int m_CurrentHealth;
    void Strike();
};

