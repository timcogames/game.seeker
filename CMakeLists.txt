# Проверяем версию CMake
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

# Устанавливаем имя проекта
set(GAME_SEEKER_PROJECT_NAME game_seeker)
project(${GAME_SEEKER_PROJECT_NAME})

# Устанавливаем версию библиотеки
set(GAME_SEEKER_VERSION_MAJOR 0)
set(GAME_SEEKER_VERSION_MINOR 1)
set(GAME_SEEKER_VERSION_PATCH 0)
set(GAME_SEEKER_VERSION_STRING ${GAME_SEEKER_VERSION_MAJOR}.${GAME_SEEKER_VERSION_MINOR}.${GAME_SEEKER_VERSION_PATCH})

# Определяем каталог вывода по умолчанию
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
else()
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
endif()

set(GAME_SEEKER_DIR ${CMAKE_SOURCE_DIR})

include_directories(${GAME_SEEKER_DIR}/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_core/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_math/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_platform-glx11/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_ois-x11/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_graphics/include)

file(GLOB_RECURSE GAME_SEEKER_HEADERS ${GAME_SEEKER_DIR}/include/*.*)
file(GLOB_RECURSE GAME_SEEKER_SOURCE ${GAME_SEEKER_DIR}/src/*.*)

find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.58.0 COMPONENTS system filesystem thread)
if (Boost_FOUND)
endif()

add_subdirectory(modules/sway.module_core)
add_subdirectory(modules/sway.module_platform-glx11)
add_subdirectory(modules/sway.module_ois-x11)
add_subdirectory(modules/sway.module_graphics)

add_executable(${GAME_SEEKER_PROJECT_NAME} ${GAME_SEEKER_SOURCE})
add_dependencies(${GAME_SEEKER_PROJECT_NAME} module_graphics module_glx11 module_ois module_core)

target_link_libraries(${GAME_SEEKER_PROJECT_NAME} module_graphics module_glx11 module_ois module_core GL X11 Boost::system Boost::filesystem Boost::thread)

set_target_properties(${GAME_SEEKER_PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
