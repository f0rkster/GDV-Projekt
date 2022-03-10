#pragma once

#include "yoshix_fix_function.h"

#include "CGame.h"
#include "SKeyState.h"

class CApp : public gfx::IApplication
{
public: 
    CApp();
    ~CApp();

private:
   

private:

    CRectangle* m_Background;
    CGame* m_pGame;
    SKeyState m_KeyState;

    float        m_FieldOfViewY;     // Vertical view angle of the camera

    gfx::BHandle m_pPlayerMesh;
    gfx::BHandle m_pShieldMesh;
    gfx::BHandle m_pEnemyMesh;
    gfx::BHandle m_pBulletMesh;
    gfx::BHandle m_pBackgroundMesh;

private:
    bool InternOnStartup();
    bool InternOnShutdown();
    bool InternOnCreateMeshes();
    bool InternOnReleaseMeshes();
    bool InternOnResize(int _Width, int _Height);
    bool InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown);
    bool InternOnUpdate();
    bool InternOnFrame();
};