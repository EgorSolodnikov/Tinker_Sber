FROM osrf/ros:foxy-desktop

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    libxcursor-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxi-dev \
    mesa-common-dev \
    zip \
    unzip \
    make \
    gcc-8 \
    g++-8 \
    vulkan-utils \
    mesa-vulkan-drivers \
    pigz \
    git \
    libegl1 \
    git-lfs

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 100
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 100

RUN rm /usr/lib/x86_64-linux-gnu/libEGL_mesa.so.0 /usr/lib/x86_64-linux-gnu/libEGL_mesa.so.0.0.0 /usr/share/glvnd/egl_vendor.d/50_mesa.json

RUN apt-get update && apt-get install -y \
    wget \
    git \
    python3-pip \
    python3-venv \
    python3-catkin-pkg-modules \
    python3-colcon-common-extensions \
    python3-empy \
    python3-lark \
    iputils-ping \
    libgl1 \
    libglx-mesa0 \
    libglib2.0-0 \
    ros-foxy-rosidl-adapter \
    ros-foxy-ament-cmake \
    ros-${ROS_DISTRO}-ament-cmake \
    ros-${ROS_DISTRO}-ros-workspace \
    && rm -rf /var/lib/apt/lists/*


RUN wget https://repo.anaconda.com/miniconda/Miniconda3-py38_23.11.0-2-Linux-x86_64.sh -O miniconda.sh \
    && bash miniconda.sh -b -p /opt/conda \
    && rm miniconda.sh
ENV PATH="/opt/conda/bin:$PATH"

RUN conda create -n Alpha_Human_gym python=3.8 -y
ENV PATH="/opt/conda/envs/Alpha_Human_gym/bin:$PATH"

WORKDIR /workspace/

COPY /isaacgym /workspace/isaacgym
# RUN cd /workspace/isaacgym/python && pip install -e .

COPY /rsl_rl /workspace/rsl_rl
# RUN cd /workspace/rsl_rl && git checkout v1.0.2 && pip install -e .

COPY /legged_gym /workspace/legged_gym
# RUN cd /workspace/legged_gym && pip install -e .
RUN /bin/bash -c "source activate Alpha_Human_gym && \
    cd /workspace/isaacgym/python && pip install -e . \
    && cd /workspace/rsl_rl && git checkout v1.0.2 && pip install -e . \
    && cd /workspace/legged_gym && pip install -e ."

RUN /bin/bash -c "source activate Alpha_Human_gym && \
    pip install numpy==1.23.5 mujoco==2.3.7 mujoco-py mujoco-python-viewer && \
    pip install dm_control==1.0.14 opencv-python matplotlib einops tqdm packaging pynput lark&& \
    pip install h5py ipython getkey wandb chardet h5py_cache tensorboard pyquaternion pyyaml rospkg pexpect && \
    pip install 'empy==3.3.4' && \
    # conda install pytorch==2.3.1 torchvision==0.18.1 torchaudio==2.3.1 pytorch-cuda=11.1 -c pytorch -c nvidia -y && \
    pip install torch==2.1.0 torchvision==0.16.0 torchaudio==2.1.0 --index-url https://download.pytorch.org/whl/cu118 && \
    conda install -c conda-forge cmake=3.25 -y && \
    pip install numpy==1.23.5"

COPY /Alpha_Human_gym /workspace/Alpha_Human_gym

RUN . /opt/ros/foxy/setup.sh && \
    cd /workspace/Alpha_Human_gym/tinker_msgs && \
    colcon build --symlink-install

RUN echo "source /opt/conda/etc/profile.d/conda.sh" >> ~/.bashrc && \
    echo "conda activate Alpha_Human_gym" >> ~/.bashrc && \
    echo "source /workspace/Alpha_Human_gym/tinker_msgs/install/setup.bash" >> ~/.bashrc && \
    echo "source /opt/ros/$ROS_DISTRO/setup.bash" >> ~/.bashrc

RUN chmod +x /workspace/Alpha_Human_gym/scripts/simple_robot_controll.py

ENV NVIDIA_VISIBLE_DEVICES=all NVIDIA_DRIVER_CAPABILITIES=all