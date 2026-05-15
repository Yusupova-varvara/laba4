#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>

using namespace std;

// Проверка на простое число
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

// Вывод массива
void print(const vector<int>& v, string name) {
    cout << name << ": ";
    for (auto x : v) cout << x << " ";
    cout << endl;
}

int main() {
    // Генератор knuth_b (вариант 2)
    knuth_b gen(random_device{}());
    uniform_int_distribution<> d1(10, 30);
    uniform_int_distribution<> d2(10, 100);

    // Пункт 1: создаём массивы
    vector<int> arr1(20), arr2(8);
    for (auto& x : arr1) x = d1(gen);
    for (auto& x : arr2) x = d1(gen);

    print(arr1, "arr1");
    print(arr2, "arr2");

    // Пункт 2: чётные на нечётных индексах
    vector<int> even;
    for (int i = 1; i < arr1.size(); i += 2)
        if (arr1[i] % 2 == 0) even.push_back(arr1[i]);
    
    cout << "Количество четных элементов на нечетных индексах: " << even.size() << endl;
    cout << "Значения: ";
    for (auto x : even) cout << x << " ";
    cout << endl;

    // Пункт 3: какие числа из arr2 есть в arr1
    map<int, int> count;
    for (int x : arr1) count[x]++;
    
    bool found = false;
    cout << "Числа из arr2, встречающиеся в arr1:" << endl;
    for (int x : arr2) {
        if (count[x] > 0) {
            cout << "  " << x << " встречается " << count[x] << " раз(а)" << endl;
            found = true;
        }
    }
    if (!found) cout << "  Ни одно число не встречается" << endl;

    // Пункт 4: циклический сдвиг влево
    vector<int> shifted = arr1;
    if (!shifted.empty()) {
        int first = shifted[0];
        for (int i = 0; i < shifted.size() - 1; i++)
            shifted[i] = shifted[i + 1];
        shifted.back() = first;
    }
    print(arr1, "Исходный arr1");
    print(shifted, "После сдвига влево на 1");

    // Пункт 5: простые числа
    vector<int> arr5(20);
    for (auto& x : arr5) x = d2(gen);
    print(arr5, "Исходный массив");

    vector<int> primes;
    for (int x : arr5)
        if (isPrime(x)) primes.push_back(x);
    
    sort(primes.begin(), primes.end(), greater<int>());

    vector<int> modified = arr5;
    for (int& x : modified)
        if (!isPrime(x)) x = 0;

    cout << "Простые числа (отсортированы по убыванию): ";
    for (auto x : primes) cout << x << " ";
    cout << endl;
    
    cout << "Модифицированный массив (составные заменены на 0): ";
    for (auto x : modified) cout << x << " ";
    cout << endl;

    int sum1 = 0, sum2 = 0;
    for (auto x : primes) sum1 += x;
    for (auto x : modified) sum2 += x;
    
    cout << "Сумма простых чисел: " << sum1 << endl;
    cout << "Сумма элементов модифицированного массива: " << sum2 << endl;

    return 0;
}
