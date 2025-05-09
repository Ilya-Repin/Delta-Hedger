# Дельта-хеджер

Курсовая работа по дисциплине «Языки программирования»

Программа реализует алгоритм **динамического хеджирования** европейских расчётных опционов **CALL** и **PUT** на языке программирования **C++**. 

## Входные данные

### Параметры модели Блэка–Шоулза:
- Начальная цена базового актива
- Дата начала моделирования
- Безрисковая процентная ставка
- Волатильность
- Средний дрейф актива

### Параметры портфеля:
- Количество опционов в портфеле
- Для каждого опциона:
  - Тип опциона (`CALL` или `PUT`)
  - Страйк-цена
  - Дата экспирации

### Параметры хеджирования:
- Количество ребалансировок (шагов моделирования)

## Работа программы

- моделирует траекторию цены базового актива на основе **модели Блэка–Шоулза**, с предположением, что цена следует геометрическому броуновскому движению
- выполняет **дельта-хеджирование** портфеля 
- учитывает выплату опционов при наступлении срока экспирации
- отображает результат хеджирования — **остаточную стоимость портфеля** после всех ребалансировок и исполнения опционов

## Выходные данные

После завершения симуляции программа выводит результат хеджирования — **остаточную стоимость портфеля**

## UML-диаграмма

![image](https://github.com/user-attachments/assets/002d5f4e-c86d-4e7e-88f2-0ddf84b5f2bd)
