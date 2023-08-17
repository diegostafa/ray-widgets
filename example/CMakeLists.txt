set(OUT "example")

find_package(raylib)

add_executable(${OUT} main.cpp)
target_link_libraries(${OUT} PUBLIC
    raylib
    ${RW_LIB})

