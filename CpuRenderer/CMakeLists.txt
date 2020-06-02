cmake_minimum_required(VERSION 2.7)
project(CpuRenderer)

set(GLEW_PATH thirdparty/glew)
set(GLFW_PATH thirdparty/glfw)
set(SDL2_PATH thirdparty/SDL2)
set(SDL_STATIC ON CACHE BOOL "build sdl static library")
set(SDL_SHARED OFF CACHE BOOL "build sdl shared library")
set(SDL2_LIBRARIES SDL2-static SDL2main)
set(INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)

set (CMAKE_INSTALL_PREFIX ${INSTALL_DIR})

include_directories(${GLEW_PATH}/include)
include_directories(${GLFW_PATH}/include)
include_directories(${SDL2_PATH}/include)
add_subdirectory(${GLEW_PATH}/build/cmake)
add_subdirectory(${GLFW_PATH})
add_subdirectory(${SDL2_PATH})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
								${CMAKE_CURRENT_SOURCE_DIR}/include/test.h)
target_link_libraries(${PROJECT_NAME} glew_s)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

if(WIN32)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

install (TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIR})
install (DIRECTORY ${RES_DIR}  DESTINATION ${INSTALL_DIR})