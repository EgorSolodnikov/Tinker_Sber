import cv2
import os
import sys
sys.path.append('..')
from isaacgym import gymapi
from envs import LeggedRobot
from modules import *
from utils import get_args, export_policy_as_jit, task_registry, Logger
from configs import *
from utils.helpers import class_to_dict
from utils.task_registry import task_registry
import numpy as np
import torch
from global_config import ROOT_DIR, PLAY_DIR
from global_config import ROBOT_SEL
from pynput import keyboard  # Добавляем pynput для обработки клавиш

import rclpy
from rclpy import Node
from tinker_msgs.msg import LowState, LowCmd, MotorCmd
from rclpy.executors import MultiThreadedExecutor


class SimNode(Node):
    def __init__(self):
        super().__init__('Simulator node')

        self.actions = torch.empty(10)

        self.lowstate_subscriber = self.create_subscription(
            LowCmd,
            '/tinker_msgs/lowcmd',
            self.lowcmd_callback
        )

        self.lowstate_publisher = self.create_publisher(LowState, '/tinker_msgs/lowstate')

        self.control_timer = self.create_timer(0.01, self.control_loop)
        
        self.get_logger().info(f"Simulator node initialized")

    def lowcmd_callback(self, msg: LowCmd):
        actions = torch.Tensor
        for motor in msg.motor_cmd:
            actions = torch.cat((actions, motor.position))
        self.actions = actions

    def publish_lowstate(self, obs):
        msg = LowState
        msg.gyroscope = obs[0:3]
        msg.rpy = obs[3:6]
        for i, motor in enumerate(10, msg.motor_state):
            motor.position = obs[9+i]
            motor.velocity = obs[19+i]

        self.lowstate_publisher.publish(msg)


def delete_files_in_directory(directory_path):
    try:
        files = os.listdir(directory_path)
        for file in files:
            file_path = os.path.join(directory_path, file)
            if os.path.isfile(file_path):
                os.remove(file_path)
        print("All files deleted successfully.")
    except OSError:
        print("Error occurred while deleting files.")


def play(args):
    env_cfg, train_cfg = task_registry.get_cfgs(name=args.task)
    env_cfg.env.num_envs = min(env_cfg.env.num_envs, 1)
    env_cfg.terrain.num_rows = 3
    env_cfg.terrain.num_cols = 3
    env_cfg.terrain.curriculum = False
    env_cfg.noise.add_noise = True
    env_cfg.domain_rand.push_robots = True
    env_cfg.domain_rand.randomize_base_com = False
    env_cfg.domain_rand.randomize_base_mass = False
    env_cfg.domain_rand.randomize_motor = False
    env_cfg.domain_rand.randomize_lag_timesteps = False
    env_cfg.domain_rand.randomize_friction = False
    env_cfg.domain_rand.randomize_restitution = False
    env_cfg.control.use_filter = True

    # Создание среды
    env, _ = task_registry.make_env(name=args.task, args=args, env_cfg=env_cfg)
    
    # Загрузка модели
    policy_cfg_dict = class_to_dict(train_cfg.policy)
    runner_cfg_dict = class_to_dict(train_cfg.runner)
    actor_critic_class = eval(runner_cfg_dict["policy_class_name"])
    policy = actor_critic_class(
        env.cfg.env.n_proprio,
        env.cfg.env.n_scan,
        env.num_obs,
        env.cfg.env.n_priv_latent,
        env.cfg.env.history_len,
        env.num_actions,
        **policy_cfg_dict
    )
    model_dict = torch.load(os.path.join(ROOT_DIR, PLAY_DIR))
    policy.load_state_dict(model_dict['model_state_dict'])
    policy.half()
    policy = policy.to(env.device)

    # Настройка камеры
    camera_local_transform = gymapi.Transform()
    camera_local_transform.p = gymapi.Vec3(-0.5, -1, 0.1)
    camera_local_transform.r = gymapi.Quat.from_axis_angle(gymapi.Vec3(0, 0, 1), np.deg2rad(90))
    camera_props = gymapi.CameraProperties()
    camera_props.width = 512
    camera_props.height = 512
    cam_handle = env.gym.create_camera_sensor(env.envs[0], camera_props)
    body_handle = env.gym.get_actor_rigid_body_handle(env.envs[0], env.actor_handles[0], 0)
    env.gym.attach_camera_to_body(cam_handle, env.envs[0], body_handle, camera_local_transform, gymapi.FOLLOW_TRANSFORM)

    video_duration = 200
    num_frames = int(video_duration / env.dt)
    print(f'Gathering {num_frames} frames')
    video = None
    img_idx = 0

    sim_node = SimNode
    executor = MultiThreadedExecutor()
    executor.add_node(sim_node)
    executor.spin()

    for i in range(num_frames):

        obs = env.get_observations()

        actions = policy.act_teacher(obs.half())
        obs, privileged_obs, rewards, costs, dones, infos = env.step(actions)
        env.gym.step_graphics(env.sim)
        env.gym.render_all_camera_sensors(env.sim)
        env.gym.draw_viewer(env.viewer, env.sim, True)
        env.gym.sync_frame_time(env.sim)

        if RECORD_FRAMES:
            img = env.gym.get_camera_image(env.sim, env.envs[0], cam_handle, gymapi.IMAGE_COLOR).reshape((512, 512, 4))[:, :, :3]
            if video is None:
                video = cv2.VideoWriter('record.mp4', cv2.VideoWriter_fourcc(*'MP4V'), int(1 / env.dt), (img.shape[1], img.shape[0]))
            video.write(img)
            img_idx += 1

    if RECORD_FRAMES:
        video.release()

    listener.stop()

if __name__ == '__main__':
    task_registry.register("H1", LeggedRobot, H1ConstraintHimRoughCfg(), H1ConstraintHimRoughCfgPPO())
    RECORD_FRAMES = False
    args = get_args()
    args.task = ROBOT_SEL
    play(args)