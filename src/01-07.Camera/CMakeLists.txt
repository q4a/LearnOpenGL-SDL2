set(SRC_FILES Camera.cpp)

file(COPY shader
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ../Assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(01-07.Camera ${SRC_FILES})
add_executable(01-07.Camera2 Camera_with_class.cpp)

if (MSVC)
    target_link_libraries(01-07.Camera PRIVATE SDL2::SDL2 SDL2::SDL2main GLAD)
    target_link_libraries(01-07.Camera2 PRIVATE SDL2::SDL2 SDL2::SDL2main GLAD)

    set_property(TARGET 01-07.Camera PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
    set_property(TARGET 01-07.Camera2 PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
else()
    target_link_libraries(01-07.Camera ${SDL2_LIBRARIES} GLAD)
    target_link_libraries(01-07.Camera2 ${SDL2_LIBRARIES} GLAD)
endif ()
