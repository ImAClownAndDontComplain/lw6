#include "shadow_map_technique.h"
#include "pipeline.h"


ShadowMapTechnique::ShadowMapTechnique()
{
}

bool ShadowMapTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "shaders/shadow_map.vs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "shaders/shadow_map.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    m_WVPLocation = GetUniformLocation("gWVP");
    m_WorldMatrixLocation = GetUniformLocation("gWorld");
    m_lightWorldPosLoc = GetUniformLocation("gLightWorldPos");

    if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
	m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
        m_lightWorldPosLoc == INVALID_UNIFORM_LOCATION) {
        return false;
    }

    return true;
}


void ShadowMapTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}


void ShadowMapTechnique::SetWorld(const Matrix4f& World)
{
    glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)World.m);
}

void ShadowMapTechnique::SetLightWorldPos(const Vector3f& Pos)
{
    glUniform3f(m_lightWorldPosLoc, Pos.x, Pos.y, Pos.z);    
}