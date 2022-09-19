#include <iostream>
#include <map>
#include <chrono>
#include <fstream>
int main () {
    std:: ofstream file("MAP_RESULTS.txt");
    unsigned long long string_amount;
    std:: cin >> string_amount;
    std:: map<std:: string, unsigned long long> map;
    std:: chrono:: high_resolution_clock:: time_point InsertBegin = std:: chrono:: high_resolution_clock:: now();
    for (unsigned long long i = 0; i < string_amount; ++i) {
        std:: string key;
        unsigned long long value;
        std:: cin >> key >> value;
        std:: map<std:: string, unsigned long long>:: iterator iterator;
        iterator = map.find(key);
        if (iterator == map.end()) {
            map[key] = value;
            std:: cout << "OK" << "\n";
        } 
        else {
            std:: cout << "Exist" << "\n";
        }
    }
    std:: chrono:: high_resolution_clock:: time_point InsertEnd = std:: chrono:: high_resolution_clock:: now();
    std:: chrono:: high_resolution_clock:: time_point SearchBegin = std:: chrono:: high_resolution_clock:: now();
    for (unsigned long long i = 0; i < string_amount; ++i) {
        std:: string key;
        std:: cin >> key;
        std:: map<std:: string, unsigned long long>:: iterator iterator;
        iterator = map.find(key);
        if (iterator != map.end()) {
            std:: cout << "OK: " << map[key] << "\n";
        } 
        else {
            std:: cout << "NoSuchWord" << "\n";
        }
    }
    std:: chrono:: high_resolution_clock:: time_point SearchEnd = std:: chrono:: high_resolution_clock:: now();
    std:: chrono:: high_resolution_clock:: time_point EraseBegin = std:: chrono:: high_resolution_clock:: now();
    for (unsigned long long i = 0; i < string_amount; ++i) {
        std:: string key;
        std:: cin >> key;
        std:: map<std:: string, unsigned long long>:: iterator iterator;
        iterator = map.find(key);
        if (iterator != map.end()) {
            map.erase(key);
            std:: cout << "OK " << "\n";
        }
        else {
            std:: cout << "NoSuchWord" << "\n";
        }
    }
    std:: chrono:: high_resolution_clock:: time_point EraseEnd = std:: chrono:: high_resolution_clock:: now();
    unsigned long long InsertionTime = std:: chrono:: duration_cast<std:: chrono:: milliseconds>(InsertEnd - InsertBegin).count();
    unsigned long long SearchingTime = std:: chrono:: duration_cast<std:: chrono:: milliseconds>(SearchEnd - SearchBegin).count();
    unsigned long long ErasingTime = std:: chrono:: duration_cast<std:: chrono:: milliseconds>(EraseEnd - EraseBegin).count();
    file << "Insertion time in map: " << InsertionTime << " ms" << "\n";
    file << "Searching time in map: " << SearchingTime << " ms" << "\n";
    file << "Erasing time in map: " << ErasingTime << " ms" << "\n";
    return 0;
}