#include <iostream>
#include <vector>
#include <algorithm>
const int DEFAULT_MINIMAL_PRICE = 100;
const int DEFAULT_VALUE = -1;
std:: vector<int> Find(int& N, int& M, std:: vector<std:: vector<double>>& input) {
    std:: vector<int> answer;
    for (int i = 0; i < N; ++i) {
        int minimal_price = DEFAULT_MINIMAL_PRICE; //недостижимая цена
        int row = DEFAULT_VALUE; //строка с минимальной стоимостью
        int input_line_number = DEFAULT_VALUE; //номер считанной строки
        int price = N;
        for (int j = i; j < M; ++j) {
            if (input[j][i] != 0 && input[j][price] < minimal_price) {
                minimal_price = input[j][price];
                row = j;
            }
        }
        if (row == -1) return std:: vector<int>();
        input_line_number = input[row][price + 1];
        answer.push_back(input_line_number);
        input[i].swap(input[row]);
        for (int k = i + 1; k < M; ++k) {
            double m = input[k][i] / input[i][i];
            for (int v = i; v < N; ++v) {
                input[k][v] -= input[i][v] * m;
            }
        }
    }
    return answer;
}
int main() {
    int M, N;
    std:: cin >> M >> N;
    std:: vector<std:: vector<double>> input(M, std:: vector<double>(N + 2)); //M строк, N + 2 - считываем также цену добавки и записываем номер считанной строки в 1-индексации
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N + 1; ++j) {
            std:: cin >> input[i][j];
        }
        input[i][N + 1] = i + 1; //номер считанной строки
    }
    std:: vector<int> result = Find(N, M, input);
    if (result.size() == 0) {
        std:: cout << -1 << "\n";
        return 0;
    }
    std:: sort(result.begin(), result.end());
    for (int i = 0; i < result.size(); ++i) {
        std:: cout << result[i] << " ";
    }
    return 0;
}
