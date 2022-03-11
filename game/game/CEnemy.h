#pragma once
#include "CRectangle.h"
class CEnemy : public CRectangle
{
private:
    static constexpr float m_PointA[3] = { -0.15f, -0.15f, 0.0f };
    static constexpr float m_PointB[3] = {  0.15f, -0.15f, 0.0f };
    static constexpr float m_PointC[3] = {  0.15f,  0.15f, 0.0f };
    static constexpr float m_PointD[3] = { -0.15f,  0.15f, 0.0f };
    static constexpr float m_Color[4]  = { 1.0f, 0.0f, 0.0f, 1.0f };
    static constexpr int m_MaxTick = 60;

public:
    enum EMoveState {LEFT, RIGHT, DOWN};
    CEnemy(float _X, float _Y);
    ~CEnemy();
    void OnUpdate();
    EMoveState m_MoveState;

private:
    void move(EMoveState _State);
};

