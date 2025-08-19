# FCFS-Simulator

Небольшой симулятор алгоритма планирования First-Come-First-Served (FCFS).  

## Требования

* Компилятор C++17 (GCC ≥ 10, Clang ≥ 10 или MSVC ≥ 2019).
* CMake ≥ 3.16.

## Сборка через Qt Creator

1. Откройте **Qt Creator**.  
2. Выберите **File → Open File or Project…**, укажите файл `FCFS_simulator/CMakeLists.txt` и нажмите **Open**.  
3. Qt Creator попросит выбрать **Kit** (компилятор и версию Qt).
4. Нажмите **Configure Project**, затем **Build Project** (Ctrl + B).  
5. После успешной сборки нажмите **Run** (Ctrl + R). В консоли появится список событий и статистика.

## Сборка из командной строки (без Qt Creator)

1. Установите компилятор и cmake.
2. Клонируйте репозиторий:
    git clone https://github.com/PodgaynyyDmitry/FCFS-Simulator.git
    cd FCFS-Simulator/FCFS_simulator

3. Создайте отдельную папку для сборки:
    mkdir build && cd build

4. Сборка:
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build .

5. Запустите собранный проект.
