#pragma once

#include <algorithm>

#include "Painter/Painter.h"
#include "Ray/Ray.h"
#include "Object/Camera/Camera.h"

namespace Raytracer {

class SceneColorPainter : public Painter {
public:
    SceneColorPainter(const float3& Background = { 0, 0, 0 })
        : Painter(Background) {};
    virtual ~SceneColorPainter() {};

    virtual float3 Paint(const Camera& Camera, const std::optional<SurfaceRecord>& Record) const override
    {
        if (Record && Record->IsFront) {
            return Record->Color * Record->Radiance;
        }
        return Background;
    }

    virtual RenderFlags GetRenderFlags() const override
    {
        return { .DirectLight = true };
    }
};

}