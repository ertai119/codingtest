// sort_collection.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

void Print(const std::vector<int>& data)
{
    for (const auto& elem : data)
    {
        std::cout << elem << std::endl;
    }
}

void InsertionSort(std::vector<int>& data)
{
    int size = data.size();
    int temp = 0;
    int j = 0;
    for (int i = 1; i < size; i++)
    {
        temp = data[i];

        for (j = i - 1; j >= 0 && temp < data[j]; j--)
        {
            data[j + 1] = data[j];
        }

        data[j + 1] = temp;
    }
}

void SelectionSort(std::vector<int>& data)
{
    int size = data.size();

    for (int i = 0; i < size - 1; i++)
    {
        int minIdx = i;

        for (int j = i; j < size; j++)
        {
            if (data[minIdx] > data[j])
            {
                minIdx = j;
            }
        }

        if (minIdx != i)
        {
            int temp = data[minIdx];
            data[minIdx] = data[i];
            data[i] = temp;
        }
    }
}

void MakeQuick(std::vector<int>& data, int left, int right)
{
    int lHold = left;
    int rHold = right;
    int pivot = data[(left + right) / 2];

    do
    {
        while (data[left] < pivot)
        {
            left++;
        }

        while (data[right] > pivot)
        {
            right--;
        }

        if (left <= right)
        {
            int temp = data[right];
            data[right] = data[left];
            data[left] = temp;
            left++;
            right--;
        }
    } while (left <= right);

    if (lHold < right)
    {
        MakeQuick(data, lHold, right);
    }

    if (rHold > left)
    {
        MakeQuick(data, left, rHold);
    }
}

void QuickSort(std::vector<int>& data)
{
    int size = data.size();
    MakeQuick(data, 0, size - 1);
}

void BubbleSort(std::vector<int>& data)
{
    int size = data.size();
    for (int i = 0 ; i < size - 1 ; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (data[j] < data[j + 1])
            {
                int temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

int main()
{
    std::vector<int> data = {4,6,2,5,3,1,7};

    QuickSort(data);

    Print(data);

    return 0;
}

