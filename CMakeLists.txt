cmake_minimum_required(VERSION 3.12)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_NAME game)
add_executable(${PROJECT_NAME} main_3.cpp  )

project(${PROJECT_NAME} VERSION 1.0 DESCRIPTION "Project 3 ")
enable_language(C CXX)

include_directories(${PROJECT_NAME} include src utils project)

target_sources(${PROJECT_NAME} PRIVATE 
./include/glad.c 

./include/model.cpp
./include/shader.cpp
./include/mesh.cpp
./include/controls.cpp
./include/physical.cpp
./include/collisions.cpp
./include/particle.cpp

./include/physical_contact.cpp
./include/set_up.cpp

./utils/control_callbacks.cpp

./project/orbit.cpp
)


target_link_libraries(${PROJECT_NAME}
    GL
    X11
    assimp
    glfw
    pthread
    Xrandr
    Xi
    dl
)

target_compile_options(${PROJECT_NAME} PRIVATE -Og -g3 )

set(PROJECT_NAME orbit)
add_executable(${PROJECT_NAME} main_2.cpp  )

project(${PROJECT_NAME} VERSION 1.0 DESCRIPTION "Project 2") 
enable_language(C CXX)

include_directories(${PROJECT_NAME} include src utils project)

target_sources(${PROJECT_NAME} PRIVATE 
./include/glad.c 

./include/model.cpp
./include/shader.cpp
./include/mesh.cpp
./include/controls.cpp
./project/orbit.cpp
./include/physical.cpp
./include/particle.cpp
./include/collisions.cpp
./include/physical_contact.cpp

./include/set_up.cpp

./utils/control_callbacks.cpp

./project/orbit.cpp
)


target_link_libraries(${PROJECT_NAME}
    GL
    X11
    assimp
    glfw
    pthread
    Xrandr
    Xi
    dl
)
target_compile_options(${PROJECT_NAME} PRIVATE -O3 )


set(PROJECT_NAME scene)
add_executable(${PROJECT_NAME} main_1.cpp  )

project(${PROJECT_NAME} VERSION 1.0 DESCRIPTION "Project 3") 
enable_language(C CXX)

include_directories(${PROJECT_NAME} include src utils project)

target_sources(${PROJECT_NAME} PRIVATE 
./include/glad.c 

./include/model.cpp
./include/shader.cpp
./include/mesh.cpp
./include/controls.cpp
./project/orbit.cpp
./include/physical.cpp
./include/particle.cpp
./include/collisions.cpp
./include/physical_contact.cpp

./include/set_up.cpp

./utils/control_callbacks.cpp

./project/orbit.cpp
)


target_link_libraries(${PROJECT_NAME}
    GL
    X11
    assimp
    glfw
    pthread
    Xrandr
    Xi
    dl
)

target_compile_options(${PROJECT_NAME} PRIVATE -O3 )

