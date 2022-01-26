#pragma once

struct SBullet
{
    enum EState
    {
        Up,
        Down,
    };

    float   m_Speed;
    float   m_Translation[3];

    EState  m_State;
};
