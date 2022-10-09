#include "Object/Camera/OrthographicCamera.h"
#include "Ray/Ray.h"

namespace Raytracer {

OrthographicCamera::OrthographicCamera()
    : OrthoWidth(25)
{
}

Ray OrthographicCamera::MakeRay(const float2& UV) const
{
    const float2 Full = { GetOrthoWidth(), GetOrthoWidth() / GetAspectRatio() };
    const float2 Half = Full / 2.0f;
    const float3 Dir = GetDirection();
    const float3 CameraU = normalize(cross(float3 { 0, 0, 1 }, Dir));
    const float3 CameraV = normalize(cross(CameraU, Dir));
    const float3 LeftTop = GetLocation() - (Half.x * CameraU) - (Half.y * CameraV);
    const float2 Position = Full * UV;
    const float3 Origin = LeftTop + (Position.x * CameraU) + (Position.y * CameraV);

    return Ray(Origin, Dir);
}

OrthographicCamera& OrthographicCamera::SetOrthoWidth(const float& InWidth)
{
    OrthoWidth = InWidth;
    return *this;
}

float OrthographicCamera::GetOrthoWidth() const
{
    return OrthoWidth;
}

}
