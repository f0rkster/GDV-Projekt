#pragma once
#include "CTriangle.h"
#include "SKeyState.h"
#include "CBullet.h"
#include <vector>

class CPlayer : public CTriangle{
private:
    static constexpr float m_PointA[3] = { -0.5f, -0.5f, 0.0f };
    static constexpr float m_PointB[3] = {  0.5f, -0.5f, 0.0f };
    static constexpr float m_PointC[3] = {  0.0f,  0.0f, 0.0f };
    static constexpr float m_Color[4]  = {  0.0f,  1.0f, 0.0f , 1.0f};

public:
    enum EPlayerMoveState {LEFT, RIGHT};
    enum EPlayerShootState {READY, SHOOT, COOLDOWN};
    CPlayer();
    ~CPlayer();
    void OnUpdate(SKeyState* _KeyState);
    EPlayerShootState m_ShootState;
    std::vector<CBullet*> m_Bullets;
private:
    void Move(EPlayerMoveState _State);
    void Shoot(SKeyState* _KeyState);
};