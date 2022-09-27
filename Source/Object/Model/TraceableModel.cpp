#include "Object/Model/TraceableModel.h"

namespace Raytracer {

using namespace linalg::aliases;

void TraceableModel::SetLocation(const float3& Location)
{
    this->Location = Location;
}

float3 TraceableModel::GetLocation() const
{
    return Location;
}

bool TraceableModel::IsTraceable() const
{
    return true;
}

void TraceableModel::SetColor(const float3& Color) {
    this->Color = Color;
}

float3 TraceableModel::GetColor() const
{
    return Color;
}

}