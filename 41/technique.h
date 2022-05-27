#ifndef TECHNIQUE_H
#define	TECHNIQUE_H

#include <list>
#include <GL/glew.h>

class Technique
{
public:

    Technique();

    virtual ~Technique();

    virtual bool Init();

    void Enable();

protected:

    bool TXTshader(GLenum ShaderType, const char* ShaderText);

    bool AddShader(GLenum ShaderType, const char* pFilename);

    bool Finalize();

    GLint GetUniformLocation(const char* pUniformName);
    
    GLint GetProgramParam(GLint param);
    
    GLuint m_shaderProg;    
    
private:

    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;
};

#endif	/* TECHNIQUE_H */

