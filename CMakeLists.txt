cmake_minimum_required(VERSION 3.5)
project(RayTracing)

set(CMAKE_CXX_STANDARD 26)

add_executable(RayTracing main.cpp
        vec3.h
        color.h
        ray.h
        hittable.h
        sphere.h
        hittable_list.h
        utility.h)
