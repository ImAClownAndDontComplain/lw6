#ifndef MOTION_BLUR_TECHNIQUE_H
#define	MOTION_BLUR_TECHNIQUE_H

#include "technique.h"
#include "math_3d.h"

class MotionBlurTechnique : public Technique {
public:

    MotionBlurTechnique();

    virtual bool Init();

    void SetColorTextureUnit(uint TextureUnit);    
    void SetMotionTextureUnit(uint TextureUnit);
    
private:
    GLuint m_colorTextureLocation;
    GLuint m_motionTextureLocation;
};



#endif	/* MOTION_BLUR_TECHNIQUE_H */

