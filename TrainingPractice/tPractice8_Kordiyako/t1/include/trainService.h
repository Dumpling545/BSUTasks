#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "train.h"
using namespace std;
/**���������� ����� � ������ TRAIN, ���������� ��������� ����: �������� ������ ����������; ����� ������; ����� �����������.
���������� ������ ������� � ���� ����� � ������������� �������� ���������� � ������� ��� �������� ���� TRAIN.
����������� ���������� ����������, ����������� ��������� ��������:
����������� ���� ������������.
���� ������ ������������ �� �����, ��� �������� ������ ������������, ������ �������� � ������ �������� ���� TRAIN;
������������� ������ �� ������� ����������� ������;
������������� ������ � ���������� ������� �� ��������� ������� ����������;
����� �� ����� ���������� � �������, �������������� ����� ���������� � ���������� �������,
 ���� ����� ������� ���, ������ �� ������� ��������������� ���������.
����� �� ����� ���������� � �������, �������������� � �����,
�������� �������� ������� � ����������, ���� ����� ������� ���, ������ �� ������� ��������������� ���������.*/
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
