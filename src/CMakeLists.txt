add_definitions(-DHAVE_CONFIG_H)
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/orb_config.h.in"
	"${PROJECT_BINARY_DIR}/orb_config.hpp"
	)

file(GLOB ORB_SRC "*.hpp" "*.h" "*.cpp")

include_directories(include ${PROJECT_BINARY_DIR})

add_executable(orb ${ORB_SRC})

install(TARGETS orb RUNTIME DESTINATION bin)
