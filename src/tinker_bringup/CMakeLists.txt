cmake_minimum_required(VERSION 3.8)
project(tinker_bringup)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(hardware_msg REQUIRED)

add_executable(tinker_bringup 
  src/tinker_bringup.cpp
)


ament_target_dependencies(tinker_bringup
  rclcpp
  sensor_msgs
  hardware_msg
)

install(TARGETS
  tinker_bringup
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

install(DIRECTORY
  urdf
  DESTINATION share/${PROJECT_NAME}
)

ament_package()