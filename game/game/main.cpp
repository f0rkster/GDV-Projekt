
#include "yoshix_fix_function.h"

#include <array>
#include <iostream>
#include <math.h>

#include "SBullet.h"
#include "SKeyState.h"
#include "SPlayer.h"

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

        SBullet     m_Bullet;
        SPlayer     m_Player;

        SKeyState   m_KeyState;

    private:
        void CreatePlayer(BHandle* _ppMesh);
        void CreateBullet(BHandle* _ppMesh);


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
        m_Bullet.m_Speed            = 0.1f;
        m_Bullet.m_State            = SBullet::Up;
        m_Bullet.m_Translation[0]   = 0.0f;
        m_Bullet.m_Translation[1]   = 0.0f;
        m_Bullet.m_Translation[2]   = 0.0f;

        m_Player.m_Speed            = 0.1f;
        m_Player.m_State            = SPlayer::Idle;
        m_Player.m_Translation[0]   = 0.0f;
        m_Player.m_Translation[1]   = -9.0f;
        m_Player.m_Translation[2]   = 0.0f;
        m_Player.m_Health           = 3;

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
    void CApplication::CreateBullet(BHandle* _ppMesh) 
    {
        // -----------------------------------------------------------------------------
        // Define the vertices of the mesh and their attributes.
        // -----------------------------------------------------------------------------

        static float s_Size = 0.1;

        static float s_BulletVertices[][3] =
        {
            { -1.0f * s_Size, -3.0f * s_Size, 0.0f * s_Size, },
            {  1.0f * s_Size, -3.0f * s_Size, 0.0f * s_Size, },
            {  1.0f * s_Size,  3.0f * s_Size, 0.0f * s_Size, },
            { -1.0f * s_Size,  3.0f * s_Size, 0.0f * s_Size, },
        };

        static float s_BulletColors[][4] =
        {
            { 1.0f, 1.0f, 1.0f, 1.0f, },        // Color of vertex 0.
            { 1.0f, 1.0f, 1.0f, 1.0f, },        // Color of vertex 1.
            { 1.0f, 1.0f, 1.0f, 1.0f, },        // Color of vertex 2.
            { 1.0f, 1.0f, 1.0f, 1.0f, },        // Color of vertex 3
        };

        // -----------------------------------------------------------------------------
        // Define the topology of the mesh via indices. An index addresses a vertex from
        // the array above. Three indices represent one triangle. When defining the 
        // triangles of a mesh imagine that you are standing in front of the triangle 
        // and looking to the center of the triangle. If the mesh represents a closed
        // body such as a cube, your view position has to be outside of the body. Now
        // define the indices of the addressed vertices of the triangle in counter-
        // clockwise order.
        // -----------------------------------------------------------------------------
        static int s_BulletIndices[][3] =
        {
            { 0, 1, 2, },
            { 0, 2, 3, },
        };

        // -----------------------------------------------------------------------------
        // Define the mesh and its material. The material defines the look of the
        // surface covering the mesh. If the material should contain normals, colors, or
        // texture coordinates then their number has to match the number of vertices.
        // If you do not support normals in a mesh, YoshiX will not apply lighting to
        // this mesh. A textured mesh always has to contain texture coordinates and a
        // handle to a texture. A mesh always has to contain vertices and indices.
        // -----------------------------------------------------------------------------
        SMeshInfo MeshInfo;

        MeshInfo.m_pVertices        = &s_BulletVertices[0][0];
        MeshInfo.m_pNormals         = nullptr;
        MeshInfo.m_pColors          = &s_BulletColors[0][0];
        MeshInfo.m_pTexCoords       = nullptr;
        MeshInfo.m_NumberOfVertices = 4;
        MeshInfo.m_NumberOfIndices  = 6;
        MeshInfo.m_pIndices         = &s_BulletIndices[0][0];
        MeshInfo.m_pTexture         = nullptr;

        CreateMesh(MeshInfo, _ppMesh);    
    }
    
    void CApplication::CreatePlayer(BHandle* _ppMesh)
    {
        // -----------------------------------------------------------------------------
        // Define the vertices of the mesh and their attributes.
        // -----------------------------------------------------------------------------
        static float s_Size = 0.3;

        static float s_PlayerVertices[][3] =
        {
            { -4.0f * s_Size, -2.0f * s_Size, 0.0f * s_Size, },
            {  4.0f * s_Size, -2.0f * s_Size, 0.0f * s_Size, },
            {  0.0f * s_Size,  2.0f * s_Size, 0.0f * s_Size, },
        };

        static float s_PlayerColors[][4] =
        {
            { 0.0f, 1.0f, 0.0f, 1.0f, },        // Color of vertex 0.
            { 0.0f, 1.0f, 0.0f, 1.0f, },        // Color of vertex 1.
            { 0.0f, 1.0f, 0.0f, 1.0f, },        // Color of vertex 2.
        };

        // -----------------------------------------------------------------------------
        // Define the topology of the mesh via indices. An index addresses a vertex from
        // the array above. Three indices represent one triangle. When defining the 
        // triangles of a mesh imagine that you are standing in front of the triangle 
        // and looking to the center of the triangle. If the mesh represents a closed
        // body such as a cube, your view position has to be outside of the body. Now
        // define the indices of the addressed vertices of the triangle in counter-
        // clockwise order.
        // -----------------------------------------------------------------------------
        static int s_PlayerIndices[][3] =
        {
            { 0, 1, 2, },
        };


        // -----------------------------------------------------------------------------
        // Define the mesh and its material. The material defines the look of the
        // surface covering the mesh. If the material should contain normals, colors, or
        // texture coordinates then their number has to match the number of vertices.
        // If you do not support normals in a mesh, YoshiX will not apply lighting to
        // this mesh. A textured mesh always has to contain texture coordinates and a
        // handle to a texture. A mesh always has to contain vertices and indices.
        // -----------------------------------------------------------------------------
        SMeshInfo MeshInfo;

        MeshInfo.m_pVertices        = &s_PlayerVertices[0][0];
        MeshInfo.m_pNormals         = nullptr;
        MeshInfo.m_pColors          = &s_PlayerColors[0][0];
        MeshInfo.m_pTexCoords       = nullptr;
        MeshInfo.m_NumberOfVertices = 3;
        MeshInfo.m_NumberOfIndices  = 3;
        MeshInfo.m_pIndices         = &s_PlayerIndices[0][0];
        MeshInfo.m_pTexture         = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

    bool CApplication::InternOnCreateMeshes()
    {
        CreateBullet(&m_pBulletMesh);
        CreatePlayer(&m_pPlayerMesh);

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


        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnResize(int _Width, int _Height)
    {

        float zNear = 0.1f;
        float zFar  = 100.0f;
        float zoom  = 50.0f;

        float ProjectionMatrix[16] =
        {
            zoom/_Width,    0,              0,                      0,
            0,              zoom/_Height,   0,                      0,
            0,              0,              1.0f/(zFar - zNear),    0,
            0,              0,              zNear / (zNear - zFar), 1,
        };

        // GetProjectionMatrix(m_FieldOfViewY, static_cast<float>(_Width) / static_cast<float>(_Height), 0.1f, 100.0f, ProjectionMatrix);


        SetProjectionMatrix(ProjectionMatrix);

        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnUpdate()
    {
        //float Eye[3];
        //float At[3];
        //float Up[3];
        //
        //float ViewMatrix[16];
        //
        //// -----------------------------------------------------------------------------
        //// Define position and orientation of the camera in the world.
        //// -----------------------------------------------------------------------------
        //Eye[0] = 0.0f; At[0] = 0.0f; Up[0] = 0.0f;
        //Eye[1] = 0.0f; At[1] = 0.0f; Up[1] = 1.0f;
        //Eye[2] = -8.0f; At[2] = 0.0f; Up[2] = 0.0f;
        //
        //GetViewMatrix(Eye, At, Up, ViewMatrix);
        //
        //SetViewMatrix(ViewMatrix);
        
        switch (m_Bullet.m_State)
        {
            case SBullet::Up:
            {
                m_Bullet.m_Translation[1] += m_Bullet.m_Speed;
            }
            case SBullet::Down:
            {
                m_Bullet.m_Translation[1] -= m_Bullet.m_Speed;
            }
            break;
        }

        switch (m_Player.m_State)
        {
            case SPlayer::Idle:
            {
                if (m_KeyState.m_IsLArrowDown) m_Player.m_State = SPlayer::Left;
                if (m_KeyState.m_IsRArrowDown) m_Player.m_State = SPlayer::Right;
                if (m_KeyState.m_IsSpaceDown)  m_Player.m_State = SPlayer::Shoot;
            }
            break;

            case SPlayer::Left:
            {
                m_Player.m_Translation[0] -= m_Player.m_Speed;

                if (!m_KeyState.m_IsLArrowDown) m_Player.m_State = SPlayer::Idle;
            }
            break;

            case SPlayer::Right:
            {
                m_Player.m_Translation[0] += m_Player.m_Speed;

                if (!m_KeyState.m_IsRArrowDown) m_Player.m_State = SPlayer::Idle;
            }
            break;

            case SPlayer::Shoot:
            {
                if (!m_KeyState.m_IsSpaceDown) m_Player.m_State = SPlayer::Idle;
            }
            break;
        }

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