#include "Object/Model/TraceableModel.h"

namespace Raytracer {

using namespace linalg::aliases;

TraceableModel& TraceableModel::SetLocation(const float3& Location)
{
    this->Location = Location;
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

TraceableModel& TraceableModel::SetColor(const float3& Color) {
    this->Color = Color;
    return *this;
}

float3 TraceableModel::GetColor() const
{
    return Color;
}

}