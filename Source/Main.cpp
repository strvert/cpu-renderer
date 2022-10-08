#include <iostream>
#include <numbers>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "linalg/linalg.h"

#include "Material/Color.h"
#include "Object/Objects.h"
#include "Painter/Painters.h"
#include "Ray/Ray.h"
#include "Sampler/Samplers.h"
#include "Scene/ObjectsScene.h"
#include "Tracer/Tracer.h"

using namespace std::literals::string_literals;
using namespace linalg::aliases;
namespace RT = Raytracer;

static void InitObjects(RT::ObjectsScene& Scene)
{
    Scene.Emplace<RT::SphereModel>("sphere1"s, 2)
        .SetLocation({ 0, -5, 2 })
        .SetColor(RT::NamedColor::Red);

    Scene.Emplace<RT::SphereModel>("sphere2"s, 3)
        .SetLocation({ 0, 0, 3 })
        .SetColor(RT::NamedColor::Green);

    Scene.Emplace<RT::SphereModel>("sphere3"s, 2)
        .SetLocation({ 0, 5, 2 })
        .SetColor(RT::NamedColor::Blue);

    Scene.Emplace<RT::PlaneModel>("ground"s, float3 { 0, 0, 1 })
        .SetLocation({ 0, 0, 0 })
        .SetColor(RT::NamedColor::White);
}

static void InitCameras(RT::ObjectsScene& Scene)
{
    Scene.Emplace<RT::Camera>("cam1"s)
        .SetLocation({ -10, 0, 3 })
        .SetDirection({ 0.5, 0, 0.0 });
    //  .SetAspectRatio(1);

    Scene.Emplace<RT::Camera>("cam2"s)
        .SetLocation({ -8, 0, 15 })
        .SetDirection({ 0.65f, 0.0f, -1.0f });
    //  .SetAspectRatio(1);
}

static void InitLights(RT::ObjectsScene& Scene)
{
    Scene.Emplace<RT::DirectionalLight>("dlight1"s)
        .SetDirection({ 0.3f, 0.3f, -1.0f })
        .SetLocation({})
        .SetIntensity(0.5);

    Scene.Emplace<RT::PointLight>("plight1"s)
        .SetLocation({ -7, -5, 5 })
        .SetIntensity(20);
}

static void InitScene(RT::ObjectsScene& Scene)
{
    InitObjects(Scene);
    InitCameras(Scene);
    InitLights(Scene);
}

int main()
{
    RT::Tracer Tracer(1920);

    Tracer.EmplaceSampler<RT::RGSS>();

    RT::ObjectsScene& Scene = Tracer.EmplaceScene<RT::ObjectsScene>();

    Scene.ClearAll();

    InitScene(Scene);

    Scene.SwitchCamera("cam1"s);

    Tracer.EmplacePainter<RT::SceneColorPainter>();
    Tracer.Render();
    Tracer.Save("Render.png"s);
}
