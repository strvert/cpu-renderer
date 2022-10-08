#include "Sampler/RGSS.h"

using namespace linalg::aliases;

namespace Raytracer {

RGSS::RGSS()
    : Scale(1)
    , Pattern(std::nullopt)
{
    UpdatePattern();
}

std::vector<float2> RGSS::GetSamplePattern(const uint2&)
{
    if (!Pattern) {
        UpdatePattern();
    }
    return *Pattern;
}

RGSS& RGSS::SetScale(const std::uint32_t& InScale)
{
    this->Scale = InScale;
    UpdatePattern();
    return *this;
}

void RGSS::UpdatePattern()
{
    if (!Pattern) {
        Pattern = std::vector<float2>();
    }

    Pattern->clear();
    Pattern->reserve(Scale * Scale * UnitPattern.size());

    float TileSize = 1.0f / static_cast<float>(Scale);
    for (std::uint32_t TileY = 0; TileY < Scale; TileY++) {
        for (std::uint32_t TileX = 0; TileX < Scale; TileX++) {
            const float2& P = float2 { static_cast<float>(TileX), static_cast<float>(TileY) } * TileSize;
            for (const auto& Sample : UnitPattern) {
                Pattern->emplace_back(P + (Sample / static_cast<float>(Scale)));
            }
        }
    }
}

}
