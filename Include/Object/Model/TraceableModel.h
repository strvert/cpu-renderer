#pragma once

#include <memory>
#include <optional>

#include "Ray/Ray.h"
#include "Object/SceneObject.h"

namespace Raytracer {

class TraceableModel : public SceneObject {
public:
    TraceableModel()
    {
    }
    virtual ~TraceableModel() { }

    virtual void SetLocation(const float3& Location) override;
    virtual float3 GetLocation() const override;
    virtual bool IsTraceable() const override;

    virtual void SetColor(const float3& Color);
    virtual float3 GetColor() const;
    virtual std::optional<Record> RayCast(const Ray& Ray, const TRange<>& Range) const = 0;

private:
    float3 Location;
    float3 Color;
};

}