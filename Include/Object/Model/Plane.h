#pragma once

#include "TraceableModel.h"

namespace Raytracer {

class PlaneModel : public TraceableModel {
public:
    PlaneModel(const float3 InNormal)
        : Normal(InNormal)
    {
    }

    virtual ~PlaneModel() override { }

    virtual std::optional<SurfaceRecord> RayCast(const Ray& Ray, const TRange<>& Range) const override;

private:
    float3 Normal;
};

}
