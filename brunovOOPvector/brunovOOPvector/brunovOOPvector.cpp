/*В одномерном массиве, состоящем из п вещественных элементов, вычислить:
1) максимальный элемент массива;
2) сумму элементов массива, расположенных до последнего положительного элемента.*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    vector<double> arr(n); 
    cout << "Введите элементы массива: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; 
    }
    double max = arr[0]; 
    double sum = 0;
    int lastPositiveIndex = -1; // индекс последнего положительного элемента, или -1, если нет таких элементов

    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] > 0) {
            lastPositiveIndex = i;
        }
    }
    for (int i = 0; i < lastPositiveIndex; i++) {
        sum += arr[i];
    }
    cout << "Максимальный элемент: " << max << endl;
    if (lastPositiveIndex == -1) cout << "Положительных элементов нет" << endl;
    else cout << "Сумма элементов до последнего положительного элемента: " << sum << endl;
    return 0;
}