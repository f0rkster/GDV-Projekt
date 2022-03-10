#pragma once
#include "CShapes.h"

class CRectangle : public CShapes
{
public:
    static constexpr float s_StandardA[3] = { -1.0f, -1.0f, 0.0f };
    static constexpr float s_StandardB[3] = {  1.0f, -1.0f, 0.0f };
    static constexpr float s_StandardC[3] = {  1.0f,  1.0f, 0.0f };
    static constexpr float s_StandardD[3] = { -1.0f,  1.0f, 0.0f };
    static constexpr float s_StandardColor[4] = { 1.0f,  1.0f, 1.0f, 1.0f };

private:
    float m_PointA[3];
    float m_PointB[3];
    float m_PointC[3];
    float m_PointD[3];
    float m_Color[4];
    float m_Vertices[4][3];
    float m_Colors[4][4];
    int   m_Indices[2][3];

public:
    CRectangle();
    CRectangle(float _PointA[3], float _PointB[3], float _PointC[3], float _PointD[3]);
    CRectangle(float _PointA[3], float _PointB[3], float _PointC[3], float _PointD[3], float _Color[4]);
    ~CRectangle();
    gfx::SMeshInfo getMeshInfo() override;
protected:
    void fillVertices();
    void fillColors();
    void fillIndices();

};

