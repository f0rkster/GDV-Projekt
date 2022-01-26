#pragma once

struct SPlayer
{
    enum EState
    {
        Idle,
        Left,
        Right,
        Shoot,
        GettingHurt,
    };

    float   m_Speed;
    float   m_Translation[3];

    EState  m_State;

    int     m_Health;
};
