#include "Tracer/Tracer.h"

#include <iostream>

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
    Buffer[Index] = static_cast<byte3>(float3(255) * Color);
}

void Tracer::Render()
{
    if (!Painter) {
        std::cerr << "Painterオブジェクトが構築されていません" << std::endl;
        std::exit(1);
    }

    if (const OptRef<Camera> CameraRef = Scene->GetActiveCamera(); CameraRef) {
        const Camera& Camera = CameraRef->get();
        const auto& Res = Camera.CalcResolution(ImageWidth);
        const float3& Location = Camera.GetLocation();

        AllocateBuffer(Res);

        for (std::size_t Y = 0; Y < Res.y; Y++) {
            for (std::size_t X = 0; X < Res.x; X++) {
                const std::size_t Index = PixelToIndex(Res, { X, Y });
                const float2 UV = PixelToUV(Res, { X, Y });

                const Ray PrimaryRay = Camera.MakeRay(UV);
                const float3 Color = Painter->Paint(Camera, Scene->Raycast(PrimaryRay));
                SetPixelByIndex(Index, Color);
            }
        }

        LastRender.Resolution = Res;
    }
}

void Tracer::Save(const std::string& Filename) const
{
    const uint2 Res = LastRender.Resolution;
    stbi_write_png(Filename.c_str(), Res.x, Res.y, 3, Buffer.data(), 0);
}

void Tracer::AllocateBuffer(const uint2& Res)
{
    Buffer.resize(Res.x * Res.y);
}

}