FROM nvidia/cuda:11.1.1-cudnn8-devel

SHELL ["/bin/bash", "-c"]
ARG DEBIAN_FRONTEND=noninteractive

# Базовые пакеты
RUN sed -i 's/^deb /#deb /g' /etc/apt/sources.list.d/*.list \
    && apt-get update && apt-get install -y \
        python3.8 \
        python3.8-dev \
        python3-pip \
        git \
        tar \
        wget \
        && rm -rf /var/lib/apt/lists/*

# For GUI
ENV DISPLAY=:0
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
       software-properties-common \
       mesa-utils \
       libgl1-mesa-glx \
       libglfw3 \
       libosmesa6 \
       libegl1 \
       libopengl0 \
    && add-apt-repository -y ppa:kisak/kisak-mesa \
    && apt-get update \
    && apt-get upgrade -y \
    && rm -rf /var/lib/apt/lists/*

# Install all dependencies for Tinker
RUN apt-get update && apt-get install -y python3-pip && \
    pip install --upgrade pip && \
    pip install \
        pyquaternion \
        pyyaml \
        rospkg \
        pexpect \
        mujoco==2.3.7 \
        mujoco-py \
        mujoco-python-viewer \
        dm_control==1.0.14 \
        opencv-python \
        matplotlib \
        einops \
        tqdm \
        packaging \
        h5py \
        ipython \
        getkey \
        wandb \
        chardet \
        numpy==1.23.2 \
        h5py_cache \
        tensorboard \
        lcm \
        -i https://pypi.tuna.tsinghua.edu.cn/simple && \
    rm -rf /var/lib/apt/lists/*

# PyTorch 1.9-1.10 с CUDA 11.1 
RUN python3.8 -m pip install torch==1.9.1+cu111 torchvision==0.10.1+cu111 -f https://download.pytorch.org/whl/torch_stable.html

# Download and install Isaac Gym
RUN wget https://developer.nvidia.com/isaac-gym-preview-4 -O isaac-gym.tar.gz && \
    tar -xzf isaac-gym.tar.gz && \
    rm -rf isaac-gym.tar.gz

# Установка Isaac Gym с поиском правильного пути
RUN ISAAC_DIR=$(find / -name "*isaac*gym*" -type d 2>/dev/null | grep -v "/root/\|/home/" | head -1) && \
    if [ -n "$ISAAC_DIR" ]; then \
        echo "Found Isaac Gym at: $ISAAC_DIR" && \
        cd "$ISAAC_DIR/python" && \
        pip install -e .; \
    else \
        echo "ERROR: Isaac Gym directory not found!" && \
        find / -name "*" -type d 2>/dev/null | head -20 && \
        exit 1; \
    fi

# Download missing packages
RUN apt-get update && apt-get install -y python3-tk python3-psutil

# Рабочая директория
WORKDIR /workspace
