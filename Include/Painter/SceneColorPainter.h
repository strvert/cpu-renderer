#pragma once

#include <algorithm>

#include "Painter/Painter.h"
#include "Ray/Ray.h"
#include "Object/Camera/Camera.h"

namespace Raytracer {

class SceneColorPainter : public Painter {
public:
    SceneColorPainter(const float3& InBackground = { 0, 0, 0 })
        : Painter(InBackground) {}
    virtual ~SceneColorPainter() override {}

    virtual float3 Paint(const Camera&, const std::optional<SurfaceRecord>& Record) const override
    {
        if (Record && Record->IsFront) {
            return Record->Color * ToGamma(Record->Radiance);
        }
        return Background;
    }

    static float ToGamma(const float& LinearRadiance) {
        return std::max(0.0f, std::pow(LinearRadiance, 1.0f/2.2f));
    }

    virtual RenderFlags GetRenderFlags() const override
    {
        return { .DirectLight = true };
    }
};

}
