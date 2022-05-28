#ifndef SHADOW_VOLUME_TECHNIQUE_H
#define	SHADOW_VOLUME_TECHNIQUE_H

#include "technique.h"
#include "math_3d.h"

class ShadowVolumeTechnique : public Technique {
public:

    ShadowVolumeTechnique();

    virtual bool Init();

    void SetVP(const Matrix4f& VP);
    void SetWorldMatrix(const Matrix4f& World);
    void SetLightPos(const Vector3f& Pos);
    
private:
    
    GLuint m_VPLocation;
    GLuint m_WorldMatrixLocation;
    GLuint m_lightPosLocation;
};


#endif	/* SHADOW_VOLUME_TECHNIQUE_H */
