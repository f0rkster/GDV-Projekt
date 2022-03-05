#pragma once

#include "yoshix_fix_function.h"
#include "CPlayer.h"

enum EGameState {START, RUN, PAUSED, GAMEOVER};
class CGame {
public:
    CGame();
    ~CGame();

    void initGame();
    void runGame();
    void finalizedGame();


private: 
    EGameState m_State;

};
