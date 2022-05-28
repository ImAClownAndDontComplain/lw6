#include <limits.h>
#include <string>
#include <C:\glfx-master\include\gl\glfx.h>
#include <assert.h>

#include "shadow_volume_technique.h"

using namespace std;

static const char* pEffectFile = "shadow_volume.glsl";

ShadowVolumeTechnique::ShadowVolumeTechnique() : Technique(pEffectFile)
{   
}


bool ShadowVolumeTechnique::Init()
{
    if (!CompileProgram("ShadowVolume")) {
        return false;
    }
    
    m_VPLocation = GetUniformLocation("gVP");
    m_WorldMatrixLocation = GetUniformLocation("gWorld");
    m_lightPosLocation = GetUniformLocation("gLightPos");

    if (m_VPLocation == INVALID_UNIFORM_LOCATION ||
        m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
        m_lightPosLocation == INVALID_UNIFORM_LOCATION) {
        return false;
    }
            
    return true;
}


void ShadowVolumeTechnique::SetVP(const Matrix4f& VP)
{
    glUniformMatrix4fv(m_VPLocation, 1, GL_TRUE, (const GLfloat*)VP.m);    
}


void ShadowVolumeTechnique::SetWorldMatrix(const Matrix4f& WorldInverse)
{
    glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.m);
}


void ShadowVolumeTechnique::SetLightPos(const Vector3f& Pos)
{
    glUniform3f(m_lightPosLocation, Pos.x, Pos.y, Pos.z);
}