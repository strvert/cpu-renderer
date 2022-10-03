#pragma once

#include <functional>
#include "Object/Light/Light.h"
#include "Material/Color.h"

// DirectionalLightのIntensityはルクスとする

namespace Raytracer {

struct Ray;

class DirectionalLight : public Light {
public:
    DirectionalLight()
        : Light(1, Color::White)
        , Direction(float3{ 0.0f, 0.0f, -1.0f })
    {
    }

    virtual ~DirectionalLight() { }

    virtual ShadowRay MakeShadowRay(const float3& SurfacePoint) const override;
    virtual float GetIrradiance(const float3& SurfacePoint, const float3& Normal) const override;

    float3 GetDirection() const;
    DirectionalLight& SetDirection(const float3& Direction);

private:
    float3 Direction;
};

}