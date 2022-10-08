#pragma once

#include "Sampler.h"
#include <array>
#include <iostream>
#include <optional>

namespace Raytracer {

// Rotate grid supersampling (RGSS)
class RGSS : public Sampler {
public:
    RGSS();

    virtual std::vector<float2> GetSamplePattern(const uint2&);

    RGSS& SetScale(const std::uint32_t& Scale);

    void UpdatePattern();

private:
    std::uint32_t Scale;
    std::optional<std::vector<float2>> Pattern;

    inline static constexpr const std::array<float2, 4> UnitPattern = {
        float2 { 5.0 / 8.0, 1.0 / 8.0 },
        float2 { 1.0 / 8.0, 3.0 / 8.0 },
        float2 { 7.0 / 8.0, 5.0 / 8.0 },
        float2 { 3.0 / 8.0, 6.0 / 8.0 }
    };
};

}