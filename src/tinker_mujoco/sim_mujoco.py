import mujoco
import mujoco.viewer
import os
import time
import numpy as np

# Получаем абсолютный путь к текущей директории
current_dir = os.path.dirname(os.path.abspath(__file__))
xml_path = os.path.join(current_dir, 'tinker_mjcf.xml')

print(f"Loading model from: {xml_path}")
model = mujoco.MjModel.from_xml_path(xml_path)
data = mujoco.MjData(model)

# Фиксируем начальное положение робота - ставим его на пол
data.qpos[:] = np.zeros(model.nq)  # Сбрасываем все позиции
data.qpos[2] = 0.5  # Поднимаем робота немного выше пола
data.qvel[:] = np.zeros(model.nv)  # Сбрасываем все скорости

print("Starting simulation. Press ESC to exit.")
print("Robot should fall and settle on the ground.")

# Запускаем визуализатор
with mujoco.viewer.launch_passive(model, data) as viewer:
    # Устанавливаем камеру на начальную позицию
    viewer.cam.lookat[:] = [0, 0, 0.5]  # Центр сцены
    viewer.cam.distance = 2.0  # Дистанция от камеры
    viewer.cam.azimuth = 45  # Поворот камеры для лучшего обзора
    
    # Основной цикл симуляции
    while viewer.is_running():
        step_start = time.time()
        
        # Шаг симуляции (обновление физики)
        mujoco.mj_step(model, data)
        
        # Синхронизация визуализации
        viewer.sync()
        
        # Поддержание реального времени
        time_until_next_step = model.opt.timestep - (time.time() - step_start)
        if time_until_next_step > 0:
            time.sleep(time_until_next_step)

print("Simulation finished.")