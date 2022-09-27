#include <iostream>
#include <numbers>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "linalg/linalg.h"

#include "Object/Model/Plane.h"
#include "Object/Model/Sphere.h"
#include "Painter/FacingRatioPainter.h"
#include "Painter/WorldNormalPainter.h"
#include "Ray/Ray.h"
#include "Scene/ObjectsScene.h"
#include "Shader/Color.h"
#include "Tracer/Tracer.h"

using namespace std::literals::string_literals;
using namespace linalg::aliases;
namespace RT = Raytracer;

void InitObjects(RT::ObjectsScene& Scene)
{
    {
        auto& Model = Scene.Emplace<RT::SphereModel>("sphere1"s, 2);
        Model.SetLocation({ 0, -5, -1 });
        Model.SetColor(RT::Color::Red);
    }
    {
        auto& Model = Scene.Emplace<RT::SphereModel>("sphere2"s, 3);
        Model.SetLocation({ 0, 0, 0 });
        Model.SetColor(RT::Color::Green);
    }
    {
        auto& Model = Scene.Emplace<RT::SphereModel>("sphere3"s, 2);
        Model.SetLocation({ 0, 5, -1 });
        Model.SetColor(RT::Color::Blue);
    }

    {
        auto& Model = Scene.Emplace<RT::PlaneModel>("ground"s, float3 { 0, 0, 1 });
        Model.SetLocation({ 0, 0, -3 });
        Model.SetColor(RT::Color::White);
    }
}

void InitCameras(RT::ObjectsScene& Scene)
{
    {
        RT::Camera& Camera = Scene.Emplace<RT::Camera>("cam1"s);
        Camera.SetLocation({-10, 0, 0});
        Camera.SetDirection({0.5, 0, 0.0});
    }

    {
        RT::Camera& Camera = Scene.Emplace<RT::Camera>("cam2"s);
        Camera.SetLocation({0, 0, 8});
        Camera.SetDirection({0.01, 0, -1});
        // Camera.SetAspectRatio(1);
    }
}

int main()
{
    RT::Tracer Tracer(720);

    RT::ObjectsScene& Scene = Tracer.EmplaceScene<RT::ObjectsScene>();

    Scene.ClearAll();

    InitObjects(Scene);
    InitCameras(Scene);

    Scene.SwitchCamera("cam1"s);
    Tracer.EmplacePainter<RT::WorldNormalPainter>();
    Tracer.Render();
    Tracer.Save("WorldNormal.png"s);

    Tracer.EmplacePainter<RT::FacingRatioPainter>();
    Tracer.Render();
    Tracer.Save("FacingRatio.png"s);
}
