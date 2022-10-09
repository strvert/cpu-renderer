#include <iostream>
#include <numbers>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "linalg/linalg.h"

#include "Material/Color.h"
#include "Material/Materials.h"
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
        .SetMaterial(std::make_shared<RT::Lambert>())
        .SetColor(RT::NamedColor::Red);

    Scene.Emplace<RT::SphereModel>("sphere2"s, 3)
        .SetLocation({ 0, 0, 3 })
        .SetMaterial(std::make_shared<RT::PerfectReflection>())
        .SetColor({ 0.0f, 0.8f, 0.8f });

    Scene.Emplace<RT::SphereModel>("sphere3"s, 2)
        .SetLocation({ 0, 5, 2 })
        .SetMaterial(std::make_shared<RT::PerfectReflection>())
        .SetColor(RT::NamedColor::Indigo);

    Scene.Emplace<RT::PlaneModel>("ground"s, float3 { 0, 0, 1 })
        .SetLocation({ 0, 0, 0 })
        .SetMaterial(std::make_shared<RT::Lambert>())
        .SetColor({ 0.1f, 0.9f, 0.1f });

    Scene.Emplace<RT::PlaneModel>("wall"s, float3 { 0, 1, 0 })
        .SetLocation({ 0, -10, 0 })
        .SetMaterial(std::make_shared<RT::PerfectReflection>())
        .SetColor({ 1.0f, 1.0f, 1.0f });
}

static void InitCameras(RT::ObjectsScene& Scene)
{
    Scene.Emplace<RT::Camera>("cam1"s)
        .SetLocation({ -10, 0, 3 })
        .SetDirection({ 0.5, -0.1, 0.0 });
    //  .SetAspectRatio(1);

    Scene.Emplace<RT::Camera>("cam2"s)
        .SetLocation({ -8, 0, 15 })
        .SetDirection({ 0.65f, 0.0f, -1.0f });
    //  .SetAspectRatio(1);
}

void InitLights(RT::ObjectsScene& Scene)
{
    Scene.Emplace<RT::DirectionalLight>("dlight1"s)
        .SetDirection({ -0.3f, -0.3f, -1.0f })
        .SetLightColor({ 1.0f, 1.0f, 1.0f })
        .SetIntensity(1.2f);

    Scene.Emplace<RT::PointLight>("plight1"s)
        .SetLocation({ -6, -5, 4 })
        .SetLightColor({ 1.0f, 1.0f, 1.0f })
        .SetIntensity(1);
}

static void InitScene(RT::ObjectsScene& Scene)
{
    InitObjects(Scene);
    InitCameras(Scene);
    InitLights(Scene);
}

int main()
{
    RT::Tracer Tracer(640);

    Tracer.EmplaceSampler<RT::RGSS>().SetScale(2);

    RT::ObjectsScene& Scene = Tracer.EmplaceScene<RT::ObjectsScene>();

    Scene.ClearAll();

    InitScene(Scene);

    Scene.SwitchCamera("cam1"s);

    Tracer.EmplacePainter<RT::SceneColorPainter>();
    Tracer.Render();
    Tracer.Save("Render.png"s);
}
