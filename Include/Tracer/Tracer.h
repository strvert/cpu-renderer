#pragma once

#include <memory>
#include <optional>
#include <span>
#include <vector>

#include "Painter/Painter.h"
#include "Ray/Ray.h"
#include "Scene/Scene.h"
#include "Sampler/Sampler.h"
#include "Tracer/RenderRecord.h"
#include "linalg/linalg.h"

namespace Raytracer {

class TraceableScene;

enum class RenderMode {
    FinalColor = 0,
    WorldNormal
};

using namespace linalg::aliases;

class Tracer {

public:
    Tracer(const std::uint32_t& ImageWidth);

    template <typename T, typename... Ts>
    T& EmplaceScene(Ts&&... Args)
    {
        CurrentScene = std::make_unique<T>(std::forward<Ts>(Args)...);
        return dynamic_cast<T&>(*CurrentScene);
    }

    template <typename T, typename... Ts>
    T& EmplacePainter(Ts&&... Args)
    {
        CurrentPainter = std::make_unique<T>(std::forward<Ts>(Args)...);
        return dynamic_cast<T&>(*CurrentPainter);
    }

    template <typename T, typename... Ts>
    T& EmplaceSampler(Ts&&... Args)
    {
        CurrentSampler = std::make_unique<T>(std::forward<Ts>(Args)...);
        return dynamic_cast<T&>(*CurrentSampler);
    }

    float2 RadianFov() const;

    void SetPixelByIndex(const std::size_t Index, const float3& Color);
    void SetPixelByIndex(const std::span<byte3> PartialBuffer, const std::size_t Index, const float3& Color);

    void Render();
    void ScanlineRender(std::span<byte3> PartialBuffer, const Camera& Cam, std::uint32_t Y);

    void Save(const std::string& Filename) const;

private:
    void AllocateBuffer(const uint2& Res);

    static std::size_t PixelToIndex(const uint2& Res, const uint2& Position);

    static float2 PixelToUV(const uint2& Res, const float2& Position);

    std::uint32_t ImageWidth;

    std::vector<byte3> Buffer;
    std::unique_ptr<TraceableScene> CurrentScene;
    std::unique_ptr<Painter> CurrentPainter;
    std::unique_ptr<Sampler> CurrentSampler;

    std::optional<RenderRecord> LastRender;
};

}