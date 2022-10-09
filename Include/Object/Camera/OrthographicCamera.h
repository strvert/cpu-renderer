#pragma once

#include "Camera.h"

namespace Raytracer {

class OrthographicCamera : public Camera {
public:
    OrthographicCamera();
    virtual ~OrthographicCamera() override { }

    virtual struct Ray MakeRay(const float2& UV) const override;

    OrthographicCamera& SetOrthoWidth(const float& Width);
    float GetOrthoWidth() const;

private:
    float OrthoWidth;
};

}
