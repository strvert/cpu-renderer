#pragma once

namespace Raytracer {

template <typename T>
using Ref = std::reference_wrapper<T>;

template <typename T>
using OptRef = std::optional<Ref<T>>;

template <typename T>
T& Value(OptRef<T> Ref)
{
    return Ref.value().get();
}

}