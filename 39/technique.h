#pragma once

#include <list>
#include <GL/glew.h>

class Technique
{
public:

    Technique(const char* pEffectFile);

    ~Technique();

    void Enable();

protected:
    
    bool CompileProgram(const char* pProgram);
    
    GLint GetUniformLocation(const char* pUniformName);
    
    GLint GetProgramParam(GLint param);

private:    
    GLint m_effect;    
    GLint m_shaderProg;
    const char* m_pEffectFile;
};

#define INVALID_UNIFORM_LOCATION 0xFFFFFFFF

