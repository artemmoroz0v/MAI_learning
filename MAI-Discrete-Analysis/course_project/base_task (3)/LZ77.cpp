#include <iostream>
#include <vector>
const char END_OF_FILE = ' ';

//<offset, size, next> - code
struct Node {
    int offset;
    int size;
    char next;
    Node (int offset, int size, char next) {
        this->offset = offset;
        this->size = size;
        this->next = next;
    }
};

void Encode (std:: string& text, std:: vector<Node*>& encoded) {
    int global_position = 0;
    while (global_position < text.size()) {
        Node* result = new Node(0, 0, text[global_position]);
        for (int i = 0; i < global_position; ++i) {
            int local_position = global_position;
            int local_size = 0;
            for (int j = i; text[local_position] == text[j] && local_position < text.size(); ++j) { //смещаемся по тексту и ищем самый большой size
                ++local_size;
                ++local_position;
            }
            if (local_size >= result->size && local_size != 0) {
                result->size = local_size;
                result->offset = global_position - i;
                if (local_position >= text.size()) { //если превысили или на конце текста
                    result->next = END_OF_FILE;
                }
                else {
                    result->next = text[local_position]; //кладем следующий символ, если все ок
                }
            }
        }
        encoded.emplace_back(result);
        global_position += result->size + 1; // смещаем наш итератор на следующую ячейку после последнего обработанного символа
    }
}

void Decode (std:: string& text, std:: vector<Node*>& code) {
    int global_position = 0;
    for (int i = 0; i < code.size(); ++i) {
        if (code[i]->size > 0) { //если есть что брать
            global_position = text.size() - code[i]->offset; //смещаемся на длину строки - смещение
            for (int j = 0; j < code[i]->size; ++j) {
                text.push_back(text[global_position + j]); //прибавляем в текст пока j < размера того, что берем
            }
        }
        if (code[i]->next == END_OF_FILE) { //если пустой, выходим
            break;
        }
        else {
            text.push_back(code[i]->next); //добавляем следующий символ в текст, если не пустой символ
        }
    }
}

int main() {
    std:: ios:: sync_with_stdio(false);
    std:: cin.tie(0);
    std:: cout.tie(0);
    std:: string operation;
    std:: string text;
    std:: vector<Node*> encoded;
    std:: vector<Node*> code;
    std:: cin >> operation;
    if (operation == "compress") {
        std:: cin >> text;
        Encode(text, encoded);
        for (int i = 0; i < encoded.size(); ++i) {
            std:: cout << encoded[i]->offset << " " << encoded[i]->size << " " << encoded[i]->next << "\n";
        }
    }
    else if (operation == "decompress") {
        int offset, size;
        char next = END_OF_FILE;
        while (std:: cin >> offset >> size) {
            std:: cin >> next;
            Node* inputed = new Node(offset, size, next);
            code.emplace_back(inputed);
        }
        if (code[code.size() - 1]->next == code[code.size() - 2]->next) {
            code[code.size() - 1]->next = END_OF_FILE;
        }
        Decode(text, code);
        std:: cout << text << "\n";
    }
    for (int i = 0; i < code.size(); ++i) {
        delete code[i];
    }
    for (int i = 0; i < encoded.size(); ++i) {
        delete encoded[i];
    }
    return 0;
}