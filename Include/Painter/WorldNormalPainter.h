#pragma once

#include "Painter/Painter.h"
#include "Ray/Ray.h"

namespace Raytracer {

class WorldNormalPainter : public Painter {
public:
    WorldNormalPainter(const float3& Background = { 0, 0, 0 })
        : Painter(Background) {};
    virtual ~WorldNormalPainter() {};

    virtual float3 Paint(const Camera&, const std::optional<SurfaceRecord>& Record) const override
    {
        if (Record && Record->IsFront) {
            return (Record->Normal + 1.0f) * 0.5f;
        }
        return Background;
    }
};

}