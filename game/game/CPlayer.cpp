#include "CPlayer.h"

CPlayer::CPlayer()
{
	m_Speed = 0.1f;

	m_Translation[0] = 0.0f;
	m_Translation[1] = -9.0f;
	m_Translation[2] = 0.0f;
	
	m_Health = 3;

	m_State = CPlayer::Idle;
}

void CPlayer::CreatePlayer(gfx::BHandle* _ppMesh)
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
    gfx::SMeshInfo MeshInfo;

    MeshInfo.m_pVertices = &s_PlayerVertices[0][0];
    MeshInfo.m_pNormals = nullptr;
    MeshInfo.m_pColors = &s_PlayerColors[0][0];
    MeshInfo.m_pTexCoords = nullptr;
    MeshInfo.m_NumberOfVertices = 3;
    MeshInfo.m_NumberOfIndices = 3;
    MeshInfo.m_pIndices = &s_PlayerIndices[0][0];
    MeshInfo.m_pTexture = nullptr;

    CreateMesh(MeshInfo, _ppMesh);
}


void CPlayer::OnUpdate(SKeyState _keyState)
{
    switch (m_State)
    {
    case CPlayer::Idle:
    {
        if (_keyState.m_IsLArrowDown) m_State = CPlayer::Left;
        if (_keyState.m_IsRArrowDown) m_State = CPlayer::Right;
        if (_keyState.m_IsSpaceDown)  m_State = CPlayer::Shoot;
    }
    break;

    case CPlayer::Left:
    {
        m_Translation[0] -= m_Speed;

        if (!_keyState.m_IsLArrowDown) m_State = CPlayer::Idle;
    }
    break;

    case CPlayer::Right:
    {
        m_Translation[0] += m_Speed;

        if (!_keyState.m_IsRArrowDown) m_State = CPlayer::Idle;
    }
    break;

    case CPlayer::Shoot:
    {
        if (!_keyState.m_IsSpaceDown) m_State = CPlayer::Idle;
    }
    break;
    }
}

CPlayer::~CPlayer()
{
}
