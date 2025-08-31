cmake_minimum_required(VERSION 3.16)
project(Elevation_Caused_Error_DF_System C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- Raylib dependency (optional visualization) ---
include(FetchContent)
# Share FetchContent downloads/builds em ~/.cache/cmake por padrão
if(NOT DEFINED FETCHCONTENT_BASE_DIR)
  set(FETCHCONTENT_BASE_DIR "$ENV{HOME}/.cache/cmake" CACHE PATH "Base dir for FetchContent downloads" FORCE)
endif()
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if(NOT raylib_FOUND)
  message(STATUS "raylib not found system-wide; fetching ${RAYLIB_VERSION}...")
  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG ${RAYLIB_VERSION}
  )
  FetchContent_MakeAvailable(raylib)
endif()

# Targets
add_library(df_error STATIC
  src/df_error.c
)

target_include_directories(df_error PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(df_demo
  src/df_demo.c
)

target_include_directories(df_demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(df_demo PRIVATE df_error m)

# Optional 3D interactive visualization
add_executable(df_viz
  src/df_viz.c
)
target_include_directories(df_viz PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(df_viz PRIVATE df_error m raylib)
if (TARGET raylib)
  target_include_directories(df_viz PRIVATE ${raylib_SOURCE_DIR}/src)
endif()

# Install
install(TARGETS df_demo df_viz RUNTIME DESTINATION bin)
install(TARGETS df_error ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

# Doxygen
find_package(Doxygen QUIET)
if (DOXYGEN_FOUND)
  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating documentation with Doxygen"
    VERBATIM)
endif()
