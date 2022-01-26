#pragma once
#include "yoshix_fix_function.h"

#include "CEntity.h"
#include "SKeyState.h"

class CPlayer : public CEntity
{
private:
    enum EState
    {
        Idle,
        Left,
        Right,
        Shoot,
        Cooldown,
        GettingHurt,
    };

    EState  m_State;

    int     m_Health;

public:
    CPlayer();
    void CreatePlayer(gfx::BHandle* _ppMesh);
    void OnUpdate(SKeyState _keyState);
    ~CPlayer();
};
