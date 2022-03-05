#pragma once

#include "yoshix_fix_function.h"
#include "CGame.h"

class CApp : public gfx::IApplication
{
public: 
    CApp();
    ~CApp();

private:
   

private:

    float        m_FieldOfViewY;     // Vertical view angle of the camera

    //CPlayer m_Player;

    float m_PointA[3] = { -0.5f, -1.0f, 0.0f };
    float m_PointB[3] = { 0.5f, -1.0f, 0.0f };
    float m_PointC[3] = { 0.0f,  0.0f, 0.0f };

    CTriangle* m_Triangle = new CTriangle(m_PointA, m_PointB, m_PointC);
    
    CPlayer* m_Player = new CPlayer();

    gfx::BHandle m_pPlayerMesh;


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