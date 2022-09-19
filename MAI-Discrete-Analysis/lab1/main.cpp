#include <iostream>
#include <vector>

const short int AMOUNT_OF_DIGITS = 10;
const short int AMOUNT_OF_LETTERS = 26;
const short int AMOUNT_OF_RANKS = 7;

struct Map {
    std:: string key;
    unsigned long long value;
};

void RadixSort (std:: vector<Map*>& inputed) {
    int chars[AMOUNT_OF_LETTERS] = {};
    std:: vector<Map*> sorted(inputed.size());
    for (short int i = AMOUNT_OF_RANKS; i >= 0; --i) {
        if (inputed[0]->key[i] == ' ') {
            continue;
        }
        else if (inputed[0]->key[i] >= '0' && inputed[0]->key[i] <= '9') {
            for (int x = 0; x < inputed.size(); ++x) {
                ++chars[inputed[x]->key[i] - '0'];
            }
            for (short int t = 1; t < AMOUNT_OF_DIGITS; ++t) {
                chars[t] += chars[t - 1];
            }
            for (int x = inputed.size(); x != 0; --x) {
                --chars[inputed[x - 1]->key[i] - '0'];
                sorted[chars[inputed[x - 1]->key[i] - '0']] = inputed[x - 1];
            }
        }
        else {
            for (int x = 0; x < inputed.size(); ++x) {
                ++chars[inputed[x]->key[i] - 'A'];
            }
            for (short int t = 1; t < AMOUNT_OF_LETTERS; ++t) {
                chars[t] += chars[t - 1];
            }
            for (int x = inputed.size(); x != 0; --x) {
                --chars[inputed[x - 1]->key[i] - 'A'];
                sorted[chars[inputed[x - 1]->key[i] - 'A']] = inputed[x - 1];
            }
        }
        for (short int p = 0; p < AMOUNT_OF_LETTERS; ++p) {
            chars[p] = 0;
        }
        std:: swap(inputed, sorted);
    }
}

int main () {
    std:: ios:: sync_with_stdio(false);
    std:: cin.tie(0);
    std:: cout.tie(0);
    std:: vector<Map*> inputed;
    std:: string first_string, second_string, third_string;
    unsigned long long value;
    while (std:: cin >> first_string >> second_string >> third_string >> value) {
        Map* data = new Map();
        data->key = first_string + " " + second_string + " " + third_string;
        data->value = value;
        inputed.push_back(data);
    }
    if (inputed.size() != 0) {
        RadixSort(inputed);
    }
    for (int i = 0; i < inputed.size(); ++i) {
        std:: cout << inputed[i]->key << "\t" << inputed[i]->value << "\n";
    }
    for (int i = 0; i < inputed.size(); ++i) {
        delete inputed[i];
    }
    return 0;
}