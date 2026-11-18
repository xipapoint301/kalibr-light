cmake_minimum_required(VERSION 3.16)
project(kalibr_light LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

find_package(Eigen3 REQUIRED NO_MODULE)
find_package(Ceres REQUIRED)

# Sophus: header-only, лежит в libs/Sophus. Его CMakeLists требует CMake>=3.24,
# поэтому объявляем интерфейсную цель сами.
add_library(sophus INTERFACE)
add_library(Sophus::Sophus ALIAS sophus)
target_include_directories(sophus SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/Sophus)
target_link_libraries(sophus INTERFACE Eigen3::Eigen)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
  Eigen3::Eigen
  Ceres::ceres
  Sophus::Sophus
  ${OpenCV_LIBS}
)
