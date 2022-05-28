#include <limits.h>
#include "math_3d.h"
#include <string>
#include <C:/glfx-master/include/gl/glfx.h>


#include "lighting_technique.h"
#include "util.h"

using namespace std;

LightingTechnique::LightingTechnique()
{   
}


bool LightingTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "shaders/lighting.vs")) {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "shaders/lighting.fs")) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }
    
    m_WVPLocation = GetUniformLocation("gWVP");
    m_WorldMatrixLocation = GetUniformLocation("gWorld");
    m_samplerLocation = GetUniformLocation("gColorMap");
    m_shadowMapLocation = GetUniformLocation("gShadowMap");
    m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
    m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
    m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");

    if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
        m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
        m_samplerLocation == INVALID_UNIFORM_LOCATION ||
        m_shadowMapLocation == INVALID_UNIFORM_LOCATION ||
        m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
        m_matSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
        m_matSpecularPowerLocation == INVALID_UNIFORM_LOCATION) {
        return false;
    }

    m_pointLightLocation.Color = GetUniformLocation("gPointLight.Base.Color");
    m_pointLightLocation.AmbientIntensity = GetUniformLocation("gPointLight.Base.AmbientIntensity");
    m_pointLightLocation.Position = GetUniformLocation("gPointLight.Position");
    m_pointLightLocation.DiffuseIntensity = GetUniformLocation("gPointLight.Base.DiffuseIntensity");
    m_pointLightLocation.Atten.Constant = GetUniformLocation("gPointLight.Atten.Constant");
    m_pointLightLocation.Atten.Linear = GetUniformLocation("gPointLight.Atten.Linear");
    m_pointLightLocation.Atten.Exp = GetUniformLocation("gPointLight.Atten.Exp");

    if (m_pointLightLocation.Color == INVALID_UNIFORM_LOCATION ||
        m_pointLightLocation.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
        m_pointLightLocation.Position == INVALID_UNIFORM_LOCATION ||
        m_pointLightLocation.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
        m_pointLightLocation.Atten.Constant == INVALID_UNIFORM_LOCATION ||
        m_pointLightLocation.Atten.Linear == INVALID_UNIFORM_LOCATION ||
        m_pointLightLocation.Atten.Exp == INVALID_UNIFORM_LOCATION) {
        return false;
    }

    return true;
}

void LightingTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);    
}

void LightingTechnique::SetWorldMatrix(const Matrix4f& WorldInverse)
{
    glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.m);
}


void LightingTechnique::SetColorTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(m_samplerLocation, TextureUnit);
}


void LightingTechnique::SetShadowMapTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(m_shadowMapLocation, TextureUnit);
}


void LightingTechnique::SetEyeWorldPos(const Vector3f& EyeWorldPos)
{
    glUniform3f(m_eyeWorldPosLocation, EyeWorldPos.x, EyeWorldPos.y, EyeWorldPos.z);
}


void LightingTechnique::SetMatSpecularIntensity(float Intensity)
{
    glUniform1f(m_matSpecularIntensityLocation, Intensity);
}


void LightingTechnique::SetMatSpecularPower(float Power)
{
    glUniform1f(m_matSpecularPowerLocation, Power);
}


void LightingTechnique::SetPointLight(const PointLight& Light)
{
    glUniform3f(m_pointLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
    glUniform1f(m_pointLightLocation.AmbientIntensity, Light.AmbientIntensity);
    glUniform1f(m_pointLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
    glUniform3f(m_pointLightLocation.Position, Light.Position.x, Light.Position.y, Light.Position.z);
    glUniform1f(m_pointLightLocation.Atten.Constant, Light.Attenuation.Constant);
    glUniform1f(m_pointLightLocation.Atten.Linear, Light.Attenuation.Linear);
    glUniform1f(m_pointLightLocation.Atten.Exp, Light.Attenuation.Exp);
}

