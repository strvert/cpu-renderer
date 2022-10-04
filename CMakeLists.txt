cmake_minimum_required(VERSION 3.10)

project(cpp-raytracer)

add_executable(raytracer)

target_compile_features(raytracer
    PRIVATE
    cxx_std_20
    )

target_compile_options(raytracer
    PRIVATE
    -Wall
    -Wextra
    )

target_include_directories(raytracer
    PRIVATE
    Include
    ThirdParty/Include
    )

target_sources(raytracer
    PRIVATE
    Source/Main.cpp
    Source/Object/Model/Sphere.cpp
    Source/Object/Model/Plane.cpp
    Source/Object/Model/TraceableModel.cpp
    Source/Object/Light/DirectionalLight.cpp
    Source/Object/Light/PointLight.cpp
    Source/Object/Camera/Camera.cpp
    Source/Ray/Ray.cpp
    Source/Scene/Scene.cpp
    Source/Scene/ObjectsScene.cpp
    Source/Tracer/Tracer.cpp
    Source/Material/Material.cpp
    Source/Material/Lambert.cpp
    Source/Console/Progress.cpp
    )