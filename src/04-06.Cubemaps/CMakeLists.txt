set(SRC_FILES cubemaps_skybox.cpp)

file(COPY shader
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ../Assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(04-06.cubemaps_skybox ${SRC_FILES})

if (MSVC)
    target_link_libraries(04-06.cubemaps_skybox PRIVATE SDL2::SDL2 SDL2::SDL2main GLAD)
    set_property(TARGET 04-06.cubemaps_skybox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
else()
    target_link_libraries(04-06.cubemaps_skybox ${SDL2_LIBRARIES} GLAD)
endif ()
