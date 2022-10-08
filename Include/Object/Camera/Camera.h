#pragma once

#include "Object/SceneObject.h"
#include "linalg/linalg.h"

namespace Raytracer {

class Camera : public SceneObject {
public:
    Camera();

    virtual ~Camera() { }

    virtual Camera& SetLocation(const float3& Location) override;
    virtual float3 GetLocation() const override;
    virtual bool IsTraceable() const override;

    Camera& SetDirection(const float3& Direction);
    float3 GetDirection() const;

    Camera& SetAspectRatio(const float& Ratio);
    float GetAspectRatio() const;

    Camera& SetFocalLength(const float& FocalLength);
    float GetFocalLength() const;

    Camera& SetFov(const float& Horizontal);
    float2 GetRadianFov() const;

    uint2 CalcResolution(const std::uint32_t& Width) const;

    float3 ScreenUVToPosition(const float2& UV) const;
    struct Ray MakeRay(const float2& UV) const;

private:
    float3 Location;
    float3 Direction;
    float FocalLength;
    float HorizontalFov;
    float AspectRatio;
};

}