#----------- general -----------

cmake_minimum_required(VERSION 3.24)
project(sfmlgraphic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#----------- project -----------

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(CMakeUtils REQUIRED)
include(${cmakeutils_SOURCE_DIR}/ToolBSL.cmake)

bsl_store()

find_package(System REQUIRED)
find_package(IGraphic REQUIRED)
find_package(Maths REQUIRED)
find_package(Sfml REQUIRED)

bsl_restore()

set(SOURCE_FILES sources/sfml.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

#----------- dependencies -----------

target_link_libraries(${PROJECT_NAME} 
  igraphic
  maths
  
  SFML::Graphics
  SFML::Window
  SFML::System
  SFML::Audio
)

#----------- includes -----------

target_include_directories(${PROJECT_NAME} PUBLIC
  includes/audio
  includes/window
  includes/graphic
  includes/event
  includes
)

#----------- dev -----------

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

#----------- tests -----------

find_package(GoogleTest REQUIRED)

enable_testing()

file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME}_tests 
  gtest_main
  igraphic
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
