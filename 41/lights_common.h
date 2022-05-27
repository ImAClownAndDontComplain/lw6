#ifndef LIGHTS_COMMON_H
#define	LIGHTS_COMMON_H
#include "math_3d.h"

class BaseLight
{
public:
    std::string Name;
    Vector3f Color;
    float AmbientIntensity;
    float DiffuseIntensity;

    BaseLight()
    {
        Color = Vector3f(0.0f, 0.0f, 0.0f);
        AmbientIntensity = 0.0f;
        DiffuseIntensity = 0.0f;
    }
       
};


class DirectionalLight : public BaseLight
{      
public:
    Vector3f Direction;

    DirectionalLight()
    {
        Direction = Vector3f(0.0f, 0.0f, 0.0f);
    }
    
};


struct LightAttenuation
{
    float Constant;
    float Linear;
    float Exp;
};


class PointLight : public BaseLight
{
public:
    Vector3f Position;
    LightAttenuation Attenuation;

    PointLight()
    {
        Position = Vector3f(0.0f, 0.0f, 0.0f);
        Attenuation.Constant = 0.0f;
        Attenuation.Linear = 0.0f;
        Attenuation.Exp = 0.0f;
    }
    
};


class SpotLight : public PointLight
{
public:
    Vector3f Direction;
    float Cutoff;

    SpotLight()
    {
        Direction = Vector3f(0.0f, 0.0f, 0.0f);
        Cutoff = 0.0f;
    }
    
};


#define COLOR_WHITE Vector3f(1.0f, 1.0f, 1.0f)
#define COLOR_RED Vector3f(1.0f, 0.0f, 0.0f)
#define COLOR_GREEN Vector3f(0.0f, 1.0f, 0.0f)
#define COLOR_CYAN Vector3f(0.0f, 1.0f, 1.0f)
#define COLOR_BLUE Vector3f(0.0f, 0.0f, 1.0f)

#endif
