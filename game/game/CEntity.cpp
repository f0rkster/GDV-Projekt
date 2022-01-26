#include "CEntity.h"
#include <iostream>

CEntity::CEntity() {
	m_Speed = 0.0f;

	m_Translation[0] = 0.0f;
	m_Translation[1] = 0.0f;
	m_Translation[2] = 0.0f;

	m_Scale[0] = 1.0f;
	m_Scale[1] = 1.0f;
	m_Scale[2] = 1.0f;

	m_Rotation[0] = 0.0f;
	m_Rotation[1] = 0.0f;
	m_Rotation[2] = 0.0f;
}

CEntity::~CEntity() {

}