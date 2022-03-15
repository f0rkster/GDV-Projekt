#pragma once
#include "CRectangle.h"

enum class EBulletState {DOWN, UP};
class CBullet : public CRectangle
{
private:
    static constexpr float m_PointA[3] = { -0.025f, -0.1f, 0.0f };
    static constexpr float m_PointB[3] = {  0.025f, -0.1f, 0.0f };
    static constexpr float m_PointC[3] = {  0.025f,  0.1f, 0.0f };
    static constexpr float m_PointD[3] = { -0.025f,  0.1f, 0.0f };
    static constexpr float m_Color[4] = { 1.0f,  1.0f, 1.0f, 1.0f };

public:
    CBullet(float _X, float _Y, EBulletState _State);
    ~CBullet();
    void OnUpdate();

    EBulletState m_State;
};

