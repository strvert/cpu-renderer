#pragma once

#include "Object/Light/Light.h"
#include "Material/Color.h"
#include <functional>

namespace Raytracer {

class DirectionalLight : public Light {
public:
    DirectionalLight()
        : Light(1, Color::White)
        , Direction(float3{ 0.0f, 0.0f, -1.0f })
    {
    }

    virtual ~DirectionalLight() { }

    float3 GetDirection() const;
    DirectionalLight& SetDirection(const float3& Direction);

private:
    float3 Direction;
};

}