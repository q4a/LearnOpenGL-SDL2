set(SRC_FILES HelloWindow.cpp)

add_executable(01-01.HelloWindow ${SRC_FILES})

if (MSVC)
    # Linking with vcpkg
    target_link_libraries(01-01.HelloWindow PRIVATE SDL2::SDL2 SDL2::SDL2main GLAD)
else()
    target_link_libraries(01-01.HelloWindow ${SDL2_LIBRARIES} GLAD)
endif ()
