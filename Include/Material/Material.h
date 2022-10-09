#pragma once

#include "Ray/Ray.h"

namespace Raytracer {

struct SurfaceRecord;

class Material {
public:
    Material() { }
    virtual ~Material();

    virtual std::optional<Ray> Reflect(const float3& Position, const float3& Normal, const Ray& InRay) const = 0;
    virtual bool ForceShadowRay() const = 0;
};

}
