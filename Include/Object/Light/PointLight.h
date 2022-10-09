#pragma once

#include <functional>
#include "Material/Color.h"
#include "Object/Light/Light.h"

// DirectionalLightのIntensityはカンデラとする

namespace Raytracer {

class PointLight : public Light {
public:
    PointLight()
        : Light(1, NamedColor::White)
    {
    }

    virtual ShadowRay MakeShadowRay(const float3& SurfacePoint) const override;
    virtual float3 GetIrradiance(const float3& SurfacePoint, const float3& Normal) const override;

    virtual ~PointLight() override { }
};

}
