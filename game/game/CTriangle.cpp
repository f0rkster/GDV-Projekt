#include "CTriangle.h"
#include "yoshix_fix_function.h"
#include <iostream>

CTriangle::CTriangle()
{
    memcpy(this->m_PointA, this->s_StandardA, sizeof(this->m_PointA));
    memcpy(this->m_PointB, this->s_StandardB, sizeof(this->m_PointB));
    memcpy(this->m_PointC, this->s_StandardC, sizeof(this->m_PointC));
    memcpy(this->m_Color,  this->s_StandardColor, sizeof(this->m_Color));

    fillVertices();
    fillColors();
    fillIndices();
}

CTriangle::CTriangle(float _PointA[3], float _PointB[3], float _PointC[3])
{
    memcpy(this->m_PointA, _PointA, sizeof(this->m_PointA));
    memcpy(this->m_PointB, _PointB, sizeof(this->m_PointB));
    memcpy(this->m_PointC, _PointC, sizeof(this->m_PointC));
    memcpy(this->m_Color,  this->s_StandardColor, sizeof(this->m_Color));

    fillVertices();
    fillColors();
    fillIndices();
}

CTriangle::CTriangle(float _PointA[3], float _PointB[3], float _PointC[3], float _Color[4])
{
    memcpy(this->m_PointA, _PointA, sizeof(this->m_PointA));
    memcpy(this->m_PointB, _PointB, sizeof(this->m_PointB));
    memcpy(this->m_PointC, _PointC, sizeof(this->m_PointC));
    memcpy(this->m_Color,  _Color,  sizeof(this->m_Color));

    fillVertices();
    fillColors();
    fillIndices();
}

CTriangle::~CTriangle()
{
}

void CTriangle::fillVertices() {
    this->m_Vertices[0][0] = this->m_PointA[0];
    this->m_Vertices[0][1] = this->m_PointA[1];
    this->m_Vertices[0][2] = this->m_PointA[2];
    this->m_Vertices[1][0] = this->m_PointB[0];
    this->m_Vertices[1][1] = this->m_PointB[1];
    this->m_Vertices[1][2] = this->m_PointB[2];
    this->m_Vertices[2][0] = this->m_PointC[0];
    this->m_Vertices[2][1] = this->m_PointC[1];
    this->m_Vertices[2][2] = this->m_PointC[2];
}

void CTriangle::fillColors() {
    this->m_Colors[0][0] = this->m_Color[0];
    this->m_Colors[0][1] = this->m_Color[1];
    this->m_Colors[0][2] = this->m_Color[2];
    this->m_Colors[0][3] = this->m_Color[3];
    this->m_Colors[1][0] = this->m_Color[0];
    this->m_Colors[1][1] = this->m_Color[1];
    this->m_Colors[1][2] = this->m_Color[2];
    this->m_Colors[1][3] = this->m_Color[3];
    this->m_Colors[2][0] = this->m_Color[0];
    this->m_Colors[2][1] = this->m_Color[1];
    this->m_Colors[2][2] = this->m_Color[2];
    this->m_Colors[2][3] = this->m_Color[3];
}

void CTriangle::fillIndices() {
    this->m_Indices[0][0] = 0;
    this->m_Indices[0][1] = 1;
    this->m_Indices[0][2] = 2;
}

gfx::SMeshInfo CTriangle::getMeshInfo(){
    gfx::SMeshInfo MeshInfo;

    MeshInfo.m_pVertices = &this->m_Vertices[0][0];
    MeshInfo.m_pNormals = nullptr;
    MeshInfo.m_pColors = &this->m_Colors[0][0];
    MeshInfo.m_pTexCoords = nullptr;
    MeshInfo.m_NumberOfVertices = 3;
    MeshInfo.m_NumberOfIndices = 3;
    MeshInfo.m_pIndices = &this->m_Indices[0][0];
    MeshInfo.m_pTexture = nullptr;

    return MeshInfo;
}
