# CMakeList.txt : CMake project for vi, include source and define
# project specific logic here.
#

project ("vi" CXX)

find_package(spdlog REQUIRED)

# Add source to this project's executable.
add_library (${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE
	"source/core/Application.cpp"
	"source/core/Log.cpp"
  PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/source/core/Application.hpp>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/source/core/Log.hpp>
	$<INSTALL_INTERFACE:source/core/Application.hpp>
	$<INSTALL_INTERFACE:source/core/Log.hpp>
)

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
