#pragma once

#include "Camera.h"

namespace Raytracer {

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera();

    virtual ~PerspectiveCamera() override { }

    virtual struct Ray MakeRay(const float2& UV) const override;

    PerspectiveCamera& SetFocalLength(const float& FocalLength);
    float GetFocalLength() const;

    PerspectiveCamera& SetFov(const float& Horizontal);
    float2 GetRadianFov() const;

    float3 ScreenUVToPosition(const float2& UV) const;

private:
    float FocalLength;
    float HorizontalFov;
};

}
