#include <iostream>
#include <numbers>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "linalg/linalg.h"

#include "Object/Objects.h"
#include "Painter/Painters.h"
#include "Ray/Ray.h"
#include "Scene/ObjectsScene.h"
#include "Material/Color.h"
#include "Tracer/Tracer.h"

using namespace std::literals::string_literals;
using namespace linalg::aliases;
namespace RT = Raytracer;

void InitObjects(RT::ObjectsScene& Scene)
{
    Scene.Emplace<RT::SphereModel>("sphere1"s, 2)
        .SetLocation({ 0, -5, -1 })
        .SetColor(RT::Color::Red);

    Scene.Emplace<RT::SphereModel>("sphere2"s, 3)
        .SetLocation({ 0, 0, 0 })
        .SetColor(RT::Color::Green);

    Scene.Emplace<RT::SphereModel>("sphere3"s, 2)
        .SetLocation({ 0, 5, -1 })
        .SetColor(RT::Color::Blue);

    Scene.Emplace<RT::PlaneModel>("ground"s, float3 { 0, 0, 1 })
        .SetLocation({ 0, 0, -3 })
        .SetColor(RT::Color::White);
}

void InitCameras(RT::ObjectsScene& Scene)
{
    Scene.Emplace<RT::Camera>("cam1"s)
        .SetLocation({ -10, 0, 0 })
        .SetDirection({ 0.5, 0, 0.0 });
    //  .SetAspectRatio(1);

    Scene.Emplace<RT::Camera>("cam2"s)
        .SetLocation({ 0, 0, 8 })
        .SetDirection({ 0.001, 0, -1 });
    //  .SetAspectRatio(1);
}

void InitLights(RT::ObjectsScene& Scene)
{
    Scene.Emplace<RT::DirectionalLight>("dlight1"s)
        .SetDirection({ 0.3, 0.3, -1 })
        .SetLocation({})
        .SetIntensity(0.5);

    // Scene.Emplace<RT::PointLight>("plight1"s)
    //     .SetLocation({8, -8, 8})
    //     .SetIntensity(0.3);
}

void InitScene(RT::ObjectsScene& Scene)
{
    InitObjects(Scene);
    InitCameras(Scene);
    InitLights(Scene);
}

int main()
{
    RT::Tracer Tracer(1080);

    RT::ObjectsScene& Scene = Tracer.EmplaceScene<RT::ObjectsScene>();

    Scene.ClearAll();

    InitScene(Scene);

    Scene.SwitchCamera("cam1"s);
    // Tracer.EmplacePainter<RT::WorldNormalPainter>();
    // Tracer.Render();
    // Tracer.Save("WorldNormal.png"s);

    // Tracer.EmplacePainter<RT::FacingRatioPainter>();
    // Tracer.Render();
    // Tracer.Save("FacingRatio.png"s);

    Tracer.EmplacePainter<RT::SceneColorPainter>();
    Tracer.Render();
    Tracer.Save("Lambert.png"s);
}
