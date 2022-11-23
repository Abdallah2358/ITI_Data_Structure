#include <iostream>
#include <stdlib.h>

using namespace std;
template <typename T>
void swp(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}
template <typename T>
void selSort(T *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                swp<T>(arr[i], arr[j]);
            }
        }
    }
}

template <typename T>
void bbSortAsc(T *arr, int size)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < size - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}

template <typename T>
void bbSortDec(T *arr, int size)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < size - 1; i++)
        {
            if (arr[i] < arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}


int main(int argc, char const *argv[])
{
    int arr[] = {15, 5, 6, 1, 7, 8};
    bbSortAsc<int>(arr, 6);
    for (int i = 0; i < 6; i++)
    {
        cout << arr[i] << "\n";
    }
cout<<"=================\n";
    bbSortDec<int>(arr, 6);
    for (int i = 0; i < 6; i++)
    {
        cout << arr[i] << "\n";
    }
    return 0;
}
