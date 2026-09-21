cmake_minimum_required(VERSION 3.10)

project(TestV3)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(Geant4 REQUIRED ui_all vis_all)  #ui - user interaction vis- visualization
include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

file(GLOB MACRO_FILES "macros/*.mac") #all macros created in the fututre will be copied
file(COPY ${MACRO_FILES} DESTINATION ${CMAKE_BINARY_DIR}/)

add_executable(sim sim.cc ${sources})
target_link_libraries(sim ${Geant4_LIBRARIES})

add_custom_target(TestV3 DEPENDS sim)