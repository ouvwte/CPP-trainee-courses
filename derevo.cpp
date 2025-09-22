/*Разработать программу для реализации структуры дерево:
1)      Сформировать АВЛ-дерево, тип информационного поля int.
2)      Распечатать полученное дерево отсортировав элементы по ключу.
3)      Распечатать структуру дерева (указать для каждого узла его потомков, начиная с корня).
4)      Обеспечить поиск элемента по ключу и вывод пути до него.
5)      Найти максимальный и минимальный элементы дерева, количество листьев в дереве, высоту дерева.
*/

#include <iostream>
#include<string>

using namespace std;

//структура для представления узлов дерева
struct Node {
    int key;
    int height;
    Node* l;
    Node* r;
    Node(int k) { key = k; l = r = 0; height = 1; }
};

//инициализируем корень дерева
Node* root = NULL;

int height(Node* p) {
    if (p) return p->height;
    else return 0;
}

// сравнение высоты левого и правого поддеревьев
int bfactor(Node* p) {
    return height(p->r) - height(p->l);
}

// новая высота для повернутого поддерева 
void fixheight(Node* p) {
    int hl = height(p->l);
    int hr = height(p->r);
    if (hl > hr) p->height = hl + 1;
    else p->height = hr + 1;
}

Node* rotateR(Node* p) {
    Node* q = p->l;
    p->l = q->r;
    q->r = p;
    fixheight(p);
    fixheight(q);
    return q;
}

Node* rotateL(Node* q) {
    Node* p = q->r;
    q->r = p->l;
    p->l = q;
    fixheight(q);
    fixheight(p);
    return q;
}

Node* balance(Node* p) {
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->r) < 0)
            p->r = rotateR(p->r);
        return rotateL(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->l) > 0)
            p->l = rotateL(p->l);
        return rotateR(p);
    }
    return p;
}

//вставка ключа к в дерево с корнем р
Node* insert(Node* p, int k) {
    if (!p) return new Node(k);
    if (k < p->key)
        p->l = insert(p->l, k);
    else
        p->r = insert(p->r, k);
    return balance(p);
}

//поиск ключа к в дереве с корнем р
void seek(Node* p, int k) {
    cout << p->key << " ";
    if (k > p->key)
        seek(p->r, k);
    else if (k < p->key)
        seek(p->l, k);
}

void printS(Node* p) {
    if (p->l)
        printS(p->l);
    cout << p->key << " ";
    if (p->r)
        printS(p->r);
}

void print(Node* p) {
    if (p->l)
        cout << p->key << "->" << (p->l)->key << endl;
    if (p->r)
        cout << p->key << "->" << (p->r)->key << endl;
    if (p->l)
        print(p->l);
    if (p->r)
        print(p->r);
}

void min(Node* p) {
    if (p->l == NULL) {
        cout << "Минимальный элемент: " << p->key << endl;
    }
    else {
        min(p->l);
    }
}

void max(Node* p) {
    if (p->r == NULL) {
        cout << "Максимальный элемент: " << p->key << endl;
    }
    else {
        max(p->r);
    }
}

//считаем количество листьев
int list(Node* p) {
    int chet;
    if ((p->l == NULL) && (p->r == NULL)) {
        chet = 1;
    }
    else {
        chet = 0;
    }
    if (p->l) {
        chet += list(p->l);
    }
    if (p->r) {
        chet += list(p->r);
    }
    return chet;
}

int main() {
    setlocale(LC_ALL, "rus");
    int num, n;
    while (1) {
        cout << "1 - Добавить элемент с клавиатуры\n";
        cout << "2 - Вывести отсортированные элементы\n";
        cout << "3 - Вывести структуру дерева\n";
        cout << "4 - Поиск элемента по ключу\n";
        cout << "5 - Поиск минимального элемента\n";
        cout << "6 - Поиск максимального элемента\n";
        cout << "7 - Значение высоты\n";
        cout << "8 - Количество листьев\n";
        cout << "9 - Выход\n";
        cin >> num;
        switch (num) {
        case 1:
            cout << "Введите элемент: ";
            cin >> n;
            root = insert(root, n);
            break;
        case 2:
            printS(root);
            cout << endl;
            break;
        case 3:
            print(root);
            break;
        case 4:
            cout << "Ведите ключ узла: ";
            cin >> n;
            seek(root, n);
            cout << endl;
            break;
        case 5:
            min(root);
            break;
        case 6:
            max(root);
            break;
        case 7:
            cout << "Высота дерева: " << height(root) << endl;
            break;
        case 8:
            cout << "Число листьев: " << list(root) << endl;
            break;
        case 9:
            exit(0);
        default:
            cout << "Неверный номер действия, повторите попытку\n";
            break;
        }
    }
}