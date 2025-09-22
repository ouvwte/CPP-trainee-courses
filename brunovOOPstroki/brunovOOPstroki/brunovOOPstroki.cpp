#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	cout << "Задание 1." << endl;
    //Отсортировать слова в строке в лексикографическом порядке(по алфавиту)
	cout << "Введите строку: ";
	string s;
	getline(cin, s);
    vector<string> words;
    size_t pos;
    while ((pos = s.find(' ')) != string::npos) {
        string word = s.substr(0, pos);
        if (word.length() > 0)
            words.push_back(word);
        s.erase(0, pos + 1);
    }
    if (s.length() > 0)
        words.push_back(s);
    sort(words.begin(), words.end());
    cout << "Строка после сортировки слов в лексикографическом порядке: ";
    for (auto word : words) {
        cout << word << " ";
    }
    cout << endl;

    cout << "Задание 2." << endl;
    //Написать программу, которая считывает текст из файла и выводит его на экран, меняя местами каждые два соседних слова.
    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;
    ifstream in(filename);
    if (!in) {
        cerr << "Ошибка при открытии файла " << filename << endl;
        return 1;
    }
    vector<string> slova;
    string stroka;
    while (in >> stroka) {
        slova.push_back(stroka);
    }
    in.close();
    for (int i = 0; i < slova.size() - 1; i += 2) {
        swap(slova[i], slova[i + 1]);
    }
    cout << "Текст после замены каждых двух соседних слов:" << endl;
    for (auto stroka : slova) {
        cout << stroka << " ";
    }
    cout << endl;
	return 0;
}