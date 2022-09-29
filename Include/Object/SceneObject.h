#pragma once

#include <functional>
#include "linalg/linalg.h"

namespace Raytracer {

class SceneObject {
protected: 
    using float3 = linalg::aliases::float3;
    using float2 = linalg::aliases::float2;
    using uint2 = linalg::aliases::uint2;

public:
    virtual ~SceneObject() { }

    virtual SceneObject& SetLocation(const float3& Location) = 0;
    virtual float3 GetLocation() const = 0;
    virtual bool IsTraceable() const = 0;
};

}