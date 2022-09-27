#pragma once

#include "Object/Light/Light.h"

namespace Raytracer {

class PointLight : public Light {
public:
    PointLight(const float Intensity, const float3& Color)
        : Light(Intensity, Color)
        , Direction(Direction)
    {
    }

    virtual ~PointLight() { }
};

}