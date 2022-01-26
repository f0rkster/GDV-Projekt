
#include "yoshix_fix_function.h"

#include <array>
#include <iostream>
#include <math.h>

#include "CBullet.h"
#include "CPlayer.h"
#include "CShield.h"

#include "SKeyState.h"

using namespace gfx;

namespace
{
    class CApplication : public IApplication
    {
    public:

        CApplication();
        virtual ~CApplication();

    private:

    private:

        float       m_FieldOfViewY;     // Vertical view angle of the camera

        BHandle     m_pBulletMesh;
        BHandle     m_pPlayerMesh;
        BHandle     m_pShieldMesh;

        CBullet     m_Bullet;
        CPlayer     m_Player;
        CShield     m_Shields[3];

        SKeyState   m_KeyState;


    private:
        virtual bool InternOnStartup();
        virtual bool InternOnShutdown();
        virtual bool InternOnCreateTextures();
        virtual bool InternOnReleaseTextures();
        virtual bool InternOnCreateMeshes();
        virtual bool InternOnReleaseMeshes();
        virtual bool InternOnResize(int _Width, int _Height);
        virtual bool InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown);
        virtual bool InternOnUpdate();
        virtual bool InternOnFrame();
    };
} // namespace

namespace
{
    CApplication::CApplication()
        : m_FieldOfViewY    (60.0f)
        , m_pBulletMesh     (nullptr)
        , m_pPlayerMesh     (nullptr)
        , m_pShieldMesh     (nullptr)
        , m_Bullet          ()
        , m_Player          ()
        , m_KeyState        ()
    {
    }

    // -----------------------------------------------------------------------------

    CApplication::~CApplication()
    {
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnStartup()
    {
        m_KeyState.m_IsLArrowDown   = false;
        m_KeyState.m_IsRArrowDown   = false;
        m_KeyState.m_IsSpaceDown    = false;

        // -----------------------------------------------------------------------------
        // Define the background color of the window. Colors are always 4D tuples,
        // whereas the components of the tuple represent the red, green, blue, and alpha 
        // channel. The alpha channel indicates the transparency of the color. A value
        // of 1 means the color is completely opaque. A value of 0 means the color is
        // completely transparent. The channels red, green, and blue also are values
        // 0..1 with 0 indicating the minimum intensity and 1 the maximum intensity.
        // -----------------------------------------------------------------------------
        float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f, };

        SetClearColor(ClearColor);

        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnShutdown()
    {
        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnCreateTextures()
    {
        // -----------------------------------------------------------------------------
        // Load an image from the given path and create a YoshiX texture representing
        // the image.
        // -----------------------------------------------------------------------------

        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnReleaseTextures()
    {
        // -----------------------------------------------------------------------------
        // Important to release the texture again when the application is shut down.
        // -----------------------------------------------------------------------------

        return true;
    }

    // -----------------------------------------------------------------------------
    

    bool CApplication::InternOnCreateMeshes()
    {
        m_Bullet.CreateBullet(&m_pBulletMesh);
        m_Player.CreatePlayer(&m_pPlayerMesh);

        for(CShield shield : m_Shields)
        {
            shield.CreateShield(&m_pShieldMesh);
        }

        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnReleaseMeshes()
    {
        // -----------------------------------------------------------------------------
        // Important to release the mesh again when the application is shut down.
        // -----------------------------------------------------------------------------
        ReleaseMesh(m_pBulletMesh);
        ReleaseMesh(m_pPlayerMesh);
        ReleaseMesh(m_pShieldMesh);

        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnResize(int _Width, int _Height)
    {
        ////Ortogonal Camera
        //float zNear = 0.1f;
        //float zFar  = 100.0f;
        //float zoom  = 50.0f;
        //
        //float ProjectionMatrix[16] =
        //{
        //    zoom/_Width,    0,              0,                      0,
        //    0,              zoom/_Height,   0,                      0,
        //    0,              0,              1.0f/(zFar - zNear),    0,
        //    0,              0,              zNear / (zNear - zFar), 1,
        //};

        float ProjectionMatrix[16];
        GetProjectionMatrix(m_FieldOfViewY, static_cast<float>(_Width) / static_cast<float>(_Height), 0.1f, 100.0f, ProjectionMatrix);


        SetProjectionMatrix(ProjectionMatrix);

        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnUpdate()
    {
        float Eye[3];
        float At[3];
        float Up[3];
        
        float ViewMatrix[16];
        
        // -----------------------------------------------------------------------------
        // Define position and orientation of the camera in the world.
        // -----------------------------------------------------------------------------
        Eye[0] = 0.0f; At[0] = 0.0f; Up[0] = 0.0f;
        Eye[1] = 0.0f; At[1] = 0.0f; Up[1] = 1.0f;
        Eye[2] = -20.0f; At[2] = 0.0f; Up[2] = 0.0f;
        
        GetViewMatrix(Eye, At, Up, ViewMatrix);
        
        SetViewMatrix(ViewMatrix);
        m_Bullet.OnUpdate();
        m_Player.OnUpdate(m_KeyState);


        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnFrame()
    {
        float WorldMatrix[16];

        // -----------------------------------------------------------------------------
        // Set the position of the mesh in the world and draw it.
        // -----------------------------------------------------------------------------
        GetTranslationMatrix(m_Player.m_Translation[0], m_Player.m_Translation[1], 0.0f, WorldMatrix);

        SetWorldMatrix(WorldMatrix);

        DrawMesh(m_pPlayerMesh);

        GetTranslationMatrix(m_Bullet.m_Translation[0], m_Bullet.m_Translation[1], 0.0f, WorldMatrix);

        SetWorldMatrix(WorldMatrix);

        DrawMesh(m_pBulletMesh);

        float xPos = -10.0f;
        for (CShield shield : m_Shields)
        {
                shield.m_Translation[0] = xPos;

                GetTranslationMatrix(shield.m_Translation[0], shield.m_Translation[1], 0.0f, WorldMatrix);

                SetWorldMatrix(WorldMatrix);

                DrawMesh(m_pShieldMesh);

                xPos += 10;
        }


        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown)
    {
        if (_Key == 'A')
        {
            m_KeyState.m_IsLArrowDown = _IsKeyDown;
        }
        if (_Key == 'D')
        {
            m_KeyState.m_IsRArrowDown = _IsKeyDown;
        }
        if (_Key == ' ')
        {
            m_KeyState.m_IsSpaceDown = _IsKeyDown;
        }


        return true;
    }
} // namespace

void main()
{
    CApplication Application;

    RunApplication(800, 600, "YoshiX Example", &Application);
}