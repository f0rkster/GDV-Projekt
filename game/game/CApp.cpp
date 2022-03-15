#include "CApp.h"
#include "yoshix_fix_function.h"

#include "Data.h"

#include <iostream>

CApp::CApp()
    : m_pGame(nullptr)
    , m_FieldOfViewY(60.0f)    // Set the vertical view angle of the camera to 60 degrees.
    , m_pPlayerMesh(nullptr)
    , m_pShieldMesh(nullptr)
    , m_pEnemyMesh(nullptr)
    , m_pBulletMesh(nullptr)
    , m_pBottomLineMesh(nullptr)
    , m_pBackgroundMesh(nullptr)
{

    // -----------------------------------------------------------------------------
    // Background
    // -----------------------------------------------------------------------------
    float BackgroundA[3] = { -WIDTH / 2, -HEIGHT / 2, 0 };
    float BackgroundB[3] = { WIDTH / 2, -HEIGHT / 2, 0 };
    float BackgroundC[3] = { WIDTH / 2,  HEIGHT / 2, 0 };
    float BackgroundD[3] = { -WIDTH / 2,  HEIGHT / 2, 0 };
    float BackgroundGreyValue = 0.15;
    float BackgroundColor[4] = { BackgroundGreyValue, BackgroundGreyValue, BackgroundGreyValue, 1.0f };
    m_Background = new CRectangle(BackgroundA, BackgroundB, BackgroundC, BackgroundD, BackgroundColor);

    float BottomLineHeight = 0.05f;
    float BottomLineA[3] = { -WIDTH / 2, -BottomLineHeight / 2, 0 };
    float BottomLineB[3] = { WIDTH / 2, -BottomLineHeight / 2, 0 };
    float BottomLineC[3] = { WIDTH / 2,  BottomLineHeight / 2, 0 };
    float BottomLineD[3] = { -WIDTH / 2,  BottomLineHeight / 2, 0 };
    float BottomLineColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
    m_BottomLine = new CRectangle(BottomLineA, BottomLineB, BottomLineC, BottomLineD, BottomLineColor);
    float YPos = -1.5f;
    m_BottomLine->m_Translation[1] = YPos;

}

CApp::~CApp() {
    delete m_pGame;
    delete m_Background;
    delete m_BottomLine;
}

bool CApp::InternOnStartup() {

    m_pGame = new CGame(&m_pPlayerMesh, &m_pShieldMesh, &m_pEnemyMesh, &m_pBulletMesh);

    // -----------------------------------------------------------------------------
    // Define the background color of the window. Colors are always 4D tuples,
    // whereas the components of the tuple represent the red, green, blue, and alpha 
    // channel. The alpha channel indicates the transparency of the color. A value
    // of 1 means the color is completely opaque. A value of 0 means the color is
    // completely transparent. The channels red, green, and blue also are values
    // 0..1 with 0 indicating the minimum intensity and 1 the maximum intensity.
    // -----------------------------------------------------------------------------
    float ClearColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f, };

    gfx::SetClearColor(ClearColor);

    return true;
}

bool CApp::InternOnShutdown() {
    return true;
}

bool CApp::InternOnCreateMeshes() {
    gfx::CreateMesh(m_pGame->m_pPlayer->getMeshInfo(), &m_pPlayerMesh);

    for (CShield* s : m_pGame->m_pShields)
    {
        gfx::CreateMesh(s->getMeshInfo(), &m_pShieldMesh);
    }

    for (CBullet* b : m_pGame->m_pPlayer->m_Bullets)
    {
        gfx::CreateMesh(b->getMeshInfo(), &m_pBulletMesh);
    }

    for (CEnemy* e : m_pGame->m_pEnemies)
    {
        gfx::CreateMesh(e->getMeshInfo(), &m_pEnemyMesh);
    }


    gfx::CreateMesh(m_BottomLine->getMeshInfo(), &m_pBottomLineMesh);
    gfx::CreateMesh(m_Background->getMeshInfo(), &m_pBackgroundMesh);
    return true;
}

bool CApp::InternOnReleaseMeshes() {

    gfx::ReleaseMesh(m_pPlayerMesh);
    gfx::ReleaseMesh(m_pShieldMesh);
    gfx::ReleaseMesh(m_pBulletMesh);
    gfx::ReleaseMesh(m_pEnemyMesh);
    gfx::ReleaseMesh(m_pBottomLineMesh);
    gfx::ReleaseMesh(m_pBackgroundMesh);
    return true;
}

bool CApp::InternOnResize(int _Width, int _Height) {
    float ProjectionMatrix[16];

    // -----------------------------------------------------------------------------
    // The projection matrix defines the size of the camera frustum. The YoshiX
    // camera has the shape of a pyramid with the eye position at the top of the
    // pyramid. The horizontal view angle is defined by the vertical view angle
    // and the ratio between window width and window height.
    // -----------------------------------------------------------------------------
    gfx::GetProjectionMatrix(m_FieldOfViewY, static_cast<float>(_Width) / static_cast<float>(_Height), 0.1f, 100.0f, ProjectionMatrix);

    gfx::SetProjectionMatrix(ProjectionMatrix);

    return true;
}

bool CApp::InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown) {
    if (_Key == ' ') m_KeyState.m_isSPACEdown = _IsKeyDown;
    if (_Key == 'A' || _Key == 37) m_KeyState.m_isAdown = _IsKeyDown; // 37 is the Left Arrow https://stackoverflow.com/questions/2876275/what-are-the-ascii-values-of-up-down-left-right
    if (_Key == 'D' || _Key == 39) m_KeyState.m_isDdown = _IsKeyDown; // 39 is the Right Arrow https://stackoverflow.com/questions/2876275/what-are-the-ascii-values-of-up-down-left-right
    return true;
}

bool CApp::InternOnUpdate() {
    float Eye[3];
    float At[3];
    float Up[3];

    float ViewMatrix[16];

    switch (m_pGame->m_State)
    {
    case EGameState::START:
        break;
    case EGameState::RUN:
        m_pGame->RunGame(&m_KeyState);
        break;
    case EGameState::GAMEOVER:
        m_pGame->FinalizedGame();
        break;
    case EGameState::PAUSED:
        break;
    }

    // -----------------------------------------------------------------------------
    // Define position and orientation of the camera in the world.
    // -----------------------------------------------------------------------------
    Eye[0] = 0.0f; At[0] = 0.0f; Up[0] = 0.0f;
    Eye[1] = 0.0f; At[1] = 0.0f; Up[1] = 1.0f;
    Eye[2] = -8.0f; At[2] = 0.0f; Up[2] = 0.0f;

    gfx::GetViewMatrix(Eye, At, Up, ViewMatrix);

    gfx::SetViewMatrix(ViewMatrix);

    return true;
}

bool CApp::InternOnFrame() {
    float WorldMatrix[16];

    // -----------------------------------------------------------------------------
    // Set the position of the mesh in the world and draw it.
    // -----------------------------------------------------------------------------
    gfx::GetTranslationMatrix(m_pGame->m_pPlayer->m_Translation[0], m_pGame->m_pPlayer->m_Translation[1], m_pGame->m_pPlayer->m_Translation[2], WorldMatrix);
    gfx::SetWorldMatrix(WorldMatrix);
    gfx::DrawMesh(m_pPlayerMesh);

    for (CShield* s : m_pGame->m_pShields) {
        gfx::GetTranslationMatrix(s->m_Translation[0], s->m_Translation[1], s->m_Translation[2], WorldMatrix);
        gfx::SetWorldMatrix(WorldMatrix);
        gfx::DrawMesh(m_pShieldMesh);
    }

    for (CBullet* b : m_pGame->m_pPlayer->m_Bullets) {
        gfx::GetTranslationMatrix(b->m_Translation[0], b->m_Translation[1], b->m_Translation[2], WorldMatrix);
        gfx::SetWorldMatrix(WorldMatrix);
        gfx::DrawMesh(m_pBulletMesh);
    }

    for (CEnemy* e : m_pGame->m_pEnemies) {
        gfx::GetTranslationMatrix(e->m_Translation[0], e->m_Translation[1], e->m_Translation[2], WorldMatrix);
        gfx::SetWorldMatrix(WorldMatrix);
        gfx::DrawMesh(m_pEnemyMesh);
    }

    for (CBullet* b : m_pGame->m_EnemieBullets) {
        gfx::GetTranslationMatrix(b->m_Translation[0], b->m_Translation[1], b->m_Translation[2], WorldMatrix);
        gfx::SetWorldMatrix(WorldMatrix);
        gfx::DrawMesh(m_pBulletMesh);
    }

    // -----------------------------------------------------------------------------
    // Background
    // -----------------------------------------------------------------------------
    gfx::GetTranslationMatrix(m_BottomLine->m_Translation[0], m_BottomLine->m_Translation[1], m_BottomLine->m_Translation[2], WorldMatrix);
    gfx::SetWorldMatrix(WorldMatrix);
    gfx::DrawMesh(m_pBottomLineMesh);

    gfx::GetTranslationMatrix(m_Background->m_Translation[0], m_Background->m_Translation[1], m_Background->m_Translation[2], WorldMatrix);
    gfx::SetWorldMatrix(WorldMatrix);
    gfx::DrawMesh(m_pBackgroundMesh);

    return true;
}
