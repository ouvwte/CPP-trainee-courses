//Дан файл целых чисел. Создать новый файл, содержащий те же элементы, 
// что и исходный файл, но в обратном порядке.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream input("input.txt"); 
    ofstream output("output.txt"); 

    vector<int> numbers; 

    int number;
    while (input >> number) { 
        numbers.push_back(number); 
    }

    // переворачиваем вектор
    reverse(numbers.begin(), numbers.end());

    for (int i = 0; i < numbers.size(); i++) { 
        output << numbers[i] << " ";
    }

    cout << "File has been reversed successfully." << endl;

    input.close(); 
    output.close(); 

    return 0;
}