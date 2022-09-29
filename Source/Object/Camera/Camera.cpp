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
    SetAspectRatio(16.0 / 9.0);
    SetFov(90);
    SetFocalLength(12);
}

Camera& Camera::SetLocation(const float3& Location)
{
    this->Location = Location;
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

Camera& Camera::SetDirection(const float3& Direction)
{
    this->Direction = normalize(Direction);
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

Camera& Camera::SetFocalLength(const float& FocalLength)
{
    this->FocalLength = FocalLength;
    return *this;
}

float Camera::GetFocalLength() const
{
    return FocalLength;
}

Camera& Camera::SetFov(const float& Horizontal)
{
    HorizontalFov = Horizontal;
    return *this;
}

float2 Camera::GetRadianFov() const
{
    const float RadHFov = HorizontalFov * (std::numbers::pi_v<float> / 180.0f);
    return { RadHFov, 2 * std::atan(std::tan(RadHFov / 2) / GetAspectRatio()) };
}

uint2 Camera::CalcResolution(const std::uint32_t& Width) const
{
    return static_cast<uint2>(float2 { static_cast<float>(Width), static_cast<float>(Width) / GetAspectRatio() });
}

float3 Camera::ScreenUVToPosition(const float2& UV) const
{
    const float2 HalfFov = GetRadianFov() / 2.0f;
    const float2 Half = FocalLength * tan(HalfFov);
    const float2 Full = 2.0f * Half;

    const float3 CameraU = normalize(cross(float3 { 0, 0, 1 }, Direction));
    const float3 CameraV = normalize(cross(CameraU, Direction));

    const float3 Center = Location + Direction * FocalLength;
    const float3 LeftTop = Center - (Half.x * CameraU) - (Half.y * CameraV);

    const float2 Position = Full * UV;
    return LeftTop + (Position.x * CameraU) + (Position.y * CameraV);
}

Ray Camera::MakeRay(const float2& UV) const
{
    return Ray(GetLocation(), normalize(ScreenUVToPosition(UV) - GetLocation()));
}

}