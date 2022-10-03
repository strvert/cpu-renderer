#pragma once

#include "Object/SceneObject.h"
#include "linalg/linalg.h"

namespace Raytracer {

struct Ray;

using linalg::aliases::float3;

class Light : public SceneObject {
public:
    Light(const float Intensity, const float3& Color)
        : Intensity(Intensity)
        , Color(Color)
    {
    }

    virtual ~Light() { }

    using ShadowRay = std::tuple<Ray, float>;

    virtual Light& SetLocation(const float3& Location) override
    {
        this->Location = Location;
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

    virtual Light& SetLightColor(const float3& Color)
    {
        this->Color = Color;
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

    virtual Light& SetIntensity(const float& Intensity)
    {
        this->Intensity = Intensity;
        return *this;
    }

    virtual float GetIrradiance(const float3& SurfacePoint, const float3& Normal) const = 0;

    virtual ShadowRay MakeShadowRay(const float3& SurfacePoint) const = 0;

private:
    float Intensity;
    float3 Location;
    float3 Color;
};

}