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

TraceableModel& TraceableModel::SetMaterial(std::shared_ptr<Material> InMaterial) {
    this->Mat = std::move(InMaterial);
    return *this;
}

std::weak_ptr<Material> TraceableModel::GetMaterial() const {
    return Mat;
}

float3 TraceableModel::GetColor() const
{
    return Color;
}

}
