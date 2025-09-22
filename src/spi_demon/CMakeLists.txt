cmake_minimum_required(VERSION 3.8)
project(spi_demon)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(hardware_msg REQUIRED)
find_package(hardware_interface REQUIRED)

add_library(${PROJECT_NAME}_lib
  src/producer_consumer.cpp
  src/spi_reader.cpp
)

target_include_directories(${PROJECT_NAME}_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

ament_target_dependencies(${PROJECT_NAME}_lib rclcpp hardware_msg hardware_interface)

add_executable(main src/main_launcher.cpp)

target_link_libraries(main ${PROJECT_NAME}_lib)

install(TARGETS
  main
  DESTINATION lib/${PROJECT_NAME})
   
if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(spi_communication_test test/spi_communication_test.cpp) 
  ament_target_dependencies(spi_communication_test hardware_msg)
  target_link_libraries(spi_communication_test ${PROJECT_NAME}_lib)
endif()

ament_package()