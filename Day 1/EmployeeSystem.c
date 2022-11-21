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

// Global Variables
struct Employee EArr[10];
int MenuCurrent = 0, ExitFlag = 0, currentView = 0; // 0 main

// emp func
void printEmpData(empID)
{
    struct Employee temp = EArr[empID];
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
        printf("Please Choose EmpID between 1 and 10 : ");
        scanf("%i", &temp);
        if (isIdExist(temp))
        {
            printf("\nThis ID already used.\n");
        }

    } while (isIdExist(temp));
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

char *lineEditor(int x, int y, char start, char end)
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
                line[i] = '\0';
                return;
                break;

            case ESC:
                exit(0);

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
    char row, col;
    char done = FALSE;
    do
    {
        if (col == 1)
        {
            switch (row)
            {
            case 1:
                copyStr(temp.name, lineEditor(15, 10, aSmall, zSmall));

                break;
            case 2:
                temp.salary = atof(lineEditor(15, 13, zero, nine));
                break;
            case 3:
                temp.tax = atof(lineEditor(15, 16, zero, nine));
                break;
            case 4:
                copyStr(temp.address, lineEditor(15, 19, aSmall, zSmall));
                break;
            }
        }
        else
        {
            switch (row)
            {
            case 1:
                temp.age = atoi(lineEditor(55, 10, zero, nine));
                break;
            case 2:
                copyStr(temp.gender, lineEditor(55, 13, aSmall, zSmall));
                break;
            case 3:
                temp.overTime = atof(lineEditor(55, 16, zero, nine));
                break;
            }
        }

    } while (!done);

    copyStr(temp.name, lineEditor(15, 10, aSmall, zSmall));
    temp.salary = atof(lineEditor(15, 13, zero, nine));
    temp.tax = atof(lineEditor(15, 16, zero, nine));
    copyStr(temp.address, lineEditor(15, 19, aSmall, zSmall));

    temp.age = atoi(lineEditor(55, 10, zero, nine));

    copyStr(temp.gender, lineEditor(55, 13, aSmall, zSmall));

    temp.overTime = atof(lineEditor(55, 16, zero, nine));

    EArr[empID] = temp;
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
    char returnFlag = 0, ch;
    do
    {
        printf("Please Choose EmpID between 1 and 10 : ");
        scanf("%i", &id);
        if (isIdExist(id))
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
                returnFlag = 1;
        }
    } while (!isIdExist(id) && !returnFlag);
}

void showAllEmp()
{
    for (int i = 0; i < 10; i++)
    {
        if (isIdExist(i))
        {
            printEmpData(i);
        }
    }
    printf("\nPress Any key to return to main menu\n");
    _getch();
}

void DeleteEmpById()
{
    int id;
    char returnFlag = 0;
    do
    {
        printf("Please Choose EmpID between 1 and 10 : ");
        scanf("%i", &id);
        if (isIdExist(id))
        {
            EArr[id].id = -1;
            returnFlag = 1;
            printf("\nEmp #%i Deleted\nPress Any key to return to main menu\n", id);
            _getch();
        }
        else
        {
            printf("\nThis ID Does Not Exist.\n");
            printf("\nPlease Try Again or press Backspace to return to Main Menu\n");
            char ch = _getch();
            if (ch == 8)
                returnFlag = 1;
        }
    } while (!isIdExist(id) && !returnFlag);
}
void DeleteAllEmp()
{

    char returnFlag = 0;
    char ch;
    do
    {
        printf("Are You sure You want to delete !!! ALL !!! Employee Data ? y/n\n");
        ch = _getche();
        if (ch == 'y')
        {
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
