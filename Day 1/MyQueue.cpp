#include <iostream>
#include <stdlib>

using namespace std;

template <typename T>
class MyStack
{
    T *queue;
    int head, tail;
    int Size;

public:
    MyStack(int L)
    {
        cout << "Stack Ctor \n";
        Size = L;
        head = 0;
        tail = 0;
        queue = new T[Size];
    }

    ~MyStack()
    {
        cout << "Destructor \n";
        delete[] queue;
    }

    int IsFull()
    {
        return (head - tail) == Size;
    }

    int IsEmpty() { return (head - tail) == 0; }

    void Enq(int n)
    {
        if (!IsFull())
        {
            if (head < Size)
            {
                queue[head++] = n;
            }
            else
            {
                head = 0;
                queue[head] = n;
            }
        }
        else
            cout << "Queue is Full \n";
    }

    T Deq()
    {
        if (!IsEmpty())
        {
            if (tail < Size)
            {
                return queue[++tail];
            }
            else
            {
                tail = 0;
                return queue[tail];
            }
        }
        else
        {
            cout << "Queue is Empty \n";
            return -1;
        }
    }
    T peek()
    {
        if (!IsEmpty())
            return queue[tail];
        else
        {
            cout << "Queue is Empty \n";
            return -1;
        }
    }
    int GetCount()
    {
        return abs(head - tail);
    }
};

int main(int argc, char const *argv[])
{

    return 0;
}
