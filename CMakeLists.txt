cmake_minimum_required(VERSION 3.11)
set(PROJECT_NAME ray-widgets)
set(RW_STATIC_LIB  ${PROJECT_NAME}-static)
set(RW_SHARED_LIB  ${PROJECT_NAME}-shared)
set(RW_LIB "")
set(CMAKE_CXX_STANDARD 17)

project(
    ${PROJECT_NAME}
    VERSION 1.0
    DESCRIPTION "A set of widgets for building simple user interfaces in raylib"
    HOMEPAGE_URL "https://github.com/diegostafa/ray-widgets"
    LANGUAGES CXX
)

add_subdirectory(deps/raylib)
find_package(raylib)

file(GLOB_RECURSE SOURCES "core/*.cpp" "extra/*.cpp" "helpers/*.cpp" "utils/*.cpp")

option(RAY_WIDGETS_STATIC ${RW_STATIC_LIB} ON)
option(RAY_WIDGETS_SHARED ${RW_SHARED_LIB} OFF)

if(RAY_WIDGETS_STATIC)
    set(RW_LIB ${RW_STATIC_LIB})
    add_library(${RW_LIB} STATIC)
endif()

if(RAY_WIDGETS_SHARED)
    set(RW_LIB ${RW_SHARED_LIB})
    add_library(${RW_LIB} SHARED)
endif()

target_include_directories(${RW_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/include)
target_include_directories(${RW_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/extra/include)
target_include_directories(${RW_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/helpers/include)
target_include_directories(${RW_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/utils/include)
target_link_libraries(${RW_LIB} raylib)
target_sources(${RW_LIB} PRIVATE ${SOURCES})


add_subdirectory(example)