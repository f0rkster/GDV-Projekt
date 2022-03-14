#include "CRectangle.h"

#include "yoshix_fix_function.h"
#include <iostream>

CRectangle::CRectangle()
{
    memcpy(m_PointA, s_StandardA, sizeof(m_PointA));
    memcpy(m_PointB, s_StandardB, sizeof(m_PointB));
    memcpy(m_PointC, s_StandardC, sizeof(m_PointC));
    memcpy(m_PointD, s_StandardD, sizeof(m_PointD));
    memcpy(m_Color, s_StandardColor, sizeof(m_Color));

    fillVertices();
    fillColors();
    fillIndices();
}

CRectangle::CRectangle(float _PointA[3], float _PointB[3], float _PointC[3], float _PointD[3])
{
    memcpy(m_PointA, _PointA, sizeof(m_PointA));
    memcpy(m_PointB, _PointB, sizeof(m_PointB));
    memcpy(m_PointC, _PointC, sizeof(m_PointC));
    memcpy(m_PointD, _PointD, sizeof(m_PointD));
    memcpy(m_Color, s_StandardColor, sizeof(m_Color));

    fillVertices();
    fillColors();
    fillIndices();
}

CRectangle::CRectangle(float _PointA[3], float _PointB[3], float _PointC[3], float _PointD[3], float _Color[4])
{
    memcpy(m_PointA, _PointA, sizeof(m_PointA));
    memcpy(m_PointB, _PointB, sizeof(m_PointB));
    memcpy(m_PointC, _PointC, sizeof(m_PointC));
    memcpy(m_PointD, _PointD, sizeof(m_PointD));
    memcpy(m_Color, _Color, sizeof(m_Color));

    fillVertices();
    fillColors();
    fillIndices();
}

CRectangle::~CRectangle(){
}

void CRectangle::fillVertices() {
    m_Vertices[0][0] = m_PointA[0];
    m_Vertices[0][1] = m_PointA[1];
    m_Vertices[0][2] = m_PointA[2];
    m_Vertices[1][0] = m_PointB[0];
    m_Vertices[1][1] = m_PointB[1];
    m_Vertices[1][2] = m_PointB[2];
    m_Vertices[2][0] = m_PointC[0];
    m_Vertices[2][1] = m_PointC[1];
    m_Vertices[2][2] = m_PointC[2];
    m_Vertices[3][0] = m_PointD[0];
    m_Vertices[3][1] = m_PointD[1];
    m_Vertices[3][2] = m_PointD[2];
}

void CRectangle::fillColors() {
    m_Colors[0][0] = m_Color[0];
    m_Colors[0][1] = m_Color[1];
    m_Colors[0][2] = m_Color[2];
    m_Colors[0][3] = m_Color[3];
    m_Colors[1][0] = m_Color[0];
    m_Colors[1][1] = m_Color[1];
    m_Colors[1][2] = m_Color[2];
    m_Colors[1][3] = m_Color[3];
    m_Colors[2][0] = m_Color[0];
    m_Colors[2][1] = m_Color[1];
    m_Colors[2][2] = m_Color[2];
    m_Colors[2][3] = m_Color[3];
    m_Colors[3][0] = m_Color[0];
    m_Colors[3][1] = m_Color[1];
    m_Colors[3][2] = m_Color[2];
    m_Colors[3][3] = m_Color[3];
}

void CRectangle::fillIndices() {
    m_Indices[0][0] = 0;
    m_Indices[0][1] = 1;
    m_Indices[0][2] = 2;
    m_Indices[1][0] = 0;
    m_Indices[1][1] = 2;
    m_Indices[1][2] = 3;
}

gfx::SMeshInfo CRectangle::getMeshInfo() {
    gfx::SMeshInfo MeshInfo;

    MeshInfo.m_pVertices = &m_Vertices[0][0];
    MeshInfo.m_pNormals = nullptr;
    MeshInfo.m_pColors = &m_Colors[0][0];
    MeshInfo.m_pTexCoords = nullptr;
    MeshInfo.m_NumberOfVertices = 4;
    MeshInfo.m_NumberOfIndices = 6;
    MeshInfo.m_pIndices = &m_Indices[0][0];
    MeshInfo.m_pTexture = nullptr;

    return MeshInfo;
}