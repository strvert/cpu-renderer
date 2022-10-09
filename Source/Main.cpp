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
    Scene.Emplace<RT::PlaneModel>("ground"s, float3 { 0, 0, 1 })
        .SetLocation({ 0, 0, 0 })
        .SetMaterial(std::make_shared<RT::Lambert>())
        .SetColor(RT::NamedColor::Snow);
}

static void InitCameras(RT::ObjectsScene& Scene)
{
    Scene.Emplace<RT::Camera>("cam1"s)
        .SetLocation({ -10, 0, 6 })
        .SetDirection({ 0.5, 0.0, -0.2 });
    //  .SetAspectRatio(1);

    Scene.Emplace<RT::Camera>("cam2"s)
        .SetLocation({ -8, 0, 15 })
        .SetDirection({ 0.65f, 0.0f, -1.0f });
    //  .SetAspectRatio(1);
}

static void InitLights(RT::ObjectsScene& Scene)
{
    Scene.Emplace<RT::DirectionalLight>("dlight1"s)
        .SetDirection({ -0.3f, -0.3f, -1.0f })
        .SetLightColor(float3 { 1.0f, 1.0f, 1.0f } * 0.1f)
        .SetIntensity(1.2f);

    Scene.Emplace<RT::PointLight>("plight1"s)
        .SetLocation({ -6, -5, 4 })
        .SetLightColor({ 1.0f, 1.0f, 1.0f })
        .SetLightColor(float3 { 1.0f, 1.0f, 1.0f } * 0.1f)
        .SetIntensity(1);
}

static void ScatterSpheres(RT::ObjectsScene& Scene)
{
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_real_distribution<> dist1(-1.0, 1.0);
    std::uniform_real_distribution<> dist2(0.0, 1.0);
    std::vector<std::shared_ptr<RT::Material>> Mats;
    Mats.push_back(std::make_shared<RT::PerfectReflection>());
    Mats.push_back(std::make_shared<RT::Lambert>());
    std::uniform_int_distribution<> matdist(0, Mats.size() - 1);
    std::vector<float3> Cols = {
        RT::NamedColor::Aqua,
        RT::NamedColor::Azure,
        RT::NamedColor::Indigo,
        RT::NamedColor::Cyan,
        RT::NamedColor::Darkblue,
        RT::NamedColor::Yellow
    };
    std::uniform_int_distribution<> coldist(0, Cols.size() - 1);

    for (int i = 0; i < 40; i++) {
        float R = dist2(engine) * 4;
        Scene.Emplace<RT::SphereModel>("sphere"s + std::to_string(i), R)
            .SetLocation({ dist1(engine) * 50 + 40, dist1(engine) * 50, R })
            .SetMaterial(Mats.at(matdist(engine)))
            .SetColor(Cols.at(coldist(engine)));
    }
}

static void InitScene(RT::ObjectsScene& Scene)
{
    InitObjects(Scene);
    ScatterSpheres(Scene);
    InitCameras(Scene);
    InitLights(Scene);
}

int main()
{
    RT::Tracer Tracer(1280);

    Tracer.EmplaceSampler<RT::NSS>();
    Tracer.SetSamples(1);

    RT::ObjectsScene& Scene = Tracer.EmplaceScene<RT::ObjectsScene>();

    Scene.ClearAll();
    Scene.SetBackgroundRadiance({ 0.5f, 0.5f, 0.5f });

    InitScene(Scene);
    Scene.SwitchCamera("cam1"s);

    Tracer.EmplacePainter<RT::SceneColorPainter>();
    Tracer.Render();
    Tracer.Save("Render.png"s);
}
