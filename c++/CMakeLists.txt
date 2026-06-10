cmake_minimum_required(VERSION 3.16)
project(cpp_practice CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 컴파일 경고 활성화
add_compile_options(-Wall -Wextra -Wpedantic)

# 기본 Debug 빌드
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# src/ 안의 각 .cpp 파일을 독립 실행 파일로 빌드
file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

foreach(source ${SOURCES})
  get_filename_component(name ${source} NAME_WE)
  add_executable(${name} ${source})
endforeach()
