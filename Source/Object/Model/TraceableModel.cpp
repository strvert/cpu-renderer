#include "Object/Model/TraceableModel.h"
#include "Core/Types.h"

namespace Raytracer {

using namespace linalg::aliases;

TraceableModel::~TraceableModel() {}

TraceableModel& TraceableModel::SetLocation(const float3& InLocation)
{
    this->Location = InLocation;
    return *this;
}

float3 TraceableModel::GetLocation() const
{
    return Location;
}

bool TraceableModel::IsTraceable() const
{
    return true;
}

TraceableModel& TraceableModel::SetColor(const float3& InColor) {
    this->Color = InColor;
    return *this;
}

TraceableModel& TraceableModel::SetMaterial(std::unique_ptr<Material> InMaterial) {
    this->Mat = std::move(InMaterial);
    return *this;
}

OptRef<Material> TraceableModel::GetMaterial() {
    if (Mat) {
        return std::nullopt;
    }

    return std::ref(*Mat);
}

float3 TraceableModel::GetColor() const
{
    return Color;
}

}
