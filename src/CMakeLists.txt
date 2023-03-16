include_directories(src)

add_library(GLAD STATIC glad.c)

add_subdirectory(01-01.HelloWindow)
add_subdirectory(01-02.HelloTriangle)
add_subdirectory(01-03.Shaders)
add_subdirectory(01-04.Texture)
add_subdirectory(01-05.Transform)
add_subdirectory(01-06.Coordinates)
add_subdirectory(01-07.Camera)
add_subdirectory(03-01.Mesh)
