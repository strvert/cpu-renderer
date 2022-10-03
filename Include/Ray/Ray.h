#pragma once

#include "linalg/linalg.h"
#include "Material/Material.h"
#include <functional>
#include <optional>

namespace Raytracer {

using namespace linalg::aliases;

template <typename T = float>
class TRange {
public:
    constexpr TRange(const T& TMin, const T& TMax)
        : TMin(TMin)
        , TMax(TMax)
    {
    }

    constexpr TRange()
        : TRange(0, 0)
    {
    }

    bool Included(const T& Value) const
    {
        return Value <= TMax && Value >= TMin;
    }

    static constexpr TRange<T> Full()
    {
        return TRange<T>(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max());
    }

    static constexpr TRange<T> Positive()
    {
        return TRange<T>(0, std::numeric_limits<T>::max());
    }

    static constexpr TRange<T> Negative()
    {
        return TRange<T>(std::numeric_limits<T>::lowest(), 0);
    }

    T TMin;
    T TMax;
};

struct Ray {
    Ray(const float3& Origin, const float3& Direction)
        : Origin(Origin)
        , Direction(normalize(Direction))
    {
    }

    float3 Origin;
    float3 Direction;

    float3 P(const float T) const
    {
        return Origin + T * Direction;
    }
};

struct SurfaceRecord {
    float T;
    bool IsFront;
    float3 Position;
    float3 Color;
    float3 Normal;
    std::optional<Material> Material;
};

}