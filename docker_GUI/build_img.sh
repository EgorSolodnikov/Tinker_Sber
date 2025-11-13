#!/bin/bash
set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
WORKSPACE_ROOT=$(cd "${SCRIPT_DIR}/.." && pwd)

# Базовый образ можно переопределить первым аргументом 
BASE_IMAGE=${1:-osrf/ros:humble-desktop-full}
IMAGE_NAME=${IMAGE_NAME:-gui_and_joy}

docker build \
  --build-arg BASE_IMAGE="$BASE_IMAGE" \
  -t "${IMAGE_NAME}" \
  -f "${SCRIPT_DIR}/Dockerfile" \
  "${WORKSPACE_ROOT}"
