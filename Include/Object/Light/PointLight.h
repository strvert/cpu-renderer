#pragma once

#include <functional>
#include "Material/Color.h"
#include "Object/Light/Light.h"

// DirectionalLightのIntensityはカンデラとする

namespace Raytracer {

class PointLight : public Light {
public:
    PointLight()
        : Light(1, Color::White)
    {
    }

    virtual ShadowRay MakeShadowRay(const float3& SurfacePoint) const;
    virtual float GetIrradiance(const float3& SurfacePoint, const float3& Normal) const override;

    virtual ~PointLight() { }
};

}