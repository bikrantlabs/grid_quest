cmake_minimum_required(VERSION 3.5)
project(grid_quest)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/headers)
file(GLOB_RECURSE SRCS src/*.c)
set(CMAKE_BUILD_TYPE Debug)
# Find GTK4 package using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Include GTK3 directories
include_directories(${GTK4_INCLUDE_DIRS} src/ src/headers/)
add_definitions(${GTK4_CFLAGS_OTHER})

link_directories(src/headers/)

# Add the main executable
add_executable(${PROJECT_NAME} ${SRCS})


# Link GTK4 libraries
target_link_libraries(grid_quest ${GTK4_LIBRARIES})
target_include_directories(grid_quest PRIVATE ${PROJECT_SOURCE_DIR}/src/headers/)