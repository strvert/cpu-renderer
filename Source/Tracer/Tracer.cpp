#include "Tracer/Tracer.h"

#include <algorithm>
#include <future>
#include <iostream>
#include <list>
#include <optional>
#include <thread>

#include "Console/Progress.h"
#include "Object/Camera/Camera.h"
#include "Ray/Ray.h"
#include "Scene/Scene.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

namespace Raytracer {

using namespace linalg::aliases;
using namespace std::chrono_literals;

Tracer::Tracer(const std::uint32_t& ImageWidth)
    : ImageWidth(ImageWidth)
{
}

std::size_t Tracer::PixelToIndex(const uint2& Res, const uint2& Position)
{
    return Position.y * Res.x + Position.x;
}

float2 Tracer::PixelToUV(const uint2& Res, const float2& Position)
{
    return Position / static_cast<float2>(Res);
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

        std::list<std::future<void>> Futures(Res.y);
        std::generate_n(std::begin(Futures), Res.y, [&, Y = -1]() mutable {
            Y++;
            return std::async(std::launch::async, [this, Y, &Res, &Camera] {
                ScanlineRender(std::span { Buffer }.subspan(Y * Res.x, Res.x), Camera, Y);
            });
        });

        auto&& RenderProgress = Progress(Res.y, 100);
        while (true) {
            if (Futures.size() == 0) {
                break;
            }

            std::this_thread::sleep_for(5ms);
            std::erase_if(Futures, [&RenderProgress](std::future<void>& Future) {
                if (Future.wait_for(0s) == std::future_status::ready) {
                    RenderProgress.Increment(1);
                    return true;
                }
                return false;
            });
        }
        RenderProgress.End();

        LastRender = RenderRecord { .Resolution = Res };
    }
}

void Tracer::ScanlineRender(std::span<byte3> PartialBuffer, const Camera& Cam, std::uint32_t Y)
{
    const auto& Res = Cam.CalcResolution(ImageWidth);

    for (std::uint32_t X = 0; X < Res.x; X++) {
        const std::vector<float2>& Positions = CurrentSampler->SamplePositions({X, Y});

        float3 Color;
        for (const auto& Position : Positions) {
            const Ray PrimaryRay = Cam.MakeRay(PixelToUV(Res, Position));
            Color += CurrentPainter->Paint(Cam, CurrentScene->RayCast(CurrentPainter->GetRenderFlags(), PrimaryRay));
        }

        SetPixelByIndex(PartialBuffer, X, Color / static_cast<float>(Positions.size()));
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