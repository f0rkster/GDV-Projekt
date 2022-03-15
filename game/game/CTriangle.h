#pragma once
#include "CShapes.h"
#include "yoshix_fix_function.h"

class CTriangle : public CShapes {
public:
    static constexpr float s_StandardA[3] = { -4.0f, -2.0f, 0.0f };
    static constexpr float s_StandardB[3] = { 4.0f, -2.0f, 0.0f };
    static constexpr float s_StandardC[3] = { 0.0f,  2.0f, 0.0f };
    static constexpr float s_StandardColor[4] = { 1.0f,  1.0f, 1.0f, 1.0f };

public:
    float m_PointA[3];
    float m_PointB[3];
    float m_PointC[3];
    float m_Color[4];
    float m_Vertices[3][3];
    float m_Colors[3][4];
    int   m_Indices[1][3];

public:
    CTriangle();
    CTriangle(float _PointA[3], float _PointB[3], float _PointC[3]);
    CTriangle(float _PointA[3], float _PointB[3], float _PointC[3], float _Color[4]);
    ~CTriangle();
    gfx::SMeshInfo getMeshInfo() override;
protected:
    void fillVertices();
    void fillColors();
    void fillIndices();
};