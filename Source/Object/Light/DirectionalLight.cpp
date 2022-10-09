#include "Object/Light/DirectionalLight.h"
#include "Ray/Ray.h"
#include <limits>
#include <iostream>

namespace Raytracer {

using linalg::aliases::float3;

float3 DirectionalLight::GetDirection() const
{
    return Direction;
}

DirectionalLight& DirectionalLight::SetDirection(const float3& InDirection)
{
    this->Direction = normalize(InDirection);
    return *this;
}

Light::ShadowRay DirectionalLight::MakeShadowRay(const float3& SurfacePosition) const
{
    return { Ray(SurfacePosition, -Direction), std::numeric_limits<float>::max() };
}

float3 DirectionalLight::GetIrradiance(const float3&, const float3& Normal) const
{
    return GetLightColor() * GetIntensity() * std::max(0.0f, dot(Normal, -Direction));
}

}
