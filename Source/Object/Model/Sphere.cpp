#include "Object/Model/Sphere.h"

namespace Raytracer {

std::optional<SurfaceRecord> SphereModel::RayCast(const Ray& Ray, const TRange<float>& Range) const
{
    const float3 CS = GetLocation() - Ray.Origin;
    const float A = dot(Ray.Direction, Ray.Direction);
    const float B = -dot(Ray.Direction, CS);
    const float C = dot(CS, CS) - Radius * Radius;

    const float D = B * B - A * C;

    if (D >= 0) {
        const float T = (-B - std::sqrt(D)) / A;
        if (Range.Included(T)) {
            const float3 P = Ray.P(T);
            const float3 N = (P - GetLocation()) / Radius;
            const bool Front = dot(N, Ray.Direction) < 0;
            return SurfaceRecord { .T = T, .IsFront = Front, .Position = P, .Color = GetColor(), .Normal = N };
        }
    }

    return std::nullopt;
}

}