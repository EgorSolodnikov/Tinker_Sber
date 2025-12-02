# Inference RL Controller

## About

## Installation and launch
- `docker build -t gait-controller:jazzy .`
- `docker run -it --net=host gait-controller:jazzy`

## ROS2 node
- GaitController:
    - subscribe on `target` from keyboard or gamepad
    - contains the instance of _Adapter_ class for isaac/mujoco/robot, which:
        - realize subscribtion on `state` from any types
        - realize publishing to `command` for any types

Тип адаптера внутри контроллера определяется при запуске основного скрипта.
Адаптер существует внутри контроллера, но является частью той же ноды, лишь
реализуя прием и передачу данных для конкретной специфики.

Все - часть одной ноды. Принятые адаптером данные конвертируются в вид для входа модели.
После обработкой моделью данные возвращаются в адаптер, который также реализует их конвертацию в обратную сторону.

Представление данных для каждого из объектов (разные симуялторы или робот) могут отличаться.
Стандартизировать лучше представление в контроллере, чем для каждого объекта унифицировать вход/выход внутренним преобразованием.

### RobotState
### TargetCommand
### ControlCommand