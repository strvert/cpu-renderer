#include "Material/PerfectReflection.h"

namespace Raytracer {

PerfectReflection::PerfectReflection()
{
}

std::optional<Ray> PerfectReflection::Reflect(const float3& Position, const float3& Normal, const Ray& InRay) const
{
    return Ray(
        Position,
        normalize(InRay.Direction + 2.0f * length(InRay.Direction) * dot(-InRay.Direction, Normal) * Normal));
}

bool PerfectReflection::ForceShadowRay() const
{
    return false;
}

}
