cmake_minimum_required(VERSION 2.7)
project(CpuRenderer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(GLEW_PATH thirdparty/glew)
set(GLFW_PATH thirdparty/glfw)
set(TINY_OBJLOADER_PATH thirdparty/tiny_obj_loader)
set(LODEPNG_PATH thirdparty/lodepng)

set(INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)

set (CMAKE_INSTALL_PREFIX ${INSTALL_DIR})

include_directories(${GLEW_PATH}/include)
include_directories(${GLFW_PATH}/include)
include_directories(${TINY_OBJLOADER_PATH})
include_directories(${LODEPNG_PATH})

add_subdirectory(${GLEW_PATH}/build/cmake)
add_subdirectory(${GLFW_PATH})
add_subdirectory(${TINY_OBJLOADER_PATH})
add_subdirectory(${LODEPNG_PATH})

if(WIN32)
	set(SDL2_PATH thirdparty/SDL2)
	set(SDL_STATIC ON CACHE BOOL "build sdl static library")
	set(SDL_SHARED OFF CACHE BOOL "build sdl shared library")
	set(SDL2_LIBRARIES SDL2-static SDL2main)
	add_subdirectory(${SDL2_PATH})
	include_directories(${SDL2_PATH}/include)
elseif(APPLE OR UNIX)
	find_package(SDL2 REQUIRED)
	include_directories(${SDL2_INCLUDE_DIRS})
	string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_executable(${PROJECT_NAME}  ${SOURCES} ${HEADERS})
								
target_link_libraries(${PROJECT_NAME} glew_s)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} tinyObjLoader)
target_link_libraries(${PROJECT_NAME} lodepng)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

if(WIN32)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

install (TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIR})
install (DIRECTORY ${RES_DIR}  DESTINATION ${INSTALL_DIR})