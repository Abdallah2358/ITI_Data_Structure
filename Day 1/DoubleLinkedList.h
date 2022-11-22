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

    Node(T data)
    {
        this->data = data;
        this->pNext = this->pPrev = NULL;
    };
};
template <typename T>

class DoubleLinkedList
{
private:
    Node<T> *pLast;
    Node<T> *pStart;

public:
    DoubleLinkedList(/* args */);
    void AddNode(T data)
    {
        Node<T> *pNew = Node(data);
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
    Node *SearchList(T key)
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
