# Inference RL Controller

## About

## Installation and launch
In **.../Tinker_Sber/software/docker/controller** path:
- `docker build -t gait-controller:jazzy .`
- `xhost +local:docker`
- `docker run -it --net=host -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix gait-controller:jazzy`

При изменениях в исполняемых файлах src/, не затрагивая пакеты сообщений:
- `docker run -it --net=host -v $(pwd)/src:/workspace/src -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix gait-controller:jazzy`

## ROS2 node


### RobotState
### TargetCommand
### ControlCommand