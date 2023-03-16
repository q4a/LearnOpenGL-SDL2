set(SRC_FILES HelloTriangle.cpp)

add_executable(01-02.HelloTriangle ${SRC_FILES})

if (MSVC)
    # Linking with vcpkg
    target_link_libraries(01-02.HelloTriangle PRIVATE SDL2::SDL2 SDL2::SDL2main GLAD)
else()
    target_link_libraries(01-02.HelloTriangle ${SDL2_LIBRARIES} GLAD)
endif ()
