set(SRC_FILES Transform.cpp)

file(COPY shader
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(01-05.Transform ${SRC_FILES})

if (MSVC)
    target_link_libraries(01-05.Transform PRIVATE SDL2::SDL2 SDL2::SDL2main GLAD)
else()
    target_link_libraries(01-05.Transform ${SDL2_LIBRARIES} GLAD)
endif ()
