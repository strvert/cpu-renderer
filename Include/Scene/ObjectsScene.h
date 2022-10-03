#pragma once

#include <concepts>

#include "Scene.h"

#include "Object/Camera/Camera.h"
#include "Object/Light/Light.h"
#include "Object/Model/TraceableModel.h"

namespace Raytracer {

class ObjectsScene : public TraceableScene {
    template <typename T>
    using ObjectCollection = std::unordered_map<std::string, std::unique_ptr<T>>;

public:
    virtual ~ObjectsScene();

    template <typename T, typename... Ts>
    requires std::derived_from<T, TraceableModel>
        T& Emplace(const std::string& Name, Ts&&... Args)
    {
        return EmplaceInternal<T>(Models, Name, std::forward<Ts>(Args)...);
    }

    template <typename T, typename... Ts>
    requires std::derived_from<T, Camera>
        T& Emplace(const std::string& Name, Ts&&... Args)
    {
        return EmplaceInternal<T>(Cameras, Name, std::forward<Ts>(Args)...);
    }

    template <typename T, typename... Ts>
    requires std::derived_from<T, Light>
        T& Emplace(const std::string& Name, Ts&&... Args)
    {
        return EmplaceInternal<T>(Lights, Name, std::forward<Ts>(Args)...);
    }

    OptRef<TraceableModel> Find(const std::string& Name)
    {
        if (!Models.contains(Name)) {
            return std::nullopt;
        }
        return std::ref(*Models.at(Name));
    }

    void ClearAll();

    virtual std::optional<const SurfaceRecord> RayCast(const Ray& Ray, const TRange<float>& Range) const override;
    virtual OptRef<Camera> GetActiveCamera() const override;
    
    bool SwitchCamera(const std::string& Name);

private:
    template <typename T, typename CollectionT, typename... Ts>
    static T& EmplaceInternal(CollectionT& Collection, const std::string& Name, Ts&&... Args)
    {
        auto [Iter, _] = Collection.insert_or_assign(Name, std::make_unique<T>(std::forward<Ts>(Args)...));
        return dynamic_cast<T&>(*Iter->second);
    }

    std::optional<const SurfaceRecord> CheckHit(const Ray& Ray, const TRange<float>& Range) const;


    ObjectCollection<TraceableModel> Models;
    ObjectCollection<Camera> Cameras;
    ObjectCollection<Light> Lights;
    std::string ActiveCameraName;
};

}