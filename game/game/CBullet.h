#pragma once
#include "CRectangle.h"

class CBullet : public CRectangle
{
private:
    static constexpr float m_PointA[3] = { -0.025f, -0.1f, 0.0f };
    static constexpr float m_PointB[3] = {  0.025f, -0.1f, 0.0f };
    static constexpr float m_PointC[3] = {  0.025f,  0.1f, 0.0f };
    static constexpr float m_PointD[3] = { -0.025f,  0.1f, 0.0f };
    static constexpr float m_Color[4] = { 1.0f,  1.0f, 1.0f, 1.0f };

public:
    CBullet(float _X, float _Y);
    ~CBullet();
    void OnUpdate();
};

