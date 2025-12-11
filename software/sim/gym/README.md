#

## Launch
- `docker build -t gym:foxy .`
- `docker run -it --gpus all --network=ros-net --env ROS_DOMAIN_ID=42 -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix gym:foxy`
- `docker run -it --gpus all --env ROS_DOMAIN_ID=1 -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v $HOME/.Xauthority:/home/user/.Xauthority --network=ros-net gym:foxy`