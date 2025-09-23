/*
Составить программу, которая содержит текущую информацию о книгах в библиотеке. Сведения о книгах содержат:
- номер УДК;
- фамилию и инициалы автора;
- название;
- год издания;
- количество экземпляров данной книги в библиотеке.
Программа должна обеспечивать:
- начальное формирование данных о всех книгах в библиотеке в виде списка;
- при взятии каждой книги вводится номер УДК, и программа уменьшает значение
количества книг на единицу или выдает сообщение о том, что требуемой книги в библиотеке нет, 
или требуемая книга находится на руках;
- при возвращении каждой книги вводится номер УДК, и программа увеличивает значение количества книг на единицу;
- по запросу выдаются сведения о наличии книг в библиотеке.
*/

#include <iostream>
#include <list>
#include <string>
using namespace std;
struct Book {
    int udk;
    string author;
    string title;
    int year;
    int quantity;
};
// Создание ноыой книги
Book createBook(int udk, string author, string title, int year, int quantity) {
    Book book;
    book.udk = udk;
    book.author = author;
    book.title = title;
    book.year = year;
    book.quantity = quantity;
    return book;
}
int main() {
    setlocale(LC_ALL, "Russian");
    list<Book> library;
    library.push_back(createBook(123, "Пушкин А.С.", "Евгений Онегин", 1833, 5));
    library.push_back(createBook(456, "Достоевский Ф.М.", "Преступление и наказание", 1866, 3));
    library.push_back(createBook(789, "Лермонтов М.Ю.", "Герой нашего времени", 1840, 2));
    int udk;
    int action;
    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Взять книгу" << endl;
        cout << "2. Вернуть книгу" << endl;
        cout << "3. Проверить наличие книги" << endl;
        cout << "4. Выйти из программы" << endl;
        cin >> action;
        if (action == 1) { // Взять книгу
            cout << "Введите номер УДК книги: ";
            cin >> udk;
            bool found = false;
            for (auto& book : library) {
                if (book.udk == udk) {
                    if (book.quantity > 0) {
                        book.quantity--;
                        cout << "Книга \"" << book.title << "\" взята в библиотеке" << endl;
                    }
                    else {
                        cout << "Книги \"" << book.title << "\" нет в наличии" << endl;
                    }
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Книга с номером УДК " << udk << " не найдена в библиотеке" << endl;
            }
        }
        else if (action == 2) { // Вернуть книгу
            cout << "Введите номер УДК книги: ";
            cin >> udk;
            bool found = false;
            for (auto& book : library) {
                if (book.udk == udk) {
                    book.quantity++;
                    cout << "Книга \"" << book.title << "\" возвращена в библиотеку" << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Книга с номером УДК " << udk << " не найдена в библиотеке" << endl;
            }
        }
        else if (action == 3) { // Проверить наличие книги
            cout << "Введите номер УДК книги: ";
            cin >> udk;
            bool found = false;
            for (auto& book : library) {
                if (book.udk == udk) {
                    cout << "Книга \"" << book.title << "\" есть в наличии: " << book.quantity << " шт." << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Книга с номером УДК " << udk << " не найдена в библиотеке" << endl;
            }
        }
        else if (action == 4) { // Выйти из программы
            break;
        }
        else { 
            cout << "Некорректный ввод" << endl;
        }
    }
    return 0;
}