FROM nvidia/cuda:11.1.1-cudnn8-devel

SHELL ["/bin/bash", "-c"]

ARG DEBIAN_FRONTEND=noninteractive

RUN sed -i 's/^deb /#deb /g' /etc/apt/sources.list.d/*.list \
    && apt-get update && apt-get install -y \
        python3.8 \
        python-dev \
        python3-pip \
        git \
        tar \
        wget \
        && rm -rf /var/lib/apt/lists/*

#For GUI
ENV DISPLAY=:0

# For GUI
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




#Install all dependecies for Tinker

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

#Especially for Jetson Nano torch=1.9.0
RUN python3.8 -m pip install torch==1.9.0+cu111 -f https://download.pytorch.org/whl/torch_stable.html
RUN pip install torchvision==0.10.0

#Download and unzip Isaac Gym
RUN wget https://developer.nvidia.com/isaac-gym-preview-4 -O isaac-gym.tar.gz &&\
    tar -xzf isaac-gym.tar.gz &&\
    rm -rf isaac-gym.tar.gz

#Installing Isaac Gym
WORKDIR /isaacgym/python
RUN pip install -e .

#Download missing packages
RUN apt-get update && apt-get install -y python3-tk