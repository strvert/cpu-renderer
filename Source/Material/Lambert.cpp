#include "Material/Lambert.h"

namespace Raytracer {

Lambert::Lambert()
    : RandomEngine(std::mt19937(std::random_device()()))
{
}

std::optional<Ray> Lambert::Reflect(const float3& Position, const float3& Normal, const Ray& InRay) const
{
    // FIXME: バカの実装なので直すこと
    float3 AdHoc = this->RandomVectorInHemisphere(Normal);
    return Ray(Position, dot(Normal, AdHoc) <= 0 ? abs(AdHoc) : AdHoc);
}

bool Lambert::ForceShadowRay() const
{
    return true;
}

float3 Lambert::RandomVectorInHemisphere(const float3&) const
{
    // FIXME: 明らかの偏りのあるバカの実装なので直すこと(その2)
    return normalize(float3(Distribution(RandomEngine), Distribution(RandomEngine), Distribution(RandomEngine)));
}

}