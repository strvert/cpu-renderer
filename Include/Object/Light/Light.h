#pragma once

#include "Object/SceneObject.h"
#include "linalg/linalg.h"

namespace Raytracer {

    using linalg::aliases::float3;

class Light : public SceneObject {
public:
    Light(const float Intensity, const float3& Color)
        : Intensity(Intensity)
        , Color(Color)
    {
    }

    virtual ~Light() { }

    virtual void SetLocation(const float3& Location) override
    {
        this->Location = Location;
    }

    virtual float3 GetLocation() const override
    {
        return Location;
    }

    virtual bool IsTraceable() const override
    {
        return false;
    }

    virtual void SetLightColor(const float3& Color)
    {
        this->Color = Color;
    }

    virtual float3 GetLightColor() const
    {
        return Color;
    }

private:
    float Intensity;
    float3 Location;
    float3 Color;
};

}