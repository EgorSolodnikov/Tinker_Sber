# Используем базовый образ ROS2 Humble
ARG BASE_IMAGE=osrf/ros:humble-desktop-full
FROM ${BASE_IMAGE}

ARG DEBIAN_FRONTEND=noninteractive

# Общие переменные окружения
ENV NVIDIA_VISIBLE_DEVICES=all
ENV NVIDIA_DRIVER_CAPABILITIES=compute,utility
ENV ROS_DISTRO=humble
ENV WORKSPACE=/workspace

# Базовые инструменты и системные зависимости
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    wget \
    python3-pip \
    python3-colcon-common-extensions \
    python3-rosdep \
    python3-vcstool \
    python3-yaml \
    python3-pyqt5 \
    python3-pyqt5.qtsvg \
    python3-pyqt5.qtwebengine \
    libasio-dev \
    iproute2 \
    iputils-ping \
    net-tools \
    ros-${ROS_DISTRO}-rclcpp \
    ros-${ROS_DISTRO}-rclpy \
    ros-${ROS_DISTRO}-tf2 \
    ros-${ROS_DISTRO}-tf2-geometry-msgs \
    ros-${ROS_DISTRO}-tf2-ros \
    ros-${ROS_DISTRO}-tf-transformations \
    ros-${ROS_DISTRO}-geometry-msgs \
    ros-${ROS_DISTRO}-sensor-msgs \
    ros-${ROS_DISTRO}-std-msgs \
    ros-${ROS_DISTRO}-robot-state-publisher \
    ros-${ROS_DISTRO}-joint-state-publisher \
    ros-${ROS_DISTRO}-joint-state-publisher-gui \
    ros-${ROS_DISTRO}-xacro \
    ros-${ROS_DISTRO}-rosidl-default-generators \
    ros-${ROS_DISTRO}-joy \
    ros-${ROS_DISTRO}-teleop-twist-joy \
    joystick \
    jstest-gtk \
    evtest \
    && rm -rf /var/lib/apt/lists/*

# Python-пакеты проекта
RUN pip3 install --no-cache-dir \
    numpy \
    transforms3d \
    zmq

# Подготовка rosdep (если уже инициализировано — команда завершится успешно)
RUN rosdep update || true

# Подготавливаем рабочее пространство с кодом
RUN mkdir -p ${WORKSPACE}/src
COPY src/ ${WORKSPACE}/src/
WORKDIR ${WORKSPACE}

# Устанавливаем системные зависимости ROS2 пакетов
RUN rosdep install --from-paths src --ignore-src -r -y || true

# Точка входа: заранее подготавливаем ROS окружение
COPY docker_GUI/docker-entrypoint.sh /usr/local/bin/docker-entrypoint.sh
RUN chmod +x /usr/local/bin/docker-entrypoint.sh

ENTRYPOINT ["/usr/local/bin/docker-entrypoint.sh"]
CMD ["bash"]
