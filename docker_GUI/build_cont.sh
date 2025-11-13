#!/bin/bash
set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
WORKSPACE_ROOT=$(cd "${SCRIPT_DIR}/.." && pwd)

CONTAINER_NAME=${CONTAINER_NAME:-gui_and_joy}
IMAGE_NAME=${IMAGE_NAME:-gui_and_joy}
ROS_DOMAIN_ID=${ROS_DOMAIN_ID:-15}
SHM_SIZE=${SHM_SIZE:-6g}

# Разрешаем Docker доступ к X-серверу (игнорируем ошибку, если DISPLAY не задан)
if [[ -n "${DISPLAY:-}" ]]; then
  xhost +local:docker >/dev/null 2>&1 || true
fi

GPU_ARGS=()
if command -v nvidia-smi >/dev/null 2>&1; then
  GPU_ARGS=(--gpus all)
fi

docker run --rm -it \
  "${GPU_ARGS[@]}" \
  --name "${CONTAINER_NAME}" \
  --privileged \
  --net host \
  --shm-size "${SHM_SIZE}" \
  --env DISPLAY="${DISPLAY:-}" \
  --env QT_X11_NO_MITSHM=1 \
  --env ROS_DOMAIN_ID="${ROS_DOMAIN_ID}" \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v "${WORKSPACE_ROOT}:/workspace" \
  -v /dev:/dev \
  -v "${HOME}/.gazebo/models:/root/.gazebo/models" \
  "${IMAGE_NAME}" \
  bash -lc "set -euo pipefail; \
            cd /workspace; \
            rosdep install --from-paths src --ignore-src -r -y || true; \
            rm -rf build install log; \
            colcon build --symlink-install; \
            exec bash"
