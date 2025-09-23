#include <iostream>
//#include <Windows.h>

using namespace std;

struct Student {
	string fio;
	int avgmark;
	bool comm;
	Student* Next;
	Student* Prev;
};

Student* send = 0;
Student* sbeg = 0;

void insert(string f, int am, bool cm) {
	Student* st = new Student;
	Student* s = sbeg;
	st->fio = f;
	st->avgmark = am;
	st->comm = cm;
	if (send == 0) {
		sbeg = st;
		send = st;
		st->Prev = 0;
		st->Next = 0;
	}
	else {
		while (s) {
			if (st->fio < s->fio) {
				if (s == sbeg) {
					st->Prev = 0;
					st->Next = s;
					s->Prev = st;
					sbeg = st;
				}
				else {
					st->Prev = s->Prev;
					st->Next = s;
					(s->Prev)->Next = st;
					s->Prev = st;
				}
				break;
			}
			s = s->Next;
		}
		if (s == 0) {
			st->Next = 0;
			st->Prev = send;
			send->Next = st;
			send = st;
		}
	}
}

void remove(string f) {
	Student* st = sbeg;
	while (st->fio != f) {
		st = st->Next;
	}
	if (st == sbeg) {
		sbeg = st->Next;
		if (sbeg) {
			sbeg->Prev = 0;
		}
	}
	else if (st == send) {
		send = st->Prev;
		send->Next = 0;
	}
	else {
		(st->Next)->Prev = st->Prev;
		(st->Prev)->Next = st->Next;
	}
	delete st;
}

int main() {
	setlocale(LC_ALL, "Russian");
	int num;
	Student *st;
	string f;
	int am;
	bool cm;
	while (1) {
		cout << "Выберете действие:" << endl;
		cout << "1 - Добавить студента" << endl;
		cout << "2 - Удалить студента" << endl;
		cout << "3 - Вывести всех студентов" << endl;
		cout << "4 - Вывести данные о студенте" << endl;
		cout << "5 - Вывести всех студентов со средним баллом больше 3" << endl;
		cout << "6 - Вывести всех платников" << endl;
		cout << "7 - Выход" << endl;
		cin >> num;
		switch (num) {
			case 1:
				cout << "Введите ФИО "; cin >> f;
				cout << "Введите среднюю оценку"; cin >> am;
				cout << "введите на какой основе учится студент (бюджет - 0, внебюджет - 1)"; cin >> cm;
				insert(f,am,cm);
				break;
			case 2:
				cout << "Введите имя"; cin >> f;
				remove(f);
				break;
			case 3:
				st = sbeg;
				while (st) {
					cout << st->fio << ' ' << st->avgmark << ' ' << st->comm << endl;
				break;
				}
			case 4:
				cout << "Введите имя"; cin >> f;
				st = sbeg;
				while (st->fio != f) st = st->Next;
				cout << st->fio << ' ' << st->avgmark << ' ' << st->comm << endl;
				break;
			case 5:
				st = sbeg;
				while (st) {
					if (st->comm) cout << st->fio << ' ' << st->avgmark << ' ' << st->comm << endl;
					st = st->Next;
				break;
				}
			case 6:
				st = sbeg;
				while (st) {
					if (st->comm) cout << st->fio << ' ' << st->avgmark << ' ' << st->comm << endl;
					st = st->Next;
				break;
				}
			case 7:
				exit(0);
			default:
				cout << "Неверный номер действия";
			break;
		}
	}
}