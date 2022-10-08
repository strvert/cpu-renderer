#include "Scene/ObjectsScene.h"
#include "Ray/Ray.h"
#include "Painter/Painter.h"
#include <iostream>

namespace Raytracer {

ObjectsScene::~ObjectsScene() { }

void ObjectsScene::ClearAll()
{
    Models.clear();
}

std::optional<const SurfaceRecord> ObjectsScene::RayCast(const RenderFlags& Flags, const Ray& InRay, const TRange<float>& Range) const
{
    std::optional<SurfaceRecord> WorkingRec = CheckHit(InRay, Range);

    if (!WorkingRec) {
        return std::nullopt;
    }

    TRange<float> WorkingRange(Range.TMin, WorkingRec->T);

    if (Flags.DirectLight) {
        for (const auto& [Key, Light] : Lights) {
            const auto& [SRay, T] = Light->MakeShadowRay(WorkingRec->Position);
            if (const std::optional<SurfaceRecord>& DirectShadowRecord = CheckHit(SRay, TRange(0.00001f, T))) {
            } else {
                WorkingRec->Radiance += Light->GetIrradiance(WorkingRec->Position, WorkingRec->Normal);
            }
        }
    }

    return WorkingRec;
}

std::optional<const SurfaceRecord> ObjectsScene::CheckHit(const Ray& InRay, const TRange<float>& Range) const
{
    std::optional<SurfaceRecord> WorkingRec;
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

}
