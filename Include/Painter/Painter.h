#pragma once

#include "linalg/linalg.h"
#include "Object/Camera/Camera.h"

namespace Raytracer {

using linalg::aliases::float3;
struct SurfaceRecord;

struct RenderFlags {
    bool DirectLight;
};

class Painter {
public:
    Painter(const float3& InBackground)
        : Background(InBackground)
    {
    }

    virtual ~Painter() {}
    virtual float3 Paint(const Camera& Camera, const std::optional<SurfaceRecord>& Record) const = 0;
    virtual RenderFlags GetRenderFlags() const = 0;

protected:
    float3 Background;
};

}
