#include "Scene/ObjectsScene.h"

namespace Raytracer {

ObjectsScene::~ObjectsScene() { }

void ObjectsScene::ClearAll()
{
    Models.clear();
}

std::optional<const Record> ObjectsScene::Raycast(const Ray& Ray, const TRange<float>& Range) const
{
    TRange<> WorkingRange = Range;
    std::optional<Record> WorkingRec;

    for (const auto& [Key, Model] : Models) {
        const std::optional<Record>& Rec = Model->Test(Ray, WorkingRange);

        if (!Rec) {
            continue;
        }

        if (Rec->T > WorkingRange.TMax) {
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
    if (Name.empty() && Cameras.contains(Name)) {
    if (!Name.empty() && Cameras.contains(Name)) {
        return std::ref(*Cameras.at(Name));
    }
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