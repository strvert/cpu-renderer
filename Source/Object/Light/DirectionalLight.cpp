#include "Object/Light/DirectionalLight.h"

namespace Raytracer {

using linalg::aliases::float3;

float3 DirectionalLight::GetDirection() const
{
    return Direction;
}

DirectionalLight& DirectionalLight::SetDirection(const float3& Direction)
{
    this->Direction = normalize(Direction);
    return *this;
}

}