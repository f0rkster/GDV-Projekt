#pragma once

#include "yoshix_fix_function.h"

#include "CEntity.h"

class CBullet : public CEntity
{
private:
    enum EState
    {
        Idle,
        Up,
        Down,
    };

    EState  m_State;

public:

    CBullet();
    void CreateBullet(gfx::BHandle* _ppMesh);
    void OnUpdate();
    ~CBullet();
};
