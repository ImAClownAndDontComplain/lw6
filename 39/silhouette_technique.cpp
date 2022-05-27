#include <limits.h>
#include <string>
#include <C:\glfx-master\include\gl\glfx.h>
#include <assert.h>

#include "silhouette_technique.h"
#include "util.h"

using namespace std;

static const char* pEffectFile = "silhouette.glsl";

SilhouetteTechnique::SilhouetteTechnique() : Technique(pEffectFile)
{   
}


bool SilhouetteTechnique::Init()
{
    if (!CompileProgram("Silhouette")) {
        return false;
    }
    
    m_WVPLocation = GetUniformLocation("gWVP");
    m_WorldMatrixLocation = GetUniformLocation("gWorld");
    m_lightPosLocation = GetUniformLocation("gLightPos");

    return true;
}


void SilhouetteTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);    
}


void SilhouetteTechnique::SetWorldMatrix(const Matrix4f& WorldInverse)
{
    glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.m);
}


void SilhouetteTechnique::SetLightPos(const Vector3f& Pos)
{
    glUniform3f(m_lightPosLocation, Pos.x, Pos.y, Pos.z);
}