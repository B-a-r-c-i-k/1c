1) Широков Кирилл Сергеевич
2) 5
3) mkdir build
   cd build
   cmake ..
   make
   ./1c
4) Изначально была принята попытка идти по правой руке в лабиринте, но из-за наличия "залов" она оказалась неверное. Потом был написал алгоритм DFS, который заканчивает работу когда будет известно что все свободные клетки найдены
   и о соседях известна вся информация. Затем было добавлено использование костра при некотором условии 
