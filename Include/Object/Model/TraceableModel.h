#pragma once

#include <memory>
#include <optional>

#include "Core/Types.h"
#include "Ray/Ray.h"
#include "Material/Material.h"
#include "Object/SceneObject.h"

namespace Raytracer {

class TraceableModel : public SceneObject {
public:
    TraceableModel()
    {
    }
    virtual ~TraceableModel() override;

    virtual TraceableModel& SetLocation(const float3& Location) override;
    virtual float3 GetLocation() const override;
    virtual bool IsTraceable() const override;

    virtual TraceableModel& SetColor(const float3& Color);
    virtual float3 GetColor() const;
    virtual TraceableModel& SetMaterial(std::shared_ptr<Material> InMaterial);
    virtual std::weak_ptr<Material> GetMaterial() const;
    virtual std::optional<SurfaceRecord> RayCast(const Ray& Ray, const TRange<>& Range) const = 0;

private:
    float3 Location;
    float3 Color;
    std::shared_ptr<Material> Mat;
};

}
