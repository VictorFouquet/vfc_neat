# ----------------------
# Fetch Criterion if not found
# ----------------------
find_package(Criterion QUIET)

if(NOT Criterion_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        Criterion
        GIT_REPOSITORY https://github.com/Snaipe/Criterion
        GIT_TAG v2.4.2  # Use the latest stable version
    )
    FetchContent_MakeAvailable(Criterion)
    set(CRITERION_TARGET criterion)  # FetchContent uses lowercase
else()
    set(CRITERION_TARGET Criterion::criterion)  # find_package uses namespaced
endif()

# Collect test sources
file(GLOB TEST_SRC CONFIGURE_DEPENDS src/*.c)

# Create the test executable
add_executable(neat_test ${TEST_SRC})

# Include directories
target_include_directories(neat_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include   # neat headers
    ${CMAKE_CURRENT_SOURCE_DIR}/src           # test headers
)

# Link against neat library and Criterion
target_link_libraries(neat_test PRIVATE 
    neat 
    m
    ${CRITERION_TARGET}
)

# Debug/Release compile flags
target_compile_options(neat_test PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -fsanitize=address,undefined>
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
)

# CRITICAL: Add sanitizer link flags for Debug mode
target_link_options(neat_test PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)