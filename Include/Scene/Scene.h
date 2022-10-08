#pragma once

#include <optional>
#include <unordered_map>

#include "Ray/Ray.h"

namespace Raytracer {

struct RenderFlags;

template <typename T>
using Ref = std::reference_wrapper<T>;

template <typename T>
using OptRef = std::optional<Ref<T>>;

template <typename T>
T& Value(OptRef<T> Ref)
{
    return Ref.value().get();
}

class TraceableScene {
public:
    virtual ~TraceableScene() { }
    virtual std::optional<const struct SurfaceRecord> RayCast(const RenderFlags& Flags, const struct Ray& Ray, const TRange<float>& Range = TRange<>::Positive()) const = 0;
    virtual OptRef<class Camera> GetActiveCamera() const = 0;
};

}