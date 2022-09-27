#pragma once

#include "linalg/linalg.h"
#include "Object/Camera/Camera.h"

namespace Raytracer {

using linalg::aliases::float3;
class Record;

class Painter {
public:
    Painter(const float3& Background)
        : Background(Background)
    {
    }

    virtual ~Painter() {};
    virtual float3 Paint(const Camera& Camera, const std::optional<Record>& Record) const = 0;

protected:
    float3 Background;
};

}