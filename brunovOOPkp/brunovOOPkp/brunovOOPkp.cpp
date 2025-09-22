/* Составить программу, которая содержит текущую информацию о книгах в библиотеке.
Сведения о книгах содержат:
    номер УДК;
    фамилию и инициалы автора;
    название;
    год издания;
    количество экземпляров данной книги в библиотеке.
Программа должна обеспечивать:
    начальное формирование данных о всех книгах в библиотеке в виде списка;
    при взятии каждой книги вводится номер УДК, и программа уменьшает значение 
количества книг на единицу или выдает сообщение о том, что требуемой книги в библиотеке нет, или требуемая книга находится на руках;
    при возвращении каждой книги вводится номер УДК, и программа увеличивает значение количества книг на единицу;
    по запросу выдаются сведения о наличии книг в библиотеке.
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;
class Book {
private:
    string udc; // номер УДК
    string author; // фамилия и инициалы автора
    string title; // название
    int year; // год издания
    int count; // количество экземпляров в библиотеке
public:
    Book() {}
    Book(string u, string a, string t, int y, int c) {
        udc = u;
        author = a;
        title = t;
        year = y;
        count = c;
    }
    string getUdc() { return udc; }
    string getAuthor() { return author; }
    string getTitle() { return title; }
    int getYear() { return year; }
    int getCount() { return count; }
    void decreaseCount() { count--; }
    void increaseCount() { count++; }
};
class Library {
private:
    map<string, Book> books; // список книг в библиотеке
public:
    void addBook(Book b) {
        books[b.getUdc()] = b;
    }
    void takeBook(string udc) {
        if (books.find(udc) != books.end()) { // если книга есть в библиотеке
            if (books[udc].getCount() > 0) { // и есть свободные экземпляры
                books[udc].decreaseCount();
                cout << "Вы взяли книгу \"" << books[udc].getTitle() << "\"" << endl;
            }
            else {
                cout << "Требуемой книги в библиотеке нет" << endl;
            }
        }
        else {
            cout << "Требуемой книги в библиотеке нет" << endl;
        }
    }
    void returnBook(string udc) {
        if (books.find(udc) != books.end()) { // если книга есть в библиотеке
            books[udc].increaseCount();
            cout << "Вы вернули книгу \"" << books[udc].getTitle() << "\"" << endl;
        }
        else {
            cout << "Требуемой книги в библиотеке нет" << endl;
        }
    }
    void printBooks() {
        cout << "Книги в библиотеке:" << endl;
        for (auto it = books.begin(); it != books.end(); it++) {
            cout << it->second.getUdc() << " " << it->second.getAuthor() << " \"" << it->second.getTitle() << "\" " << it->second.getYear() << " г. Кол-во: " << it->second.getCount() << endl;
        }
    }
};
int main() {
    setlocale(LC_ALL, "Russian");
    // начальное формирование данных о книгах
    Library library;
    Book book1("123.45", "Пушкин А.С.", "Евгений Онегин", 1833, 3);
    Book book2("543.21", "Достоевский Ф.М.", "Преступление и наказание", 1866, 2);
    Book book3("987.65", "Лермонтов М.Ю.", "Герой нашего времени", 1840, 1);
    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);
    // работа с библиотекой
    int choice = 0;
    string udc;
    while (choice != 4) {
        cout << "Выберите действие:" << endl;
        cout << "1. Взять книгу" << endl;
        cout << "2. Вернуть книгу" << endl;
        cout << "3. Показать список книг" << endl;
        cout << "4. Выйти" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Введите номер УДК книги, которую хотите взять:" << endl;
            cin >> udc;
            library.takeBook(udc);
            break;
        case 2:
            cout << "Введите номер УДК книги, которую хотите вернуть:" << endl;
            cin >> udc;
            library.returnBook(udc);
            break;
        case 3:
            library.printBooks();
            break;
        case 4:
            break;
        default:
            cout << "Неверный выбор" << endl;
            break;
        }
    }
    return 0;
}