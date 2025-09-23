#include <iostream> 
#include <cstdio>
#include <list>
#include <array>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

static const int PARTS_NUMBER = 8;
static const int COMB_SIZE = 3;
static const int MAIN_LENG = 1000;
static const array<int, PARTS_NUMBER> LENGTHS = { 100, 200, 140, 130, 150, 110, 105, 103 };
static const array<int, PARTS_NUMBER> PLAN = { 50, 30, 100, 50, 30, 20, 56, 45 };


// структура с тремя элементами (вариант разделения трубы)
struct path {
    int first;
    int second;
    int third;
};

// заполнение списка комбинаций
void fill_list(list<path>& combs) {

    //для каждой из 8 деталей
    for (auto i = 1; i <= PARTS_NUMBER; i++) {

        // заполняем варианты по три детали
        for (auto j = 1; j <= COMB_SIZE; j++) {

            switch (j) {

            case 1:
                combs.push_back({ i, 0, 0 });
                break;

            case 2:
                for (auto second_part = i + 1; second_part <= PARTS_NUMBER; second_part++) {
                    combs.push_back({ i, second_part, 0 });
                }
                break;

            case 3:
                for (auto second_part = i + 1; second_part <= PARTS_NUMBER; second_part++) {
                    for (auto third_part = second_part + 1; third_part <= PARTS_NUMBER; third_part++) {
                        combs.push_back({ i, second_part, third_part });
                    }
                }
                break;
            }
        }
    }

    // вывод списка комбинаций
// for(auto it = combs.begin(); it != combs.end(); it++) {
// printf("%d %d %d\n", it->first, it->second, it->third);
// }

    return;
}

void depth_search(path& s, fstream& f, fstream& file_comb, string& comb) {
    //подсчет длины комбинации
    int var_len = 0;

    string tmp;

    //посимвольный разбор комбинации
    for (auto i = 0; i < comb.size(); i++) {

        //подсчет длины комбинации каждой детали в последовательности
        var_len += LENGTHS[((int)comb[i]) - 48 - 1];

        // если превышена длина трубы - возврат на этап выше
        if (var_len > MAIN_LENG)
            return;
    }

    //проверка на порог и запись в случае, если комбинация подходит
    if ((var_len >= 0.98 * MAIN_LENG) && (var_len < 1 * MAIN_LENG)) {
        f << "(tube length used: " << var_len << ") combination: " << comb << "\n";
        file_comb << comb << "\n";
    }

    // переход к следующим комбинациям

    if (s.first != 0) {

        tmp = comb + to_string(s.first);
        depth_search(s, f, file_comb, tmp);
    }

    if (s.second != 0) {

        tmp = comb + to_string(s.second);
        depth_search(s, f, file_comb, tmp);
    }

    if (s.third != 0) {

        tmp = comb + to_string(s.third);
        depth_search(s, f, file_comb, tmp);
    }

    return;
}

/*void search_double(fstream &file_matrix) {
    // создание файла для записи значений без дубликатов
    string file_name_clear = "clear.txt";
    fstream file_clear(file_name_clear, ios::in | ios::out | ios::trunc);
    // перевод каретки на начало файла
    file_matrix.seekg(0, ios::beg);

    //построчное считываение из файла
    int s;
    string str_matrix;
    int len_file = 0;

    for(; !file_comb.eof(); getline(file_comb, str_matrix)) {
        // какое кол файла было считано
        len_file = str_matrix.length();

    file_clear.close();
    return;
}
*/
void read_sequence(fstream& file_comb) {
    // создание файла для записи матрицы 
    string file_name_matrix = "matrix.txt";
    fstream file_matrix(file_name_matrix, ios::in | ios::out | ios::trunc);
    // перевод каретки на начало файла
    file_comb.seekg(0, ios::beg);

    //построчное считываение из файла 
    // посимвольное разбиение 
    // занесение в массив количества повторений
    int s;
    string str_matrix;
    int len_file = 0;

    for (; !file_comb.eof(); getline(file_comb, str_matrix)) {
        // какое кол файла было считано
        len_file = str_matrix.length();
        int length[PARTS_NUMBER] = { 0, 0, 0, 0, 0, 0, 0, 0 };

        for (int i = 0; i < str_matrix.length(); i++) {
            if (str_matrix[i] == '1') {
                length[0] ++;
            }
            if (str_matrix[i] == '2') {
                length[1] ++;
            }
            if (str_matrix[i] == '3') {
                length[2] ++;
            }
            if (str_matrix[i] == '4') {
                length[3] ++;
            }
            if (str_matrix[i] == '5') {
                length[4] ++;
            }
            if (str_matrix[i] == '6') {
                length[5] ++;
            }
            if (str_matrix[i] == '7') {
                length[6] ++;
            }
            if (str_matrix[i] == '8') {
                length[7] ++;
            }
        }

        //соединение массива в строку для записи
        string str_iter;
        for (int it = 0; it < PARTS_NUMBER; it++) {
            str_iter += to_string(length[it]);
            if (it != PARTS_NUMBER - 1) str_iter += " ";
        }

        file_matrix << str_iter << '\n';

        // переход на новую строчку на количество символов, которые были считаны в файле
        len_file = 0;
        str_matrix = "";
    }

    //serch_double(file_matrix);    
    file_matrix.close();
    return;
}

void find_paths(list<path>& combs) {
    string file_name = "paths.txt";
    string file_name_counts = "counts.txt";

    fstream file(file_name, ios::in | ios::out | ios::trunc);
    fstream file_counts(file_name_counts, ios::in | ios::out | ios::trunc);

    int var_len, buf_size;
    string buffer = "";

    for (auto it = combs.begin(); it != combs.end(); it++) {

        //длина изначальной комбинации
        var_len = LENGTHS[it->first - 1];
        if (it->second != 0) var_len += LENGTHS[it->second - 1];
        if (it->third != 0) var_len += LENGTHS[it->third - 1];

        // если комбинация из одной детали
        if (it->second == 0) {

            // буфер со строкой комбинации
            buffer += to_string(it->first);

            // пока не превышен порог
            while (var_len < MAIN_LENG) {

                //если план еще не выполнен
                if (buffer.size() < PLAN[it->first - 1]) {

                    // если комбинация проходит по порогу (98-99.99% от трубы) - записать её
                    if ((var_len >= 0.98 * MAIN_LENG) && (var_len < 1 * MAIN_LENG)) {
                        file << "(tube length used: " << var_len << ") combination: " << buffer << "\n";
                        file_counts << buffer << "\n";
                    }

                    var_len += LENGTHS[it->first - 1];
                    buffer += to_string(it->first);

                }
                else {
                    // если план выполнен - переходим к следующей последовательности
                    break;
                }
            }
        }
        else {

            // если комбинация из двух или более деталей
            // передаем текущую комбинацию    
            buffer += to_string(it->first);
            buffer += to_string(it->second);
            if (it->third != 0) buffer += to_string(it->third);

            //cout << buffer << endl;

            depth_search(*it, file, file_counts, buffer);

        }

        // зануление буфера строки с комбинацией
        buffer = "";

    }

    // подсчет элементов последовательности
    file.close();

    read_sequence(file_counts);

    file_counts.close();

    return;

}


int main() {

    // создание списка всех комбинаций
    list <path> combs;
    // нахождение всех комбинаций
    fill_list(combs);

    //запись всех вариантов в файл
    find_paths(combs);
    return 0;
}