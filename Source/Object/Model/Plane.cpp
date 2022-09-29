#include "Object/Model/Plane.h"

#include <iostream>

namespace Raytracer {

std::optional<Raytracer::Record> PlaneModel::RayCast(const Ray& Ray, const TRange<float>& Range) const
{
    const float D = dot(Ray.Direction, Normal);

    if (D == 0) {
        return std::nullopt;
    }

    const float3 O = length2(Ray.Origin) == 0 ? float3 { 0.0001, 0.0001, 0.0001 } : Ray.Origin;

    const float T = -dot(O - GetLocation(), Normal) / D;
    if (T <= 0 || !Range.Included(T)) {
        return std::nullopt;
    }

    const bool Front = D < 0;
    return Record { .T = T, .IsFront = Front, .Position = Ray.P(T), .Color = GetColor(), .Normal = Normal };
}

}