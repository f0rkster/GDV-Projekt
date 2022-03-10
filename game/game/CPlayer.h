#pragma once
#include "CTriangle.h"
#include "SKeyState.h"

class CPlayer : public CTriangle{
private:
    static constexpr float m_PointA[3] = { -0.5f, -0.5f, 0.0f };
    static constexpr float m_PointB[3] = {  0.5f, -0.5f, 0.0f };
    static constexpr float m_PointC[3] = {  0.0f,  0.0f, 0.0f };
    static constexpr float m_Color[4]  = {  0.0f,  1.0f, 0.0f , 1.0f};
public:
    enum EPlayerMoveState {LEFT, RIGHT};
    CPlayer();
    ~CPlayer();
    void OnUpdate(SKeyState* _KeyState);
private:
    void Move(EPlayerMoveState _State);
};