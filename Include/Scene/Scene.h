#pragma once

#include <optional>
#include <unordered_map>

#include "Core/Types.h"
#include "Ray/Ray.h"

namespace Raytracer {

struct RenderFlags;

class TraceableScene {
public:
    virtual ~TraceableScene() { }
    virtual std::optional<const struct SurfaceRecord> RayCast(const RenderFlags& Flags, const struct Ray& Ray, const TRange<float>& Range = TRange<>::Positive(), const std::uint64_t Depth = 0) const = 0;
    virtual OptRef<class Camera> GetActiveCamera() const = 0;
};

}
