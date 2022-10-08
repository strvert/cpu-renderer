#pragma once

#include "Object/SceneObject.h"
#include "linalg/linalg.h"

namespace Raytracer {

struct Ray;

using linalg::aliases::float3;

class Light : public SceneObject {
public:
    Light(const float InIntensity, const float3& InColor)
        : Intensity(InIntensity)
        , Color(InColor)
    {
    }

    virtual ~Light() override { }

    using ShadowRay = std::tuple<Ray, float>;

    virtual Light& SetLocation(const float3& InLocation) override
    {
        this->Location = InLocation;
        return *this;
    }

    virtual float3 GetLocation() const override
    {
        return Location;
    }

    virtual bool IsTraceable() const override
    {
        return false;
    }

    virtual Light& SetLightColor(const float3& InColor)
    {
        this->Color = InColor;
        return *this;
    }

    virtual float3 GetLightColor() const
    {
        return Color;
    }

    virtual float GetIntensity() const
    {
        return Intensity;
    }

    virtual Light& SetIntensity(const float& InIntensity)
    {
        this->Intensity = InIntensity;
        return *this;
    }

    virtual float GetIrradiance(const float3& SurfacePoint, const float3& Normal) const = 0;

    virtual ShadowRay MakeShadowRay(const float3& SurfacePoint) const = 0;

private:
    float3 Location;
    float Intensity;
    float3 Color;
};

}
