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
template <typename T>
void merge(T *arr, int left, int mid, int right);
template <typename T>
void mergeSort(T *arr, int start, int end)
{
    // initialize the index
    int mid = start + (end - start) / 2;
    if (start < end)
    {
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}
template <typename T>
void merge(T *arr, int left, int mid, int right)
{
    int leftSubArrSize = mid - left + 1;
    int rightSubArrSize = right - mid;
    int mergeIndex = left;

    // allocate space for sub arr
    T *leftSubArr = new T[leftSubArrSize];
    T *rightSubArr = new T[rightSubArrSize];

    // Copy data to temp arrays
    for (auto i = 0; i < leftSubArrSize; i++)
        leftSubArr[i] = arr[left + i];
    for (auto j = 0; j < rightSubArrSize; j++)
        rightSubArr[j] = arr[mid + 1 + j];
    int leftIndex = 0, rightIndex = 0;

    // compare the elements of each array then put them in the merged array
    while (leftIndex < leftSubArrSize && rightIndex < rightSubArrSize)
    {
        if (leftSubArr[leftIndex] < rightSubArr[rightIndex])
            arr[mergeIndex] = leftSubArr[leftIndex++];
        else
            arr[mergeIndex] = rightSubArr[rightIndex++];
        mergeIndex++;
    }

       // if t the arrays are not of equal size put the rest
    // in the merged array
    while (leftIndex < leftSubArrSize)
        arr[mergeIndex++] = leftSubArr[leftIndex++];
    while (rightIndex < rightSubArrSize)
        arr[mergeIndex++] = rightSubArr[rightIndex++];
    delete[] leftSubArr;
    delete[] rightSubArr;
}

int main(int argc, char const *argv[])
{
    int arr[] = {15, 5, 6, 1, 7, 8};
    auto arr_size = sizeof(arr) / sizeof(arr[0]);

    mergeSort<int>(arr, 0, arr_size);
    for (int i = 0; i < 6; i++)
    {
        cout << arr[i] << "\n";
    }

    return 0;
}
