#pragma once

#include "Ray/Ray.h"

namespace Raytracer {

struct SurfaceRecord;

struct SurfaceResponse {
    bool Valid;
    Ray Out;
};

class Material {
public:
    Material() { }
    virtual ~Material();

    virtual SurfaceResponse Reflect(const SurfaceRecord& Record, const Ray& InRay) const = 0;
};

}