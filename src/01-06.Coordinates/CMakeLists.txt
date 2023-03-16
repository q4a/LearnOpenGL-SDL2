set(SRC_FILES Coordinates.cpp)

file(COPY shader
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(01-06.Coordinates ${SRC_FILES})

if (MSVC)
    target_link_libraries(01-06.Coordinates PRIVATE SDL2::SDL2 SDL2::SDL2main GLAD)
else()
    target_link_libraries(01-06.Coordinates ${SDL2_LIBRARIES} GLAD)
endif ()
