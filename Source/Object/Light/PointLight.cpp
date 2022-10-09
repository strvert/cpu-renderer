#include "Object/Light/PointLight.h"
#include "Ray/Ray.h"
#include <iostream>

namespace Raytracer {

Light::ShadowRay PointLight::MakeShadowRay(const float3& SurfacePoint) const
{
    const float3& Dir = GetLocation() - SurfacePoint;
    return { Ray(SurfacePoint, Dir), length(Dir) };
}

float3 PointLight::GetIrradiance(const float3& SurfacePoint, const float3& Normal) const
{
    const float3& Dir = GetLocation() - SurfacePoint;
    const float& Len = length(Dir);
    const float& Irradiance = GetIntensity() * std::max(0.0f, dot(Normal, normalize(Dir))) / (Len * Len);
    return Irradiance * GetLightColor();
}

}
