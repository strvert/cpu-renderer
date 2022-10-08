cmake_minimum_required(VERSION 3.10)

project(cpp-raytracer)

add_executable(raytracer)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

target_compile_features(raytracer
    PRIVATE
    cxx_std_20
    )

target_compile_options(raytracer
    PRIVATE
    -Wall
    -Wextra
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-padded
    -Wno-weak-vtables
    -Wno-undef
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_options(raytracer
        PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -g3
        -O0
        )
    target_link_options(raytracer
        PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        )
elseif(CMAKE_BUILD_TYPE STREQUAL Development)
    target_compile_options(raytracer
        PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -O2
        )
    target_link_options(raytracer
        PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        )
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_options(raytracer
        PRIVATE
        -O3
        )
endif()


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
    Source/Sampler/RGSS.cpp
    Source/Tracer/Tracer.cpp
    Source/Material/Material.cpp
    Source/Material/Lambert.cpp
    Source/Console/Progress.cpp
    )