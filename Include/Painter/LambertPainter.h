#pragma once

#include <algorithm>

#include "Painter/Painter.h"
#include "Ray/Ray.h"
#include "Object/Camera/Camera.h"

namespace Raytracer {

class LambertPainter : public Painter {
public:
    LambertPainter(const float3& Background = { 0, 0, 0 })
        : Painter(Background) {};
    virtual ~LambertPainter() {};

    virtual float3 Paint(const Camera& Camera, const std::optional<Record>& Record) const override
    {
        if (Record && Record->IsFront) {
            return Record->Color * float3(-std::min<float>(0, dot(Camera.GetCameraDirection(), Record->Normal)));
        }
        return Background;
    }

private:

};

}