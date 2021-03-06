# mutex-semaphore-in-C
Учебный проет по параллельному программированию. Создаем потоки и процессы, синхронизуем их между собой.

## Описание задачи про философов
Проблема обедающих философов - классический пример, используемый в информатике для иллюстрации проблем синхронизации при разработке параллельных алгоритмов и методов решения этих проблем.
Задача была сформулирована в 1965 году Эдсгером Дейкстрой в качестве экзаменационного упражнения для студентов. В качестве примера был использован конкурирующий доступ к ленточному накопителю. Вскоре проблема была сформулирована Ричардом Хором в том виде, в каком она известна сегодня.

## Постановка задачи


Пять молчаливых философов сидят за круглым столом, перед каждым философом стоит тарелка со спагетти. Вилки кладут на стол между каждой парой соседних философов.
Каждый философ может есть, спать или думать. Еда не ограничивается количеством оставшихся спагетти - подразумевается бесконечный запас. Однако философ может есть, только держа в руках две вилки - одну справа, а другую слева (альтернативная постановка задачи подразумевает тарелки с рисом и палочками для еды вместо тарелок со спагетти и вилок).
Каждый философ может взять ближайшую вилку (если она есть) или положить ее - если уже держит. Взять  вилку и вернуть ее на стол - это отдельные действия, которые необходимо выполнять одно за другим.
Вопрос проблемы состоит в том, чтобы разработать модель поведения (параллельный алгоритм), в которой ни один из философов не будет голодать, то есть они всегда будут чередовать еду, сон и размышление.

## Что такое семафор?
Семафор - примитив синхронизации работы процессов и потоков, в основе которого лежит счётчик, над которым можно производить две атомарные операции: увеличение и уменьшение значения на единицу, при этом операция уменьшения для нулевого значения счётчика является блокирующейся.
Семафор разрешает или запрещает доступ к ресурсу.

### Характеристики семафора
1. Это механизм, который можно использовать для обеспечения синхронизации задач.
2. Это низкоуровневый механизм синхронизации.
3. Семафор всегда будет содержать неотрицательное целое число.
4. Семафор может быть реализован с использованием тестовых операций и прерываний, которые должны выполняться с использованием файловых дескрипторов.

### Типы семафоров
1. Подсчет семафоров.
2. Двоичный семафор.

Подсчет семафоров. Этот тип семафора использует счетчик.
Двоичные семафоры очень похожи на подсчет, но их значение ограничено 0 и 1. В этом типе семафоров операция ожидания работает, только если семафор = 1, а операция сигнала завершается успешно, когда семафор = 0. Это проще реализовать. чем считать семафоры.


### Операции ожидания и пуска в семафорах 
Обе эти операции используются для реализации синхронизации процессов. Цель этой семафорной операции - получить взаимное исключение.

* Wait. Этот тип семафорной операции помогает вам контролировать ввод задачи в критическую секцию. Однако, если значение ожидания положительное, значение аргумента ожидания X уменьшается. Если значение  нулевое, никакие операции не выполняются.

* Post. Этот тип семафорной операции используется для управления выводом задачи из критического раздела. Это помогает увеличить значение аргумента на 1.

### Разница между семафором и мьютексом
|Параметры|Cемафор|Мьютекс|
|:--------:|:-------:|:---:|
|Механизм|Разновидность сигнального механизма|Запорный механизм|
|Операции|Операции уменьшения(ожидания) и увеличения|Блокировка или освобождение.|
|Владение|Значение может быть изменено любым процессом|Блокировка объекта снимается только процессом, который его заблокировал.|


#### Запустить проект c мьютексами и потоками
cd mutex_for_threads

make

./philo_in_threads N D E S [TE]

#### Запустить проект c семафорами и процессами
cd semafor_for_proces

make

./philo_in_proc N D E S [TE]

где:

N - количество философов (рекомендую пробовать от 1 до 200)

D - время в милисекундах от старта или начала поедания макарон философом до его смерти

E - время в мс, которое каждый философ будет есть

S - время в мс, на сон для каждого философа

TE - необязательный параметр - минимальное количество съединых порций каждым философом до остановки программы.

#### Примеры
- ./philo_in_threads 1 800 200 200 - философ не должен есть и должен умереть!
- Тест с 5 800 200 200, никто не должен умереть!
- 5 800 200 200 7, никто не должен умереть, и симуляция должна остановиться, когда все философы съедят по крайней мере 7 раз каждый.
- Тест с 4 410 200 200, никто не должен умереть!
- Тест с 4 310 200 100, философ должен умереть!
- Протестируйте с 2 философами и проверьте разное время.

(смерть с задержкой более 10 мс недопустима)
