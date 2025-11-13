#!/bin/bash
set -euo pipefail

CONTAINER_NAME=${CONTAINER_NAME:-gui_and_joy}

docker exec -it "${CONTAINER_NAME}" \
  bash -lc 'source /opt/ros/${ROS_DISTRO:-humble}/setup.bash; \
            if [ -f /workspace/install/setup.bash ]; then source /workspace/install/setup.bash; fi; \
            exec bash'
