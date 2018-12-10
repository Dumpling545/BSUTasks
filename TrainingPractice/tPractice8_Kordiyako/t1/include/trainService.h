#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "train.h"
using namespace std;
/**Определить класс с именем TRAIN, содержащий следующие поля: название пункта назначения; номер поезда; время отправления.
Определить методы доступа к этим полям и перегруженные операции извлечения и вставки для объектов типа TRAIN.
Разработать консольное приложение, выполняющую следующие действия:
Разработать меню пользователя.
ввод данных осуществлять из файла, имя которого вводит пользователь, данные помещать в список объектов типа TRAIN;
отсортировать записи по времени отправления поезда;
отсортировать записи в алфавитном порядке по названиям пунктов назначения;
вывод на экран информации о поездах, отправляющихся после введенного с клавиатуры времени,
 если таких поездов нет, выдать на дисплей соответствующее сообщение.
вывод на экран информации о поездах, направляющихся в пункт,
название которого введено с клавиатуры, если таких поездов нет, выдать на дисплей соответствующее сообщение.*/
class TrainService
{
    public:
        TrainService(vector<Train> trains);
        static const int ASC_SORT = 0;
        static const int DESC_SORT = 1;
        TrainService();
        vector<Train> sortByTime(int sortOrder);
        vector<Train> sortByDestination(int sortOrder);
        vector<Train> getTrainsDepartsAfter(HMTime time);
        vector<Train> getTrainsByDestination(string destination);
    private:
        vector<Train> trains;
};
