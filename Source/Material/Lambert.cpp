#include "Material/Lambert.h"

namespace Raytracer {

Lambert::Lambert()
    : RandomEngine(std::mt19937(std::random_device()()))
{
}

SurfaceResponse Lambert::Reflect(const SurfaceRecord& Record, const Ray&) const
{
    return { true, Ray(Record.Position, this->RandomVectorInHemisphere(Record.Normal)) };
}

float3 Lambert::RandomVectorInHemisphere(const float3&) const
{
    return normalize(float3(Distribution(RandomEngine), Distribution(RandomEngine), Distribution(RandomEngine)));
}

}