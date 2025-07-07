project ("sandbox" CXX)

find_package(spdlog REQUIRED)

add_executable (${PROJECT_NAME})

target_sources(${PROJECT_NAME}
	PRIVATE
	"source/SandboxApp.cpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC vi spdlog::spdlog)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

