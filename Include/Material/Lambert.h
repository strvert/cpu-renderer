#pragma once

#include "Material/Material.h"
#include <random>

namespace Raytracer {

class Lambert : public Material {
public:
    Lambert();

    virtual SurfaceResponse Reflect(const SurfaceRecord& Record, const Ray& InRay) const = 0;

private:
    float3 RandomVectorInHemisphere(const float3& Normal) const;

    std::mt19937 RandomEngine;
    inline static std::uniform_real_distribution<float> Distribution
        = std::uniform_real_distribution ( 0.0f, 1.0f );
};

}