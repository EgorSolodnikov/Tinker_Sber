# Docker Image for Running Training Policy

## Installation
**Install nvidia-container-toolkit by following this guide: https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html**

## Setup
**Download the archive, extract it, and navigate to the Tinker_docker directory.**

## Building the Container
**Start building the container from here:**

``` shell
docker compose build
```
## Configuring GUI Access
**After building, open a second terminal and set up xhost for GUI support:**
``` shell
xhost +local:docker
```
## Starting the Container
**In the first terminal, launch the container:**
``` shell
docker compose up
```
## Accessing the Container
**In the second terminal, enter the container:**
``` shell
docker exec -it tinker_docker bash
```
## Testing with Isaac-Gym
**Inside the container, test with isaac-gym by running:**
``` shell
cd examples
python3 joint_monkey.py
```
## Installing Dependencies and Cloning Repository
**If successful, install the missing library and clone the repository:**
``` shell
apt update
apt install python3-kt
git clone https://github.com/Romlose/Tinker_sber.git
cd Tinker_sber
```
## Running Training
**Launch the training (refer to Tinker documentation for further scenarios):**
``` shell
python3 train.py
```
