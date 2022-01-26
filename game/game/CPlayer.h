#pragma once

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
        GettingHurt,
    };

    EState  m_State;

    int     m_Health;

public:
    CPlayer();
    void OnUpdate(SKeyState _keyState);
    ~CPlayer();
};
