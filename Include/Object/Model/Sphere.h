#pragma once

#include "TraceableModel.h"

namespace Raytracer {

struct SphereModel : public TraceableModel {
    SphereModel(const float InRadius)
        : Radius(InRadius)
    {
    }

    virtual ~SphereModel() override { }

    virtual std::optional<SurfaceRecord> RayCast(const Ray& Ray, const TRange<>& Range) const override;

    float Radius;
};

}
