#include "Scene/ObjectsScene.h"
#include "Painter/Painter.h"
#include "Ray/Ray.h"
#include <iostream>
#include <memory>

namespace Raytracer {

static constexpr const float ScatteredTMin = 0.00001f;

ObjectsScene::~ObjectsScene() { }

void ObjectsScene::ClearAll()
{
    Models.clear();
    Lights.clear();
    Cameras.clear();
}

std::optional<const SurfaceRecord> ObjectsScene::RayCast(const RenderFlags& Flags, const Ray& InRay, const TRange<float>& Range, const std::uint64_t Depth) const
{
    std::optional<SurfaceRecord> WorkingRec = CheckHit(InRay, Range);

    if (Depth > 10) {
        return std::nullopt;
    }

    if (!WorkingRec) {
        return SurfaceRecord {
            .T = 0,
            .IsFront = true,
            .Position = float3(),
            .Normal = float3(),
            .Radiance = BackgroundRadiance,
            .Mat = std::weak_ptr<Material>()
        };
    }

    if (const std::shared_ptr<Material> Mat = WorkingRec->Mat.lock()) {
        if (const std::optional<Ray> Reflected = Mat->Reflect(WorkingRec->Position, WorkingRec->Normal, InRay)) {
            if (const std::optional<SurfaceRecord> ReflectedRec = RayCast(Flags, *Reflected, TRange(ScatteredTMin, std::numeric_limits<float>::max()), Depth + 1)) {
                WorkingRec->Radiance *= ReflectedRec->Radiance / std::numbers::pi_v<float>;
            }
        }

        if (Flags.DirectLight && Mat->ForceShadowRay()) {
            for (const auto& [Key, Light] : Lights) {
                const auto& [SRay, ST] = Light->MakeShadowRay(WorkingRec->Position);
                if (const std::optional<SurfaceRecord>& DirectShadowRecord = CheckHit(SRay, TRange(ScatteredTMin, ST))) {
                } else {
                    WorkingRec->Radiance += Light->GetIrradiance(WorkingRec->Position, WorkingRec->Normal) / std::numbers::pi_v<float>;
                }
            }
        }
    }

    return WorkingRec;
}

std::optional<const SurfaceRecord> ObjectsScene::CheckHit(const Ray& InRay, const TRange<float>& Range) const
{
    std::optional<SurfaceRecord> WorkingRec = std::nullopt;
    TRange<float> WorkingRange = Range;

    for (const auto& [Key, Model] : Models) {
        const std::optional<SurfaceRecord>& Rec = Model->RayCast(InRay, WorkingRange);

        if (!Rec || !WorkingRange.Included(Rec->T)) {
            continue;
        }

        WorkingRec = Rec;
        WorkingRange.TMax = Rec->T;
    }

    return WorkingRec;
}

OptRef<Camera> ObjectsScene::GetActiveCamera() const
{
    const auto& Name = ActiveCameraName;
    if (!Name.empty() && Cameras.contains(Name)) {
        return std::ref(*Cameras.at(Name));
    }
    std::cerr << Name << "は無効です" << std::endl;
    return std::nullopt;
}

bool ObjectsScene::SwitchCamera(const std::string& Name)
{
    if (Cameras.contains(Name)) {
        ActiveCameraName = Name;
        return true;
    }
    return false;
}

ObjectsScene& ObjectsScene::SetBackgroundRadiance(const float3& InBackground)
{
    BackgroundRadiance = InBackground;
    return *this;
}

}
