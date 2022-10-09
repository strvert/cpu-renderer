#pragma once

#include <functional>
#include "linalg/linalg.h"
#include <memory>
#include <optional>
#include <ostream>

namespace Raytracer {

using namespace linalg::aliases;

template <typename T = float>
class TRange {
public:
    constexpr TRange(const T& InTMin, const T& InTMax)
        : TMin(InTMin)
        , TMax(InTMax)
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

// deducation guide
template <typename T>
TRange(T TMin, T TMax) -> TRange<T>;

struct Ray {
    Ray(const float3& InOrigin, const float3& InDirection)
        : Origin(InOrigin)
        , Direction(normalize(InDirection))
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
    float3 Normal;
    float3 Radiance;
    std::weak_ptr<class Material> Mat;
};

}

std::ostream& operator<<(std::ostream& os, const linalg::aliases::float3& R);
std::ostream& operator<<(std::ostream& os, const Raytracer::Ray& R);
