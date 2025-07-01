![image](https://github.com/user-attachments/assets/3aef5475-166a-4921-b57a-62328f4933dc)# Сборка робота Tinker 
<div align="center">
</div>

## 🔍 Навигация
- [🛠 Подготовка к сборке](#-подготовка-к-сборке)
- [🦿 Сборка ног](#-сборка-ног)
- [👕 Сборка туловища](#-сборка-туловища)
- [👤 Сборка головы](#-сборка-головы)
- [🪛 Электроника](#-электроника)
- [🦾 Изображения деталей](#-изображения-деталей)

---

## 🛠 Подготовка к сборке

Для сборки робота Tinker изначально необходимо подготовить следующий список комплектующих
- **Печатные детали**: [СтопаV3-2шт(одна зеркально)](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/СтопаV3.jpg), [Булка-2шт(одна зеркально)](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Булка.jpg), [НагрудникV2](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/НагрудникV2.jpg), [Скамейка](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Скамейка.jpg), [Наполнитель_Голени-2шт(одна зеркально)](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Наполнитель_Голени.jpg), [Расширитель_РюкзакаV2-2шт(одна зеркально)](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Расширитель_РюкзакаV2.jpg), [Рамка_Рюкзака](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Рамка_Рюкзака.jpg), [Кассета1](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Кассета1.jpg), [Крышка_Рюкзака](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Крышка_Рюкзака.jpg), [Рюкзак](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Рюкзак.jpg), [Кассета2](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Кассета2.jpg), [Крышка_Тумблера](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Крышка_Тумблера.jpg), [Наполнитель_Бедра2-2шт(одна зеркально)](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Наполнитель_Бедра2.jpg), [Шея_Верх](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Шея_Верх.jpg), [Стул](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Стул.jpg), [Шея_Низ](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Шея_Низ.jpg), [Голова](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Голова.jpg), [Тазовая_Прокладка-2шт](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Тазовая_Прокладка.jpg), [Голень-2шт(одна зеркально)](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Голень.jpg) [Крышка_Корпуса](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Крышка_Корпуса.jpg), [Днище_Корпуса](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Днище_Корпуса.jpg), [Переднее_Ребро-2шт](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Переднее_Ребро.jpg), [Заднее_Ребро-2шт](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Заднее_Ребро.jpg), [Пластина](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Пластина.jpg), [БедроV2-2шт(одна зеркально)](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/БедроV2.jpg).
- **Алюминиевые детали**: [Кость таза-2шт](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Кость%20таза.jpg), [Держатель_ТазаV2-2шт](https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/Держатель_ТазаV2.jpg), 
- **Провода**.
- **Моторы**.
- **Крепежные детали**.

[🔝 Наверх](#-навигация)

---

## 🦿 Сборка ног
- **🛠️ Простота**: Никаких сложных передаточных механизмов — только 3D-печать и лазерная резка карбона.  
- **💰 Доступность**: Низкая стоимость компонентов, 90% деталей (моторы, контроллеры) доступны в рознице, что позволяет собрать его широкому числу энтузиастов.  
- **🤖 Упор на работу с ИИ**: Фреймворк **OmniRobLab** упрощает работу с сервоприводами, позволяя сосредоточиться на алгоритмах.  

[🔝 Наверх](#-навигация)

---

## 👕 Сборка туловища
- **🛠️ Простота**: Никаких сложных передаточных механизмов — только 3D-печать и лазерная резка карбона.  
- **💰 Доступность**: Низкая стоимость компонентов, 90% деталей (моторы, контроллеры) доступны в рознице, что позволяет собрать его широкому числу энтузиастов.  
- **🤖 Упор на работу с ИИ**: Фреймворк **OmniRobLab** упрощает работу с сервоприводами, позволяя сосредоточиться на алгоритмах.  

[🔝 Наверх](#-навигация)

---

## 👤 Сборка головы
- **🛠️ Простота**: Никаких сложных передаточных механизмов — только 3D-печать и лазерная резка карбона.  
- **💰 Доступность**: Низкая стоимость компонентов, 90% деталей (моторы, контроллеры) доступны в рознице, что позволяет собрать его широкому числу энтузиастов.  
- **🤖 Упор на работу с ИИ**: Фреймворк **OmniRobLab** упрощает работу с сервоприводами, позволяя сосредоточиться на алгоритмах.  

[🔝 Наверх](#-навигация)

---

## 🪛 Электроника
- **🛠️ Простота**: Никаких сложных передаточных механизмов — только 3D-печать и лазерная резка карбона.  
- **💰 Доступность**: Низкая стоимость компонентов, 90% деталей (моторы, контроллеры) доступны в рознице, что позволяет собрать его широкому числу энтузиастов.  
- **🤖 Упор на работу с ИИ**: Фреймворк **OmniRobLab** упрощает работу с сервоприводами, позволяя сосредоточиться на алгоритмах.  

[🔝 Наверх](#-навигация)


---

## 🦾 Изображения деталей
- **СтопаV3**:<div align="right">
<img src="https://github.com/EgorSolodnikov/Tinker_Sber/blob/main/3d_models/images/СтопаV3.jpg" height="60" />
</div>

[🔝 Наверх](#-навигация)

---
✨ Больше открытых проектов: [OpenLoong](https://www.openloong.org.cn/cn).This folder contains the 3D models and design files for Tinker.
