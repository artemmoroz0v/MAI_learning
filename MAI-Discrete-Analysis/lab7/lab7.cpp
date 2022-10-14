#include <iostream>
#include <vector>
#include <string>
int main() {
    long long n;
    std:: cin >> n;
    long long m;
    std:: cin >> m;
    long long lower_bound = 1; //нижняя граница - начало в 10^0
    long long upper_bound = 0;
    long long result = 0;
    std:: string number = std:: to_string(n);
    long long length = number.size();
    for (long long i = 0; i < length; ++i) {
        upper_bound = upper_bound * 10 + (long long)number[i] - (long long)'0'; //верхняя граница - число, состоящее из i+1 символа исходного числа
        long long left = lower_bound + (m - lower_bound % m) % m; //минимальное число, не меньшее d=10^i, кратное m.
        long long right = upper_bound - upper_bound % m; //максимальное число, не большее upper_bound, кратное m.
        if (left <= right) {
            result += (right - left) / m + 1;
        }
        lower_bound *= 10; //умножаем на 10
    }
    if (!(n % m)) {
        --result; //декрементируем результат, если n так же делится на m без остатка
    }
    std:: cout << result << "\n";
    return 0;
}
