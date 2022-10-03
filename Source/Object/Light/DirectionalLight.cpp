#include "Object/Light/DirectionalLight.h"
#include "Ray/Ray.h"
#include <limits>

namespace Raytracer {

using linalg::aliases::float3;

float3 DirectionalLight::GetDirection() const
{
    return Direction;
}

DirectionalLight& DirectionalLight::SetDirection(const float3& Direction)
{
    this->Direction = normalize(Direction);
    return *this;
}

Light::ShadowRay DirectionalLight::MakeShadowRay(const float3& SurfacePosition) const
{
    return { Ray(SurfacePosition, -Direction), std::numeric_limits<float>::max() };
}

float DirectionalLight::GetIrradiance(const float3&, const float3& Normal) const
{
    return GetIntensity() * dot(Normal, -Direction);
}

}