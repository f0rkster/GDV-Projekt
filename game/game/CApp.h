#pragma once

#include "yoshix_fix_function.h"
#include "CPlayer.h"
#include "CShield.h"

class CApp : public gfx::IApplication
{
public: 
    CApp();
    ~CApp();

private:
   

private:

    float        m_FieldOfViewY;     // Vertical view angle of the camera

    CPlayer* m_Player = new CPlayer();
    CShield* m_Shield = new CShield();

    gfx::BHandle m_pPlayerMesh;
    gfx::BHandle m_pShieldMesh;


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