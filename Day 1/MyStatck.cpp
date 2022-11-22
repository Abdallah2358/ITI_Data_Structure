#include <iostream>
#include <stdlib.h>

using namespace std;
template <typename T>
class Node
{
public:
    T data;
    Node<T> *pNext;
    Node<T> *pPrev;
    Node()
    {
        this->pNext = this->pPrev = NULL;
    }
    Node(T data)
    {
        this->data = data;
        this->pNext = this->pPrev = NULL;
    };
};
template <typename T>
class DoubleLinkedList
{
public:
    Node<T> *pLast;
    Node<T> *pStart;

    DoubleLinkedList(/* args */)
    {
        pLast = NULL;
        pStart = NULL;
    }
    void AddNode(T data)
    {
        Node<T> *pNew = new Node<T>();
        pNew->data = data;
        if (pLast == NULL)
        {
            pLast = pStart = pNew;
        }
        else
        {
            pLast->pNext = pNew;
            pNew->pPrev = pLast;
            pLast = pNew;
        }
    }
    Node<T> *SearchList(T key)
    {
        Node<T> *pSearch = pStart;
        while (pSearch != NULL)
        {
            if (pSearch->data == key)
                break;
            pSearch = pSearch->pNext;
        }
        return pSearch;
    }

    void Display(T key)
    {
        Node<T> *pDisp = SearchList(key);
        if (pDisp == NULL)
        {
            cout << "NotFound" << endl;
        }
        else
        {
            cout << pDisp->data << endl;
        }
    }
    void displayAll()
    {
        Node<T> *pDisp = this->pStart;
        while (pDisp != NULL)
        {
            cout << pDisp->data << endl;
            pDisp = pDisp->pNext;
        }
    }
    void deleteNode(T key)
    {
        Node<T> *pDelete = SearchList(key);
        if (pDelete == NULL)
        {
            cout << "NotFound" << endl;
        }
        else if (this->pStart == this->pLast)
        {
            this->pLast = this->pStart = NULL;
        }
        else if (this->pStart == pDelete)
        {
            pStart = pStart->pNext;
            pStart->pPrev = NULL;
        }
        else if (pLast == pDelete)
        {
            pLast = pLast->pPrev;
            pLast->pNext = NULL;
        }
        else
        {
            pDelete->pPrev->pNext = pDelete->pNext;
            pDelete->pNext->pPrev = pDelete->pPrev;
        }
        delete pDelete;
    }
    void deleteAll()
    {
        Node<T> *pTemp;
        while (pStart != NULL)
        {
            pTemp = pStart;
            pStart = pStart->pNext;
            delete pTemp;
        }
        pLast = NULL;
    }
    ~DoubleLinkedList()
    {
        deleteAll();
    };
};

template <typename T>
class MyStack
{
    DoubleLinkedList<T> stk;
    int Tos;
    int Size;

public:
    MyStack(int s = 5)
    {
        Size = s;
        Tos = 0;
    }
    MyStack(MyStack &s)
    {
        Size = s.Size;
        Tos = s.Tos;
        stk = s.stk;
    }

    bool IsFull() { return (Tos == Size); }

    bool IsEmpty() { return Tos == 0; }

    void Push(T n)
    {
        if (!IsFull())
            stk.AddNode(n);
        else
            cout << "Stack is Full \n";
    }

    T Pop()
    {
        if (!IsEmpty())
        {
            T temp = stk.pLast->data;
            stk.deleteNode(temp);
            return temp;
        }
        else
        {
            cout << "Stack is Empty \n";
            return NULL;
        }
    }
    int peek()
    {
        if (!IsEmpty())
            return stk.pLast->data;
        else
        {
            cout << "Stack is Empty \n";
            return NULL;
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
    void print()
    {
        Node<T> *temp = stk.pStart;
        while (temp)
        {
            cout << temp->data << endl;
            temp = temp->pNext;
        }
    }

    MyStack operator+(const MyStack &s)
    {
        MyStack newStack;
        newStack.Size = Size + s.Size;
        Node<T> *temp = stk.pStart;
        while (temp)
        {
            newStack.Push(temp->data);
            temp = temp->pNext;
        }

        temp = s.stk.pStart;
        while (temp)
        {
            newStack.Push(temp->data);
            temp = temp->pNext;
        }
        return newStack;
    }
};

int main(int argc, char const *argv[])
{
    MyStack<int> s1(4), s2(4);
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);
    s1.Push(4);
    s2.Push(8);
    s2.Push(7);
    s2.Push(5);
    s2.Push(5);

    (s1 + s2).print();
    return 0;
}
