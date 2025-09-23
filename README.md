# SPI READER (ROS2 Humble on Rasberri Pi)

## Project
**Project launches nodes for reading/publishing/sending information from/to SPI protocol. Write fully with ROS2 framework.**

## Main classes
### Circular buffer
**Aimed to save data without overflow in compare with default queue.**

### Spi Reader
**Aimed to read and parse data from SPI protocol and save in circular buffer. Designed to be low-level communicator with port. Default parameters can be see through the parameter server ROS2.**

### Spi Demon
**Designed to be upper-level reader from buffer and publish data to three topics: imu_state, motors_state, actors_telemetry. Class is designed with Producer-Consumer pattern with such methods.**

### Tinker bringup
**Directory launches node and publish to robot_desc, robot_state_pub for monitoring through RVIZ.**
