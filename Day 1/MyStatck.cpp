#include <iostream>

using namespace std;

template <typename T>
class MyStack
{
    int *stk;
    int Tos;
    int Size;

public:
    MyStack(int L = 5)
    {
        Size = L;
        Tos = 0;
        stk = new T[Size];
    }
    MyStack(MyStack &s)
    {
        Size = s.Size;
        Tos = s.Tos;
        stk = new T[Size];
        for (int i = 0; i < Tos; i++)
        {
            stk[i] = s.stk[i];
        }
    }

    ~MyStack()
    {
        for (int i = 0; i < Tos; i++)
        {
            stk[i] = -1;
        }

        delete[] stk;
    }

    int IsFull() { return (Tos == Size); }

    int IsEmpty() { return Tos == 0; }

    void Push(int n)
    {
        if (!IsFull())
            stk[Tos++] = n;
        else
            cout << "Stack is Full \n";
    }

    int Pop()
    {
        if (!IsEmpty())
            return stk[--Tos];
        else
        {
            cout << "Stack is Empty \n";
            return -1;
        }
    }
    int peek()
    {
        if (!IsEmpty())
            return stk[Tos];
        else
        {
            cout << "Stack is Empty \n";
            return -1;
        }
    }
    int GetCount()
    {
        return Tos;
    }
    MyStack reverse()
    {
        MyStack s(Size);
        for (int i = Tos - 1; i >= 0; i--)
        {
            s.Push(stk[i]);
        }
        return s;
    }

    MyStack operator+(const MyStack &s)
    {
        MyStack newStack;

        newStack.Size = Size + s.Size;
        newStack.stk = new T[Size];
        for (int i = 0; i < Tos; i++)
        {
            newStack.stk[i] = stk[i];
            newStack.Tos += 1;
        }
        for (int i = Tos, k = 0; i < (s.Tos + Tos); k++, i++)
        {
            newStack.stk[i] = s.stk[k];

            newStack.Tos += 1;
        }
        return newStack;
    }

    friend void vContent(const MyStack &s);
};
void vContent(const MyStack &s)
{
    for (int i = 0; i < s.Tos; i++)
    {
        cout << s.stk[i] << endl;
    }
}
int main(int argc, char const *argv[])
{
    MyStack s1(4), s2(4);
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);
    s1.Push(4);
    s2.Push(8);
    s2.Push(7);
    s2.Push(5);
    s2.Push(5);

    vContent(s1 + s2);
    return 0;
}
