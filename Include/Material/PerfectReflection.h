#pragma once

#include "Material/Material.h"
#include <random>

namespace Raytracer {

class PerfectReflection : public Material {
public:
    PerfectReflection();

    virtual std::optional<Ray> Reflect(const float3& Position, const float3& Normal, const Ray& InRay) const override;
    virtual bool ForceShadowRay() const override;
};

}
