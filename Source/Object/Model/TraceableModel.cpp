#include "Object/Model/TraceableModel.h"

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

float3 TraceableModel::GetColor() const
{
    return Color;
}

}
