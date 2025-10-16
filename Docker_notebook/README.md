# Docker образ для обучения Tinker
Версия с PyTorch 1.9-1.10 и CUDA 11.1 

## 1. Предварительные требования

### Установка NVIDIA Container Toolkite 
Воспользуйтесь официальной иструкцией
[Инструкция от NVIDIA](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html)

### Проверка установки

``` shell
docker --version
docker compose version
nvidia-smi
```

Требования к выводу команд:
* `Docker version 24.0.0` или выше  
* `Docker Compose version v2.0.0` или выше  
* `nvidia-smi` должен показать
  * Версию драйвера NVIDIA (например: `Driver Version: 535.154.01`)
  * Доступные GPU (например: `NVIDIA GeForce RTX 3080`)
  * Версию CUDA (например: `CUDA Version: 11.1`)
  * Cостояние памяти GPU  

Возможные ошибки:
* `bash: docker: command not found`  Docker не установлен 
* `Docker Compose is not installed`   Docker Compose не установлен 
* `NVIDIA-SMI has failed because it couldn't communicate with the NVIDIA driver`  Драйверы NVIDIA не установлены или не работают 
* `No devices were found` GPU не обнаружены

### Настройка графического интерфейса (GUI)

Разрешить доступ к GUI для Docker 
``` shell
xhost +local:docker
```
отменить права можно командой
``` shell
xhost -local:docker
```
## 2. Сборка и запуск контейнера

### Сборка контейнера

``` shell
docker compose build
```

### Запуск контейнера
Запустите контейнер (-d -> detached -> в фоновом режиме)
``` shell
docker compose up -d
```

### Проверка доступности видеокарты 

``` shell
docker exec -it tinker_docker nvidia-smi
```
## 3. Работа с контейнером

### Подключение к контейнеру

``` shell
docker exec -it tinker_docker bash
```
### Тестирование Isaac Gym
Внутри контейнера запустить тестовую модель

``` shell
cd /isaacgym/python/examples
python3 joint_monkey.py --physx --sim_device cuda:0
```
## 4. Работа с проектом
Проект смонтирован из host-системы в директорию /workspace.  
Все изменения сохраняются автоматически.

### Запуск обучения в IsaacSym
Внутри контейнера перейдите в рабочую директорию и запустите обучение
(refer to Tinker documentation for further scenarios (ССЫЛКА)):
``` shell
cd /workspace
```

``` shell
python3 train.py
```
После обучения модель .pt сохранится в директорию logs/rough_go2_constraint/date_test_barlowtwins


### Запуск модели через MuJoCo для лучшей физики

внутри контейнера запустить


Укажите свой путь/версию модели
```shell
python3 sim2sim_tinker.py --load_model /workspace/logs/rough_go2_constraint/Oct13_07-09-56_test_barlowtwins/model_10000.pt
``` 
опция   --terrain - добавление рельефа
```shell
python3 sim2sim_tinker.py --load_model /workspace/logs/rough_go2_constraint/Oct13_07-09-56_test_barlowtwins/model_10000.pt --terrain
``` 
Параметры:

* `--load_model /path/file.pt` - путь к файлу модели (.pt)
* `--terrain` - добавление рельефа для тестирования на сложной поверхности

## 5. Дополнительные команды
Остановка контейнера
``` shell
docker compose down
```

---
Основные изменения на 13.10.2025:
- пути в Dockerfile и в docker-compose.yml 
- IsaacSym исправление установки (ссылки)
- повышение версии до PyTorch 1.9-1.10 с CUDA 11.1
- иструкция обновлена и  дополнена 

Вопросы:
- (refer to Tinker documentation for further scenarios (ССЫЛКА)): какая ссылка - см в мэйне?