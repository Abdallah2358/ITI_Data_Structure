#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define NormalPen 0x0F
#define HighLightPen 0XF0
#define Enter 0x0D
#define ESC 27
#define UP 72
#define Down 80
#define RIGHT 77
#define LEFT 75
#define Tap 9
#define BackSpace 8
#define aSmall 97
#define zSmall 122
#define zero 48
#define nine 57

// Structures
struct Employee
{
    int id;
    int age;
    char name[100];
    char address[200];
    char gender[8];
    double salary;
    double overTime;
    double tax;
};

class Node
{
public:
    Employee data;
    Node *pNext;
    Node *pPrev;
};

Node *NewNode(Employee emp)
{
    Node *pNew = new Node();
    if (pNew == NULL)
        exit(0);
    pNew->data = emp;
    pNew->pNext = pNew->pPrev = NULL;
    return pNew;
}

// Structures

// Global Variables
struct Employee EArr[10];

int MenuCurrent = 0, ExitFlag = 0, currentView = 0; // 0 main

// Linked List
Node *pLast;
Node *pStart;

void AddNode(Employee emp)
{
    Node *pnew = NewNode(emp);
    if (pLast == NULL)
    {
        pLast = pStart = pnew;
    }
    else
    {
        pLast->pNext = pnew;
        pnew->pPrev = pLast;
        pLast = pnew;
    }
}

Node *SearchList(int key)
{
    Node *pSearch = pStart;
    while (pSearch != NULL)
    {
        if (pSearch->data.id == key)
            break;
        pSearch = pSearch->pNext;
    }
    return pSearch;
}

// emp func
void printEmpData(int empID)
{
    // struct Employee temp = EArr[empID];
    struct Employee temp = SearchList(empID)->data;
    printf("\nEmployee #%i\nName : %s ,Age: %d ,Gender: %s ,Salary : %.2lf ,Over Time : %.2lf ,Tax : %.2lf ,Address : %s \n",
           temp.id, temp.name, temp.age, temp.gender, temp.salary, temp.overTime, temp.tax, temp.address);
}

// Writing to console Functions
void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
void clearScreen()
{
    textattr(NormalPen);
    system("cls");
}

// Helper fuc
void copyStr(char *dest, char *src)
{
    int i = 0;
    for (; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

// Main Menu Functions
void showMainMenu()
{
    clearScreen();
    char choices[6][20] = {" New ", "Display By ID", "Display All", "Delete By ID", "Delete All", "Exit"};
    for (int i = 0; i < 6; i++)
    {
        gotoxy(15, 10 + 3 * i);
        if (MenuCurrent == i)
        {
            textattr(HighLightPen);
        }
        else
        {
            textattr(NormalPen);
        }
        printf(choices[i]);
    }
}

void returnToMainMenu()
{
    showMainMenu();
    currentView = 0;
}
void updateMainMenu()
{
    char inp;
    inp = _getche();
    switch (inp)
    {
    case ESC:
        ExitFlag = 1;
        break;
    case Enter:
        //" New ", "DisplayByID", "DisplayAll", "DeleteByID", "DeleteAll", "Exit"
        if (MenuCurrent == 5)
            ExitFlag = 1;
        currentView = MenuCurrent + 1;
        break;
    case -32:
        inp = _getche();
        switch (inp)
        {
        case UP:
            MenuCurrent--;
            if (MenuCurrent < 0)
                MenuCurrent = 5;
            break;
        case Down:
            MenuCurrent++;
            if (MenuCurrent > 5)
                MenuCurrent = 0;
            break;
        }
        break;
    }
    showMainMenu();
}

// Initialization Functions
void initId()
{
    for (int i = 0; i < 10; i++)
    {
        EArr[i].id = -1;
    }
}

void Init()
{
    showMainMenu();
    initId();
}

// Input Functions
char isIdExist(int empId)
{
    return EArr[empId].id != -1;
}

int chooseEmpID()
{
    int temp;
    do
    {
        printf("Please Choose EmpID : ");
        scanf("%i", &temp);
        if (SearchList(temp))
        {
            printf("\nThis ID already used.\n");
        }
    } while (SearchList(temp));
    return temp;
}

void showInputForm()
{
    char returnFlag = 0;
    char inpFields[8][15] = {"Name :", "Salary :", "Tax :", "Address :", "Age :", "Gender :", "Over Time :"};
    int shift = 3;
    for (int i = 0; i < 4; i++)
    {
        gotoxy(5, 10 + 3 * i);
        printf(inpFields[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        gotoxy(40, 10 + 3 * i);
        printf(inpFields[i + 4]);
    }
}

char *lineEditor(int x, int y, char start, char end, int *row, int *col, char *done)
{
    int i = 0;
    static char line[11];
    char *pCurrent = line, *pEnd = line;
    char ch;

    while (pEnd < &line[11])
    {
        gotoxy(x, y);
        ch = _getch();

        if ((ch >= start && ch <= end) || ch == '.')
        {
            printf("%c", ch);
            line[i] = ch;
            pEnd++;
            pCurrent++;
            i++;
            x++;
        }
        else
        {
            switch (ch)
            {
            case Enter:
                if (*row == 3 && *col == 2)
                {
                    *done = TRUE;
                }
                if (*row == 4)
                {
                    (*col)++;
                }
                (*row)++;

                line[i] = '\0';
                return line;
                break;

            case ESC:
                exit(0);
            case Tap:
                if (*row == 3 && *col == 2)
                {
                    (*col)--;
                    (*row) = 5;
                }
                if (*row == 4)
                {
                    (*col)++;
                }
                (*row)++;
                line[i] = '\0';
                return line;
                break;
            case BackSpace:
                if (pCurrent == pEnd && i > 0)
                {
                    *pEnd = '\0';   // remove the last letter from array;
                    gotoxy(--x, y); // move back
                    printf(" ");    // remove character
                    i--;            // reduce i
                    pEnd--;
                    pCurrent--;
                }
                else if (pCurrent > line)
                {
                    // go back 1
                    x--;
                    pCurrent--;

                    // shift array
                    int j = 0;
                    for (; j < pEnd - pCurrent - 1; j++)
                    {
                        *(pCurrent + j) = *(pCurrent + j + 1);
                        gotoxy(x + j, y);
                        printf("%c", *(pCurrent + j + 1));
                    }

                    // remove the last char from screen
                    gotoxy(x + j, y);
                    printf(" ");

                    // put null terminator at the end
                    *pEnd = '\0';
                    pEnd--;
                    i--;
                }
                break;
            case -32:
                ch = getch();
                switch (ch)
                {
                case RIGHT:
                    if (pCurrent < pEnd)
                    {
                        gotoxy(++x, y);
                        pCurrent++;
                    }

                    break;
                case LEFT:
                    if (pCurrent > line)
                    {
                        gotoxy(--x, y);
                        pCurrent--;
                    }
                    break;
                case UP:
                    (*row)--;
                    line[i] = '\0';
                    return line;
                    break;
                case Down:
                    (*row)++;
                    line[i] = '\0';
                    return line;
                    break;
                }
                break;
            }
        }
    }
    line[i] = '\0';
    return line;
}

void receiveFormInput(int empID)
{
    struct Employee temp;
    temp.id = empID;
    int row = 1, col = 1;
    char done = FALSE;
    do
    {
        if (col > 2)
            col = 1;
        if (col == 2 && row > 3)
        {
            row = 1;
        }
        else
        {
            if (row > 4)
            {
                row = 1;
            }
        }
        if (row == 0)
        {
            row = 4;
        }

        if (col == 1)
        {
            switch (row)
            {
            case 1:
                copyStr(temp.name, lineEditor(15, 10, aSmall, zSmall, &row, &col, &done));
                break;
            case 2:
                temp.salary = atof(lineEditor(15, 13, zero, nine, &row, &col, &done));
                break;
            case 3:
                temp.tax = atof(lineEditor(15, 16, zero, nine, &row, &col, &done));
                break;
            case 4:
                copyStr(temp.address, lineEditor(15, 19, aSmall, zSmall, &row, &col, &done));
                break;
            }
        }
        else
        {
            switch (row)
            {
            case 1:
                temp.age = atoi(lineEditor(55, 10, zero, nine, &row, &col, &done));
                break;
            case 2:
                copyStr(temp.gender, lineEditor(55, 13, aSmall, zSmall, &row, &col, &done));
                break;
            case 3:
                temp.overTime = atof(lineEditor(55, 16, zero, nine, &row, &col, &done));
                break;
            }
        }
    } while (!done);

    AddNode(temp);
    // EArr[empID] = temp;
}

void showNetSalary(int id)
{
    double net = EArr[id].salary + EArr[id].overTime - EArr[id].tax;
    printEmpData(id);
    printf("Net Salary : %lf\n", net);
    printf("Press Any key to return to main menu\n");
    _getch();
}

void showEmpByID()
{
    int id;
    bool returnFlag = false, ch;
    do
    {
        printf("Please Choose EmpID between 1 and 10 : ");
        scanf("%i", &id);
        if (SearchList(id))
        {
            printEmpData(id);
            printf("\nPress Any key to return to main menu\n");
            _getch();
        }
        else
        {
            printf("\nThis ID Does Not Exist.\n");
            printf("\nPlease Try Again or press Backspace to return\n");
            ch = _getch();
            if (ch == 8)
                returnFlag = true;
        }
    } while (!SearchList(id) && !returnFlag);
}

void showAllEmp()
{
    Node *temp = pStart;
    while (temp)
    {
        printEmpData(temp->data.id);
        temp = temp->pNext;
    }
    printf("\nPress Any key to return to main menu\n");
    _getch();
}

void DeleteEmpById()
{
    int id;
    bool returnFlag = false;
    do
    {
        printf("Please Choose EmpID between 1 and 10 : ");
        scanf("%i", &id);
        Node *pDel = SearchList(id);
        if (pDel == NULL)
        {
            printf("\nThis ID Does Not Exist.\n");
            printf("\nPlease Try Again or press Backspace to return to Main Menu\n");
            char ch = _getch();
            if (ch == 8)
                returnFlag = true;
        }
        else
        {
            if (pStart == pLast)
            {
                pStart = pLast = NULL;
            }
            else if (pStart = pDel)
            {
                pStart = pStart->pNext;
                pStart->pPrev = NULL;
            }
            else if (pLast == pDel)
            {
                pLast = pLast->pPrev;
                pLast->pPrev = NULL;
            }
            else
            {
                pDel->pNext->pPrev = pDel->pPrev;
                pDel->pPrev->pNext = pDel->pNext;
            }
            delete pDel;
            returnFlag = 1;
            printf("\nEmp #%i Deleted\nPress Any key to return to main menu\n", id);
            _getch();
        }
    } while (!isIdExist(id) && !returnFlag);
}

void DeleteAllEmp()
{
    char returnFlag = false;
    char ch;
    do
    {
        printf("Are You sure You want to delete !!! ALL !!! Employee Data ? y/n\n");
        ch = _getche();
        if (ch == 'y')
        {
            Node *temp = pStart;
            while (temp)
            {
                pStart = pStart->pNext;
                delete temp;
                temp = pStart;
            }

            for (int i = 0; i < i; i++)
                EArr[i].id = -1;
            printf("\nThanks, All Emp Data was deleted press any key to return to Main Menu \n");
            _getch();
        }
        else if (ch == 'n')
        {
            printf("\nThanks, Nothing was deleted press any key to return to Main Menu \n");
            _getch();
        }
        else
        {
            printf("\nInValid Input, Please Try Again or press Backspace to return to Main Menu\n");
            _getch();
            clearScreen();
        }
    } while (ch != 'y' && ch != 'n' && !returnFlag);
}

int main()
{
    Init();
    int temp;
    do
    {
        switch (currentView)
        {
        case 0:
            updateMainMenu();
            break;
        case 1:
            clearScreen();
            temp = chooseEmpID(); // a waste of 4 bytes :(
            showInputForm();
            receiveFormInput(temp);
            clearScreen();
            showNetSalary(temp);
            returnToMainMenu();
            break;
        case 2:
            clearScreen();
            showEmpByID();
            returnToMainMenu();
            break;
        case 3:
            clearScreen();
            showAllEmp();
            returnToMainMenu();
            break;
        case 4:
            clearScreen();
            DeleteEmpById();
            returnToMainMenu();
            break;
        case 5:
            clearScreen();
            DeleteAllEmp();
            returnToMainMenu();
            break;
        default:
            break;
        }
    } while (!ExitFlag);

    return 0;
}
