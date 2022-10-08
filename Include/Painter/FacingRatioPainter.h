#pragma once

#include <algorithm>

#include "Object/Camera/Camera.h"
#include "Painter/Painter.h"
#include "Ray/Ray.h"

namespace Raytracer {

class FacingRatioPainter : public Painter {
public:
    FacingRatioPainter(const float InMinBrightness = 0, const float3& InBackground = { 0, 0, 0 })
        : Painter(InBackground)
        , MinBrightness(InMinBrightness)
    {
    }
    virtual ~FacingRatioPainter() override {}

    virtual float3 Paint(const Camera& Camera, const std::optional<SurfaceRecord>& Record) const override
    {
        if (Record && Record->IsFront) {
            return float3(std::max(MinBrightness, -dot(Camera.GetDirection(), Record->Normal)));
        }
        return Background;
    }

    virtual RenderFlags GetRenderFlags() const override
    {
        return { .DirectLight = false };
    }

private:
    float MinBrightness;
};

}
