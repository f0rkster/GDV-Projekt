#pragma once

#include "yoshix_fix_function.h"

#include "CEntity.h"

class CShield : public CEntity
{
private:
    enum EState
    {
        Idle,
        Impact,
        Dead,
    };

    static const int m_MaxHealth = 5;

    int     m_Health;

    EState  m_State;

public:

    CShield();
    void CreateShield(gfx::BHandle* _ppMesh);
    void OnUpdate();
    ~CShield();
};
