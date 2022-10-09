#include "Object/Camera/Camera.h"

#include "Ray/Ray.h"
#include <numbers>

using linalg::aliases::float2;
using linalg::aliases::float3;
using linalg::aliases::uint2;

namespace Raytracer {

Camera::Camera()
{
    // Default Settings
    SetAspectRatio(16.0f / 9.0f);
}

Camera& Camera::SetLocation(const float3& InLocation)
{
    this->Location = InLocation;
    return *this;
}

float3 Camera::GetLocation() const
{
    return Location;
}

bool Camera::IsTraceable() const
{
    return false;
}

Camera& Camera::SetDirection(const float3& InDirection)
{
    this->Direction = normalize(InDirection);
    return *this;
}

float3 Camera::GetDirection() const
{
    return Direction;
}

Camera& Camera::SetAspectRatio(const float& Ratio)
{
    AspectRatio = Ratio;
    return *this;
}

float Camera::GetAspectRatio() const
{
    return AspectRatio;
}

uint2 Camera::CalcResolution(const std::uint32_t& Width) const
{
    return static_cast<uint2>(float2 { static_cast<float>(Width), static_cast<float>(Width) / GetAspectRatio() });
}

}
