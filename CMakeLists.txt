# Проверяем версию cmake
cmake_minimum_required(VERSION 3.5)

# Имя проекта
project(ray_tracing)

# Флаги компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

# Исходные фаилы
set(SOURCE_EXE main.cpp Additional.h Window.cpp Camera.cpp Light.cpp ObjLoader.cpp Render.cpp Scene.cpp Shape.cpp Sphere.cpp TraversalTree.cpp Triangle.cpp tests.cpp Material.h)

# Дополнительные директории с заголовочными файлами
include_directories(../Geometry)

# Добавляем директорию с библиотекой вычислительной геометрии
link_directories(../Geometry/build)

# Библиотека работы с X Window System
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

# SDL для работы с изображеними
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

# Исполняемый фаил
add_executable(ray_tracing ${SOURCE_EXE})

# Линкуем с библиотеками
target_link_libraries(ray_tracing Geometry ${X11_LIBRARIES} ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES} )