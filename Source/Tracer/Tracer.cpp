#include "Tracer/Tracer.h"

#include <future>
#include <iostream>
#include <optional>

#include "Console/Progress.h"
#include "Object/Camera/Camera.h"
#include "Ray/Ray.h"
#include "Scene/Scene.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

namespace Raytracer {

using namespace linalg::aliases;

Tracer::Tracer(const std::uint32_t& ImageWidth)
    : ImageWidth(ImageWidth)
{
}

std::size_t Tracer::PixelToIndex(const uint2& Res, const uint2& Position)
{
    return Position.y * Res.x + Position.x;
}

float2 Tracer::PixelToUV(const uint2& Res, const uint2& Position)
{
    return static_cast<float2>(Position) / static_cast<float2>(Res);
}

void Tracer::SetPixelByIndex(const std::size_t Index, const float3& Color)
{
    SetPixelByIndex(Buffer, Index, Color);
}

void Tracer::SetPixelByIndex(const std::span<byte3> PartialBuffer, const std::size_t Index, const float3& Color)
{
    PartialBuffer[Index] = static_cast<byte3>(float3(255) * min(Color, 1.0f));
}

void Tracer::Render()
{
    if (!CurrentPainter) {
        std::cerr << "Painterオブジェクトが構築されていません" << std::endl;
        std::exit(1);
    }

    if (const OptRef<Camera> CameraRef = CurrentScene->GetActiveCamera(); CameraRef) {
        const Camera& Camera = CameraRef->get();
        const auto& Res = Camera.CalcResolution(ImageWidth);

        AllocateBuffer(Res);

        // auto&& RenderProgress = Progress(Res.y * Res.x, 100);
        std::vector<std::future<void>> Futures;
        Futures.reserve(Res.y);

        for (std::uint32_t Y = 0; Y < Res.y; Y++) {
            Futures.push_back(
                std::async(std::launch::async, [this, Y, &Res, &Camera] {
                    ScanlineRender(std::span { Buffer }.subspan(Y * Res.x, Res.x), Camera, Y);
                }));
            // RenderProgress.Update((1 + Y) * Res.x);
        }
        // RenderProgress.End();

        for (auto& Future : Futures) {
            Future.wait();
        }

        LastRender = RenderRecord { .Resolution = Res };
    }
}

void Tracer::ScanlineRender(std::span<byte3> PartialBuffer, const Camera& Cam, std::uint32_t Y)
{
    const auto& Res = Cam.CalcResolution(ImageWidth);
    for (std::uint32_t X = 0; X < Res.x; X++) {
        const float2 UV = PixelToUV(Res, { X, Y });

        const Ray PrimaryRay = Cam.MakeRay(UV);
        const float3 Color = CurrentPainter->Paint(Cam, CurrentScene->RayCast(CurrentPainter->GetRenderFlags(), PrimaryRay));
        SetPixelByIndex(PartialBuffer, X, Color);
    }
}

void Tracer::Save(const std::string& Filename) const
{
    if (!LastRender) {
        std::cerr << "RenderRecordが無効です" << std::endl;
        return;
    }
    const uint2 Res = LastRender->Resolution;
    stbi_write_png(Filename.c_str(), Res.x, Res.y, 3, Buffer.data(), 0);
}

void Tracer::AllocateBuffer(const uint2& Res)
{
    Buffer.resize(Res.x * Res.y);
}

}