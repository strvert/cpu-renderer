#pragma once

#include "Sampler.h"
#include <array>
#include <iostream>
#include <optional>

namespace Raytracer {

// Non-supersamping
class NSS : public Sampler {
public:
    NSS() {}

    virtual std::vector<float2> GetSamplePattern(const uint2&) override
    {
        return { { 0.5, 0.5 } };
    }

private:
};

}
