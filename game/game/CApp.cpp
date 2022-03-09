#include "CApp.h"
#include "yoshix_fix_function.h"

CApp::CApp()
    : m_FieldOfViewY(60.0f)    // Set the vertical view angle of the camera to 60 degrees.
    , m_pPlayerMesh(nullptr)
    , m_pShieldMesh(nullptr)
{
}

CApp::~CApp() {

}

bool CApp::InternOnStartup() {

    // -----------------------------------------------------------------------------
    // Define the background color of the window. Colors are always 4D tuples,
    // whereas the components of the tuple represent the red, green, blue, and alpha 
    // channel. The alpha channel indicates the transparency of the color. A value
    // of 1 means the color is completely opaque. A value of 0 means the color is
    // completely transparent. The channels red, green, and blue also are values
    // 0..1 with 0 indicating the minimum intensity and 1 the maximum intensity.
    // -----------------------------------------------------------------------------
    float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f, };

    gfx::SetClearColor(ClearColor);

    return true;
}

bool CApp::InternOnShutdown() {
    return true;
}

bool CApp::InternOnCreateMeshes() {
    gfx::CreateMesh(m_Player->getMeshInfo(), &this->m_pPlayerMesh);
    gfx::CreateMesh(m_Shield->getMeshInfo(), &this->m_pShieldMesh);
    return true;
}

bool CApp::InternOnReleaseMeshes() {

    gfx::ReleaseMesh(this->m_pPlayerMesh);
    gfx::ReleaseMesh(this->m_pShieldMesh);
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
    return true;
}

bool CApp::InternOnUpdate() {
    float Eye[3];
    float At[3];
    float Up[3];

    float ViewMatrix[16];

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
    gfx::GetTranslationMatrix(0.0f, 0.0f, 0.0f, WorldMatrix);

    gfx::SetWorldMatrix(WorldMatrix);

    gfx::DrawMesh(this->m_pPlayerMesh);
    gfx::DrawMesh(this->m_pShieldMesh);

    return true;
}
