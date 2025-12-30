cmake_minimum_required(VERSION 3.16)
project(neat LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

if (NOT TARGET vfc_utils)
    FetchContent_Declare(
        vfc_utils
        GIT_REPOSITORY https://github.com/VictorFouquet/vfc_utils.git
        GIT_TAG 1.2.3
    )
    FetchContent_MakeAvailable(vfc_utils)
endif()

# Option to build tests (default OFF when used as a subdirectory)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # Building neat as the main project - enable tests by default
    option(NEAT_BUILD_TESTS "Build neat tests" ON)
else()
    # Building neat as a subdirectory - disable tests by default
    option(NEAT_BUILD_TESTS "Build neat tests" OFF)
endif()

if(NEAT_BUILD_TESTS)
    add_subdirectory(test)
endif()

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.c)
add_library(neat STATIC ${SRC_FILES})
set_target_properties(neat PROPERTIES OUTPUT_NAME neat)

target_compile_options(neat
    PRIVATE
        -Wall -Wextra
        $<$<CONFIG:Debug>:-g -O0 -fsanitize=address,undefined -fstack-protector-strong>
        $<$<CONFIG:Release>:-O3 -DNDEBUG>
)

target_link_options(neat
    PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

target_include_directories(neat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(neat
    PUBLIC
        vfc_utils
        m
)
