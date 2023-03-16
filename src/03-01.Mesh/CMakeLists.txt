set(SRC_FILES Mesh.cpp)

file(COPY shader
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(03-01.Mesh ${SRC_FILES})

if (MSVC)
    target_link_libraries(03-01.Mesh PRIVATE SDL2::SDL2 SDL2::SDL2main ${ASSIMP_LIBRARIES} GLAD)

    set_property(TARGET 03-01.Mesh PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
else()
    target_link_libraries(03-01.Mesh ${SDL2_LIBRARIES} ${ASSIMP_LIBRARIES} GLAD)
endif ()
