#pragma once

#include "TraceableModel.h"

namespace Raytracer {

class PlaneModel : public TraceableModel {
public:
    PlaneModel(const float3 Normal)
        : Normal(Normal)
    {
    }

    virtual ~PlaneModel() { }

    virtual std::optional<Record> RayCast(const Ray& Ray, const TRange<>& Range) const override;

private:
    float3 Normal;
};

}