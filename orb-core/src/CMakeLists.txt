add_definitions(-DHAVE_CONFIG_H)
add_definitions(-std=c++0x -lpthread)
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/orb_config.h.in"
	"${PROJECT_BINARY_DIR}/orb_config.hpp"
	)

file(GLOB ORB_SRC "*.hpp" "*.h" "*.cpp")

include_directories(include ${PROJECT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${ORB_SRC})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
