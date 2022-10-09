#pragma once

#include "Object/SceneObject.h"
#include "linalg/linalg.h"

namespace Raytracer {

class Camera : public SceneObject {
public:
    Camera();

    virtual ~Camera() override { }

    virtual Camera& SetLocation(const float3& Location) override;
    virtual float3 GetLocation() const override;
    virtual bool IsTraceable() const override;
    virtual struct Ray MakeRay(const float2& UV) const = 0;
    virtual uint2 CalcResolution(const std::uint32_t& Width) const = 0;

    virtual Camera& SetDirection(const float3& Direction);
    virtual float3 GetDirection() const;

    virtual Camera& SetAspectRatio(const float& Ratio);
    virtual float GetAspectRatio() const;

private:
    float3 Location;
    float3 Direction;
    float AspectRatio;
};

}
