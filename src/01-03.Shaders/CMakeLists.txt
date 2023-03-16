set(SRC_FILES Shader.cpp)

file(COPY shader
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(01-03.Shaders ${SRC_FILES})

if (MSVC)
    target_link_libraries(01-03.Shaders PRIVATE SDL2::SDL2 SDL2::SDL2main GLAD)
else()
    target_link_libraries(01-03.Shaders ${SDL2_LIBRARIES} GLAD)
endif ()
