#pragma once

#include "CEntity.h"

class CBullet : public CEntity
{
private:
    enum EState
    {
        Up,
        Down,
    };

    EState  m_State;

public:

    CBullet();
    void OnUpdate();
    ~CBullet();
};
