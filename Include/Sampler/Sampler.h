#pragma once

#include <algorithm>
#include <vector>
#include "linalg/linalg.h"

namespace Raytracer {

class Sampler {
protected: 
    using float3 = linalg::aliases::float3;
    using float2 = linalg::aliases::float2;
    using uint2 = linalg::aliases::uint2;

public:
    Sampler() { }
    virtual ~Sampler() { }

    virtual std::vector<float2> SamplePositions(const uint2& Position)
    {
        const float2& BasePos = static_cast<float2>(Position);
        // パターンを適用
        const std::vector<float2>& Pattern = GetSamplePattern(Position);
        std::vector<float2> Positions = {};
        std::ranges::transform(Pattern, std::back_inserter(Positions), [&BasePos](const float2& P) {
            return BasePos + P;
        });

        return Positions;
    }

    virtual std::vector<float2> GetSamplePattern(const uint2& Position) = 0;
};

}
