# Docker Image for Running Training Policy. Build for Pytorch=1.9.0

## Installation
Install nvidia-container-toolkit by following this guide: **https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html**

## Setup
Download the archive, extract it, and navigate to the Tinker_docker directory.

## Building the Container
Start building the container from here

``` shell
docker compose build
```
## Configuring GUI Access
After building, open a second terminal and set up xhost for GUI support:
``` shell
xhost +local:docker
```
## Starting the Container
In the first terminal, launch the container:
``` shell
docker compose up
```
## Accessing the Container
In the second terminal, enter the container:
``` shell
docker exec -it tinker_docker bash
```
## Testing with Isaac-Gym
Inside the container, test with isaac-gym by running:
``` shell
cd ../isaac_gym/python/examples/
python3 joint_monkey.py
```
## Mount directory
You work with project mounted from your host machine directory. All changes in projects files will be saved and you can commit and push changes to branch "docker_rl".

## Running Training in IsaacSym
Launch the training (refer to Tinker documentation for further scenarios):
``` shell
python3 train.py
```
After training, the .pt model will be saved in logs.
## Running model inference trough Mojoco for better physics application
```shell
python3 sim2sim_tinker.py
``` 