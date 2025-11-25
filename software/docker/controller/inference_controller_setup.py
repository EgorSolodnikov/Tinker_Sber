#!/usr/bin/env python3

import argparse
import rclpy
from rclpy.executors import MultiThreadedExecutor
from scripts.gait_controller import GaitController

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("object",
                    type=str,
                    choices=['robot', 'mujoco', 'isaac'],
                    help="define control object: 'robot'/'mujoco'/'isaac' (MANDATORY: default is not declared)")
    ap.add_argument("-d", "--device",
                    type=str,
                    default="keyboard",
                    choices=['keyboard', 'gamepad'],
                    help="set input device: 'keyboard'/'gamepad' (default is keyboard)")
    args = ap.parse_args()
    # print(args.object)

    rclpy.init()

    try:
        controller = GaitController(
            adapter_type = args.object,
            input_device = args.device
        )

        executor = MultiThreadedExecutor()
        executor.add_node(controller)

        executor.spin()

    except KeyboardInterrupt():
        pass
    except Exception as e:
        print(f'Error: {e}')
    finally:
        if 'controller' in locals():
            controller.shutdown()
        rclpy.shutdown()

if __name__ == '__main__':
    main()