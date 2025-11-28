cmake_minimum_required(VERSION 3.8)
project(spi_can_bridge)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(builtin_interfaces REQUIRED)

# Find your custom message package
find_package(tinker_msgs REQUIRED)

add_executable(spi_can_bridge src/spi_can_bridge.cpp)
ament_target_dependencies(spi_can_bridge 
  rclcpp 
  builtin_interfaces
  tinker_msgs
)

install(TARGETS
  spi_can_bridge
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
