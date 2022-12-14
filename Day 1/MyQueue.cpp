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
class MyQueue
{
    DoubleLinkedList<T> queue;
    int head, tail;
    int Size;

public:
    MyQueue()
    {
        Size = 0;
        head = 0;
        tail = 0;
        
    }

    int IsEmpty() { return (head - tail) == 0; }

    void Enq(T n)
    {
        queue.AddNode(n);
        head++;
    }

    T Deq()
    {
        T temp;
        if (!IsEmpty())
        {
            temp = queue.pStart->data;
            queue.deleteNode(temp);
            tail++;
            return temp;
        }
        else
        {
            cout << "Queue is Empty \n";
            return NULL;
        }
    }
    T peek()
    {
        if (!IsEmpty())
            return queue.pStart->data;
        else
        {
            cout << "Queue is Empty \n";
            return NULL;
        }
    }
    int GetCount()
    {
        return abs(head - tail);
    }
};

int main(int argc, char const *argv[])
{
    MyQueue<int> q;
    q.Enq(4);
    q.Enq(2);
    q.Enq(3);
    cout << q.Deq() << endl;
    cout << q.Deq() << endl;
    cout << "===============" << endl;
    
    q.Enq(150);
    cout << q.Deq() << endl;
    cout << q.Deq() << endl;

    return 0;
}
