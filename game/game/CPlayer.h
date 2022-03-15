#pragma once
#include "CTriangle.h"
#include "SKeyState.h"
#include "CBullet.h"
#include <vector>

enum class EPlayerMoveState {LEFT, RIGHT};
enum class EPlayerShootState {READY, SHOOT, COOLDOWN};

class CPlayer : public CTriangle{
private:
    static constexpr float m_PointA[3] = { -0.5f, -0.5f, 0.0f };
    static constexpr float m_PointB[3] = {  0.5f, -0.5f, 0.0f };
    static constexpr float m_PointC[3] = {  0.0f,  0.0f, 0.0f };
    static constexpr float m_Color[4]  = {  0.0f,  1.0f, 0.0f , 1.0f};
    static constexpr float m_MaxBullets = 3;
public:
    CPlayer();
    ~CPlayer();
    void OnUpdate(SKeyState* _KeyState);
    EPlayerShootState m_ShootState;
    std::vector<CBullet*> m_Bullets;
    bool m_IsPlayerAlive;
private:
    void Move(EPlayerMoveState _State);
    void Shoot(SKeyState* _KeyState);
};