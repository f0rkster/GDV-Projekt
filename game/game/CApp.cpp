#include "CApp.h"
#include "yoshix_fix_function.h"

#include "Data.h"

CApp::CApp()
    : m_pGame(nullptr)
    , m_FieldOfViewY(60.0f)    // Set the vertical view angle of the camera to 60 degrees.
    , m_pPlayerMesh(nullptr)
    , m_pShieldMesh(nullptr)
    , m_pEnemyMesh(nullptr)
    , m_pBulletMesh(nullptr)
    , m_pBackgroundMesh(nullptr)
{
}

CApp::~CApp() {
    delete m_pGame;
    delete m_Background;
}

bool CApp::InternOnStartup() {

    this->m_pGame = new CGame(&this->m_pPlayerMesh, &this->m_pShieldMesh, &this->m_pEnemyMesh, &this->m_pBulletMesh);

    // -----------------------------------------------------------------------------
    // Background
    // -----------------------------------------------------------------------------
    float BackgroundWidth = WIDTH;
    float BackgroundHeight = HEIGHT;
    float BackgroundA[3] = { -WIDTH / 2, -HEIGHT / 2, 0 };
    float BackgroundB[3] = {  WIDTH / 2, -HEIGHT / 2, 0 };
    float BackgroundC[3] = {  WIDTH / 2,  HEIGHT / 2, 0 };
    float BackgroundD[3] = { -WIDTH / 2,  HEIGHT / 2, 0 };
    float BackgroundGreyValue = 0.15;
    float BackgroundColor[4] = { BackgroundGreyValue, BackgroundGreyValue, BackgroundGreyValue, 1.0f };
    this->m_Background = new CRectangle(BackgroundA, BackgroundB, BackgroundC, BackgroundD, BackgroundColor);

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
    gfx::CreateMesh(m_pGame->m_pPlayer->getMeshInfo(), &this->m_pPlayerMesh);
    gfx::CreateMesh(m_pGame->m_pShields[0]->getMeshInfo(), &this->m_pShieldMesh);
    gfx::CreateMesh(m_Background->getMeshInfo(), &this->m_pBackgroundMesh);
    return true;
}

bool CApp::InternOnReleaseMeshes() {

    gfx::ReleaseMesh(this->m_pPlayerMesh);
    gfx::ReleaseMesh(this->m_pShieldMesh);
    gfx::ReleaseMesh(this->m_pBackgroundMesh);
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
    if (_Key == 'A') m_KeyState.m_isAdown = _IsKeyDown;
    if (_Key == 'D') m_KeyState.m_isDdown = _IsKeyDown;
    return true;
}

bool CApp::InternOnUpdate() {
    float Eye[3];
    float At[3];
    float Up[3];

    float ViewMatrix[16];

    m_pGame->runGame(&m_KeyState);

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
    gfx::DrawMesh(this->m_pPlayerMesh);

    for (CShield* s : m_pGame->m_pShields) {
        gfx::GetTranslationMatrix(s->m_Translation[0], s->m_Translation[1], s->m_Translation[2], WorldMatrix);
        gfx::SetWorldMatrix(WorldMatrix);
        gfx::DrawMesh(this->m_pShieldMesh);
    }


    // -----------------------------------------------------------------------------
    // Background
    // -----------------------------------------------------------------------------
    gfx::GetTranslationMatrix(m_Background->m_Translation[0], m_Background->m_Translation[1], m_Background->m_Translation[2], WorldMatrix);
    gfx::SetWorldMatrix(WorldMatrix);
    gfx::DrawMesh(this->m_pBackgroundMesh);

    return true;
}
