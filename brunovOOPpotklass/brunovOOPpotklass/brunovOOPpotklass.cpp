//Дан текстовый файл. Заменить в нем все прописные буквы на строчные.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Russian");
    /*
    string file_name;
    cout << "Введите имя файла: ";
    cin >> file_name;
    ifstream file_in(file_name);
    if (!file_in.is_open()) {
        cout << "Не удалось открыть файл!";
        return 0;
    }
    string line;
    while (getline(file_in, line)) {
        for (int i = 0; i < line.length(); i++) {
            if (isalpha(line[i]) && isupper(line[i])) {
                line[i] = tolower(line[i]);
            }
        }
        cout << line << endl;
    }
    file_in.close();
    */

    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Ошибка при открытии файла" << endl;
        return 1;
    }

    string content;
    getline(file, content, '\0');
    file.close();

    for (int i = 0; i < content.size(); i++) {
        if (isupper(content[i])) {
            content[i] = tolower(content[i]);
        }
    }

    ofstream out(filename);
    out << content;
    out.close();

    cout << "Замена прописных букв на строчные выполнена успешно!" << endl;
    return 0;
}