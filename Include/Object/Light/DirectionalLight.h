#pragma once

#include <functional>
#include "Object/Light/Light.h"

namespace Raytracer {

class DirectionalLight : public Light {
public:
    DirectionalLight(const float3& Direction, const float Intensity, const float3& Color)
        : Light(Intensity, Color)
        , Direction(Direction)
    {
    }

    virtual ~DirectionalLight() { }

    float3 GetDirection() const;

    void SetDirection(const float3& Direction);

private:
    float3 Direction;
};

}