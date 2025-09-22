#include <iostream>
#include <conio.h>
#include <clocale>

using namespace std;

struct Node
{
    int d;
    Node* Next;
    Node* Next1;
};

Node* top = NULL, * tops = NULL;

Node* push(int n)
{
    Node* ptr = new Node;
    ptr->d = n;
    if (top == NULL)
    {
        top = ptr;
        ptr->Next = NULL;
    }
    else
    {
        ptr->Next = top;
        top = ptr;
    }
    return ptr;
}

void pop()
{
    if (top == NULL) return;
    Node* ptr = top->Next;

    delete top;
    top = ptr;
}

void print() {
    Node* c = top;
    if (top == NULL) cout << "Элементов нет";
    else {
        cout << "Элементы стека: ";
        while (c != NULL) {
            cout << c->d << " ";
            c = c->Next;
        }
    }
    cout << endl;
}

Node* copy(int n) {
    Node* pv = new Node;
    pv->d = n;
    if (tops == NULL)
    {
        tops = pv;
        pv->Next1 = NULL;
    }
    else
    {
        pv->Next1 = tops;
        tops = pv;
    }
    return pv;
}

void pop1()
{
    if (tops == NULL) return;
    Node* pv = tops->Next1;
    delete tops;
    tops = pv;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int num, n, g;
    while (1) {
        cout << "Выберите действие: \n";
        cout << "1 - Добавление элемента согласно правилам работы со структурой\n";
        cout << "2 - Удаление элемента\n";
        cout << "3 - Удаление всех элементов\n";
        cout << "4 - Отображение элементов структуры  в прямом порядке\n";
        cout << "5 - Удаление всех чисел кратных 7\n";
        cout << "6 - Выход из программы\n";
        cin >> num;
        switch (num)
        {
        case 1:
            cout << "Введите число от -20 до 60\n";
            cin >> n;
            while (!(n <= 60 && n >= -20)) {
                cout << "Вы ввели неправильное число, попробуйте ещё раз\n";
                cin >> n;
            }
            push(n);
            g = n;
            break;
        case 2:
            pop();
            cout << "Элемент <<" << g << ">> удалён\n";
            break;
        case 3:
            while (top != NULL)
                pop();
            cout << "Все элементы удалены\n";
            break;
        case 4:
            print();
            break;
        case 5:
            while (top != NULL) {
                if (top->d % 7 == 0) {
                    pop();
                }
                else {
                    n = top->d;
                    copy(n);
                    pop();
                }
            }
            while (tops != NULL) {
                n = tops->d;
                push(n);
                pop1();
            }
            print();
            break;
        case 6:
            exit(0);
        default:
            cout << "Неверный номер действия\n";
            break;
        }
    }
}