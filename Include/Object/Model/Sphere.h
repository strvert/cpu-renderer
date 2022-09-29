#pragma once

#include "TraceableModel.h"

namespace Raytracer {

struct SphereModel : public TraceableModel {
    SphereModel(const float Radius)
        : Radius(Radius)
    {
    }

    virtual ~SphereModel() { }

    virtual std::optional<Record> RayCast(const Ray& Ray, const TRange<>& Range) const override;

    float Radius;
};

}