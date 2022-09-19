#include <iostream>
#include <fstream>
#include <random>
int main () {
    unsigned long long string_amount;
    std:: cin >> string_amount;
    std:: string path_name;
    std:: cin >> path_name;
    std:: ofstream file(path_name);
    std:: vector<std:: string> keys;
    std:: vector<unsigned long long> values;
    file << string_amount << "\n";
    for (unsigned long long i = 0; i < string_amount; ++i) {
        unsigned short size = std:: rand() % 256 + 1;
        std:: string file_string(size, 0);
        for (unsigned short i = 0; i < size; ++i) {
            file_string[i] = char(rand() % 26 + int('a'));
        }
        unsigned long long value = rand();
        keys.push_back(file_string);
        values.push_back(value);
    }
    for (unsigned long long i = 0; i < string_amount; ++i) {
        file << keys[i] << ' ' << values[i] << "\n";
    }
    for (unsigned long long i = 0; i < string_amount; ++i) {
        file << keys[i] << "\n";
    }
    for (unsigned long long i = 0; i < string_amount; ++i) {
        file << keys[i] << "\n";
    }
    file.close();
    return 0;
}