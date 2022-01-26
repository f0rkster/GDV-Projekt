#include "yoshix_fix_function.h"

#include "CBullet.h"

CBullet::CBullet() {
    m_Speed = 0.1f;
    m_State = CBullet::Up;
    m_Translation[0] = 0.0f;
    m_Translation[1] = 0.0f;
    m_Translation[2] = 0.0f;
}

void CBullet::CreateBullet(gfx::BHandle* _ppMesh)
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
    gfx::SMeshInfo MeshInfo;

    MeshInfo.m_pVertices = &s_BulletVertices[0][0];
    MeshInfo.m_pNormals = nullptr;
    MeshInfo.m_pColors = &s_BulletColors[0][0];
    MeshInfo.m_pTexCoords = nullptr;
    MeshInfo.m_NumberOfVertices = 4;
    MeshInfo.m_NumberOfIndices = 6;
    MeshInfo.m_pIndices = &s_BulletIndices[0][0];
    MeshInfo.m_pTexture = nullptr;

    CreateMesh(MeshInfo, _ppMesh);
}

void CBullet::OnUpdate()
{
    switch (m_State)
    {
    case CBullet::Up:
    {
        m_Translation[1] += m_Speed;
    }
    break;
    case CBullet::Down:
    {
        m_Translation[1] -= m_Speed;
    }
    break;
    }
}

CBullet::~CBullet(){}