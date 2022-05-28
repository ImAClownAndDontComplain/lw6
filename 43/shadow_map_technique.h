#ifndef SHADOW_MAP_TECHNIQUE_H
#define	SHADOW_MAP_TECHNIQUE_H

#include "technique.h"
#include "math_3d.h"
#include "mesh.h"
#include "camera.h"

#define NUM_OF_LAYERS 6

class ShadowMapTechnique : public Technique {

public:

    ShadowMapTechnique();

    virtual bool Init();
    
    void SetWVP(const Matrix4f& WVP);	
    void SetWorld(const Matrix4f& World);	
    void SetLightWorldPos(const Vector3f& Pos);
    
private:

    GLint m_WVPLocation;
    GLint m_WorldMatrixLocation;
    GLint m_lightWorldPosLoc;
};


#endif	/* SHADOW_MAP_TECHNIQUE_H */

