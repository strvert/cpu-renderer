#pragma once

#include "Material/Material.h"
#include <random>

namespace Raytracer {

class Lambert : public Material {
public:
    Lambert();

    virtual std::optional<Ray> Reflect(const float3& Position, const float3& Normal, const Ray& InRay) const override;
    virtual bool ForceShadowRay() const override;

private:
    float3 RandomVectorInHemisphere(const float3& Normal) const;

    mutable std::mt19937 RandomEngine;
    inline static std::uniform_real_distribution<float> Distribution
        = std::uniform_real_distribution(0.0f, 1.0f);
};

}