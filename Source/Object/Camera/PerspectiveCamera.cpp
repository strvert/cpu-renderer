#include "Object/Camera/PerspectiveCamera.h"

#include "Ray/Ray.h"
#include <numbers>

using linalg::aliases::float2;
using linalg::aliases::float3;
using linalg::aliases::uint2;

namespace Raytracer {

PerspectiveCamera::PerspectiveCamera()
{
    // Default Settings
    SetAspectRatio(16.0f / 9.0f);
    SetFov(90);
    SetFocalLength(12);
}

Ray PerspectiveCamera::MakeRay(const float2& UV) const
{
    return Ray(GetLocation(), normalize(ScreenUVToPosition(UV) - GetLocation()));
}

uint2 PerspectiveCamera::CalcResolution(const std::uint32_t& Width) const
{
    return static_cast<uint2>(float2 { static_cast<float>(Width), static_cast<float>(Width) / GetAspectRatio() });
}

PerspectiveCamera& PerspectiveCamera::SetFocalLength(const float& InFocalLength)
{
    this->FocalLength = InFocalLength;
    return *this;
}

float PerspectiveCamera::GetFocalLength() const
{
    return FocalLength;
}

PerspectiveCamera& PerspectiveCamera::SetFov(const float& InHorizontal)
{
    HorizontalFov = InHorizontal;
    return *this;
}

float2 PerspectiveCamera::GetRadianFov() const
{
    const float RadHFov = HorizontalFov * (std::numbers::pi_v<float> / 180.0f);
    return { RadHFov, 2 * std::atan(std::tan(RadHFov / 2) / GetAspectRatio()) };
}

float3 PerspectiveCamera::ScreenUVToPosition(const float2& UV) const
{
    const float2 HalfFov = GetRadianFov() / 2.0f;
    const float2 Half = FocalLength * tan(HalfFov);
    const float2 Full = 2.0f * Half;

    const float3 Dir = GetDirection();
    const float3 PerspectiveCameraU = normalize(cross(float3 { 0, 0, 1 }, Dir));
    const float3 PerspectiveCameraV = normalize(cross(PerspectiveCameraU, Dir));

    const float3 Center = GetLocation() + Dir * FocalLength;
    const float3 LeftTop = Center - (Half.x * PerspectiveCameraU) - (Half.y * PerspectiveCameraV);

    const float2 Position = Full * UV;
    return LeftTop + (Position.x * PerspectiveCameraU) + (Position.y * PerspectiveCameraV);
}

}
