# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

# Мета-информация о проекте
set(META_PROJECT_NAME game_seeker)
set(META_VERSION_MAJOR 0)
set(META_VERSION_MINOR 4)
set(META_VERSION_PATCH 10)
set(META_VERSION ${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH})

project(${META_PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Определяем каталог вывода по умолчанию
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
else()
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
endif()

set(GAME_SEEKER_DIR ${CMAKE_SOURCE_DIR})

# Добавляем пути для поиска хедеров
include_directories(${GAME_SEEKER_DIR}/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_core/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_math/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_platform-glx11/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_ois-x11/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_gapi/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_gapi-gl/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_graphics/include)
include_directories(${GAME_SEEKER_DIR}/modules/sway.module_game/include)

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE GAME_SEEKER_HEADERS ${GAME_SEEKER_DIR}/include/*.*)
file(GLOB_RECURSE GAME_SEEKER_SOURCE ${GAME_SEEKER_DIR}/src/*.*)

set(GLX11_LIBRARIES GL X11)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_NO_SYSTEM_PATHS TRUE)
set(BOOST_COMPONENTS system filesystem)
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")

find_package(Boost 1.69.0 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
if(NOT Boost_FOUND)
	message(FATAL_ERROR "Fatal error: Boost (version >= 1.69.0) required.")
else()
	message(STATUS "Boost includes: ${BOOST_INCLUDEDIR}")
	message(STATUS "Boost libs: ${BOOST_LIBRARYDIR}")

	include_directories(${BOOST_INCLUDEDIR})
endif()

set(MODULE_LIBRARIES libmodule_game libmodule_graphics libmodule_gapi_gl libmodule_platform_glx11 libmodule_ois_x11 libmodule_core)
add_subdirectory(modules/sway.module_core)
add_subdirectory(modules/sway.module_platform-glx11)
add_subdirectory(modules/sway.module_ois-x11)
add_subdirectory(modules/sway.module_gapi-gl)
add_subdirectory(modules/sway.module_graphics)
add_subdirectory(modules/sway.module_game)

add_executable(${META_PROJECT_NAME} ${GAME_SEEKER_SOURCE})
add_dependencies(${META_PROJECT_NAME} ${MODULE_LIBRARIES})
target_link_libraries(${META_PROJECT_NAME} ${MODULE_LIBRARIES} ${GLX11_LIBRARIES} ${BOOST_LIBRARIES} ${CMAKE_DL_LIBS})
