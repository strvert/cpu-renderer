#include "Scene/ObjectsScene.h"
#include <iostream>

namespace Raytracer {

ObjectsScene::~ObjectsScene() { }

void ObjectsScene::ClearAll()
{
    Models.clear();
}

std::optional<const Record> ObjectsScene::RayCast(const Ray& Ray, const TRange<float>& Range) const
{
    TRange<> WorkingRange = Range;
    std::optional<Record> WorkingRec;

    for (const auto& [Key, Model] : Models) {
        const std::optional<Record>& Rec = Model->RayCast(Ray, WorkingRange);

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