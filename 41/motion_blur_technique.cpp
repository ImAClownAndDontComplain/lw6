#include "motion_blur_technique.h"
#include "util.h"

static const char* VS = R"(
#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;                                             

out vec2 TexCoord0;

void main()
{       
    gl_Position = vec4(Position, 1.0);
    TexCoord0   = TexCoord;
})";

static const char* FS = R"(
#version 330

in vec2 TexCoord0;

uniform sampler2D gColorTexture;
uniform sampler2D gMotionTexture;
    
out vec4 FragColor;
                                                                                        
void main()
{                                    
    vec2 MotionVector = texture(gMotionTexture, TexCoord0).xy / 2.0;

    vec4 Color = vec4(0.0);

    vec2 TexCoord = TexCoord0;
    
    Color += texture(gColorTexture, TexCoord) * 0.4;
    TexCoord -= MotionVector;
    Color += texture(gColorTexture, TexCoord) * 0.3;
    TexCoord -= MotionVector;
    Color += texture(gColorTexture, TexCoord) * 0.2;
    TexCoord -= MotionVector;
    Color += texture(gColorTexture, TexCoord) * 0.1;

    FragColor = Color;
    })";

MotionBlurTechnique::MotionBlurTechnique()
{
    
}

bool MotionBlurTechnique::Init()
{
    if (!Technique::Init()) {
        return false;
    }

    if (!TXTshader(GL_VERTEX_SHADER, VS)) {
        return false;
    }

    if (!TXTshader(GL_FRAGMENT_SHADER, FS)) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }
    
    m_colorTextureLocation = GetUniformLocation("gColorTexture");
    m_motionTextureLocation = GetUniformLocation("gMotionTexture");
    
    if (m_motionTextureLocation == INVALID_UNIFORM_LOCATION ||
        m_colorTextureLocation == INVALID_UNIFORM_LOCATION) {
        return false;
    }

	return true;
}


void MotionBlurTechnique::SetColorTextureUnit(uint TextureUnit)
{
    glUniform1i(m_colorTextureLocation, TextureUnit);
}


void MotionBlurTechnique::SetMotionTextureUnit(uint TextureUnit)
{
    glUniform1i(m_motionTextureLocation, TextureUnit);
}

