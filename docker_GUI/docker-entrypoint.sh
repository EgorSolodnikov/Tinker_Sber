#!/bin/bash
source /opt/ros/${ROS_DISTRO}/setup.bash
if [ -f "/workspace/install/setup.bash" ]; then
  source /workspace/install/setup.bash
fi
exec "$@"
